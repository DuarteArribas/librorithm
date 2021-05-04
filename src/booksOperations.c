//global includes
#include<stdio.h>
#include <stdlib.h>
#include<stdbool.h>
#include<string.h>
//project includes
#include"booksOperations.h"
#include"books.h"
#include"mem.h"

PNodoAB Books;
CIENTIFIC_QTD *cientific_qtd=NULL;
PUBLISH_YEAR *publish_year=NULL;
int num_cientific_qtd;
int num_publish_year;

PNodoAB CriarAB(void){ 
  PNodoAB T;
  T = NULL;
  return T;
}

PNodoAB CriarNodoAB(LIVRO X){
  PNodoAB P = (PNodoAB) memalloc(sizeof(struct NodoAB));
  if (P == NULL)
    return  NULL;
  P->Elemento = X;
  P->Esquerda = NULL;
  P->Direita = NULL;
  return P;
}

int NumeroNodosAB (PNodoAB T) {
  int  e, d;
  if (T == NULL)
    return 0;
  e = NumeroNodosAB(T->Esquerda);
  d = NumeroNodosAB(T->Direita);
  return (e + d + 1);
}

PNodoAB InserirABP (PNodoAB T, LIVRO X){
  if (T == NULL) {
    T = CriarNodoAB(X);
    return T;
  }
  if (CompareBooks(X, T->Elemento) == -1)   // X.NIF < (T->Elemento).NIF)
    T->Esquerda = InserirABP(T->Esquerda, X);
  else
    T->Direita = InserirABP(T->Direita, X);
  return T;
}

int PesquisarABP (PNodoAB T, LIVRO X){   // 0 = nao existe; 1 = existe
  if (T == NULL)
    return 0;
  if (CompareBooks(X, T->Elemento) == 0)
    return 1;
  if (CompareBooks(X, T->Elemento) == -1)   // X.NIF < (T->Elemento).NIF)
    return PesquisarABP(T->Direita, X);
  else
    return PesquisarABP(T->Esquerda, X);
}

void ABPEqInsercaoBinaria (PNodoAB *TE, LIVRO L[], int inicio, int fim){
  int  meio;
  if (inicio > fim)
    return ;
  if (inicio == fim){
    *TE = InserirABP(*TE, L[inicio]);
    return;
  }
  
  meio = (inicio + fim) / 2;
  *TE = InserirABP(*TE, L[meio]);
  ABPEqInsercaoBinaria(TE, L, inicio, meio-1);
  ABPEqInsercaoBinaria(TE, L, meio+1, fim);
  
}

void CriarSequenciaEmOrdem (PNodoAB T, LIVRO L[], int *N){
  if (T != NULL){
    CriarSequenciaEmOrdem(T->Esquerda, L, N);
    L[*N] = T->Elemento;
    *N = (*N) + 1;
    CriarSequenciaEmOrdem(T->Direita, L, N);
  }
}

PNodoAB CriarABPEquilibradaIB (PNodoAB T){
  LIVRO *Lista;
  PNodoAB TE;
  int  N = 0, Num;
  TE = CriarAB();
  Num = NumeroNodosAB(T);
  if (T == NULL)
    return NULL;
  Lista = (LIVRO *) memalloc(Num * sizeof(LIVRO));
  if (Lista == NULL)
    return NULL;
  CriarSequenciaEmOrdem(T, Lista, &N);
  ABPEqInsercaoBinaria(&TE, Lista, 0, N-1);
  return TE;
}

PNodoAB LibertarNodoAB(PNodoAB P){
  P->Esquerda = NULL;
  P->Direita = NULL;
  clnmem(P);
  P = NULL;
  return P;
}

PNodoAB RemoverNodoABP (PNodoAB T){
  PNodoAB  R;
  LIVRO  X;
  if (T->Esquerda == NULL && T->Direita == NULL) {   // T � uma folha
    T = LibertarNodoAB(T);
    return T;
  }
  if (T->Esquerda == NULL) {   //  s� um filho direito 
    R = T;
    T = T->Direita;
    R = LibertarNodoAB(R);
    return T;
  }
  if (T->Direita == NULL) {     // s� um filho esquerdo
    R = T;
    T = T->Esquerda;
    R = LibertarNodoAB(R);
    return T;
  }
  // 2 filhos (1� caso): remover o nodo sucessor (nodo mais � esquerda da sub�rvore direita) e copiar a sua informa��o
  T->Direita = SubstituirNodoDireita(T->Direita, &X);
  // 2 filhos (2� caso): remover o nodo antecessor (nodo mais � direita da sub�rvore esquerda) e copiar a sua informa��o
  //  T->Esquerda = SubstituirNodoEsquerda(T->Esquerda, &X);  // 2� caso
  T->Elemento = X;
  return T;
}

