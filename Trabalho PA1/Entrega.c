#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Entrega.h"
#include "Veiculo.h"
#include "Cliente.h"
#include "Funcionario.h"

estruturaEntrega* alocarEstruturaEntrega(int numEntrega) {
    return (estruturaEntrega*)malloc(numEntrega * sizeof(estruturaEntrega));
}

FILE* abrirArquivo(const char* nomeArquivo, char* modo);


int contadorID = 0;

int geradorId() {
    FILE *arquivo = fopen("contador.txt", "r");
    if (arquivo != NULL) {
        fscanf(arquivo, "%d", &contadorID);
        fclose(arquivo);
    } else {
        contadorID = 0;
    }

    int novoId = ++contadorID;

    arquivo = fopen("contador.txt", "w");
    if (arquivo != NULL) {
        fprintf(arquivo, "%d", contadorID);
        fclose(arquivo);
    }

    return novoId;
}

int *lerIds(const char* nomeArquivo, int *tamanho) {
    FILE *arquivo = abrirArquivo(nomeArquivo, "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s\n", nomeArquivo);
        *tamanho = 0;
        return NULL;
    }

    int *ids = NULL;
    int id;
    *tamanho = 0;

    char buffer[256];  // Buffer para armazenar cada linha

    while (fgets(buffer, sizeof(buffer), arquivo)) {  // Ler linha por linha
        // Verificar se a linha contém "ID:"
        if (sscanf(buffer, "ID: %d", &id) == 1) {  // Tentar extrair o ID da linha
            ids = realloc(ids, (*tamanho + 1) * sizeof(int));
            if (ids == NULL) {
                printf("Erro ao alocar memória para IDs\n");
                fclose(arquivo);
                return NULL;
            }
            ids[*tamanho] = id;
            (*tamanho)++;
        }
    }

    fclose(arquivo);
    return ids;
}




int verificarId(int id, int *ids, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        if (ids[i] == id) {
            return 1;
        }
    }
    return 0;
}

FILE* abrirArquivo(const char* nomeArquivo, char* modo) {
    FILE* arquivo = fopen(nomeArquivo, modo);
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo");
        exit(1);
    }
    return arquivo;
}


void voltarencerrarprograma(){
    int menuEncerrar;
    printf("\nPressione 0 para sair do programa e 1 para voltar ao menu de operações : \n");
    scanf("%d", &menuEncerrar);
        if (menuEncerrar == 0)
        {
            exit(0);
        }
}


void salvarEntrega(estruturaEntrega *entrega, int numEntrega, char *modo) {
    FILE *arq_entregas = fopen("arq_entregas.txt", modo);
    for (int i = 0; i < numEntrega; i++) {
        fprintf(arq_entregas, "===== Informações das entregas (%d) =====\n", i + 1);
        fprintf(arq_entregas, "ID da entrega: %d\n", entrega[i].idEntrega);
        fprintf(arq_entregas, "ID do cliente: %d\n", entrega[i].idcliente);
        fprintf(arq_entregas, "ID do funcionário: %d\n", entrega[i].idfuncionario);
        fprintf(arq_entregas, "ID do veículo: %d\n", entrega[i].idveiculo);
        fprintf(arq_entregas, "Origem: %s\n", entrega[i].origemEntrega);
        fprintf(arq_entregas, "Destino: %s\n", entrega[i].destinoEntrega);
        fprintf(arq_entregas, "Tempo estimado da entrega (em horas): %d\n", entrega[i].tempoEntrega);
    }
    fclose(arq_entregas);
}


