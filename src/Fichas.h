#ifndef FICHAS_H
#define FICHAS_H

typedef struct {
    float saldo;
} Carteira;

// Inicializa uma carteira
Carteira* InitWallet(float fichasIniciais);

// Retorna o saldo da carteira
float CarteiraGetSaldo(const Carteira* carteira);

// Desconta um valor da carteira
int CarteiraDesconta(Carteira* carteira, float valor);

// Soma um valor na carteira
int CarteiraSoma(Carteira* carteira, float valor);

// Libera memória da carteira
int CarteiraExclui(Carteira* carteira);

#endif
