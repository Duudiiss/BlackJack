#ifndef REGRAS_H
#define REGRAS_H

#include "Jogador.h"

/* ============================================
   Funções principais de lógica do Blackjack
   ============================================ */

/* Retorna o valor da mão (A vale 1 ou 11). */
int ValorDaMao(Jogador *j);

/* Retorna 1 se a mão passou de 21, caso contrário 0. */
int Estourou(Jogador *j);

/* Retorna 1 se tem blackjack natural (A + carta de valor 10). */
int TemBlackjack(Jogador *j);

/* Pagamentos e resultados */
void AplicarVitoria(Jogador *jogador, float aposta);
void AplicarDerrota(Jogador *jogador, float aposta);
void AplicarEmpate(Jogador *jogador, float aposta);
void AplicarBlackjack(Jogador *jogador, float aposta);

/*
 * Resolve o vencedor da rodada:
 * - jogador: jogador comum
 * - dealer: jogador representando o dealer
 * - aposta: aposta já debitada da carteira
 */
void ResolverRodada(Jogador *jogador, Jogador *dealer, float aposta);

#endif
