#ifndef BARALHO_H
#define BARALHO_H

#define MAX_CARTAS 52
#define PONTO_REEMBARALHA 0.25f

typedef struct Carta Carta;
typedef struct Baralho Baralho;

Baralho* CriaBaralho();
int DestroiBaralho(Baralho* baralho);
int Embaralha(Baralho* baralho);
Carta* PegaCarta(Baralho* baralho);
int _baralhoBaixo(const Baralho* baralho);

/* Getters de BARALHO (acesso controlado) */
int BaralhoGetTamanho(const Baralho* baralho);
const Carta* BaralhoGetCarta(const Baralho* baralho, int indice);

/* Getters de CARTA (acesso controlado) */
int CartaGetNumero(const Carta* carta);
char CartaGetNaipe(const Carta* carta);
int CartaGetValor(const Carta* carta);
#endif