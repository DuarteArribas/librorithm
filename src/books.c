//global includes
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
//project includes
#include"books.h"


LIVRO createBook(void){
    LIVRO book;
    printf("ISBN: ");
    scanf("%ld", &book.ISBN);
    while(book.ISBN<1000000000000 || book.ISBN>9999999999999){
      printf("Wrong ISBN (Insert again): ");
      scanf("%ld", &book.ISBN);
    }
    printf("Title: ");
    scanf("\n%[^\n]s",book.title);
    printf("Language: ");
    scanf("\n%[^\n]s",book.language);
    printf("First Author: ");
    scanf("\n%[^\n]s",book.firstAuthor);
    printf("Second Author: ");
    scanf("\n%[^\n]s",book.secondAuthor);
    printf("Editor: ");
    scanf("\n%[^\n]s",book.editor);
    printf("Year of publish: ");
    scanf("%d", &book.yearPublish);
    printf("Cientific Area: ");
    scanf("\n%[^\n]s",book.cientificArea);
    printf("Price: ");
    scanf("%f", &book.price);
    printf("Stock Quantity: ");
    scanf("%d", &book.qtdStock);
    return book;
}

void showBook(LIVRO book){
  printf("================ Book ==================\n");
  printf("                                        \n");
  printf("   ISBN:           %ld                  \n", book.ISBN);
  printf("   Title:          %s                   \n", book.title);
  printf("   Language:       %s                   \n", book.language);
  printf("   First Author:   %s                   \n", book.firstAuthor);
  printf("   Second Author:  %s                   \n", book.secondAuthor);
  printf("   Editor:         %s                   \n", book.editor);
  printf("   Year Publish:   %d                   \n", book.yearPublish);
  printf("   Cientific Area: %s                   \n", book.cientificArea);
  printf("   Price:          %.2f                   \n", book.price);
  printf("   Stock Quantity: %d                   \n", book.qtdStock);
  printf("                                        \n");  
  printf("========================================\n");
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
int  CompareBooksISBN (LIVRO X, long int ISBN){  
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

void bookAlreadyExistsWarning(void){
  printf("========================================\n"); 
  printf("|                                      |\n");
  printf("| Book Already Exists. Insert Another: |\n");
  printf("|                                      |\n");
  printf("========================================\n"); 
}

void bookRemovedWarning(void){
  printf("========================================\n"); 
  printf("|                                      |\n");
  printf("|       Book Successfully Removed      |\n");
  printf("|                                      |\n");
  printf("========================================\n"); 
}

void unregisteredBookWarning(void){
  printf("========================================\n"); 
  printf("|                                      |\n");
  printf("|          Unregistered Book           |\n");
  printf("|                                      |\n");
  printf("========================================\n"); 
}
