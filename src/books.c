//global includes
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<ctype.h>
//project includes
#include"books.h"
#include"librorithm.h"


LIVRO createBook(void){
    LIVRO book;
    while(true){
      if(!getISBN(&book.ISBN)){
        fprintf(stderr,"\tACTION CANCELED: No BOOK was added!\n");
        return (LIVRO){.ISBN=-1};
      }else{
        break;
      }
    }
    printf("     What's the Title? (0 to CANCEL) : ");
    scanf("\n%[^\n]s",book.title);
    if(strcmp(book.title, "0")==0){
      fprintf(stderr,"\tACTION CANCELED: No BOOK was added!\n");
      return (LIVRO){.ISBN=-1};
    }
    printf("     What's the Language? (0 to CANCEL) : ");
    scanf("\n%[^\n]s",book.language);
    if(strcmp(book.language, "0")==0){
      fprintf(stderr,"\tACTION CANCELED: No BOOK was added!\n");
      return (LIVRO){.ISBN=-1};
    }
    printf("     What's the First Author? (0 to CANCEL) : ");
    scanf("\n%[^\n]s",book.firstAuthor);
    if(strcmp(book.firstAuthor, "0")==0){
      fprintf(stderr,"\tACTION CANCELED: No BOOK was added!\n");
      return (LIVRO){.ISBN=-1};
    }
    printf("     What's the Second Author? (NULL if it doesn't exist) (0 to CANCEL) : ");
    scanf("\n%[^\n]s",book.secondAuthor);
    if(strcmp(book.secondAuthor, "0")==0){
      fprintf(stderr,"\tACTION CANCELED: No BOOK was added!\n");
      return (LIVRO){.ISBN=-1};
    }
    printf("     What's the Editor? (0 to CANCEL) : ");
    scanf("\n%[^\n]s",book.editor);
    if(strcmp(book.editor, "0")==0){
      fprintf(stderr,"\tACTION CANCELED: No BOOK was added!\n");
      return (LIVRO){.ISBN=-1};
    }
    getchar();
    while(true){
      if(!getPublicationYear(&book.yearPublish)){
        fprintf(stderr,"\tACTION CANCELED: No BOOK was added!\n");
        return (LIVRO){.ISBN=-1};
      }else{
        break;
      }
    }
    while(true){
      if(!getPrice(&book.price)){
        fprintf(stderr,"\tACTION CANCELED: No BOOK was added!\n");
        return (LIVRO){.ISBN=-1};
      }else{
        break;
      }
    }
    while(true){
      if(!getStock(&book.qtdStock)){
        fprintf(stderr,"\tACTION CANCELED: No BOOK was added!\n");
        return (LIVRO){.ISBN=-1};
      }else{
        break;
      }
    }

    return book;
}


/**
 * Ask the books's ISBN
 * @param *ISBN the user's ISBN
 * @return true if the ISBN was asked successfully and false if it was canceled
 */
bool getISBN(long int *ISBN){
  char ISBNtemp[100];
  while(true){
    //header
    printf("     What's the ISBN? (0 to CANCEL) : ");
    //get ISBN input
    if(fgets(ISBNtemp,100,stdin)==NULL){
      if(ferror(stdin)){
        perror("\tERROR: There was an error reading the ISBN!");
      }
      strcpy(ISBNtemp,"");
      continue;
    }
    if(strlen(ISBNtemp)==2&&ISBNtemp[0]=='0'){
      return false;
    }
    //check if ISBN is a string
    for(size_t i=0;i<strlen(ISBNtemp)-1;i++){
      if(!isdigit(ISBNtemp[i])){
        fprintf(stderr,"\tERROR: The ISBN must be a number!\n");
        goto ISBNNUMBERLABEL;
      }
    }
    //transform ISBN into long integer
    sscanf(ISBNtemp,"%ld",ISBN);
    //verify input
    if(strlen(ISBNtemp)-1!=13){
      fprintf(stderr,"\tERROR: The ISBN must be a 13 digit number!\n");
      ISBNNUMBERLABEL:
      strcpy(ISBNtemp,"");
      continue;
    }
    else{
      return true;
    }
  }
}

/**
 * Ask the books's publication year
 * @param *PublishYear the books's publication year 
 * @return true if the year was asked successfully and false if it was canceled
 */
