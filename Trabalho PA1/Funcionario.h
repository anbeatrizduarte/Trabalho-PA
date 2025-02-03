// funcionarios.h

#ifndef FUNCIONARIO_H
#define FUNCIONARIO_H

typedef struct{
    int idfuncionario;
    char *nomefuncionario;
} estruturafuncionario;

// Funções declaradas para manipulação dos veículos
estruturafuncionario* alocarEstruturaFuncionario(int numdefuncionarios);
void salvarfuncionario(estruturafuncionario *funcionarios, int numdefuncionarios, char *modo);
void adicionarfuncionario(estruturafuncionario **funcionarios, int *numdefuncionarios);
void visualizarfuncionarios();
int contarfuncionariossNoArquivo();
void lerfuncionariossDoArquivo(estruturafuncionario *funcionario, int numdefuncionarios);
void alterarfuncionario(estruturafuncionario *funcionario, int numDefuncionarios);
void deletarfuncionario(estruturafuncionario **funcionario, int *numdefuncionarios);
void liberarMemoriasFuncionario(estruturafuncionario *funcionario, int numdefuncionarios);
void voltarencerrarprograma();

#endif