void adicionarEntrega(estruturaEntrega **entrega, int *numEntrega) {
    // Alocar memória para as strings de origem e destino
    for (int i = 0; i < *numEntrega; i++) {
        (*entrega)[i].origemEntrega = malloc(30 * sizeof(char));
        if ((*entrega)[i].origemEntrega == NULL) {
            printf("Erro ao alocar memória para a origem da entrega.\n");
            exit(1);
        }
        (*entrega)[i].destinoEntrega = malloc(30 * sizeof(char));
        if ((*entrega)[i].destinoEntrega == NULL) {
            printf("Erro ao alocar memória para o destino da entrega.\n");
            exit(1);
        }
    }

    // Ler IDs dos arquivos
    int tamanhoClientes, tamanhoFuncionarios, tamanhoVeiculos;
    int *idsClientes = lerIds("arq_clientes.txt", &tamanhoClientes);
    int *idsFuncionarios = lerIds("arq_funcionarios.txt", &tamanhoFuncionarios);
    int *idsVeiculos = lerIds("arq_veiculos.txt", &tamanhoVeiculos);

    for (int i = 0; i < *numEntrega; i++) {
        printf("===== Cadastrar uma entrega =====\n");

        // Verificar ID do cliente
        int idClienteVerificado;
        printf("Digite o ID do cliente desejado: \n");
        scanf("%d", &idClienteVerificado);
        getchar();
        if (!verificarId(idClienteVerificado, idsClientes, tamanhoClientes)) {
            printf("ID do cliente %d não encontrado.\n", idClienteVerificado);
            free((*entrega)[i].origemEntrega);
            free((*entrega)[i].destinoEntrega);
            continue;
        }

        // Verificar ID do funcionário
        int idFuncionarioVerificado;
        printf("Digite o ID do funcionário responsável: \n");
        scanf("%d", &idFuncionarioVerificado);
        getchar();
        if (!verificarId(idFuncionarioVerificado, idsFuncionarios, tamanhoFuncionarios)) {
            printf("ID do funcionário %d não encontrado.\n", idFuncionarioVerificado);
            free((*entrega)[i].origemEntrega);
            free((*entrega)[i].destinoEntrega);
            continue;
        }

        // Verificar ID do veículo
        int idVeiculoVerificado;
        printf("Digite o ID do veículo desejado: \n");
        scanf("%d", &idVeiculoVerificado);
        getchar();
        if (!verificarId(idVeiculoVerificado, idsVeiculos, tamanhoVeiculos)) {
            printf("ID do veículo %d não encontrado.\n", idVeiculoVerificado);
            free((*entrega)[i].origemEntrega);
            free((*entrega)[i].destinoEntrega);
            continue;
        }

        // Preencher os dados da entrega
        printf("Informe o endereço de origem da entrega: ");
        fgets((*entrega)[i].origemEntrega, 30, stdin);
        (*entrega)[i].origemEntrega[strcspn((*entrega)[i].origemEntrega, "\n")] = 0;

        printf("Informe o endereço de destino da entrega: ");
        fgets((*entrega)[i].destinoEntrega, 30, stdin);
        (*entrega)[i].destinoEntrega[strcspn((*entrega)[i].destinoEntrega, "\n")] = 0;

        printf("Tempo estimado da entrega (em horas): ");
        scanf("%d", &(*entrega)[i].tempoEntrega);
        getchar();

        (*entrega)[i].idEntrega = geradorId();
        (*entrega)[i].idcliente = idClienteVerificado;
        (*entrega)[i].idfuncionario = idFuncionarioVerificado;
        (*entrega)[i].idveiculo = idVeiculoVerificado;

        printf("ID da entrega (gerado automaticamente): %d\n", (*entrega)[i].idEntrega);
    }

    // Liberar memória dos IDs
    free(idsClientes);
    free(idsFuncionarios);
    free(idsVeiculos);
}

int contarEntregasNoArquivo() {
    FILE *arq_entregas = fopen("arq_entregas.txt", "r");

    int contador = 0;
    char buffer[200];
        while (fgets(buffer, sizeof(buffer), arq_entregas)) {
            if (strstr(buffer, "===== Informações das entregas")) { contador++;}
            }
    fclose(arq_entregas);
    return contador;
}

void visualizarEntrega() {
    FILE* arq_entregas = abrirArquivo("arq_entregas.txt", "r");
    
    char buffer[200];
        while (fgets(buffer, sizeof(buffer), arq_entregas)) 
        {
            printf("%s", buffer);
        }

    fclose(arq_entregas);
}

