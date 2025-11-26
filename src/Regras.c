#include <stdio.h>
#include "Regras.h"

static int calcula_valor_interno(Jogador* jogador)
{
    if (!jogador) return 0;

    int qtd = GetJogadorQuantidadeCartas(jogador);
    int soma = 0;
    int ases = 0;

    for (int i = 0; i < qtd; i++) {
        Carta* c = GetJogadorCarta(jogador, i);
        if (!c) continue;

        int numero = CartaGetNumero(c);
        int valor = CartaGetValor(c);

        soma += valor;
        if (numero == 1) {
            ases++;
        }
    }

    /* Ajustar Áses de 11 para 1 se estourar */
    while (soma > 21 && ases > 0) {
        soma -= 10; // 11 -> 1
        ases--;
    }

    return soma;
}

int RegrasCalculaValorMao(Jogador* jogador)
{
    return calcula_valor_interno(jogador);
}

int RegrasEhBlackjack(Jogador* jogador)
{
    if (!jogador) return 0;

    int qtd = GetJogadorQuantidadeCartas(jogador);
    if (qtd != 2) return 0;

    int valor = calcula_valor_interno(jogador);
    return (valor == 21);
}

int RegrasEstourou(Jogador* jogador)
{
    if (!jogador) return 0;
    int valor = calcula_valor_interno(jogador);
    return (valor > 21);
}

int RegrasDealerDevePuxar(Jogador* dealer)
{
    if (!dealer) return 0;
    int valor = calcula_valor_interno(dealer);
    return (valor < 17);
}

ResultadoMao RegrasComparaMaos(Jogador* jogador, Jogador* dealer)
{
    int valorJ = calcula_valor_interno(jogador);
    int valorD = calcula_valor_interno(dealer);

    int estourouJ = (valorJ > 21);
    int estourouD = (valorD > 21);

    if (estourouJ && !estourouD)
        return RESULTADO_JOGADOR_PERDEU;
    if (!estourouJ && estourouD)
        return RESULTADO_JOGADOR_GANHOU;
    if (estourouJ && estourouD)
        return RESULTADO_EMPATE;

    if (valorJ > valorD)
        return RESULTADO_JOGADOR_GANHOU;
    if (valorJ < valorD)
        return RESULTADO_JOGADOR_PERDEU;

    return RESULTADO_EMPATE;
}
