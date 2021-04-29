//global includes
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
//project includes
#include"books.h"


LIVRO createBook(void){
    LIVRO book;
    printf("ISBN: \n");
    scanf("%d", &book.ISBN);
    printf("Title: \n");
    scanf("\n%[^\n]s",book.title);
    printf("Language: \n");
    scanf("\n%[^\n]s",book.language);
    printf("First Author: \n");
    scanf("\n%[^\n]s",book.firstAuthor);
    printf("Second Author: \n");
    fgets(book.secondAuthor, 100, stdin);
    printf("Editor: \n");
    fgets(book.editor, 100, stdin);
    printf("Year of publish: \n");
    scanf("%d", &book.yearPublish);
    printf("Cientific Area: \n");
    fgets(book.cientificArea, 100, stdin);
    printf("Price: \n");
    scanf("%f", &book.price);
    printf("Stock Quantity: \n");
    scanf("%d", &book.qtdStock);
    return book;
}

void showBook(LIVRO book){
    printf("ISBN: %d\n", book.ISBN);
    printf("Title: %s\n", book.title);
    printf("Language: %s\n", book.language);
    printf("First Author: %s\n", book.firstAuthor);
    printf("Second Author: %s\n", book.secondAuthor);
    printf("Editor: %s\n", book.editor);
    printf("Year of publish: %d\n", book.yearPublish);
    printf("Cientific Area: %s\n", book.cientificArea);
    printf("Price: %f\n", book.price);
    printf("Stock Quantity: %d\n", book.qtdStock);
}

int  CompareBooks (LIVRO X, LIVRO Y){  
  if (X.ISBN > Y.ISBN)
    return 1;
  if (X.ISBN < Y.ISBN)
    return -1;
  return 0;
}

/*
* Devolve 0 caso sejam iguais
*/
int  CompareBooksISBN (LIVRO X, int ISBN){  
  if (X.ISBN > ISBN)
    return 1;
  if (X.ISBN < ISBN)
    return -1;
  return 0;
}

int  CompareBooksTitle (LIVRO X, char * title){  
  if (strstr(X.title, title)==NULL)
    return 1;
  return 0;
}

int  CompareBooksFirstAuthorYear (LIVRO X, char firstAuthor[100], int yearPublish){  
  if (strcmp(X.firstAuthor, firstAuthor)==0 && X.yearPublish==yearPublish){
    return 0;
  }
  return 1;
}

int CompareBooksEditorCientificArea(LIVRO X,char editor[100], char cientificArea[100]){
  if(strcmp(X.editor,editor)==0 && strcmp(X.cientificArea,cientificArea)==0){
    return 0;
  }
  return 1;
}