void alterarEntrega(estruturaEntrega *entrega, int numEntrega) {
    int idParaAlterar, infoAlterar;
    char novaOrigem[50],novoDestino[50];
    int novoTempoEntrega;
    visualizarEntrega();
    printf("\n===== Informações que podem ser alteradas =====\n");
    printf("Origem -> 1 \nDestino -> 2 \nTempo estimado da entrega (em horas) -> 3\n");
    
    printf("\nQual informação deseja alterar: ");
    scanf("%d", &infoAlterar);
    getchar();
    
    printf("\nInforme o ID do Cliente que deseja alterar: ");
    scanf("%d", &idParaAlterar);
    getchar();
    
    int encontrado = 0;

    for (int i = 0; i < numEntrega; i++) {
        if (entrega[i].idEntrega == idParaAlterar) {
            
            encontrado = 1;
            
            if (infoAlterar == 1) {
                printf("\nInforme o novo endereço de origem da entrega: ");
                fgets(novaOrigem, 50, stdin);
                novaOrigem[strcspn(novaOrigem, "\n")] = 0;
                free(entrega[i].origemEntrega);
                entrega[i].origemEntrega = malloc(30 * sizeof(char));  // Alocar nova memória
                strcpy(entrega[i].origemEntrega, novaOrigem);
            }

            else if (infoAlterar == 2) {
                printf("\nInforme o novo endereço de destino da entrega: ");
                fgets(novoDestino, 50, stdin);
                novoDestino[strcspn(novoDestino, "\n")] = 0;
                free(entrega[i].destinoEntrega);
                entrega[i].destinoEntrega = malloc(50 * sizeof(char));
                strcpy(entrega[i].destinoEntrega, novoDestino);
            }

            else if (infoAlterar == 3) {
                printf("\nInforme o novo tempo estimado da entrega (em horas): ");
                scanf("%d", &novoTempoEntrega);
                getchar();
                entrega[i].tempoEntrega = novoTempoEntrega;
            }
           
            salvarEntrega(entrega, numEntrega, "w");
            printf("\nDados da entrega alterados com sucesso.\n");
            break;
        }
    }
    
    if (!encontrado) {
        printf("Entrega com ID %d não encontrado.\n", idParaAlterar);
    }
}

void lerEntregasDoArquivo(estruturaEntrega *entrega, int numEntrega) {
    FILE* arq_entregas = abrirArquivo("arq_entregas.txt", "r");
    char buffer[200];
    int i = 0;

    while (fgets(buffer, sizeof(buffer), arq_entregas) && i < numEntrega) {
        if (strstr(buffer, "===== Informações das entregas")) {
            entrega[i].origemEntrega = malloc(30 * sizeof(char));
            if (entrega[i].origemEntrega == NULL) {
                printf("Erro ao alocar memória para o nome do veículo.\n");
                exit(1);
            }

            entrega[i].destinoEntrega = malloc(30 * sizeof(char));
            if (entrega[i].destinoEntrega == NULL) {
                printf("Erro ao alocar memória para o nome do veículo.\n");
                exit(1);
            }

            if (fgets(buffer, sizeof(buffer), arq_entregas) && strstr(buffer, "ID da entrega: ")) {
                sscanf(buffer, "ID da entrega: %d", &entrega[i].idEntrega);
            }

            if (fgets(buffer, sizeof(buffer), arq_entregas) && strstr(buffer, "ID do cliente: ")) {
                sscanf(buffer, "ID do cliente: %d", &entrega[i].idcliente);
            }

            if (fgets(buffer, sizeof(buffer), arq_entregas) && strstr(buffer, "ID do funcionário: ")) {
                sscanf(buffer, "ID do funcionário: %d", &entrega[i].idfuncionario);
            }

            if (fgets(buffer, sizeof(buffer), arq_entregas) && strstr(buffer, "ID do veículo: ")) {
                sscanf(buffer, "ID do veículo: %d", &entrega[i].idveiculo);
            }

            if (fgets(buffer, sizeof(buffer), arq_entregas) && strstr(buffer, "Origem: ")) {
                sscanf(buffer, "Origem: %[^\n]", entrega[i].origemEntrega);
            }

            if (fgets(buffer, sizeof(buffer), arq_entregas) && strstr(buffer, "Destino: ")) {
                sscanf(buffer, "Destino: %[^\n]", entrega[i].destinoEntrega);
            }

            if (fgets(buffer, sizeof(buffer), arq_entregas) && strstr(buffer, "Tempo estimado da entrega (em horas): ")) {
                sscanf(buffer, "Tempo estimado da entrega (em horas): %d", &entrega[i].tempoEntrega);
            }

            i++;
        }
    }

    fclose(arq_entregas);
}

