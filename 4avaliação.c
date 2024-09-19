#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#define M 25

typedef struct
{
    char nome[30];
    int  pontuacao;
} lista;

int cobra[M * M][2];  
int tamanhoCobra = 1; 
char ultimaDirecao = 'd';  

int comida[2]; 

void inicializarJogo() {
    cobra[0][0] = 1;
    cobra[0][1] = 1;

    comida[0] = rand() % (M - 2) + 1; 
    comida[1] = rand() % (M - 2) + 1;

    tamanhoCobra = 1;

    ultimaDirecao = 'd';  
}

void imprimirTabuleiro(int *pontos) {
    system("cls"); 
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < M; j++) {
            int encontrado = 0;

            for (int k = 0; k < tamanhoCobra; k++) {
                if (cobra[k][0] == i && cobra[k][1] == j) {
                    if (k == 0) 
                        printf(":] "); 
                    else
                        printf("O "); 
                    encontrado = 1;
                }
            }

            
            if (i == comida[0] && j == comida[1])
                printf("@ "); 
            else if (!encontrado) {
                if (i == 0 || i == M - 1 || j == 0 || j == M - 1)
                    printf(". ");
                else
                    printf("  "); 
            }
        }
        printf("\n");
    }
    printf("\033[0m\t \t ╔════════════╗\n");
    printf("\t \t ║ %2d  PONTOS ║\n", *pontos);
    printf("\t \t ╚════════════╝\n");
}


int verificarColisao() {
    if (cobra[0][0] <= 0 || cobra[0][0] >= M - 1 || cobra[0][1] <= 0 || cobra[0][1] >= M - 1) {
        return 1; 
    }

    for (int i = 1; i < tamanhoCobra; i++) {
        if (cobra[i][0] == cobra[0][0] && cobra[i][1] == cobra[0][1]) {
            return 1; 
        }
    }

    return 0; 
}

void recordes(FILE *recorde) {
    lista lista[100], temp; 
    int i, j, n = 0;

    recorde = fopen("recorde.txt", "r");

    if (recorde) {
        while (fscanf(recorde, "%d %[^\n]", &lista[n].pontuacao, lista[n].nome) == 2 && n < 100) {
            n++;
        }
        fclose(recorde);

        // Ordenar a lista do maior para o menor usando o algoritmo Bubble Sort
        for (i = 0; i < n - 1; i++) {
            for (j = 0; j < n - i - 1; j++) {
                if (lista[j].pontuacao < lista[j + 1].pontuacao) {
                    // Trocar posições se a pontuação for menor
                    temp = lista[j];
                    lista[j] = lista[j + 1];
                    lista[j + 1] = temp;
                }
            }
        }

        printf("╔══════════════════RECORDES══════════════════╗\n");
        for (i = 0; i < n; i++) {
            printf("║ %20s: %2d PONTOS            ║\n", lista[i].nome, lista[i].pontuacao);
        }
        printf("╚════════════════════════════════════════════╝\n\n");
    } else {
        printf("NENHUM RECORDE CADASTRADO!\n");
    }
}

void moverCobraAutomaticamente(int *pontos) {
    int cabecaAntiga[2];
    cabecaAntiga[0] = cobra[0][0];
    cabecaAntiga[1] = cobra[0][1];

    switch (ultimaDirecao) {
        case 'w':
            cobra[0][0]--;
            break;
        case 's':
            cobra[0][0]++;
            break;
        case 'a':
            cobra[0][1]--;
            break;
        case 'd':
            cobra[0][1]++;
            break;
        default:
            break;
    }

    if (cobra[0][0] == comida[0] && cobra[0][1] == comida[1]) {
        tamanhoCobra++;
        (*pontos)++;

        int novaPosicaoComida = 0;
        while (!novaPosicaoComida) {
            comida[0] = rand() % (M - 2) + 1; 
            comida[1] = rand() % (M - 2) + 1;

            for (int i = 0; i < tamanhoCobra; i++) {
                if (cobra[i][0] == comida[0] && cobra[i][1] == comida[1]) {
                    novaPosicaoComida = 0;
                    break;
                }
                novaPosicaoComida = 1;
            }
        }
    }

    for (int i = tamanhoCobra - 1; i > 0; i--) {
        int posicaoAtual[2];
        posicaoAtual[0] = cobra[i][0];
        posicaoAtual[1] = cobra[i][1];

        cobra[i][0] = cabecaAntiga[0];
        cobra[i][1] = cabecaAntiga[1];

        cabecaAntiga[0] = posicaoAtual[0];
        cabecaAntiga[1] = posicaoAtual[1];
    }
}

