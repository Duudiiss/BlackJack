#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "Partida.h"

struct Partida {
    Baralho* baralho;
    Jogador* jogador;
    Jogador* dealer;
    Fichas* fichas;
    int rodada_ativa;
};

static void exibe_estado_parcial(Partida* p)
{
    printf("\n============================\n");
    printf("Saldo atual: %d\n", FichasGetSaldo(p->fichas));
    printf("Aposta atual: %d\n", FichasGetAposta(p->fichas));

    printf("\nMao do Jogador:\n");
    JogadorExibeMao(p->jogador);
    printf("Valor: %d\n", RegrasCalculaValorMao(p->jogador));

    printf("\nMao do Dealer (completa):\n");
    JogadorExibeMao(p->dealer);
    printf("Valor: %d\n", RegrasCalculaValorMao(p->dealer));
    printf("============================\n");
}

static void distribui_cartas_iniciais(Partida* p)
{
    /* Limpa maos anteriores */
    JogadorLimpaMao(p->jogador);
    JogadorLimpaMao(p->dealer);

    /* Distribui 2 cartas pra cada um */
    for (int i = 0; i < 2; i++) {
        Carta* c1 = PegaCarta(p->baralho);
        JogadorRecebeCarta(p->jogador, c1);

        Carta* c2 = PegaCarta(p->baralho);
        JogadorRecebeCarta(p->dealer, c2);
    }
}

Partida* PartidaCria(int saldo_inicial)
{
    Partida* p = (Partida*)malloc(sizeof(Partida));
    if (!p) return NULL;

    p->baralho = CriaBaralho();
    if (!p->baralho) {
        free(p);
        return NULL;
    }
    Embaralha(p->baralho);

    p->jogador = CriaJogador("Jogador");
    if (!p->jogador) {
        DestroiBaralho(p->baralho);
        free(p);
        return NULL;
    }

    p->dealer = CriaJogador("Dealer");
    if (!p->dealer) {
        DestroiJogador(p->jogador);
        DestroiBaralho(p->baralho);
        free(p);
        return NULL;
    }

    p->fichas = FichasCria(saldo_inicial);
    if (!p->fichas) {
        DestroiJogador(p->dealer);
        DestroiJogador(p->jogador);
        DestroiBaralho(p->baralho);
        free(p);
        return NULL;
    }

    p->rodada_ativa = 0;
    return p;
}

int PartidaDestroi(Partida* p)
{
    if (!p) return -1;

    /* Atenção: JogadorLimpaMao já dá free nas cartas se elas forem alocadas dinâmicamente */
    JogadorLimpaMao(p->jogador);
    JogadorLimpaMao(p->dealer);

    DestroiJogador(p->dealer);
    DestroiJogador(p->jogador);

    FichasDestroi(p->fichas);
    DestroiBaralho(p->baralho);

    free(p);
    return 0;
}

/* Pede uma aposta válida do jogador, respeitando o saldo e usando módulo Fichas */
static int partida_pede_aposta(Partida* p)
{
    int saldo = FichasGetSaldo(p->fichas);
    if (saldo <= 0) {
        printf("\nVocê está sem saldo para apostar. Fim de jogo.\n");
        return -1;
    }

    while (1) {
        int valor = JogadorPedeAposta(p->jogador);
        if (valor <= 0) {
            printf("Aposta invalida. Tente novamente.\n");
            continue;
        }
        if (!FichasPodeApostar(p->fichas, valor)) {
            printf("Saldo insuficiente para apostar %d. Seu saldo: %d\n", valor, saldo);
            continue;
        }
        if (FichasRealizaAposta(p->fichas, valor) == 0) {
            printf("Aposta de %d realizada.\n", valor);
            return 0;
        }
    }
}

/* Turno do jogador: hit/stand/double */
static void turno_jogador(Partida* p)
{
    while (1) {
        if (RegrasEstourou(p->jogador)) {
            printf("\nVocê estourou!\n");
            break;
        }

        printf("\nEscolha sua acao:\n");
        printf("  (h) Hit   - pedir carta\n");
        printf("  (s) Stand - parar\n");
        printf("  (d) Double - dobrar aposta (se possível e com 2 cartas)\n");
        printf("Opcao: ");

        char opc;
        if (scanf(" %c", &opc) != 1) {
            while (getchar() != '\n'); // limpa buffer
            continue;
        }
        opc = (char)tolower((unsigned char)opc);

        if (opc == 'h') {
            if (JogadorExecutaHit(p->jogador) != 0) {
                printf("Nao e possivel dar Hit agora.\n");
                continue;
            }
            Carta* c = PegaCarta(p->baralho);
            JogadorRecebeCarta(p->jogador, c);
            JogadorExibeMao(p->jogador);
            printf("Valor da mao: %d\n", RegrasCalculaValorMao(p->jogador));
        } else if (opc == 's') {
            if (JogadorExecutaStand(p->jogador) != 0) {
                printf("Voce ja estava em Stand.\n");
            }
            break;
        } else if (opc == 'd') {
            if (GetJogadorQuantidadeCartas(p->jogador) != 2) {
                printf("Double so permitido com exatamente 2 cartas.\n");
                continue;
            }
            if (JogadorExecutaDouble(p->jogador) != 0) {
                printf("Nao e possivel dar Double agora.\n");
                continue;
            }

            int aposta = FichasGetAposta(p->fichas);
            if (!FichasPodeApostar(p->fichas, aposta)) {
                printf("Saldo insuficiente para dobrar a aposta.\n");
                continue;
            }
            FichasRealizaAposta(p->fichas, aposta);

            Carta* c = PegaCarta(p->baralho);
            JogadorRecebeCarta(p->jogador, c);
            JogadorExibeMao(p->jogador);
            printf("Valor da mao apos double: %d\n", RegrasCalculaValorMao(p->jogador));

            /* Double força stand */
            break;
        } else {
            printf("Opcao invalida.\n");
        }
    }
}

