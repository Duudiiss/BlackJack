
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "Baralho.h"

static int _verificaEmbaralhamento(const Baralho* baralho) 
{
    int ordenado = 1;
    int sequencias_ordenadas = 0;
    
    // Verifica se há muitas sequências ordenadas
    for (int i = 1; i < baralho->tamanho; i++) 
    {
        // Se esta carta vem depois da anterior na ordem natural
        if (baralho->cartas[i].numero == baralho->cartas[i-1].numero + 1 && baralho->cartas[i].naipe == baralho->cartas[i-1].naipe) 
        {
            sequencias_ordenadas++;
        }
    }

    // Se mais de 10% das cartas estão em sequência ordenada, considera mal embaralhado
    if (sequencias_ordenadas > baralho->tamanho / 10) 
    {
        return 1;
    }
    return 0;
}

static int _baralhoBaixo(const Baralho* baralho)
{
    return 0;
}

Baralho* CriaBaralho() 
{
    Baralho* baralho = (Baralho*)malloc(sizeof(Baralho));
    if (baralho == NULL) {
        return NULL;
    }
    baralho->tamanho = MAX_CARTAS;

    char naipes[] = {'C', 'O', 'E', 'P'}; // Copas, Ouros, Espadas, Paus
    int indice = 0;

    // Criação das 52 cartas do baralho
    for (int naipe = 0; naipe < 4; naipe++) 
    {
        for (int numero = 1; numero <= 13; numero++)
        {
            //Definição das cartas
            baralho->cartas[indice].numero = numero;
            baralho->cartas[indice].naipe = naipes[naipe];

            //Definição dos valores das cartas
            if(numero == 1) baralho->cartas[indice].valor = 11; // Ás
            else if(numero > 10) baralho->cartas[indice].valor = 10; // 10, J, Q, K
            else baralho->cartas[indice].valor = numero; // 2 a 9

            indice++;
        }
    }
    return baralho;
}

int DestroiBaralho(Baralho* baralho) 
{
    if (baralho == NULL) 
    {
        return -1;
    }
    free(baralho);
    return 0;
}

int Embaralha(Baralho* baralho)
{
    if (baralho == NULL) 
    {
        return -1;
    }
    srand(time(NULL));
    // Embaralhamento da posição das cartas usando troca aleatória
    for (int i = baralho->tamanho - 1; i > 0; i--) 
    {
        // random int entre 0 and baralho->tamanho-1
        int j = rand() % (i + 1);

        // Troca as cartas de posição
        Carta temp = baralho->cartas[i];
        baralho->cartas[i] = baralho->cartas[j];
        baralho->cartas[j] = temp;
    }

   
    return _verificaEmbaralhamento(baralho);
}

Carta* PegaCarta(Baralho* baralho)
{
    if (baralho == NULL || baralho->tamanho == 0) 
    {
        return NULL;
    }
    // Retira a carta do topo do baralho
    Carta* carta = &baralho->cartas[baralho->tamanho - 1];
    baralho->tamanho--;
    return carta;
}