#include <stdio.h>   // printf, fprintf, stderr
#include <stdlib.h>  // malloc, free
#include <stddef.h>  // NULL
#include <string.h>
#include "Baralho.h"
#include "Jogador.h"
#include "Partida.h"



int DealerLimpaMao(MaoDealer* dealer)
{
    if (!dealer) return 1;

    for (int i = 0; i < MAX_MAO_CARTAS; i++) {
        if (dealer->mao[i] != NULL) {
            free(dealer->mao[i]);
            dealer->mao[i] = NULL;
        }
    }
    return 0;
}

Partida* Partida_criar(Jogador * jogador) {
    // Criação da estrutura partida
    Partida *p = (Partida*)malloc(sizeof(Partida));
    if (p == NULL) {
        printf("Erro ao alocar memória para a partida!\n");
        return NULL;
    }

    
    p->jogador = jogador;


    // Criação do dealer
    p->dealer = (MaoDealer*)malloc(sizeof(MaoDealer));
    if (p->dealer == NULL) {
        printf("Erro ao alocar memória para o dealer!\n");
        free(p);
        return NULL;
    }
    for (int i = 0; i < MAX_MAO_CARTAS; i++) {
        p->dealer->mao[i] = NULL;
    }
    

    // Criação do baralho
    p->baralho = CriaBaralho();
    if (p->baralho == NULL) {
        printf("Erro ao criar o baralho!\n");
        free(p->jogador);
        free(p);
        return NULL;
    }

    // Embaralha o baralho
    if (Embaralha(p->baralho) != 0) {
        printf("Erro ao embaralhar o baralho!\n");
        DestroiBaralho(p->baralho);  // Libera o baralho em caso de erro
        free(p->jogador);
        free(p);
        return NULL;
    }

    // Inicializa o estado da partida
    // 0 iniciou
    // 1 em andamento
    // 2 finalizada
    p->estado = 0;
    
    return p;  // Retorna a partida com jogador e baralho prontos
}

int IniciarRodada(Partida *p, float apostaInicial){
    if(p->estado == 0){
        if(JogadorLimpaMao(p->jogador)){
            printf("Não consegui limpar a mão\n");
            return 2;
        }
        if(DealerLimpaMao(p->dealer)){
            printf("Não consegui limpar o dealer\n");
            return 2;
        }
        p->apostaAtual = apostaInicial;
        p->estado = 1;
        return 0;
    }
    return 1; // já estava em andamento ou finalizada
}

void mostraCartaPreenchida() {
    printf("\n");
    printf("  ---------\n");
    printf(" |■■■■■■■■■|\n");
    printf(" |■■■■■■■■■|\n");
    printf(" |■■■■■■■■■|\n");
    printf(" |■■■■■■■■■|\n");
    printf(" |■■■■■■■■■|\n");
    printf("  ---------\n");
}

int DistribuicaoInicial(Partida *p){
    Carta * c1 = PegaCarta(p->baralho);
    int d1 = JogadorRecebeCarta(p->jogador, c1);
    if (d1 != 0) return d1;

    Carta * c2 = PegaCarta(p->baralho);
    p->dealer->mao[0] = c2;

    Carta * c3 = PegaCarta(p->baralho);
    d1 = JogadorRecebeCarta(p->jogador, c3);
    if (d1 != 0) return d1;

    Carta * c4 = PegaCarta(p->baralho);
    p->dealer->mao[1] = c4;

    printf("                       Dealer:                  \n");
    mostraCartaPreenchida();
    mostraCarta(c2);
    printf("\n");
    printf("                       Sua mao:                  \n");
    mostraCarta(c1);
    printf("\n\n");
    mostraCarta(c3);

    return 0;
}


int ProcessarAcaoJogador(Partida *p, char* acao) {
    if (p == NULL || acao == NULL) {
        fprintf(stderr, "Erro: Partida ou ação inválida.\n");
        return -1; // erro genérico
    }

    // Ação: HIT
    if (strcmp(acao, "hit") == 0) {
        Carta *novaCarta = PegaCarta(p->baralho);
        if (novaCarta == NULL) {
            fprintf(stderr, "Erro: Não foi possível pegar carta do baralho.\n");
            return -1;
        }

        int d1 = JogadorRecebeCarta(p->jogador, novaCarta);
        switch (d1) {
            case 0: // sucesso
                return 0;
            case 1: // mão cheia
                fprintf(stderr, "Erro: Mão do jogador está cheia.\n");
                return 0; // segue jogo, mas não adicionou carta
            case 2: // carta inválida
                fprintf(stderr, "Erro: Carta inválida recebida.\n");
                return 0;
            default:
                fprintf(stderr, "Erro desconhecido ao receber carta.\n");
                return -1;
        }
    }

    // Ação: STAND
    if (strcmp(acao, "stand") == 0) {
        p->jogador->fez_stand = 1;
        return 1; // indica que jogador parou
    }

    // Ação inválida
    fprintf(stderr, "Erro: Ação '%s' não reconhecida.\n", acao);
    return -1;
}

int EncerrarPartida(Partida *p) {
    if (p == NULL) {
        fprintf(stderr, "Erro: Partida inválida.\n");
        return -1;
    }

    // Libera dealer
    if (p->dealer != NULL) {
        for (int i = 0; i < MAX_MAO_CARTAS; i++) {
            if (p->dealer->mao[i] != NULL) {
                free(p->dealer->mao[i]);
                p->dealer->mao[i] = NULL;
            }
        }
        free(p->dealer);
        p->dealer = NULL;
    }

    // Libera baralho
    if (p->baralho != NULL) {
        free(p->baralho);
        p->baralho = NULL;
    }

    // ⚠️ NÃO libera p->jogador (continua existindo fora da partida)

    // Finalmente libera a própria partida
    free(p);

    return 0; // sucesso
}