void deletarEntrega(estruturaEntrega **entrega, int *numEntrega) {
    int idParaDeletar;
    printf("Informe o ID da entrega que deseja deletar: ");
    scanf("%d", &idParaDeletar);
    getchar();

    int indiceParaRemover = -1;
    for (int i = 0; i < *numEntrega; i++) {
        if ((*entrega)[i].idEntrega == idParaDeletar) {
            indiceParaRemover = i;
            break;
        }
    }

    if (indiceParaRemover == -1) {
        printf("Entrega com ID %d não encontrado.\n", idParaDeletar);
        return;
    }

    // Deslocar as entregas para "remover" a entrega no vetor
    for (int i = indiceParaRemover; i < *numEntrega - 1; i++) {
        (*entrega)[i] = (*entrega)[i + 1];
    }

    // Atualizar o número de entregas
    (*numEntrega)--;

    // Realocar a memória para o novo tamanho
    *entrega = realloc(*entrega, (*numEntrega) * sizeof(estruturaEntrega));
    if (*entrega == NULL && *numEntrega > 0) {
        printf("Erro ao realocar memória após a remoção da entrega.\n");
        exit(1);
    }

    // Reescrever o arquivo com as entregas restantes
    salvarEntrega(*entrega, *numEntrega, "w");
    printf("Entrega com ID %d foi removido com sucesso.\n", idParaDeletar);
}

void liberarMemorias(estruturaEntrega *entrega, int numEntrega) {
    for (int i = 0; i < numEntrega; i++) {
        free(entrega[i].origemEntrega);
        free(entrega[i].destinoEntrega);
    }
    free(entrega);
    voltarencerrarprograma();
}

int main () {
    estruturaEntrega *entrega;

    int numEntrega, numTipoDeOperacao;

    while(1)
    {
        printf("===== Menu de Operações =====\n \n Adicionar -> 1 \n Visualizar -> 2 \n Alterar -> 3 \n Deletar -> 4 \n Sair do programa -> 5 \n\nQual operação deseja realizar: ");
          scanf("%d", &numTipoDeOperacao);
            getchar();
        
        switch(numTipoDeOperacao)
        {

        case 1:
            printf("\nQuantas entregas você deseja adicionar: ");
            scanf("%d", &numEntrega);
            getchar();
            estruturaEntrega *entrega = alocarEstruturaEntrega(numEntrega);
            adicionarEntrega(&entrega, &numEntrega);
            salvarEntrega(entrega, numEntrega,"a");
            printf("\nOs dados dos entregas cadastrados foram salvos com sucesso.\n");
            //liberarMemorias(entrega, numEntrega);
            
            break;
    
        case 2:
            numEntrega = contarEntregasNoArquivo();
            visualizarEntrega();
            voltarencerrarprograma();
            break;
    
        case 3: 
        numEntrega = contarEntregasNoArquivo();
        if (numEntrega > 0) {
            estruturaEntrega *entrega = alocarEstruturaEntrega(numEntrega);
            lerEntregasDoArquivo(entrega, numEntrega); // Ler do arquivo
            alterarEntrega(entrega, numEntrega);
            salvarEntrega(entrega, numEntrega,"w");
            liberarMemorias(entrega, numEntrega);
        } 
        break;

        case 4:
        numEntrega = contarEntregasNoArquivo();
        if (numEntrega > 0) {
            estruturaEntrega *entrega = alocarEstruturaEntrega(numEntrega);
            lerEntregasDoArquivo(entrega, numEntrega);
            deletarEntrega(&entrega, &numEntrega);
            liberarMemorias(entrega, numEntrega);
        } 
        break;

       case 5:
            exit(0);
            }
        
    }
}