#ifndef REGRAS_H
#define REGRAS_H

#include "jogador.h"
#include "carteira.h"

/* ======================================
   Funções de cálculo e estado da mão
   ====================================== */

// Retorna o valor total da mão do jogador (contando Ás como 1 ou 11)
int ValorDaMao(Jogador *j);

// Retorna 1 se o jogador estourou (valor > 21)
int Estourou(Jogador *j);

// Retorna 1 se a mão tem blackjack natural (Ás + 10)
int TemBlackjack(Jogador *j);


/* ======================================
   Pagamentos do resultado
   ====================================== */

void AplicarVitoria(Jogador *jogador, float aposta);
void AplicarDerrota(Jogador *jogador, float aposta);
void AplicarEmpate(Jogador *jogador, float aposta);
void AplicarBlackjack(Jogador *jogador, float aposta);


/* ======================================
   Resolução de uma rodada completa
   ====================================== */

// Compara mãos e aplica vitória/derrota/empate
void ResolverRodada(Jogador *jogador, Jogador *dealer, float aposta);

#endif