PNodoAB RemoverABP (PNodoAB T, LIVRO X) {
  if (CompareBooks(X, T->Elemento) == 0) {
    T = RemoverNodoABP(T);
    return T;
  }
  if (CompareBooks(X, T->Elemento) == -1)
    T->Esquerda = RemoverABP(T->Esquerda, X);
  else
    T->Direita = RemoverABP(T->Direita, X);
  return T;
}

int AlturaAB (PNodoAB T) {
  int  e, d;
  if (T == NULL)
    return -1;
  e = AlturaAB(T->Esquerda);
  d = AlturaAB(T->Direita);
  if (e > d)
    return (e + 1);  // e (altura da esquerda), 1 a raiz
  else
    return (d + 1);  // d (altura da direita), 1 a raiz
}

int verificarEquilibrio(PNodoAB T){
    int e, d;

    e = AlturaAB(T->Esquerda);
    d = AlturaAB(T->Direita);
    if(abs(e-d) > 1){
        return 0;
    }

    if(T->Esquerda != NULL && verificarEquilibrio(T->Esquerda) == 0){
        return 0;
    }
    if(T->Direita != NULL && verificarEquilibrio(T->Direita) == 0){
        return 0;
    }
    return 1;
}

PNodoAB SubstituirNodoDireita (PNodoAB T, LIVRO *X){
  PNodoAB  PAux;
  if (T->Esquerda == NULL) {
    *X = T->Elemento;
    PAux = T;
    T = T->Direita;
    PAux = LibertarNodoAB(PAux);
    return T;
  }
  T->Esquerda = SubstituirNodoDireita(T->Esquerda, X);
  return T;
}

void PesquisarABPISBN(PNodoAB T, long int ISBN){ 
  if (T == NULL)
    return;
  if (CompareBooksISBN(T->Elemento, ISBN) == 0)
    showBook(T->Elemento);
  if (CompareBooksISBN(T->Elemento, ISBN)==-1)   
    PesquisarABPISBN(T->Direita, ISBN);
  else
    PesquisarABPISBN(T->Esquerda, ISBN);
}

void PesquisarABPTitle(PNodoAB T, char title[100]){
  if (T == NULL)
    return;
  if (CompareBooksTitle(T->Elemento, title) == 0)
    showBook(T->Elemento);   
  
  PesquisarABPTitle(T->Esquerda, title);
  PesquisarABPTitle(T->Direita, title);
  
}

void PesquisarABPAuthorYear(PNodoAB T, char firstAuthor[100], int yearPublish){
  if (T == NULL)
    return;
  if (CompareBooksFirstAuthorYear(T->Elemento,firstAuthor,yearPublish)==0)
    showBook(T->Elemento); 
    
  PesquisarABPAuthorYear(T->Esquerda, firstAuthor, yearPublish);
  PesquisarABPAuthorYear(T->Direita, firstAuthor, yearPublish);
}

void PesquisarABPEditorCientificArea(PNodoAB T, char editor[100], char cientificArea[100]){
  if (T == NULL)
    return;
  if (CompareBooksEditorCientificArea(T->Elemento,editor,cientificArea)==0)
    showBook(T->Elemento); 
    
  PesquisarABPEditorCientificArea(T->Esquerda, editor, cientificArea);
  PesquisarABPEditorCientificArea(T->Direita, editor, cientificArea);
}

PNodoAB changeBookISBN(PNodoAB P, PNodoAB T, long int ISBN){
  if (T == NULL)
    return P;
  if (CompareBooksISBN(T->Elemento, ISBN) == 0){
    LIVRO X = createBook();
    while(PesquisarABP(P,X)==1){
      bookAlreadyExistsWarning();
      X=createBook();  
    }
    
    P=RemoverNodoABP(T);
    P=InserirABP(P,X);
    if(verificarEquilibrio(P)==0){
      P=CriarABPEquilibradaIB(P);
    }
    return P;
  }

  if (CompareBooksISBN(T->Elemento, ISBN)==-1)   
    return changeBookISBN(P,T->Direita, ISBN);
  else
    return changeBookISBN(P,T->Esquerda, ISBN);
}

PNodoAB removeBook(PNodoAB T, long int ISBN){
  LIVRO X;
  X.ISBN=ISBN;
  if(PesquisarABP(T,X)!=1){
    unregisteredBookWarning();
    return T;
  }
  T=RemoverABP(T,X);
  bookRemovedWarning();
  if(verificarEquilibrio(T)==0){
    T=CriarABPEquilibradaIB(T);
  }
  return T;
}