bool getPublicationYear(int *PublishYear){
  char PublishYearTemp[100];
  while(true){
    //header
    printf("     What's the Publication year? (0 to CANCEL) : ");
    //get ISBN input
    if(fgets(PublishYearTemp,100,stdin)==NULL){
      if(ferror(stdin)){
        perror("\tERROR: There was an error reading the Year!");
      }
      strcpy(PublishYearTemp,"");
      continue;
    }
    if(strlen(PublishYearTemp)==2&&PublishYearTemp[0]=='0'){
      return false;
    }
    //check if ISBN is a string
    for(size_t i=0;i<strlen(PublishYearTemp)-1;i++){
      if(!isdigit(PublishYearTemp[i])){
        fprintf(stderr,"\tERROR: The Year must be a number!\n");
        goto YEARNUMBERLABEL;
      }
    }
    //transform ISBN into integer
    sscanf(PublishYearTemp,"%d",PublishYear);
    
    if(strlen(PublishYearTemp)-1 > 4){
      fprintf(stderr,"\tERROR: The Year must be Valid\n");
      YEARNUMBERLABEL:
      strcpy(PublishYearTemp,"");
      continue;
    }
    else{
      return true;
    }
  }
}

/**
 * Ask the books's Price
 * @param *price the books's price
 * @return true if the price was asked successfully and false if it was canceled
 */
bool getPrice(float *price){
  char priceTemp[100];
  while(true){
    //header
    printf("     What's the Price? (0 to CANCEL) : ");
    //get Price input
    if(fgets(priceTemp,100,stdin)==NULL){
      if(ferror(stdin)){
        perror("\tERROR: There was an error reading the Price!");
      }
      strcpy(priceTemp,"");
      continue;
    }
    if(strlen(priceTemp)==2&&priceTemp[0]=='0'){
      return false;
    }
    //check if Price is a string
    for(size_t i=0;i<strlen(priceTemp)-1;i++){
      if(!isdigit(priceTemp[i])){
        fprintf(stderr,"\tERROR: The Price must be a number!\n");
        goto PRICENUMBERLABEL;
      }
    }
    //transform stock into integer
    sscanf(priceTemp,"%f",price);
     if(strlen(priceTemp)-1>=4){
      fprintf(stderr,"\tERROR: The inserted price is absurd\n");
      PRICENUMBERLABEL:
      strcpy(priceTemp,"");
      continue;
    }
    else{
      return true;
    }
  }
}

/**
 * Ask the books's Stock quantity
 * @param *price the books's stock
 * @return true if the stock was asked successfully and false if it was canceled
 */
bool getStock(int *stock){
  char stockTemp[100];
  while(true){
    //header
    printf("     What's the Stock? (0 to CANCEL) : ");
    //get stock input
    if(fgets(stockTemp,100,stdin)==NULL){
      if(ferror(stdin)){
        perror("\tERROR: There was an error reading the Stock!\n");
      }
      strcpy(stockTemp,"");
      continue;
    }
    if(strlen(stockTemp)==2&&stockTemp[0]=='0'){
      return false;
    }
    //check if stock is a string
    for(size_t i=0;i<strlen(stockTemp)-1;i++){
      if(!isdigit(stockTemp[i])){
        fprintf(stderr,"\tERROR: The stock must be a number!\n");
        goto STOCKNUMBERLABEL;
      }
    }
    //transform ISBN into integer
    sscanf(stockTemp,"%d",stock);
     if(strlen(stockTemp)-1>=8){
      fprintf(stderr,"\tERROR: The inserted stock is absurd\n");
      STOCKNUMBERLABEL:
      strcpy(stockTemp,"");
      continue;
    }
    else{
      return true;
    }
  }
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
  printf("   Price:          %.2f                 \n", book.price);
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


void cientificAreaWarning(void){
  printf("===============================================\n"); 
  printf("|                                             |\n");
  printf("| There isn't any book of that cientific area |\n");
  printf("|                                             |\n");
  printf("===============================================\n"); 
}

void emptybookstreeWarning(void){
  printf("===============================================\n"); 
  printf("|                                             |\n");
  printf("|            No Book is Registered            |\n");
  printf("|                                             |\n");
  printf("===============================================\n"); 
}
