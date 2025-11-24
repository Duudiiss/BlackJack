#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Jogador.h"
#include "Baralho.h"

Jogador* CriaJogador(const char* nome)
{
    if (nome == NULL || strlen(nome) == 0)
        return NULL;
    
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
    
    novo_jogador->fez_stand = 0;
    novo_jogador->fez_double = 0;
    
    return novo_jogador;
}

int DestroiJogador(Jogador* jogador)
{
     if (jogador != NULL) {
        // Libera as cartas individualmente se necessário
        for (int i = 0; i < MAX_MAO_CARTAS; i++) {
            if (jogador->cartas[i] != NULL) {
                free(jogador->cartas[i]);
            }
        }
        free(jogador);
    }
}

int GetJogadorQuantidadeCartas(Jogador* jogador)
{
    if (!jogador) return -1;

    int count = 0;
    for (int i = 0; i < MAX_CARTAS; i++)
        if (jogador->cartas[i] != NULL)
            count++;

    return count;
}

Carta* JogadorGetCarta(MaoJogador* jogador, int indice)
{
    if (!jogador) return NULL;
    if (indice < 0 || indice >= MAX_CARTAS || indice > JogadorGetQuantidadeCartas(MaoJogador* jogador)) return NULL;
    if()
    return jogador->cartas[indice];
}

int JogadorRecebeCarta(Jogador* jogador, Carta* carta)
{
    if (!jogador) return 3;
    if (!carta) return 2;
    if (jogador->fez_stand) return 1;

    int qtd = JogadorGetQuantidadeCartas(jogador);
    if (qtd >= MAX_MAO_CARTAS) return 1;

    jogador->cartas[qtd] = carta;

    return 0;
}

int JogadorLimpaMao(Jogador* jogador)
{
    if (!jogador) return 1;

    for (int i = 0; i < MAX_CARTAS; i++) {
        if (jogador->cartas[i] != NULL) {
            free(jogador->cartas[i]);
            jogador->cartas[i] = NULL;
        }
    }

    jogador->fez_stand = 0;
    jogador->fez_double = 0;

    return 0;
}

int JogadorExecutaHit(MaoJogador* jogador)
{
    if (!jogador) return 3;
    if (jogador->fez_stand) return 3;

    return 0; // success; Partida fará JogadorRecebeCarta
}

int JogadorExecutaStand(MaoJogador* jogador)
{
    if (!jogador) return 1;
    if (jogador->fez_stand) return 1;

    jogador->fez_stand = 1;
    return 0;
}

int JogadorExecutaDouble(MaoJogador* jogador)
{
    if (!jogador) return 3;

    int qtd = JogadorGetQuantidadeCartas(jogador);

    if (qtd != 2) return 3;
    if (jogador->fez_stand) return 3;
    if (jogador->fez_double) return 3;

    jogador->fez_double = 1;
    jogador->fez_stand = 1; // double força stand após uma carta

    return 0; // Partida adicionará a carta
}

int JogadorPedeAposta(MaoJogador* jogador)
{
    if (!jogador) return -1;

    int valor;
    printf("Digite o valor da aposta: ");
    if (scanf("%d", &valor) != 1)
        return -1;

    return valor > 0 ? valor : -1;
}

void JogadorExibeMao(MaoJogador* jogador)
{
    if (!jogador) return;

    printf("\nMão de %s:\n", jogador->nome);

    int qtd = JogadorGetQuantidadeCartas(jogador);

    for (int i = 0; i < qtd; i++) {
        Carta* c = jogador->cartas[i];
        if (c != NULL)
            printf("  [%d %c]\n", c->Numero, c->Naipe);
    }
}

void JogadorExibeMensagem(MaoJogador* jogador, char* mensagem)
{
    if (!jogador || !mensagem) return;
    printf("[%s] %s\n", jogador->nome, mensagem);
}

int JogadorQuerJogarNovamente(MaoJogador* jogador)
{
    if (!jogador) return -1;

    char opc;
    printf("\nJogar novamente? (s/n): ");
    scanf(" %c", &opc);

    if (opc == 's' || opc == 'S') return 1;
    if (opc == 'n' || opc == 'N') return 0;

    return -1;
}
