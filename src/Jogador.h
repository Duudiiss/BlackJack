#include "Baralho.h"
#include "Fichas.h"

#ifndef JOGADOR_H
#define JOGADOR_H

#define MAX_MAO_CARTAS 12

struct Jogador
{
    Carta* cartas[MAX_MAO_CARTAS];
    Carteira * carteira;
    char nome[50];
    int fez_stand;
    int fez_double;
};
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
