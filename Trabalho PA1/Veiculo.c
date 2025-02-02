#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include "Veiculo.h"


estruturaveiculo* alocarEstruturaVeiculo(int numdeveiculos) {
    return (estruturaveiculo*)malloc(numdeveiculos * sizeof(estruturaveiculo));
}

// Função para abrir o arquivo
FILE* abrirArquivo(char* nomeArquivo, char* modo) {
    FILE* arquivo = fopen(nomeArquivo, modo);
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo");
        exit(1);
    }
    return arquivo;
}

//Função para voltar para menu ou encerrar programa
void voltarencerrarprograma(){
    int menuEncerrar;
    printf("\nPressione 0 para sair do programa e 1 para voltar ao menu de operações : \n");
    scanf("%d", &menuEncerrar);
        if (menuEncerrar == 0)
        {
            exit(0);
        }
}

//funcao para salvar veiculo dentro do arquivo
void salvarveiculo(estruturaveiculo *veiculo, int numdeveiculos, char *modo ) {
    //a proxima linha chama a funcao de abrir arquivo
    FILE* arq_veiculos = abrirArquivo("arq_veiculos.txt", modo);
        for (int i = 0; i < numdeveiculos; i++) {
            fprintf(arq_veiculos, "===== Informações dos veiculos (%d) =====\n", i + 1);
            fprintf(arq_veiculos, "Nome: %s\n", veiculo[i].nomeveiculo);
            fprintf(arq_veiculos, "ID: %d\n", veiculo[i].idveiculo);
            fprintf(arq_veiculos, "Capacidade de carga em KG: %d\n", veiculo[i].cargaveiculo);
            fprintf(arq_veiculos, "Status veiculo: %d\n", veiculo[i].statusveiculo);
            }
    fclose(arq_veiculos);
}

//funcao para verificar se Id ja existe
int verificarId(int idveiculo)
{
    //proxima linha chama funcao de abrir arquivo
    FILE *arq_veiculos = fopen("arq_veiculos.txt", "r");
        if (arq_veiculos == NULL)
        {
        return 0;
        }
    char linha[200];
    int idLido;

    while (fgets(linha, sizeof(linha), arq_veiculos))
    {
        if (sscanf(linha, "ID: %d", &idLido) == 1)

        {
            if (idLido == idveiculo)
            {
                return 1;
            }
        }
    }
    return 0;
}

//funcao para adicionarveiculo
void adicionarveiculo(estruturaveiculo **veiculo, int *numdeveiculos){
    for (int i = 0; i < *numdeveiculos; i++) {
        (*veiculo)[i].nomeveiculo = malloc(30 * sizeof(char));
        if ((*veiculo)[i].nomeveiculo == NULL) {
            printf("Erro ao alocar memória para o nome do veículo.\n");
            exit(1);
        }
        printf("Informe o tipo do veiculo: ");
        fgets((*veiculo)[i].nomeveiculo, 30, stdin);
        (*veiculo)[i].nomeveiculo[strcspn((*veiculo)[i].nomeveiculo, "\n")] = 0;

        printf("Informe a Capacidade de carga em KG: ");
        scanf("%d", &(*veiculo)[i].cargaveiculo);

        printf("Informe o status do veiculo '0'para ocupado e '1' para disponivel: ");
        scanf("%d", &(*veiculo)[i].statusveiculo);

        while(1){
            printf("Informe o ID do veiculo(4 Digitos): ");
            scanf("%d", &(*veiculo)[i].idveiculo);
            getchar();
            if ((*veiculo)[i].idveiculo < 1000 || (*veiculo)[i].idveiculo > 9999) {
                printf("ID inválido. Tente novamente.\n");
                continue;
            }
            if(verificarId((*veiculo)[i].idveiculo)) {
                printf("Já existe um veiculo com esse ID. Tente novamente.\n");
                continue;
            }
            break;
        }
    }
}

//funcao para contar a quantidade de veiculos no arquivo
int contarveiculosNoArquivo() {
        //a proxima linha chama a funcao de abrir arquivo
    FILE *arq_veiculos = fopen("arq_veiculos.txt", "r");

    int contador = 0;
    char buffer[200];
        while (fgets(buffer, sizeof(buffer), arq_veiculos)) {
            if (strstr(buffer, "===== Informações dos veiculos")) { contador++;}
            }
    fclose(arq_veiculos);
    return contador;
}

//funcao para exibir todos veiculos
void visualizarveiculo() {
    //a proxima linha chama a funcao de abrir arquivo
    FILE* arq_veiculos = abrirArquivo("arq_veiculos.txt", "r");
    
    char buffer[200];
        while (fgets(buffer, sizeof(buffer), arq_veiculos)) 
        {
            printf("%s", buffer);
        }

    fclose(arq_veiculos);
}

