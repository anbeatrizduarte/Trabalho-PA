#ifndef ENTREGA_H
#define ENTREGA_H

#include "Cliente.h"
#include "Funcionario.h"
#include "Veiculo.h"

typedef struct {
    int idcliente;
    int idfuncionario;
    int idveiculo;
    int idEntrega;
    estruturacliente *cliente;
    char* origemEntrega;
    char* destinoEntrega;
    int tempoEntrega;
} estruturaEntrega;

estruturaEntrega* alocarEstruturaEntrega(int numdeveiculos);
int geradorId();
void voltarencerrarprograma();
void salvarEntrega(estruturaEntrega *entrega, int numEntrega, char *modo);
void adicionarEntrega (estruturaEntrega **entrega, int *numEntrega);
int contarEntregasNoArquivo();
void visualizarEntrega();
void alterarEntrega(estruturaEntrega *entrega, int numEntrega);
void lerEntregasDoArquivo(estruturaEntrega *entrega, int numEntrega);
void deletarEntrega(estruturaEntrega **entrega, int *numEntrega);
void liberarMemorias(estruturaEntrega *entrega, int numEntrega);

#endif
