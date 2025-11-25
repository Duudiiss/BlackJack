#include "Baralho.h"
#include "Jogador.h"
#include "Partida.h"

typedef struct {
    Baralho *baralho;
    Jogador *jogador;
    MaoDealer * dealer;
    int apostaAtual;
    int estado; 
    int precisaReembaralhar;
} Partida;

int DealerLimpaMao(MaoDealer* dealer)
{
    if (!dealer) return 1;

    for (int i = 0; i < MAX_MAO_CARTAS; i++) {
        if (dealer->cartas[i] != NULL) {
            free(dealer->cartas[i]);
            dealer->cartas[i] = NULL;
        }
    }
    return 0;
}

Partida* Partida_criar(Jogador * jogador) {
    // Criação da estrutura partida
    Partida *p = (Partida*)malloc(sizeof(Partida));
    if (p == NULL) {
        printf("Erro ao alocar memória para a partida!\n");
        return NULL;
    }

    
    p->jogador = jogador;

    

    // Criação do baralho
    p->baralho = CriaBaralho();
    if (p->baralho == NULL) {
        printf("Erro ao criar o baralho!\n");
        free(p->jogador);
        free(p);
        return NULL;
    }

    // Embaralha o baralho
    if (Embaralha(p->baralho) != 0) {
        printf("Erro ao embaralhar o baralho!\n");
        DestroyBaralho(p->baralho);  // Libera o baralho em caso de erro
        free(p->jogador);
        free(p);
        return NULL;
    }

    // Inicializa o estado da partida
    // 0 iniciou
    // 1 em andamento
    // 2 finalizada
    p->estado = 0;
    
    return p;  // Retorna a partida com jogador e baralho prontos
}

int IniciarRodada(Partida *p, float apostaInicial){
    if(p->estado == 0){
        if(JogadorLimpaMao(p->jogador)){
            printf("Não consegui limpar a mão");
            return 2;
        }
        if(DealerLimpaMao(p->dealer)){
            printf("Não consegui limpar o dealer");
            return 2;
        }
        p->apostaAtual = apostaInicial;
        p->estado = 1;
    }

}


int DistribuicaoInicial(Partida*p){
    Carta* PegaCarta(Baralho* baralho);
    int d1 = JogadorRecebeCarta(p->jogador, PegaCarta(p->baralho));
    //se 0, sucesso; se 1 mao cheia, se 2 carta invalida, tratar erros
    p->dealer->mao[1] = Carta* PegaCarta(Baralho* baralho);
    int d1 = JogadorRecebeCarta(p->jogador, PegaCarta(p->baralho));
    p->dealer->mao[2] = Carta* PegaCarta(Baralho* baralho);
}

int verificaBlackJackNatural(Partida *p){

    //3 para erro
    //2 para black jack dealer
    //1 para black jack jogador
    //0 para nao black jack natural
    if (jogador == NULL || jogador->cartas[0] == NULL || jogador->cartas[1] == NULL) {
        return 3;
    }
    int v1 = CartaGetValor(p->jogador->cartas[0]);
    int v2 = CartaGetValor(->jogador->cartas[1]);
    if(v1+v2==21) return 1;
    return 0;
}

int ProcessarAcaoJogador(Partida *p, char* acao) {
    if (p == NULL || acao == NULL) {
        fprintf(stderr, "Erro: Partida ou ação inválida.\n");
        return -1; // erro genérico
    }

    // Ação: HIT
    if (strcmp(acao, "hit") == 0) {
        Carta *novaCarta = PegaCarta(p->baralho);
        if (novaCarta == NULL) {
            fprintf(stderr, "Erro: Não foi possível pegar carta do baralho.\n");
            return -1;
        }

        int d1 = JogadorRecebeCarta(p->jogador, novaCarta);
        switch (d1) {
            case 0: // sucesso
                return 0;
            case 1: // mão cheia
                fprintf(stderr, "Erro: Mão do jogador está cheia.\n");
                return 0; // segue jogo, mas não adicionou carta
            case 2: // carta inválida
                fprintf(stderr, "Erro: Carta inválida recebida.\n");
                return 0;
            default:
                fprintf(stderr, "Erro desconhecido ao receber carta.\n");
                return -1;
        }
    }

    // Ação: STAND
    if (strcmp(acao, "stand") == 0) {
        p->jogador->fez_stand = 1;
        return 1; // indica que jogador parou
    }

    // Ação inválida
    fprintf(stderr, "Erro: Ação '%s' não reconhecida.\n", acao);
    return -1;
}