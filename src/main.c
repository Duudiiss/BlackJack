#include <stdio.h>
#include <string.h>
#include "Jogador.h"
#include <unistd.h>
#include "Partida.h"
#define MAX_NOME 50

Jogador * perguntaNome(){
    char nomeJogador[MAX_NOME];
    
    // Centralizando a saída e a caixa de ----
    int i;
    int largura = 40; // Largura da caixa, pode ajustar conforme necessário
    int nomeTamanho;

    // Imprime a linha de ---
    for(i = 0; i < largura; i++) {
        printf("-");
    }
    printf("\n");

    // Imprime a solicitação de nome centralizada
    printf("%*sInforme o nome do jogador: ", (largura / 2) - 14, ""); // Centraliza o texto
    scanf("%[^\n]%*c", nomeJogador); // Lê o nome com espaços até o final da linha

    // Imprime a linha de ---
    for(i = 0; i < largura; i++) {
        printf("-");
    }
    printf("\n");

    // Exibe o nome do jogador
    sleep(1);
    printf("Bem vindo: %s!\n", nomeJogador);
    //Cria Jogador

    Jogador * jogador = CriaJogador(nomeJogador);
    sleep(1);
    return jogador;
}


void mostrarMenu(void) {
    printf("\n");
    for (int i = 0; i < 40; i++) printf("-");  // Linha superior da caixa
    printf("\n");

    printf("%*sO que gostaria de fazer?\n", 20, ""); // Centralizando o título

    printf("1. Carteira\n");
    printf("2. Jogar\n");
    printf("3. Sair (Seu dinheiro é resgatado)\n");

    for (int i = 0; i < 40; i++) printf("-");  // Linha inferior da caixa
    printf("\n");
}

void jogar(Jogador * jogador){

    //1 passo
    Partida * partida = Partida_criar(jogador);

    //2 passo
    float aposta;

    // Loop para garantir que a aposta seja válida
    do {
        printf("Qual será a sua aposta para esta partida? R$: ");
        scanf("%f", &aposta);

        if (aposta <= 0) {
            printf("Aposta inválida! Por favor, insira um valor maior que zero.\n");
        } else if ( aposta > GetBalance(jogador)){
            printf("Saldo insuficiente! Por favor adicione dinheiro!");
            return;
        }
    } while (aposta <= 0); // Continua pedindo até a aposta ser válida

    printf("Sua aposta é: R$ %.2f\n", aposta);
    
    printf("Chamando dealer...\n");
    
    printf("Embaralhando...");
    
    IniciarRodada(partida,aposta);

    DistribuicaoInicial(partida);

    printf("O que voce quer fazer? Vai pedir (p) ou ficar(f)?");
    char escolha;
    scanf(" %c", &escolha);


    
}

int main(void) {
    Jogador * jogador = perguntaNome();
    int opcaoPrincipal, opcaoCarteiraDetalhada;

    do {
        mostrarMenu(); // Exibe o menu principal
        
        // Solicita a opção principal
        printf("Escolha uma opção: ");
        scanf("%d", &opcaoPrincipal);

        switch (opcaoPrincipal) {
            case 1:
                // Menu de opções para a Carteira
                do {
                    printf("\n");
                    for (int i = 0; i < 40; i++) printf("-");  // Linha superior da caixa
                    printf("\n");

                    printf("%*sCarteira: ", 20, ""); // Título centralizado
                    printf("R$%.2f \n",GetBalance(jogador));
                    printf("1. Adicionar Dinheiro\n");
                    printf("2. Resgatar Dinheiro\n");
                    printf("3. Voltar\n");

                    for (int i = 0; i < 40; i++) printf("-");  // Linha inferior da caixa
                    printf("\n");

                    // Solicita a opção do menu detalhado
                    printf("Escolha uma opção: ");
                    scanf("%d", &opcaoCarteiraDetalhada);

                    switch (opcaoCarteiraDetalhada) {
                        case 1:
                            printf("Adicionar Dinheiro selecionado.\n");
                            float valor1;
                            printf("Qual valor deseja adicionar?\n");
                            scanf("%f",&valor1);
                            somaCarteira(jogador,valor1);
                            // Aqui você pode adicionar a lógica para adicionar dinheiro
                            break;
                        case 2:
                            printf("Resgatar Dinheiro selecionado.\n");
                            float valor2;
                            printf("Qual valor deseja resgatar?\n");
                            scanf("%f",&valor2);
                            descontaCarteira(jogador,valor2);
                            // Aqui você pode adicionar a lógica para resgatar dinheiro
                            break;
                        case 3:
                            printf("Voltando ao menu principal...\n");
                            break;
                        default:
                            printf("Opção inválida. Tente novamente.\n");
                    }
                } while (opcaoCarteiraDetalhada != 3); // Volta ao menu principal quando opção 3 for selecionada
                break;
            case 2:
                printf("Você escolheu Jogar!\n");
                

                jogar(jogador);
                break;
            case 3:
                printf("Você escolheu Sair. Seu dinheiro foi resgatado: R$%.2f.\n",GetBalance(jogador));
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (opcaoPrincipal != 3); // O loop continua até o jogador escolher sair
    return 0;



}