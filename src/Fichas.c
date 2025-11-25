#include <stdio.h>
#include <stdlib.h>
#include "fichas.h"

Carteira* InitWallet(float fichasIniciais) {
    Carteira *novaCarteira = (Carteira*) malloc(sizeof(Carteira));
    if (novaCarteira == NULL) {
        fprintf(stderr, "Erro: Falha na alocação de memória para a carteira.\n");
        return NULL;
    }
    novaCarteira->saldo = fichasIniciais;
    return novaCarteira;
}

float CarteiraGetSaldo(const Carteira* carteira) {
    if (carteira == NULL) {
        fprintf(stderr, "Erro: Carteira inválida.\n");
        return -1.0f;
    }
    return carteira->saldo;
}

int CarteiraDesconta(Carteira* carteira, float valor) {
    if (carteira == NULL) {
        fprintf(stderr, "Erro: Carteira inválida.\n");
        return -1;
    }
    if (valor < 0) {
        fprintf(stderr, "Erro: Valor negativo para desconto.\n");
        return -1;
    }
    if (carteira->saldo < valor) {
        fprintf(stderr, "Erro: Saldo insuficiente.\n");
        return -1;
    }
    carteira->saldo -= valor;
    return 0;
}

int CarteiraSoma(Carteira* carteira, float valor) {
    if (carteira == NULL) {
        fprintf(stderr, "Erro: Carteira inválida.\n");
        return -1;
    }
    if (valor < 0) {
        fprintf(stderr, "Erro: Valor negativo para soma.\n");
        return -1;
    }
    carteira->saldo += valor;
    return 0;
}

int CarteiraExclui(Carteira* carteira) {
    if (carteira == NULL) {
        fprintf(stderr, "Aviso: Carteira já é NULL.\n");
        return -1;
    }
    free(carteira);
    return 0;
}
