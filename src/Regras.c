#include <stdio.h>
#include "Regras.h"
#include "carteira.h"
#include "jogador.h"

/* ============================================================
   Cálculo do valor da mão (Blackjack)
   Ás vale 1 ou 11, dependendo do melhor caso não estourar 21.
   ============================================================ */
int ValorDaMao(Jogador *j) {
    if (j == NULL) return -1;

    int soma = 0;
    int ases = 0;

    for (int i = 0; i < MAX_MAO_CARTAS; i++) {
        if (j->cartas[i] == NULL) 
            continue;

        int n = CartaGetNumero(j->cartas[i]);

        if (n >= 2 && n <= 10) {
            soma += n;
        } 
        else if (n > 10) {  
            soma += 10;      // J, Q, K
        } 
        else if (n == 1) {   // Ás
            ases++;
            soma += 1;       // conta inicialmente como 1
        }
    }

    // Ajusta ASES para valerem 11 quando possível
    while (ases > 0 && soma + 10 <= 21) {
        soma += 10;
        ases--;
    }

    return soma;
}

/* ============================================================
   Verifica condições
   ============================================================ */

int Estourou(Jogador *j) {
    return ValorDaMao(j) > 21;
}

int TemBlackjack(Jogador *j) {
    return (GetJogadorQuantidadeCartas(j) == 2 && ValorDaMao(j) == 21);
}

/* ============================================================
   Pagamento do resultado
   ============================================================ */

void AplicarVitoria(Jogador *jogador, float aposta) {
    printf("%s venceu! +%.2f fichas\n", jogador->nome, aposta);
    somaCarteira(jogador, aposta);
}

void AplicarDerrota(Jogador *jogador, float aposta) {
    printf("%s perdeu %.2f fichas.\n", jogador->nome, aposta);
    // nada a fazer, já foram descontadas no momento da aposta
}

void AplicarEmpate(Jogador *jogador, float aposta) {
    printf("%s empatou. A aposta %.2f foi devolvida.\n", jogador->nome, aposta);
    somaCarteira(jogador, aposta);
}

void AplicarBlackjack(Jogador *jogador, float aposta) {
    float ganho = aposta * 1.5f; // 3:2
    printf("%s fez BLACKJACK! Ganhou %.2f\n", jogador->nome, ganho);
    somaCarteira(jogador, ganho);
}

/* ============================================================
   Resolve o resultado entre jogador e dealer
   ============================================================ */

void ResolverRodada(Jogador *jogador, Jogador *dealer, float aposta) {
    int vJ = ValorDaMao(jogador);
    int vD = ValorDaMao(dealer);

    printf("\n--- Resultado da Rodada ---\n");
    printf("Jogador: %d | Dealer: %d\n", vJ, vD);

    // Jogador estourou
    if (vJ > 21) {
        AplicarDerrota(jogador, aposta);
        return;
    }

    // Dealer estourou
    if (vD > 21) {
        AplicarVitoria(jogador, aposta * 2);
        return;
    }

    // Blackjack natural
    if (TemBlackjack(jogador) && !TemBlackjack(dealer)) {
        AplicarBlackjack(jogador, aposta);
        return;
    }

    // Dealer tem blackjack e jogador não → derrota
    if (!TemBlackjack(jogador) && TemBlackjack(dealer)) {
        AplicarDerrota(jogador, aposta);
        return;
    }

    // Comparação normal
    if (vJ > vD) {
        AplicarVitoria(jogador, aposta * 2);
    }
    else if (vJ < vD) {
        AplicarDerrota(jogador, aposta);
    }
    else {
        AplicarEmpate(jogador, aposta);
    }
}
