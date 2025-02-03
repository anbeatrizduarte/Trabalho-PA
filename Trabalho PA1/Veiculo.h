// veiculo.h

#ifndef VEICULO_H
#define VEICULO_H

typedef struct {
    int idveiculo;
    char *nomeveiculo;
    int cargaveiculo;
    int statusveiculo;
} estruturaveiculo;

// Funções declaradas para manipulação dos veículos
estruturaveiculo* alocarEstruturaVeiculo(int numdeveiculos);
void salvarveiculo(estruturaveiculo *veiculo, int numdeveiculos, char *modo);
void adicionarveiculo(estruturaveiculo **veiculo, int *numdeveiculos);
void visualizarveiculo();
int contarveiculosNoArquivo();
void lerVeiculosDoArquivo(estruturaveiculo *veiculo, int numdeveiculos);
void alterarVeiculo(estruturaveiculo *veiculo, int numDeVeiculo);
void deletarVeiculo(estruturaveiculo **veiculo, int *numdeveiculos);
void liberarMemoriasVeiculo(estruturaveiculo *veiculo, int numdeveiculos);
void voltarencerrarprograma();

#endif