/* Turno do dealer: puxa até 17+ ou estourar */
static void turno_dealer(Partida* p)
{
    printf("\nTurno do Dealer...\n");
    JogadorExibeMao(p->dealer);
    printf("Valor inicial: %d\n", RegrasCalculaValorMao(p->dealer));

    while (RegrasDealerDevePuxar(p->dealer) && !RegrasEstourou(p->dealer)) {
        printf("Dealer puxa carta...\n");
        Carta* c = PegaCarta(p->baralho);
        JogadorRecebeCarta(p->dealer, c);
        JogadorExibeMao(p->dealer);
        printf("Valor: %d\n", RegrasCalculaValorMao(p->dealer));
    }
}

/* Executa uma rodada completa (aposta, distribuicao, acoes, resultado) */
static int partida_rodada(Partida* p)
{
    /* Se baralho estiver muito baixo, reembaralha */
    if (BaralhoGetTamanho(p->baralho) < 15) {
        printf("\nReembaralhando baralho...\n");
        Embaralha(p->baralho);
    }

    if (partida_pede_aposta(p) != 0) {
        return -1;
    }

    distribui_cartas_iniciais(p);

    printf("\nCartas distribuidas!\n");
    JogadorExibeMao(p->jogador);
    printf("Valor da sua mao: %d\n", RegrasCalculaValorMao(p->jogador));

    printf("\nMao do Dealer (parcial):\n");
    JogadorExibeMao(p->dealer); // simplificado: mostra tudo

    int blackjack_jogador = RegrasEhBlackjack(p->jogador);
    int blackjack_dealer  = RegrasEhBlackjack(p->dealer);

    if (blackjack_jogador || blackjack_dealer) {
        printf("\nVerificando Blackjack...\n");
        if (blackjack_jogador && !blackjack_dealer) {
            printf("Voce tem Blackjack!\n");
            ResultadoMao res = RESULTADO_JOGADOR_GANHOU;
            FichasAplicarResultado(p->fichas, res, 1);
        } else if (!blackjack_jogador && blackjack_dealer) {
            printf("Dealer tem Blackjack. Voce perdeu.\n");
            ResultadoMao res = RESULTADO_JOGADOR_PERDEU;
            FichasAplicarResultado(p->fichas, res, 0);
        } else {
            printf("Ambos tem Blackjack. Empate.\n");
            ResultadoMao res = RESULTADO_EMPATE;
            FichasAplicarResultado(p->fichas, res, 0);
        }
        exibe_estado_parcial(p);
        return 0;
    }

    /* Turno do jogador */
    turno_jogador(p);

    if (!RegrasEstourou(p->jogador)) {
        /* Turno do dealer só se o jogador não estourou */
        turno_dealer(p);
    }

    ResultadoMao res = RegrasComparaMaos(p->jogador, p->dealer);
    int blackjack = 0; // já tratamos blackjack antes

    if (res == RESULTADO_JOGADOR_GANHOU) {
        printf("\nVoce venceu esta rodada!\n");
    } else if (res == RESULTADO_JOGADOR_PERDEU) {
        printf("\nVoce perdeu esta rodada.\n");
    } else {
        printf("\nRodada empatada.\n");
    }

    FichasAplicarResultado(p->fichas, res, blackjack);
    exibe_estado_parcial(p);

    return 0;
}

int PartidaExecuta(Partida* p)
{
    if (!p) return -1;

    while (1) {
        int saldo = FichasGetSaldo(p->fichas);
        if (saldo <= 0) {
            printf("\nSeu saldo chegou a zero. Fim do jogo.\n");
            break;
        }

        if (partida_rodada(p) != 0) {
            break;
        }

        int resp = JogadorQuerJogarNovamente(p->jogador);
        if (resp != 1) {
            printf("\nEncerrando partida.\n");
            break;
        }
    }

    return 0;
}
