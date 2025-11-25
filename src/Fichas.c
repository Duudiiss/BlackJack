#include <stdio.h>
#include <stdlib.h>
#include "Fichas.h"
#include "Jogador.h"

Carteira* InitWallet(float fichasIniciais) {
    Carteira *novaCarteira = (Carteira*) malloc(sizeof(Carteira));
    if (novaCarteira == NULL) {
        fprintf(stderr, "Erro: Falha na alocação de memória para a carteira.\n");
        return NULL;
    }
    novaCarteira->saldo = fichasIniciais;
    return novaCarteira;
}

float GetBalance(Jogador *jogador) {
    if (jogador == NULL || jogador->carteira == NULL) {
        fprintf(stderr, "Erro: Jogador ou carteira inválidos.\n");
        return -1.0f;
    }
    return jogador->carteira->saldo;
}

int descontaCarteira(Jogador *jogador, float valor) {
    if (jogador == NULL || jogador->carteira == NULL) {
        fprintf(stderr, "Erro: Jogador ou carteira inválidos.\n");
        return -1;
    }
    if (valor < 0) {
        fprintf(stderr, "Erro: Valor negativo para desconto.\n");
        return -1;
    }
    if (jogador->carteira->saldo < valor) {
        fprintf(stderr, "Erro: Saldo insuficiente.\n");
        return -1;
    }
    jogador->carteira->saldo -= valor;
    return 0;
}

int somaCarteira(Jogador *jogador, float valor) {
    if (jogador == NULL || jogador->carteira == NULL) {
        fprintf(stderr, "Erro: Jogador ou carteira inválidos.\n");
        return -1;
    }
    if (valor < 0) {
        fprintf(stderr, "Erro: Valor negativo para soma.\n");
        return -1;
    }
    jogador->carteira->saldo += valor;
    return 0;
}

int ExcluiCarteira(Jogador *jogador) {
    if (jogador == NULL) {
        fprintf(stderr, "Erro: Jogador inválido.\n");
        return -1;
    }
    if (jogador->carteira == NULL) {
        fprintf(stderr, "Aviso: Jogador não possui carteira para excluir.\n");
        return -1;
    }

    free(jogador->carteira);
    jogador->carteira = NULL; // evita ponteiro solto
    return 0;
}