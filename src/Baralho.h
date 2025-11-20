#ifndef BARALHO_H
#define BARALHO_H

#define MAX_CARTAS 52
#define PONTO_REEMBARALHA 0.25f

struct Carta {
    int numero;
    char naipe;
    int valor;
};
typedef struct Carta Carta;

struct Baralho {
    Carta cartas[MAX_CARTAS];
    int tamanho;
};
typedef struct Baralho Baralho;

Baralho* CriaBaralho();
int DestroiBaralho(Baralho* baralho);
int Embaralha(Baralho* baralho);
Carta* PegaCarta(Baralho* baralho);
#endif