//lerVeiculosDoArquivo
void lerVeiculosDoArquivo(estruturaveiculo *veiculo, int numdeveiculos) {
    FILE* arq_veiculos = abrirArquivo("arq_veiculos.txt", "r");
    char buffer[200];
    int i = 0;

    while (fgets(buffer, sizeof(buffer), arq_veiculos) && i < numdeveiculos) {
        if (strstr(buffer, "===== Informações dos veiculos")) {
            veiculo[i].nomeveiculo = malloc(30 * sizeof(char));
            if (veiculo[i].nomeveiculo == NULL) {
                printf("Erro ao alocar memória para o nome do veículo.\n");
                exit(1);
            }

            if (fgets(buffer, sizeof(buffer), arq_veiculos) && strstr(buffer, "Nome: ")) {
                sscanf(buffer, "Nome: %[^\n]", veiculo[i].nomeveiculo);
            }

            if (fgets(buffer, sizeof(buffer), arq_veiculos) && strstr(buffer, "ID: ")) {
                sscanf(buffer, "ID: %d", &veiculo[i].idveiculo);
            }

            if (fgets(buffer, sizeof(buffer), arq_veiculos) && strstr(buffer, "Capacidade de carga em KG: ")) {
                sscanf(buffer, "Capacidade de carga em KG: %d", &veiculo[i].cargaveiculo);
            }

            if (fgets(buffer, sizeof(buffer), arq_veiculos) && strstr(buffer, "Status veiculo: ")) {
                sscanf(buffer, "Status veiculo: %d", &veiculo[i].statusveiculo);
            }

            i++;
        }
    }

    fclose(arq_veiculos);
}

//funcao para alterarVeiculo

// Função para alterar funcionario
void alterarVeiculo(estruturaveiculo *veiculo, int numDeVeiculo) {
    int idParaAlterar, infoAlterar;
    char novoTipo[30];
    int novoId, novaCarga, novoStatus;
    visualizarveiculo();
    printf("\n===== Informações que podem ser alteradas =====\n");
    printf("Tipo -> 1 \nID -> 2 \nCapacidade de carga em KG -> 3 \nStatus -> 4\n");
    
    printf("\nQual informação deseja alterar: ");
    scanf("%d", &infoAlterar);
    getchar();
    
    printf("\nInforme o ID do veículo que deseja alterar: ");
    scanf("%d", &idParaAlterar);
    getchar();
    
    int encontrado = 0;

    for (int i = 0; i < numDeVeiculo; i++) {
        if (veiculo[i].idveiculo == idParaAlterar) {
            
            encontrado = 1;
            
            if (infoAlterar == 1) {
                printf("\nInforme o novo tipo do veículo: ");
                fgets(novoTipo, 30, stdin);
                novoTipo[strcspn(novoTipo, "\n")] = 0;
                free(veiculo[i].nomeveiculo);
                veiculo[i].nomeveiculo = malloc(30 * sizeof(char));  // Alocar nova memória
                strcpy(veiculo[i].nomeveiculo, novoTipo);
            }

            else if (infoAlterar == 2) {
                while(1){
                printf("\nInforme o novo ID do veículo: ");
                scanf("%d", &novoId);
                getchar();
                if (novoId < 1000 || novoId > 9999) {
                    printf("ID inválido. Tente novamente.\n");
                    continue;
                }
                if(verificarId(novoId)) {
                    printf("Já existe um veiculo com esse ID. Tente novamente.\n");
                    continue;
                }
                break;
            }
                veiculo[i].idveiculo = novoId;
            }
            
            else if (infoAlterar == 3) {
                printf("\nInforme a nova capacidade da carga em Kg do veículo: ");
                scanf("%d", &novaCarga);
                getchar();
                veiculo[i].cargaveiculo = novaCarga;
            }

            else if (infoAlterar == 4) {
                printf("\nInforme o novo status do veículo (0 para Ocupado e 1 para Disponível): ");
                scanf("%d", &novoStatus);
                getchar();
                veiculo[i].statusveiculo = novoStatus;
            }

            

            printf("\nDados do veículo alterados com sucesso.\n");
            break;
        }
    }
    
    if (!encontrado) {
        printf("Veículo com ID %d não encontrado.\n", idParaAlterar);
    }
}

//funcao para deletarVeiculo 
void deletarVeiculo(estruturaveiculo **veiculo, int *numdeveiculos) {
    int idParaDeletar;
    printf("Informe o ID do veiculo que deseja deletar: ");
    scanf("%d", &idParaDeletar);
    getchar();

    int indiceParaRemover = -1;
    for (int i = 0; i < *numdeveiculos; i++) {
        if ((*veiculo)[i].idveiculo == idParaDeletar) {
            indiceParaRemover = i;
            break;
        }
    }

    if (indiceParaRemover == -1) {
        printf("Veiculo com ID %d não encontrado.\n", idParaDeletar);
        return;
    }

    // Liberar memoria do veiculo removido
    free((*veiculo)[indiceParaRemover].nomeveiculo);

    // troca dos elementos restantes
    for (int i = indiceParaRemover; i < (*numdeveiculos) - 1; i++) {
        (*veiculo)[i] = (*veiculo)[i + 1];
    }

    (*numdeveiculos)--;

    *veiculo = realloc(*veiculo, (*numdeveiculos) * sizeof(estruturaveiculo));
    if (*numdeveiculos > 0 && *veiculo == NULL) {
        printf("Erro ao realocar memória após a remoção do veiculo.\n");
        exit(1);
    }

    salvarveiculo(*veiculo, *numdeveiculos,"w");
    printf("Veiculo com ID %d foi removido com sucesso.\n", idParaDeletar);
}

//funcao para liberar memoria dos mallocs
void liberarMemoriasVeiculo(estruturaveiculo *veiculo, int numdeveiculos) {
    for (int i = 0; i < numdeveiculos; i++) {
        free(veiculo[i].nomeveiculo);
    }
    free(veiculo);
    voltarencerrarprograma();
}

//funcao principal
