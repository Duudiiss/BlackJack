#ifndef FICHAS_H
#define FICHAS_H

#include "Regras.h"  // para ResultadoMao

typedef struct Fichas Fichas;

/* Cria estrutura de fichas para um jogador com saldo inicial (em "dinheiro") */
Fichas* FichasCria(int saldo_inicial);

/* Destroi estrutura de fichas */
int FichasDestroi(Fichas* f);

/* Acessores */
int FichasGetSaldo(const Fichas* f);
int FichasGetAposta(const Fichas* f);

/* Verifica se é possível apostar esse valor (saldo suficiente) */
int FichasPodeApostar(const Fichas* f, int valor);

/* Registra uma aposta: debita do saldo e guarda em aposta_atual */
int FichasRealizaAposta(Fichas* f, int valor);

/* Zera a aposta atual (sem devolver nada) */
int FichasResetaAposta(Fichas* f);

/* Aplica o resultado da rodada ao saldo do jogador.
   - resultado: do ponto de vista do jogador.
   - blackjack: 1 se jogador ganhou com Blackjack, 0 caso contrário.
   Retorna 0 em sucesso, -1 se argumentos inválidos.
*/
int FichasAplicarResultado(Fichas* f, ResultadoMao resultado, int blackjack);

#endif
