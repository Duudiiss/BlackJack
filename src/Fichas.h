#ifndef FICHAS_H
#define FICHAS_H


typedef struct Jogador Jogador;

typedef struct {
    float saldo;
} Carteira;

Carteira* InitWallet(float fichasIniciais);
float GetBalance(Jogador *jogador);
int descontaCarteira(Jogador *jogador, float valor);
int somaCarteira(Jogador *jogador, float valor);
int ExcluiCarteira(Jogador *jogador);

#endif