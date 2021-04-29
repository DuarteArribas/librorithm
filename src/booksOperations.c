//global includes
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
//project includes
#include"booksOperations.h"
#include"books.h"

PNodoAB CriarAB(void){ 
  PNodoAB T;
  T = NULL;
  return T;
}

PNodoAB CriarNodoAB(LIVRO X){
  PNodoAB P = (PNodoAB) malloc(sizeof(struct NodoAB));
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
    return PesquisarABP(T->Esquerda, X);
  else
    return PesquisarABP(T->Direita, X);
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
  Lista = (LIVRO *) malloc(Num * sizeof(LIVRO));
  if (Lista == NULL)
    return NULL;
  CriarSequenciaEmOrdem(T, Lista, &N);
  ABPEqInsercaoBinaria(&TE, Lista, 0, N-1);
  return TE;
}

PNodoAB LibertarNodoAB(PNodoAB P){
  P->Esquerda = NULL;
  P->Direita = NULL;
  free(P);
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

void PesquisarABPISBN(PNodoAB T, int ISBN){ 
  if (T == NULL)
    return;
  if (CompareBooksISBN(T->Elemento, ISBN) == 0)
    showBook(T->Elemento);
  if (CompareBooksISBN(T->Elemento, ISBN)==-1)   
    PesquisarABPISBN(T->Esquerda, ISBN);
  else
    PesquisarABPISBN(T->Direita, ISBN);
}

void PesquisarABPTitulo(PNodoAB T, char titulo[100]){
  if (T == NULL)
    return;
  if (CompareBooksTitle(T->Elemento, titulo) == 0)
    showBook(T->Elemento);   
  
  PesquisarABPTitulo(T->Esquerda, titulo);
  PesquisarABPTitulo(T->Direita, titulo);
  
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

PNodoAB ChangeBookISBN(PNodoAB P, PNodoAB T, int ISBN){
  if (T == NULL)
    return P;
  if (CompareBooksISBN(T->Elemento, ISBN) == 0){
    LIVRO X = createBook();
    while(PesquisarABP(P,X)!=1){
      printf("Livro já existente introduza outro\n");
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
    return ChangeBookISBN(P,T->Esquerda, ISBN);
  else
    return ChangeBookISBN(P,T->Direita, ISBN);
}

PNodoAB RemoveBook(PNodoAB T, LIVRO X){
  if(PesquisarABP(T,X)!=1){
    printf("Livro não registado!\n");
    return T;
  }

  T=RemoverABP(T,X);
  if(verificarEquilibrio(T)==0){
    T=CriarABPEquilibradaIB(T);
  }
  return T;
}

int seeMostRecentDate(PNodoAB T, char cientificArea[100]){
  int esq,dir;
  if (T == NULL)
    return 0;
  if (strcmp(cientificArea, T->Elemento.cientificArea) == 1)
    return T->Elemento.yearPublish;  

  esq=seeMostRecentDate(T->Esquerda, cientificArea);
  dir=seeMostRecentDate(T->Direita, cientificArea);
  
  if(esq>dir){
    return esq;
  }else{
    return dir;
  }
}

void showRecentBooksCientificArea(PNodoAB P, PNodoAB T, char cientificArea[100], int k){
  int year=seeMostRecentDate(P,cientificArea);

  if (T == NULL)
    return;
  if (k>0 && strcmp(cientificArea, T->Elemento.cientificArea) == 0 && year==T->Elemento.yearPublish){
    showBook(T->Elemento);
    k--;
  }
  showRecentBooksCientificArea(P,T->Esquerda, cientificArea, k);
  showRecentBooksCientificArea(P,T->Direita, cientificArea,k);
}

void verifyIfExists(LIVRO X, CIENTIFIC_QTD **cientific_qtd, int *num_cientific_qtd){
  if(*num_cientific_qtd == 0){
    return;
  }
  for(int i=0;i<*num_cientific_qtd;i++){
    if(strcmp(X.cientificArea, (*cientific_qtd)[i].cientificArea)==0){
      (* cientific_qtd)[*num_cientific_qtd-1].qtd++;
    }
    if(strcmp(X.cientificArea, (*cientific_qtd)[i].cientificArea)!=0){
      (*num_cientific_qtd)++;
      (*cientific_qtd)=realloc((*cientific_qtd), (*num_cientific_qtd)*sizeof(CIENTIFIC_QTD));
      strcpy((* cientific_qtd)[*num_cientific_qtd-1].cientificArea, X.cientificArea);
      (* cientific_qtd)[*num_cientific_qtd-1].qtd=1;
    }
  }
}

void cientificAreaWithMoreBooks(PNodoAB T, CIENTIFIC_QTD **cientific_qtd, int *num_cientific_qtd){
  if(T==NULL){
    return;
  }

  //É assim que passo para a função?? o cientific_qtd
  verifyIfExists(T->Elemento, cientific_qtd, num_cientific_qtd);
  cientificAreaWithMoreBooks(T->Esquerda, cientific_qtd, num_cientific_qtd);
  cientificAreaWithMoreBooks(T->Direita, cientific_qtd, num_cientific_qtd);

  int maior=0;
  char cientificArea[100];
  for(int i=0;i<*num_cientific_qtd;i++){
    if(cientific_qtd[i]->qtd > maior){
      maior=cientific_qtd[i]->qtd;
      strcpy(cientificArea, cientific_qtd[i]->cientificArea);
    }
  }

  printf("Area científica com mais livres: %s", cientificArea);
}