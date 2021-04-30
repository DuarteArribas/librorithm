#ifndef BOOKSOPERATIONS_H
#define BOOKSOPERATIONS_H
//project includes
#include"books.h"

struct NodoAB {
  LIVRO  Elemento;
  struct NodoAB *Esquerda;
  struct NodoAB *Direita;
}NodoAB;

typedef struct NodoAB *PNodoAB;

PNodoAB CriarAB(void);

PNodoAB CriarNodoAB(LIVRO X);

int NumeroNodosAB (PNodoAB T);

PNodoAB InserirABP (PNodoAB T, LIVRO X);

int PesquisarABP (PNodoAB T, LIVRO X);

void ABPEqInsercaoBinaria (PNodoAB *TE, LIVRO L[], int inicio, int fim);

void CriarSequenciaEmOrdem (PNodoAB T, LIVRO L[], int *N);

PNodoAB CriarABPEquilibradaIB (PNodoAB T);

PNodoAB LibertarNodoAB(PNodoAB P);

PNodoAB RemoverNodoABP (PNodoAB T);

PNodoAB RemoverABP (PNodoAB T, LIVRO X);

int AlturaAB (PNodoAB T);

int verificarEquilibrio(PNodoAB T);

PNodoAB SubstituirNodoDireita (PNodoAB T, LIVRO *X);

void PesquisarABPISBN(PNodoAB T, long int ISBN);

void PesquisarABPTitle(PNodoAB T, char title[100]);

void PesquisarABPAuthorYear(PNodoAB T, char firstAuthor[100], int yearPublish);

void PesquisarABPEditorCientificArea(PNodoAB T, char editor[100], char cientificArea[100]);

PNodoAB ChangeBookISBN(PNodoAB P, PNodoAB T, int ISBN);

PNodoAB RemoveBook(PNodoAB T, LIVRO X);

int seeMostRecentDate(PNodoAB T, char cientificArea[100]);

void showRecentBooksCientificArea(PNodoAB P, PNodoAB T, char cientificArea[100], int k);

void verifyIfExists(LIVRO X, CIENTIFIC_QTD **cientific_qtd, int *num_cientific_qtd);

void cientificAreaWithMoreBooks(PNodoAB T, CIENTIFIC_QTD **cientific_qtd, int *num_cientific_qtd);

PNodoAB insertBook(PNodoAB T);

void showALL(PNodoAB T);

#endif