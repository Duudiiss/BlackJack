#include "Baralho.h"

#ifndef JOGADOR_H
#define JOGADOR_H

#define MAX_CARTAS 12

struct Jogador
{
    Carta* cartas[MAX_CARTAS];
    char nome[50];
};
typedef struct Jogador Jogador;

Jogador* CriaJogador(const char* nome);
int DestroiJogador(Jogador* jogador);
int SetJogadorCarta();
int JogadorLimpaMao(Jogador* jogador);
Carta* GetJogadorCarta(Jogador* jogador, int indice);
int GetJogadorQuantidadeCartas(Jogador* jogador);
int JogadorExecutaHit(Jogador* jogador, Baralho* baralho);
int JogadorExecutaStand(Jogador* jogador);
int JogadorExecutaDouble(Jogador* jogador, Baralho* baralho);
int JogadorPedeAposta(Jogador* jogador);
int JogadorQuerJogarNovamente(Jogador* jogador);
void JogadorExibeMao(Jogador* jogador);
void JogadorExibeMensagem(Jogador* jogador, char* mensagem);

#endif