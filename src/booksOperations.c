//global includes
#include<stdio.h>
#include<stdlib.h>
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

/**
 * create the binary tree
 * @return the tree root
 */
PNodoAB CriarAB(void){ 
  PNodoAB T;
  T = NULL;
  return T;
}

/**
 * Creates a node with a book
 * @param X book
 * @return node of that book
 */
PNodoAB CriarNodoAB(LIVRO X){
  PNodoAB P = (PNodoAB) memalloc(sizeof(struct NodoAB));
  if (P == NULL)
    return  NULL;
  P->Elemento = X;
  P->Esquerda = NULL;
  P->Direita = NULL;
  return P;
}

/**
 * Count the nodes of a binary tree
 * @param T the binary tree
 * @return the number of nodes
 */
int NumeroNodosAB (PNodoAB T) {
  int  e, d;
  if (T == NULL)
    return 0;
  e = NumeroNodosAB(T->Esquerda);
  d = NumeroNodosAB(T->Direita);
  return (e + d + 1);
}

/**
 * Insert a book in a binary tree
 * @param T binary tree with the books
 * @param X the book to be inserted
 * @return the tree with a new book
 */
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

/**
 * Search in the binary tree
 * @param T binary tree with the books
 * @param X the book to search
 * @return 1 if the book exists on the tree or 0 otherwise
 */
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

/**
 * Function to balance a tree from a list
 * @param TE the tree
 * @param L list of books
 * @param inicio index of the top of the list
 * @param fim end of list index
 */
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

/**
 * Function to create the sequence of elements of a tree
 * @param T tree of books
 * @param L array of type books
 * @param N number of elements
 */
void CriarSequenciaEmOrdem (PNodoAB T, LIVRO L[], int *N){
  if (T != NULL){
    CriarSequenciaEmOrdem(T->Esquerda, L, N);
    L[*N] = T->Elemento;
    *N = (*N) + 1;
    CriarSequenciaEmOrdem(T->Direita, L, N);
  }
}

/**
 * Create a balanced search tree
 * @param T the tree of books
 * @return the binary tree balanced
 */
PNodoAB CriarABPEquilibradaIB (PNodoAB T){
  LIVRO *Lista;
  PNodoAB TE;
  int  N = 0, Num;
  TE = CriarAB();
  Num = NumeroNodosAB(T);
  if (T == NULL)
    return NULL;
  Lista = (LIVRO *)malloc(Num * sizeof(LIVRO));
  if (Lista == NULL)
    return NULL;
  CriarSequenciaEmOrdem(T, Lista, &N);
  ABPEqInsercaoBinaria(&TE, Lista, 0, N-1);
  clnmem(Lista);
  return TE;
}

/**
 * Free a node from memory
 * @param T tree
 * @return the node free from memory 
 */
PNodoAB LibertarNodoAB(PNodoAB T){
  T->Esquerda = NULL;
  T->Direita = NULL;
  free(T);
  T = NULL;
  return T;
}

/**
 * Destroys a tree from memory
 * @param T tree of books
 * @return the tree destroyed
 */
PNodoAB DestruirAB(PNodoAB T){
  if (T == NULL) 
    return NULL;
  T->Esquerda = DestruirAB(T->Esquerda);
  T->Direita = DestruirAB(T->Direita);
  return LibertarNodoAB(T);
}

/**
 * Change the information of a node to be removed with information from his successor
 * @param T pointer to the node to be removed
 * @param X element to be removed
 * @return pointer to the first element of the tree and the element removed
 */
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

/**
 * Remove a node from the search tree
 * @param T tree
 * @return tree without that node
 */
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
  T->Elemento = X;
  return T;
}

/**
 * Remove a book from a tree
 * @param T the book's tree
 * @param X the book to be removed
 * @return the tree without the book
 */
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

/**
 * Determines the height of the tree
 * @param T the book's tree
 * @return the height of the tree
 */
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