int seeMostRecentDate(PNodoAB T, char cientificArea[100]){
  int esq=0,dir=0, maior=0;
  if (T == NULL)
    return 0;
  if (strcmp(cientificArea, T->Elemento.cientificArea) == 0)
    maior=T->Elemento.yearPublish;  
    
  esq=seeMostRecentDate(T->Esquerda, cientificArea);
  dir=seeMostRecentDate(T->Direita, cientificArea);
  
  
  if(maior < esq){
    maior=esq;
  }
  if(maior < dir){
    maior = dir;
  }
  return maior;
}

//K _FEITO AQUI
void showRecentBooksCientificArea(PNodoAB P, int year, char cientificArea[100], int k){
  if (P == NULL)
    return;

  if (k>0 && strcmp(cientificArea, P->Elemento.cientificArea) == 0 && year==(P->Elemento.yearPublish)){
    showBook(P->Elemento);
    k--;
  }
  showRecentBooksCientificArea(P->Esquerda, year, cientificArea, k);
  showRecentBooksCientificArea(P->Direita, year, cientificArea,k);
}

void verifyIfExistsCientificArea(LIVRO X)
{
  bool exists=false;
  for(int i=0;i<num_cientific_qtd;i++)
  {
    if(strcmp(X.cientificArea, cientific_qtd[i].cientificArea)==0)
    {
      printf("---- %s\n", cientific_qtd[i].cientificArea);
      cientific_qtd[i].qtd++;
      printf("-----%d\n", cientific_qtd[i].qtd);
      exists=true;
      break;
    }
  }
  if(!exists)
  {
    num_cientific_qtd++;
    cientific_qtd=memrealloc(cientific_qtd, num_cientific_qtd*sizeof(CIENTIFIC_QTD));
    strcpy(cientific_qtd[num_cientific_qtd-1].cientificArea, X.cientificArea);
    cientific_qtd[num_cientific_qtd-1].qtd=1;
    printf("****%s\n", cientific_qtd[num_cientific_qtd-1].cientificArea);
    printf("****%d\n", cientific_qtd[num_cientific_qtd-1].qtd);
  }
}

void verifyIfExistsYear(LIVRO X){
  bool exists=false;
  for(int i=0;i<num_publish_year;i++)
  {
    if(X.yearPublish==publish_year[i].year)
    {
      exists=true;
      publish_year[i].qtd++;
      break;
    }
  }
  if(!exists)
  {
    num_publish_year++;
    publish_year=memrealloc(publish_year, num_publish_year*sizeof(PUBLISH_YEAR));
    publish_year[num_publish_year-1].year=X.yearPublish;
    publish_year[num_publish_year-1].qtd=1;
 }
}

void cientificAreaAndYearWithMoreBooks(PNodoAB T, int option){
  if(T==NULL)
  {
    return;
  }
  
  switch (option)
  {
    case 1:
      verifyIfExistsCientificArea(T->Elemento);
      break;
    case 2:
      verifyIfExistsYear(T->Elemento);
      break;
    default:
      printf("ERROR!\n");
  }
  

  cientificAreaAndYearWithMoreBooks(T->Esquerda, option);
  cientificAreaAndYearWithMoreBooks(T->Direita, option);
}

void showCientificAreaWithMoreBooks(void){
  int maior=0;
  char cientificArea[100];
  for(int i=0;i<num_cientific_qtd;i++){
    if(cientific_qtd[i].qtd > maior){
      maior=cientific_qtd[i].qtd;
      strcpy(cientificArea, cientific_qtd[i].cientificArea);
    }
  }

  printf("===============================================\n");
  printf("                                               \n");
  printf(" Cientific Area with More Books: %s            \n", cientificArea);
  printf("                                               \n");
  printf("===============================================\n");
}

void showYearWithMorePublications(void){
  int year=0;
  int qtd=0;
  for(int i=0;i<num_publish_year;i++){
    if(publish_year[i].qtd > qtd){
      year=publish_year[i].year;
      qtd=publish_year[i].qtd;
    }
  }

  printf("=========================================\n");
  printf("                                         \n");
  printf("   Year with more publications: %d       \n", year);
  printf("                                         \n");
  printf("=========================================\n");

  
}


PNodoAB insertBook(PNodoAB T){
  if(T==NULL){
    T=CriarAB();
    LIVRO X = createBook();
    T=InserirABP(T,X);
  }else{
    LIVRO x = createBook();
    while(PesquisarABP(T, x)==1){
      bookAlreadyExistsWarning();
      x=createBook();
    }
    T=InserirABP(T, x);
    if(verificarEquilibrio(T)!=1){
      T=CriarABPEquilibradaIB(T);
    }
  }
  return T;
}

void showALL(PNodoAB T){
  if(T==NULL){
    return;
  }
  
  showBook(T->Elemento);

  showALL(T->Esquerda);
  
  showALL(T->Direita);
}