#ifndef REGRAS_H
#define REGRAS_H

#include "Jogador.h"
#include "fichas.h"

/* ============================================
   Funções principais de lógica do Blackjack
   ============================================ */

int ValorDaMao(Jogador *j);
int Estourou(Jogador *j);
int TemBlackjack(Jogador *j);

/* NOVAS FUNÇÕES - recebem Carteira* em vez de Jogador* */
void AplicarVitoria(Carteira* carteira, float aposta);
void AplicarDerrota(Carteira* carteira, float aposta);
void AplicarEmpate(Carteira* carteira, float aposta);
void AplicarBlackjack(Carteira* carteira, float aposta);

/* NOVA ASSINATURA - recebe Carteira* separadamente */
void ResolverRodada(Carteira* carteiraJogador, Carteira* carteiraDealer,
                   Jogador *jogador, Jogador *dealer, float aposta);

#endif
