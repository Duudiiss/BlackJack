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
        const Carta *c = JogadorGetCarta(j, i);
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
   NOVAS FUNÇÕES DE PAGAMENTO
   Agora recebem Carteira* diretamente em vez de Jogador*
   ------------------------- */

void AplicarVitoria(Jogador *jogador, float aposta) {
    if (!jogador) return;
    printf("AplicarVitoria: adicionando %.2f ao saldo\n", aposta);
    somaCarteira(jogador, aposta);
}

void AplicarDerrota(Jogador *jogador, float aposta) {
    (void)jogador; // aposta já foi removida anteriormente no descontaCarteira
    (void)aposta;
    printf("AplicarDerrota: aposta perdida.\n");
}

void AplicarEmpate(Jogador *jogador, float aposta) {
    if (!jogador) return;
    printf("AplicarEmpate: devolvendo aposta %.2f\n", aposta);
    somaCarteira(jogador, aposta);
}

void AplicarBlackjack(Jogador *jogador, float aposta) {
    if (!jogador) return;
    float ganho = aposta * 1.5f;
    printf("AplicarBlackjack: pagando blackjack %.2f\n", ganho);
    somaCarteira(jogador, ganho);
}

/* -------------------------
   Resolver resultado entre jogador e dealer
   AGORA recebe Carteira* em vez de Jogador*
   ------------------------- */
void ResolverRodada(Carteira* carteiraJogador, Carteira* carteiraDealer, 
                   Jogador *jogador, Jogador *dealer, float aposta) {
    if (!carteiraJogador || !jogador || !dealer) return;

    int vJ = ValorDaMao(jogador);
    int vD = ValorDaMao(dealer);

    printf("--- ResolverRodada ---\n");
    printf("Jogador: %d | Dealer: %d\n", vJ, vD);

    /* Jogador estourou */
    if (vJ > 21) {
        AplicarDerrota(carteiraJogador, aposta);
        return;
    }

    /* Dealer estourou */
    if (vD > 21) {
        AplicarVitoria(carteiraJogador, aposta);
        return;
    }

    /* Blackjack natural */
    if (TemBlackjack(jogador) && !TemBlackjack(dealer)) {
        AplicarBlackjack(carteiraJogador, aposta);
        return;
    }

    /* Dealer tem blackjack e jogador não -> derrota */
    if (!TemBlackjack(jogador) && TemBlackjack(dealer)) {
        AplicarDerrota(carteiraJogador, aposta);
        return;
    }

    /* Comparação simples */
    if (vJ > vD) {
        AplicarVitoria(carteiraJogador, aposta);
    } else if (vJ < vD) {
        AplicarDerrota(carteiraJogador, aposta);
    } else {
        AplicarEmpate(carteiraJogador, aposta);
    }
}
