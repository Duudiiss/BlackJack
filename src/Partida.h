#ifndef PARTIDA_H
#define PARTIDA_H

#include "Baralho.h"
#include "Jogador.h"

// Forward declaration da struct MaoDealer (se não estiver em outro .h)

struct MaoDealer{
    Carta * mao[12];
    int quantidade;
    int carta_oculta;
};
typedef struct MaoDealer MaoDealer;
// Estrutura da partida

typedef struct {
    Baralho *baralho;
    Jogador *jogador;
    MaoDealer *dealer;
    int apostaAtual;
    int estado;              // 0 iniciou, 1 em andamento, 2 finalizada
    int precisaReembaralhar;
} Partida;

// Funções utilitárias
int DealerLimpaMao(MaoDealer* dealer);

// Criação e encerramento da partida
Partida* Partida_criar(Jogador *jogador);
int EncerrarPartida(Partida *p);

// Controle de rodada
int IniciarRodada(Partida *p, float apostaInicial);
int DistribuicaoInicial(Partida *p);

// Verificação de blackjack natural
int verificaBlackJackNatural(Partida *p);

// Processamento de ações do jogador
int ProcessarAcaoJogador(Partida *p, char* acao);

#endif // PARTIDA_H


