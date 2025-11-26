#ifndef REGRAS_H
#define REGRAS_H

#include "Jogador.h"
#include "Baralho.h"

/* Resultado de uma rodada do ponto de vista do jogador humano */
typedef enum {
    RESULTADO_JOGADOR_PERDEU = -1,
    RESULTADO_EMPATE         =  0,
    RESULTADO_JOGADOR_GANHOU =  1
} ResultadoMao;

/* Calcula o valor total da mão, tratando Áses como 11 ou 1 */
int RegrasCalculaValorMao(Jogador* jogador);

/* Retorna 1 se a mão é um Blackjack (apenas 2 cartas somando 21), senão 0 */
int RegrasEhBlackjack(Jogador* jogador);

/* Retorna 1 se estourou (valor > 21), senão 0 */
int RegrasEstourou(Jogador* jogador);

/* Dealer deve puxar outra carta? (regra típica: < 17) */
int RegrasDealerDevePuxar(Jogador* dealer);

/* Compara jogador vs dealer e devolve o resultado para o jogador */
ResultadoMao RegrasComparaMaos(Jogador* jogador, Jogador* dealer);

#endif
