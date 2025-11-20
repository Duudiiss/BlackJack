#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Jogador.h"
#include "Baralho.h"

Jogador* CriaJogador(const char* nome)
{
    Jogador* novo_jogador = (Jogador*)malloc(sizeof(Jogador));
    
    if (novo_jogador == NULL) {
        printf("Erro de alocação de memória!\n");
        return NULL;
    }
    
    strncpy(novo_jogador->nome, nome, sizeof(novo_jogador->nome) - 1);
    novo_jogador->nome[sizeof(novo_jogador->nome) - 1] = '\0';
    
    for (int i = 0; i < MAX_CARTAS; i++) {
        novo_jogador->cartas[i] = NULL;
    }
    
    return novo_jogador;
}

int DestroiJogador(Jogador* jogador)
{
     if (jogador != NULL) {
        // Libera as cartas individualmente se necessário
        for (int i = 0; i < MAX_CARTAS; i++) {
            if (jogador->cartas[i] != NULL) {
                free(jogador->cartas[i]);
            }
        }
        free(jogador);
    }
}

int SetJogadorCarta(Jogador* jogador, Baralho* baralho)
{
    for(int i = 0; i < MAX_CARTAS; i++)
    {
        if(jogador->cartas[i] == NULL)
        {
            jogador->cartas[i] = PegaCarta(baralho);
            return 0;
        }
    }
    return 1;
}

int JogadorLimpaMao(Jogador* jogador)
{

}

Carta* GetJogadorCarta(Jogador* jogador, int indice);
int GetJogadorQuantidadeCartas(Jogador* jogador);
int JogadorExecutaHit(Jogador* jogador, Baralho* baralho);
int JogadorExecutaStand(Jogador* jogador);
int JogadorExecutaDouble(Jogador* jogador, Baralho* baralho);
int JogadorPedeAposta(Jogador* jogador);
int JogadorQuerJogarNovamente(Jogador* jogador);
void JogadorExibeMao(Jogador* jogador);
void JogadorExibeMensagem(Jogador* jogador, char* mensagem);
