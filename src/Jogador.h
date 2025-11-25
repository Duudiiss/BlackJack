#include "Baralho.h"

#ifndef JOGADOR_H
#define JOGADOR_H

#define MAX_MAO_CARTAS 12

typedef struct Jogador Jogador;

Jogador* CriaJogador(const char* nome);
int DestroiJogador(Jogador* jogador);
int JogadorExecutaHit(Jogador* jogador);
int JogadorExecutaStand(Jogador* jogador);
int JogadorExecutaDouble(Jogador* jogador);
int JogadorPedeAposta(Jogador* jogador);
int JogadorQuerJogarNovamente(Jogador* jogador);
void JogadorExibeMao(Jogador* jogador);
void JogadorExibeMensagem(Jogador* jogador, char* mensagem);

//SETTERS
int JogadorRecebeCarta(Jogador* jogador, Carta* carta);
int JogadorLimpaMao(Jogador* jogador);

//GETTERS
Carta* GetJogadorCarta(Jogador* jogador, int indice);
int GetJogadorQuantidadeCartas(Jogador* jogador);
#endif
