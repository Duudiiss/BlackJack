#ifndef PARTIDA_H
#define PARTIDA_H

#include "Baralho.h"
#include "Jogador.h"
#include "Fichas.h"
#include "Regras.h"

typedef struct Partida Partida;

/* Cria uma partida com um jogador humano, saldo inicial em fichas */
Partida* PartidaCria(int saldo_inicial);

/* Destroi tudo associado à partida */
int PartidaDestroi(Partida* p);

/* Executa o loop principal do jogo (várias rodadas) */
int PartidaExecuta(Partida* p);

#endif
