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

PNodoAB DestruirAB(PNodoAB T);

PNodoAB RemoverNodoABP (PNodoAB T);

PNodoAB RemoverABP (PNodoAB T, LIVRO X);

int AlturaAB (PNodoAB T);

int verificarEquilibrio(PNodoAB T);

PNodoAB SubstituirNodoDireita (PNodoAB T, LIVRO *X);

void PesquisarABPISBN(PNodoAB T, long int ISBN);

void PesquisarABPTitle(PNodoAB T, char title[100]);

void PesquisarABPAuthorYear(PNodoAB T, char firstAuthor[100], int yearPublish);

void PesquisarABPEditorCientificArea(PNodoAB T, char editor[100], char cientificArea[100]);

PNodoAB changeBookISBN(PNodoAB P,long int ISBN);

PNodoAB removeBook(PNodoAB T, long int ISBN);

void verifyIfExistsCientificArea(LIVRO X);

void verifyIfExistsYear(LIVRO X);

void cientificAreaAndYearWithMoreBooks(PNodoAB T, int option);

void showCientificAreaWithMoreBooks(void);

void showYearWithMorePublications(void);

PNodoAB insertBook(PNodoAB T);

void showALL(PNodoAB T);

void putInArray(PNodoAB T,char *cientificArea,LIVRO *list, int *control);

void showMostRecentCientificArea(PNodoAB T);

int getBookQuantity(PNodoAB T, long int ISBN);

void setBookQuantity(PNodoAB T, long int ISBN, int qtd);

float getBookPrice(PNodoAB T, long int ISBN);

LIVRO getMostExpensiveBook(PNodoAB T);

void getTotalStockandStockValue(PNodoAB T, int *totalStock, float *stockValue);

void restockBook(PNodoAB T, long int ISBN, int qtd);

uint64_t getMemoryWasteBooks(PNodoAB T);

#endif