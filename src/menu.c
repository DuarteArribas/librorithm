//global includes
#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<inttypes.h>
#include<string.h>
#include<ctype.h>
//project includes
#include"menu.h"
#include"mem.h"
#include"clientOperations.h"
#include"client.h"
#include"booksOperations.h"
#include"books.h"
//globals
extern clientNODE *clientlist;
extern CIENTIFIC_QTD *cientific_qtd;
extern int num_cientific_qtd;
extern PNodoAB Books;
extern PUBLISH_YEAR *publish_year;
extern int num_publish_year;

//print the menus
static
void printMainMenu(void){
  printf("========================================\n");
  printf("|     ========= MAIN MENU =========    |\n");
  printf("|                                      |\n");
  printf("|               1-File                 |\n");
  printf("|               2-Books                |\n");
  printf("|               3-Clients              |\n");
  printf("|               4-Orders               |\n");
  printf("|               5-Operations           |\n");
  printf("|               0-Exit Program         |\n");
  printf("|                                      |\n");
  printf("========================================\n");
}

static
void printFileMenu(void){
  printf("========================================\n");
  printf("|     ========= FILE MENU =========    |\n");
  printf("|                                      |\n");
  printf("|               1-New                  |\n");
  printf("|               2-Open                 |\n");
  printf("|               3-Save                 |\n");
  printf("|               0-Go Back              |\n");
  printf("|                                      |\n");
  printf("========================================\n");
}

static
void standardOperations(void){
  printf("|                                      |\n");
  printf("|               1-Insert               |\n");
  printf("|               2-Remove               |\n");
  printf("|               3-Change               |\n");
  printf("|               4-Consult              |\n");
  printf("|               0-Go Back              |\n");
  printf("|                                      |\n");
  printf("========================================\n");  
}

static
void printBooksMenu(void){
  printf("========================================\n");
  printf("|    ========= BOOKS MENU =========    |\n");
  standardOperations();
}

static
void printClientsMenu(void){
  printf("========================================\n");
  printf("|   ========= CLIENTS MENU =========   |\n");
  standardOperations();
}

static
void printBookssubMenuConsult(void){
  printf("========================================\n");
  printf("|    ========= Show BOOKS =========    |\n");
  printf("|              1-ISBN                  |\n");
  printf("|              2-Título                |\n");
  printf("|    3-First Author and year publish   |\n");
  printf("|              4-Show All              |\n");
  printf("|              0-Go Back               |\n");
  printf("|                                      |\n");
  printf("========================================\n");  
}

static
void printConsultClientsMenu(void){
  printf("========================================\n");
  printf("|   ======== CONSULT CLIENT ========   |\n");
  printf("|                                      |\n");
  printf("|            1-BY NIF                  |\n");
  printf("|            2-BY NAME                 |\n");
  printf("|            3-BY ADDRESS              |\n");
  printf("|            4-ALL CLIENTS             |\n");
  printf("|            0-Go Back                 |\n");
  printf("|                                      |\n");
  printf("========================================\n");  
}

static
void printOrdersMenu(void){
  printf("========================================\n");
  printf("|    ========= ORDER MENU =========    |\n");
  printf("|                                      |\n");
  printf("|              1-Insert                |\n");
  printf("|              2-Remove                |\n");
  printf("|              0-Go Back               |\n");
  printf("|                                      |\n");
  printf("========================================\n");  
}

static
void printOperationsMenu(void){
  printf("========================================\n");
  printf("|     ======== OPERATIONS ========     |\n");
  printf("|                                      |\n");
  printf("|              1-Operation             |\n");
  printf("|              2-Operation             |\n");
  printf("|              3-Operation             |\n");
  printf("|  4-Recent books of a cientific area  |\n");
  printf("|              5-Operation             |\n");
  printf("|   6-Cientific area with more books   |\n");
  printf("|              7-Operation             |\n");
  printf("|              8-Operation             |\n");
  printf("|        9-Year with more books        |\n");
  printf("|              10-Operation            |\n");
  printf("|              11-Operation            |\n");
  printf("|              12-Operation            |\n");
  printf("|              13-Operation            |\n");
  printf("|              14-Operation            |\n");
  printf("|              15-Operation            |\n");
  printf("|              0-Go Back               |\n");
  printf("|                                      |\n");
  printf("========================================\n");  
}

//read option
static
ssize_t getOption(void){
  ssize_t option;
  if(scanf("%zd",&option)==EOF){
    if(ferror(stdin)){
      perror("ERROR: There was an error reading the option!");
    }
    option=-1;
  }
  getchar(); 
  return option; 
}

//menu handling
void mainMenu(void){
  bool exit=false;
  ssize_t option;
  while(!exit){
    printMainMenu();
    option=getOption();
    switch(option){
      case 1:
        fileMenu();
        break;
      case 2:
        bookMenu();
        break;
      case 3:
        clientMenu();
        break;
      case 4:
        orderMenu();
        break;
      case 5:
        operationMenu();
        break;
      case 0:
        exit=true;
        break;
      default:
        fprintf(stderr,"ERROR: Invalid option!\n");
        break;
    } 
  }
  clnmem(publish_year);
  clnmem(cientific_qtd);
}

void fileMenu(void){
  bool exit=false;
  ssize_t option;
  while(!exit){
    printFileMenu();
    option=getOption();
    switch(option){
      case 1:
        //newFile();
        break;
      case 2:
        //openFile();
        break;
      case 3:
        //saveFile();
        break;
      case 0:
        exit=true;
        break;
      default:
        fprintf(stderr,"ERROR: Invalid option!\n");
        break;
    }
  }
}

