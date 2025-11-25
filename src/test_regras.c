#include <stdio.h>
#include <stdlib.h>

#include "Regras.h"
#include "Jogador.h"
#include "Baralho.h"
#include "Fichas.h"

void printResultado(const char *msg) {
    printf("\n==============================\n");
    printf("%s\n", msg);
    printf("==============================\n\n");
}

int main() {
    /* ---- Preparação ---- */
    Baralho *b = CriaBaralho();
    Embaralha(b);

    Jogador *jogador = CriaJogador("Alice");
    Jogador *dealer  = CriaJogador("Dealer");

    jogador->carteira = InitWallet(1000);
    dealer->carteira  = InitWallet(1000);

    float aposta = 100;

    printf("Saldo inicial jogador: %.2f\n", GetBalance(jogador));

    /* ---- JOGADOR recebe 2 cartas ---- */
    JogadorRecebeCarta(jogador, PegaCarta(b));
    JogadorRecebeCarta(jogador, PegaCarta(b));

    /* ---- DEALER recebe 2 cartas ---- */
    JogadorRecebeCarta(dealer, PegaCarta(b));
    JogadorRecebeCarta(dealer, PegaCarta(b));

    printf("\n--- Mão inicial ---\n");
    JogadorExibeMao(jogador);
    JogadorExibeMao(dealer);

    printf("\nValor jogador: %d\n", ValorDaMao(jogador));
    printf("Valor dealer : %d\n", ValorDaMao(dealer));

    /* ---- Teste: Blackjack natural ---- */
    if (TemBlackjack(jogador))
        printResultado("Jogador tem BLACKJACK!");

    if (TemBlackjack(dealer))
        printResultado("Dealer tem BLACKJACK!");

    /* ---- Teste: Resolução da rodada ---- */
    ResolverRodada(jogador, dealer, aposta);

    printf("\nSaldo FINAL do jogador: %.2f\n", GetBalance(jogador));
    printf("Saldo FINAL do dealer : %.2f\n", GetBalance(dealer));

    /* ---- Limpeza ---- */
    JogadorLimpaMao(jogador);
    JogadorLimpaMao(dealer);
    ExcluiCarteira(jogador);
    ExcluiCarteira(dealer);
    DestroiJogador(jogador);
    DestroiJogador(dealer);

    DestroiBaralho(b);

    return 0;
}
