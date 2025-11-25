/*
 * Regras.c
 *
 * Implementação das regras de avaliação de mãos e pagamentos para Blackjack.
 * Usa apenas a API pública presente nos headers:
 *  - Jogador.h  (GetJogadorQuantidadeCartas, GetJogadorCarta, CriaJogador, DestroiJogador, ...)
 *  - Fichas.h   (InitWallet, GetBalance, somaCarteira, descontaCarteira, ExcluiCarteira)
 *  - Baralho.h  (CartaGetNumero, CartaGetValor, etc.)
 *
 * NOTA: Regras.h deverá declarar os protótipos correspondentes. Eu gerei as funções
 * mais importantes aqui: ValorDaMao, Estourou, TemBlackjack, AplicarVitoria/Derrota/Empate/Blackjack
 * e ResolverRodada.
 */

#include <stdio.h>
#include "Jogador.h"
#include "fichas.h"
#include "Baralho.h"

/* -------------------------
   Cálculo do valor da mão
   Ás vale 1 ou 11 conforme melhor resultado <= 21
   ------------------------- */
int ValorDaMao(Jogador *j) {
    if (!j) return -1;

    int soma = 0;
    int ases = 0;
    int ncartas = GetJogadorQuantidadeCartas(j);
    for (int i = 0; i < ncartas; i++) {
        const Carta *c = GetJogadorCarta(j, i);
        if (!c) continue;
        int numero = CartaGetNumero(c);

        if (numero == 1) {        // Ás
            ases++;
            soma += 1;            // conta como 1 inicialmente
        } else if (numero > 10) { // J,Q,K
            soma += 10;
        } else {                  // 2..10
            soma += numero;
        }
    }

    /* transformar alguns Ases de 1 -> 11 enquanto possível */
    while (ases > 0 && soma + 10 <= 21) {
        soma += 10;
        ases--;
    }

    return soma;
}

/* -------------------------
   Verificadores simples
   ------------------------- */
int Estourou(Jogador *j) {
    int v = ValorDaMao(j);
    if (v < 0) return 0;
    return v > 21;
}

int TemBlackjack(Jogador *j) {
    if (!j) return 0;
    int n = GetJogadorQuantidadeCartas(j);
    if (n != 2) return 0;
    return ValorDaMao(j) == 21;
}

/* -------------------------
   Pagamentos e efeitos na carteira
   Observação de design:
   - Assumimos que a aposta já foi removida do saldo no momento da aposta.
   - As funções abaixo apenas creditam (somaCarteira) ou reembolsam (Empate).
   ------------------------- */

void AplicarVitoria(Jogador *jogador, float aposta) {
    if (!jogador) return;
    /* paga o valor da aposta como ganho (ex: aposta 20 -> +20) */
    printf("AplicarVitoria: adicionando %.2f ao saldo do jogador\n", aposta);
    somaCarteira(jogador, aposta);
}

void AplicarDerrota(Jogador *jogador, float aposta) {
    (void)aposta; /* aposta já removida previamente; nada a creditar */
    if (!jogador) return;
    printf("AplicarDerrota: aposta perdida.\n");
}

void AplicarEmpate(Jogador *jogador, float aposta) {
    if (!jogador) return;
    printf("AplicarEmpate: devolvendo aposta %.2f ao jogador\n", aposta);
    somaCarteira(jogador, aposta);
}

void AplicarBlackjack(Jogador *jogador, float aposta) {
    if (!jogador) return;
    /* paga 3:2 -> ganho de 1.5 * aposta (método: devolver aposta + lucro de 0.5*aposta) */
    float ganho = aposta * 1.5f;
    printf("AplicarBlackjack: pagando blackjack %.2f ao jogador\n", ganho);
    somaCarteira(jogador, ganho);
}

/* -------------------------
   Resolver resultado entre jogador e dealer
   - jogador: jogador
   - dealer: jogador que representa o dealer (mesmo tipo)
   - aposta: valor original da aposta (pressuposta já removida do saldo)
   ------------------------- */
void ResolverRodada(Jogador *jogador, Jogador *dealer, float aposta) {
    if (!jogador || !dealer) return;

    int vJ = ValorDaMao(jogador);
    int vD = ValorDaMao(dealer);

    printf("--- ResolverRodada ---\n");
    printf("Jogador: %d | Dealer: %d\n", vJ, vD);

    /* Jogador estourou */
    if (vJ > 21) {
        AplicarDerrota(jogador, aposta);
        return;
    }

    /* Dealer estourou */
    if (vD > 21) {
        AplicarVitoria(jogador, aposta);
        return;
    }

    /* Blackjack natural */
    if (TemBlackjack(jogador) && !TemBlackjack(dealer)) {
        AplicarBlackjack(jogador, aposta);
        return;
    }

    /* Dealer tem blackjack e jogador não -> derrota */
    if (!TemBlackjack(jogador) && TemBlackjack(dealer)) {
        AplicarDerrota(jogador, aposta);
        return;
    }

    /* Comparação simples */
    if (vJ > vD) {
        AplicarVitoria(jogador, aposta);
    } else if (vJ < vD) {
        AplicarDerrota(jogador, aposta);
    } else {
        AplicarEmpate(jogador, aposta);
    }
}
