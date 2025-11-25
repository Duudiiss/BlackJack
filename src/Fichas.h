#ifndef FICHAS_H
#define FICHAS_H

typedef struct {
    float saldo;
} Carteira;

struct Jogador;  // declaração antecipada para evitar dependência circular

// Inicializa uma carteira com o saldo inicial
Carteira* InitWallet(float fichasIniciais);

// Retorna o saldo do jogador
float GetBalance(struct Jogador *jogador);

// Desconta um valor da carteira do jogador
int descontaCarteira(struct Jogador *jogador, float valor);

// Soma um valor na carteira do jogador
int somaCarteira(struct Jogador *jogador, float valor);

// Libera memória da carteira do jogador
int ExcluiCarteira(struct Jogador *jogador);

#endif
