// cliente.h

#ifndef CLIENTE_H
#define CLIENTE_H

typedef struct{
    int idcliente;
    char *nomecliente;
    char *enderecocliente;
    int tiposervicocliente;
} estruturacliente;

// Funções declaradas para manipulação dos veículos
estruturacliente* alocarEstruturacliente(int numdeclientes);
void salvarcliente(estruturacliente *cliente, int numdeclientes, char *modo);
void adicionarcliente(estruturacliente **cliente, int *numdeclientes);
void visualizarcliente();
int contarclientesNoArquivo();
void lerclientesDoArquivo(estruturacliente *cliente, int numdeclientes);
void alterarcliente(estruturacliente *cliente, int numDecliente);
void deletarcliente(estruturacliente **cliente, int *numdeclientes);
void liberarMemoriasCliente(estruturacliente *cliente, int numdeclientes);
void voltarencerrarprograma();

#endif