/**
 * Verify if a tree is balanced or not 
 * @param T the book's tree
 * @return 0 if thr tree isn't balanced or 1 otherwise
 */
int verificarEquilibrio(PNodoAB T){
  int e, d;

  if(T==NULL){
    return 1;
  }
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

/**
 * Search in the tree for a book with a specified ISBN and show the book.
 * @param T the book tree
 * @param ISBN the ISBN of the book to be found
 */
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

/**
 * Search in the tree for a book with a specified part of a title and show the book.
 * @param T the book tree
 * @param title the parte of the title to be found
 */
void PesquisarABPTitle(PNodoAB T, char title[100]){
  if (T == NULL)
    return;
  if (CompareBooksTitle(T->Elemento, title) == 0)
    showBook(T->Elemento);   
  
  PesquisarABPTitle(T->Esquerda, title);
  PesquisarABPTitle(T->Direita, title);
  
}

/**
 * Search in the tree for a book with a specified first author and publication year. When found the book is shown
 * @param T the book tree
 * @param firstAuthor the first author
 * @param yearPublish the publication year
 */
void PesquisarABPAuthorYear(PNodoAB T, char firstAuthor[100], int yearPublish){
  if (T == NULL)
    return;
  if (CompareBooksFirstAuthorYear(T->Elemento,firstAuthor,yearPublish)==0)
    showBook(T->Elemento); 
    
  PesquisarABPAuthorYear(T->Esquerda, firstAuthor, yearPublish);
  PesquisarABPAuthorYear(T->Direita, firstAuthor, yearPublish);
}

/**
 * Search in the tree for a book with a specified editor and cientificArea. When found the book is shown
 * @param T the book tree
 * @param editor the editor
 * @param cientificArea the Cientific Area
 */
void PesquisarABPEditorCientificArea(PNodoAB T, char editor[100], char cientificArea[100]){
  if (T == NULL)
    return;
  if (CompareBooksEditorCientificArea(T->Elemento,editor,cientificArea)==0)
    showBook(T->Elemento); 
    
  PesquisarABPEditorCientificArea(T->Esquerda, editor, cientificArea);
  PesquisarABPEditorCientificArea(T->Direita, editor, cientificArea);
}

/**
 * Change a book with a specified ISBN. When the book is found the user can change all book informations
 * @param T the book tree used to scroll throught the tree
 * @param ISBN the specified ISBN
 * @return the tree updated
 */
PNodoAB changeBookISBN(PNodoAB P,long int ISBN){
  if (P == NULL)
    return P;
  if (CompareBooksISBN(P->Elemento, ISBN) == 0){
    LIVRO X = createBook();
    if(X.ISBN==-1){
      return P;
    }
    while(X.ISBN!=ISBN && PesquisarABP(P,X)==1){
      bookAlreadyExistsWarning();
      X=createBook();
      if(X.ISBN==-1){
        return P;
      }  
    }
    
    P=RemoverNodoABP(P);
    P=InserirABP(P,X);
    
    if(verificarEquilibrio(P)==0){
      P=CriarABPEquilibradaIB(P);
    }
    return P;
  }

  if (CompareBooksISBN(P->Elemento, ISBN)==-1)   
    return changeBookISBN(P->Direita, ISBN);
  else
    return changeBookISBN(P->Esquerda, ISBN);
}

/**
 * Remove a book with a specified ISBN
 * @param T the book's tree
 * @param ISBN the specified ISBN
 * @return Return the book's tree updated
 */
PNodoAB removeBook(PNodoAB T, long int ISBN){
  LIVRO X;
  X.ISBN=ISBN;
  if(PesquisarABP(T,X)!=1){
    unregisteredBookWarning();
    return T;
  }
  T=RemoverABP(T,X);
  bookRemovedWarning();
  if(T!=NULL){
    if(verificarEquilibrio(T)==0){
      T=CriarABPEquilibradaIB(T);
    }
  }
  
  return T;
}

/**
 * Verify if a specified cientific Area exists. If it didn't exists we put a new cientific area to the struct CIENTIFIC_QTD. if exists we increase the quantity.
 * @param X the book to see 
 */
void verifyIfExistsCientificArea(LIVRO X)
{
  bool exists=false;
  for(int i=0;i<num_cientific_qtd;i++)
  {
    if(strcmp(X.cientificArea, cientific_qtd[i].cientificArea)==0)
    {
      cientific_qtd[i].qtd++;
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
  }
}

/**
 * Verify if a specified year exists. If it didn't exists we put a new year to the struct PUBLISH_YEAR. if exists we increase the quantity.
 * @param X the book to see 
 */
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

/**
 * if the option is one we verify if a cientific area already exists in the struct CIENTIFIC_QTD.
 * if the option is two we verify if a year already exists in the struct PUBLISH_YEAR
 * @param T the book's tree
 * @param option indicates which function we have to do 
 */
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

/**
 * Check which cientific area has the most books and print in the screen 
 */
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

/**
 * Check which year has more publications and print in the screen 
 */
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

/**
 * Insert a bookto the book´s tree. After put in the tree check if the tree is balanced
 * @param T the book's tree
 * @return the book's tree updated
 */
PNodoAB insertBook(PNodoAB T){
  LIVRO X;

  if(T==NULL){
    X = createBook();
    if(X.ISBN==-1){
      return T;
    }
    T=InserirABP(T,X);
    return T;
  }

  X = createBook();
  if(X.ISBN==-1){
      return T;
  }
  while(PesquisarABP(T, X)==1){
    bookAlreadyExistsWarning();
    X=createBook();
    if(X.ISBN==-1){
      return T;
    }
  }

  T=InserirABP(T, X);
 
  if(verificarEquilibrio(T)==0){
    T=CriarABPEquilibradaIB(T);
  }
  
  return T;
}

/**
 * Show all the books
 * @param T the book's tree
 */
void showALL(PNodoAB T){
  if(T==NULL){
    return;
  }
  
  showBook(T->Elemento);

  showALL(T->Esquerda);
  
  showALL(T->Direita);
}

/**
 * Put in an array the books of a specific cientific area.
 * @param T Tree that contains the book's
 * @param cientificArea Cientific area of a book
 * @param list array that contains the books of a specific cientific area
 * @param contrl control variable to determine how many books have been inserted
 */
void putInArray(PNodoAB T,char *cientificArea,LIVRO *list,int *control){  
  if(T==NULL){
    return;
  }

  if(strcmp(cientificArea, T->Elemento.cientificArea)==0){
    list[(*control)]=T->Elemento;
    *control=*control+1;
  }
  putInArray(T->Esquerda, cientificArea,list, control);
  putInArray(T->Direita, cientificArea, list, control);

}

/**
 * Determine the k most recent books of a cientific area
 * @param T tree of books
 */
void showMostRecentCientificArea(PNodoAB T){
  int tamListbooks=0, k;
  LIVRO aux;
  LIVRO *list;
  char cientificArea[100];
  
  printf("How many books? ");
  scanf("%d", &k);
  printf("Cientific Area: ");
  scanf("\n%[^\n]s",cientificArea);

  list=memalloc(NumeroNodosAB(T)*sizeof(LIVRO));
  putInArray(T,cientificArea,list,&tamListbooks);

  if(tamListbooks==0){
    //if the cientific area didn't have a book, a warning message appears
    cientificAreaWarning();
    free(list);
    return;
  }
  //sorts the array in decreasing order
  for (int i = 0; i < tamListbooks; i++) 
  {
    for (int j = i + 1; j < tamListbooks; j++)
    {
      if (list[i].yearPublish < list[j].yearPublish) 
      {
        aux =  list[i];
        list[i] = list[j];
        list[j] = aux;
       }
 
    }
  }

  if(k!=tamListbooks){
    if(k < tamListbooks){
      list=memrealloc(list, k*sizeof(LIVRO));
    }else{
      k=tamListbooks;
    }
  }

  //Show the k recent books
  for(int i=0;i<k;i++){
    showBook(list[i]);
  }
  free(list);
}

/**
 * get the quantity of a book
 * @param T the book's tree
 * @param ISBN the identifier of the book
 * @return the book quantity
 */
int getBookQuantity(PNodoAB T, long int ISBN){
  int esq=0,dir=0;
  if(T==NULL){
    return 0;
  }
  if(T->Elemento.ISBN==ISBN){
    return T->Elemento.qtdStock;
  }else if(CompareBooksISBN(T->Elemento,ISBN)==-1){
    esq=getBookQuantity(T->Direita,ISBN);
  }else{
    dir=getBookQuantity(T->Esquerda,ISBN);
  }
  if(esq>0){
    return esq;
  }else{
    return dir;
  }
}

/**
 * set the quantity of a book
 * @param T the book's tree
 * @param ISBN the identifier of the book
 * @param qtd the quantity to be removed from that book
 */
void setBookQuantity(PNodoAB T, long int ISBN, int qtd){
  if(T==NULL){
    return;
  }
  if(CompareBooksISBN(T->Elemento,ISBN)==0){
    T->Elemento.qtdStock=T->Elemento.qtdStock-qtd;
  }else if(CompareBooksISBN(T->Elemento,ISBN)==-1){
    setBookQuantity(T->Direita, ISBN, qtd);
  }else{
    setBookQuantity(T->Esquerda, ISBN, qtd);
  }
}


/**
 * get the book price
 * @param T the book's tree
 * @param ISBN the identifier of the book
 * @return the price
 */
float getBookPrice(PNodoAB T, long int ISBN){
  float esq=0, dir=0;
  if(T==NULL){
    return 0;
  }
  if(CompareBooksISBN(T->Elemento,ISBN)==0){
    return T->Elemento.price;
  }else if(CompareBooksISBN(T->Elemento,ISBN)==-1){
    dir=getBookPrice(T->Direita, ISBN);
  }else{
    esq=getBookPrice(T->Esquerda, ISBN);
  }
  if(esq>0){
    return esq;
  }else{
    return dir;
  }
}

/**
 * get the most expensive book
 * @param T the book's tree
 * @return the book
 */
LIVRO getMostExpensiveBook(PNodoAB T){
  LIVRO greater, esq, dir;
  greater.ISBN=-1;
  if(T==NULL){
    return greater;
  }
  greater=T->Elemento;
  esq=getMostExpensiveBook(T->Esquerda);
  dir=getMostExpensiveBook(T->Direita);
  
  
  if(greater.price < esq.price){
    greater=esq;
  }
  if(greater.price < dir.price){
    greater = dir;
  }
  return greater;
}

/**
 * get the total stock and the stock value at the moment
 * @param T the book's tree
 * @param totalStock pointer to the total stock
 * @param stockValue pointer to the value of the stock
 */
void getTotalStockandStockValue(PNodoAB T, int *totalStock, float *stockValue){
  if(T==NULL){
    return;
  }
  *totalStock=*totalStock + T->Elemento.qtdStock;
  *stockValue=*stockValue + (T->Elemento.price * T->Elemento.qtdStock);

  getTotalStockandStockValue(T->Esquerda, totalStock, stockValue);
  getTotalStockandStockValue(T->Direita, totalStock, stockValue);
}

/**
 * Restock the book
 * @param T the book's tree
 * @param ISBN the specified ISBN
 * @param qtd the quantity to add to the stock 
 */
void restockBook(PNodoAB T, long int ISBN, int qtd){
  if(T==NULL){
    return;
  }

  if(CompareBooksISBN(T->Elemento, ISBN) == 0 ){
    T->Elemento.qtdStock = T->Elemento.qtdStock + qtd;
  }else if(CompareBooksISBN(T->Elemento, ISBN)==-1){
    restockBook(T->Direita, ISBN, qtd);
  }else{
    restockBook(T->Direita, ISBN, qtd);
  }
}