void menu(){
    printf("╔════════════════════MENU════════════════════╗\n");
    printf("║ [1] NOVO JOGO                              ║\n");
    printf("║ [2] EXIBIR RECORDS                         ║\n");
    printf("║ [0] SAIR                                   ║\n");
    printf("╚════════════════════════════════════════════╝\n\n");
    printf("ESCOLHA UMA OPÇÃO ");
}

void Entrada_invalida_num(){
    printf("\n-------------------------------------------\n");
    printf(" ENTRADA INVÁLIDA. DIGITE APENAS NÚMEROS !\n");
    printf("-------------------------------------------\n\n");
}

int main() {
    char direcao,nome[30];
    int op,op2,pontos=0,velocidade;
    FILE *recorde;

    do
    {
        
        
        do {
            menu();
            if (scanf("%d", &op) != 1 || getchar() != '\n') {
                while (getchar() != '\n');
                Entrada_invalida_num();
                op = -1;
            }
        } while (op == -1);
        

        switch (op)
        {
        case 0:
            break;
        
        case 1:

            printf("\nINFORME SEU NOME: ");
            fflush(stdin);
            scanf("%[^\n]",nome);
            for (int j = 0; nome[j]; j++)
            {
                nome[j] = toupper(nome[j]);
            }
            

            do {
                printf("╔═══════════════════MENU═════════════════════╗\n");
                printf("║ [1] FÁCIL                                  ║\n");
                printf("║ [2] NORMAL                                 ║\n");
                printf("║ [3] DIFÍCIL                                ║\n");
                printf("║ [4] HARDCORE                               ║\n");
                printf("╚════════════════════════════════════════════╝\n");
                if (scanf("%d", &op2) != 1 || getchar() != '\n') {
                    
                    while (getchar() != '\n');
                    Entrada_invalida_num();
                    op2 = -1;
                }
            } while (op2 == -1);

            switch (op2)
            {
            case 1:
                velocidade=100;
                break;
            
            case 2:
                velocidade=50;
                break;

            case 3:
                velocidade=20;
                break;

            case 4:
                velocidade=1;
                break;
            
            default:
                printf("OPÇÃO INVÁLIDA !\n");
                break;
            }

            

            recorde=fopen("recorde.txt","a+");
            if (recorde == NULL) {
                printf("Erro ao abrir o arquivo de recorde.\n");
                exit(1);
            }
            inicializarJogo();
            printf("NOVO JOGO INICIADO !\n");

            while (1) {
                imprimirTabuleiro(&pontos);
                
                
                if (_kbhit()) {
                    direcao = getch();
                    ultimaDirecao = direcao;
                }
                
                moverCobraAutomaticamente(&pontos);

                if (verificarColisao()) {
                    printf("\nFIM DE JOGO!\n\n\n");
                    ultimaDirecao = 'd';
                    fprintf(recorde,"%d %s\n",pontos,nome);
                    pontos = 0;
                    fclose(recorde);
                    break;
                }

                Sleep(velocidade);
                
            }
            break;

        case 2:
            recordes(recorde);
            break;
        
        default:
            printf("OPÇÃO INVÁLIDA !\n");
            break;
        }

    } while (op != 0);

    return 0;
}