void bookMenu(void){
  bool exit=false;
  ssize_t option;
  long int ISBN;
  while(!exit){
    printBooksMenu();
    option=getOption();
    switch(option){
      case 1:
        Books=insertBook(Books);
        break;
      case 2:
        printf("Insert an ISBN: ");
        scanf("%ld", &ISBN);
        Books=removeBook(Books, ISBN);
        break;
      case 3:
        printf("Insert an ISBN: ");
        scanf("%ld", &ISBN);
        Books=changeBookISBN(Books,Books, ISBN);
        break;
      case 4:
        booksubMenuShow();
        break;
      case 0:
        exit=true;
        break;
      default:
        fprintf(stderr,"ERROR: Invalid option!\n");
        break;
    }
  }
}

void booksubMenuShow(void){
  bool exit=false;
  ssize_t option;
  long int ISBN;
  int yearPublish;
  char title[100], firstAuthor[100];
  while(!exit){
    printBookssubMenuConsult();
    option=getOption();
    switch(option){
      case 1:
        printf("Insert an ISBN: ");
        scanf("%ld", &ISBN);
        PesquisarABPISBN(Books, ISBN);
        break;
      case 2:
        printf("Insert Title: ");
        scanf("\n%[^\n]s",title);
        PesquisarABPTitle(Books, title);
        break;
      case 3:
        printf("First Author: ");
        scanf("\n%[^\n]s",firstAuthor);
        printf("Year Publish: ");
        scanf("%d", &yearPublish);
        PesquisarABPAuthorYear(Books, firstAuthor,yearPublish);
        break;
      case 4:
        showALL(Books);
        break;
      case 0:
        exit=true;
        break;
      default:
        fprintf(stderr,"ERROR: Invalid option!\n");
        break;
    }
  }
}

static
void consultClient(void){
  bool exit=false;
  ssize_t option;
  char name[255],address[255];
  while(!exit){
    printConsultClientsMenu();
    option=getOption();
    switch(option){
      case 1:
        consultClientNIF(clientlist,getNIF());
        break;
      case 2:
        getName(name);
        consultClientName(clientlist,name);
        break;
      case 3:
        getAddress(address);
        consultClientAddress(clientlist,address);
        break;
      case 4:
        consultAll(clientlist);
        break;
      case 0:
        exit=true;
        break;
      default:
        fprintf(stderr,"ERROR: Invalid option!\n");
        break;
    }
  }
}

void clientMenu(void){
  bool exit=false;
  ssize_t option;
  clientNODE *clientToChange;
  CLIENT client;
  while(!exit){
    printClientsMenu();
    option=getOption();
    switch(option){
      case 1:
        if(isemptylist(clientlist)){
          clientlist=createLinked(newClient());
        }
        else{
          eappendlinked(clientlist,newClient());
        }
        printf("\tClient added with success!\n");
        break;
      case 2:
        removeClient(&clientlist,getNIF());
        break;
      case 3:
        clientToChange=getSearchlinked(clientlist,getNIF());
        if(clientToChange==NULL){continue;}
        client=clientToChange->data;
        changeClient(clientlist,client);
        break;
      case 4:
        consultClient();
        break;
      case 0:
        exit=true;
        break;
      default:
        fprintf(stderr,"ERROR: Invalid option!\n");
        break;
    }
  }
}

void orderMenu(void){
  bool exit=false;
  ssize_t option;
  while(!exit){
    printOrdersMenu();
    option=getOption();
    switch(option){
      case 1:
        //insertOrder();
        break;
      case 2:
        //removeOrder();
        break;
      case 0:
        exit=true;
        break;
      default:
        fprintf(stderr,"ERROR: Invalid option!\n");
        break;
    }
  }
}

void operationMenu(void){
  bool exit=false;
  ssize_t option;
  char cientificArea[100];
  int k;
  while(!exit){
    printOperationsMenu();
    option=getOption();
    switch(option){
      case 1:
        //operation1();
        break;
      case 2:
        //operation2();
        break;
      case 3:
        //operation3();
        break;
      case 4:
        printf("How many books? ");
        scanf("%d", &k);
        printf("Cientific Area: ");
        scanf("\n%[^\n]s",cientificArea);
        int year=seeMostRecentDate(Books,cientificArea);
        showRecentBooksCientificArea(Books,year, cientificArea,k);
        break;
      case 5:
        //operation5();
        break;
      case 6:
        num_cientific_qtd=1;
        cientific_qtd=memalloc(num_cientific_qtd * sizeof(CIENTIFIC_QTD));
        cientificAreaAndYearWithMoreBooks(Books,1);
        showCientificAreaWithMoreBooks();
        free(cientific_qtd);
        num_cientific_qtd=1;
        break;
      case 7:
        //operation7();
        break;
      case 8:
        //operation8();
        break;
      case 9:
        num_publish_year=1;
        publish_year=memalloc(num_publish_year * sizeof(PUBLISH_YEAR));
        cientificAreaAndYearWithMoreBooks(Books, 2);
        showYearWithMorePublications();
        free(publish_year);
        num_cientific_qtd=1;
        break;
      case 10:
        //operation10();
        break;
      case 11:
        //operation11();
        break;
      case 12:
        //operation12();
        break;
      case 13:
        //operation13();
        break;
      case 14:
        //operation14();
        break;
      case 15:
        //operation15();
        break;
      case 0:
        exit=true;
        break;
      default:
        fprintf(stderr,"ERROR: Invalid option!\n");
        break;
    }
  }
}