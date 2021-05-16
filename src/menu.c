//global includes
#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<inttypes.h>
#include<string.h>
#include<ctype.h>
//project includes
#include"menu.h"
#include"librorithm.h"
#include"fileHandling.h"
#include"mem.h"
#include"clientOperations.h"
#include"client.h"
#include"orderOperations.h"
#include"order.h"
#include"booksOperations.h"
#include"books.h"
//global variables
//data structures
extern clientNODE *clientlist;
extern ORDER_NODE_QUEUE *orderQueue;
extern PNodoAB Books;
//other
extern CIENTIFIC_QTD *cientific_qtd;
extern PUBLISH_YEAR *publish_year;
extern int num_cientific_qtd;
extern int num_publish_year;
//static function prototypes
static void     printMainMenu           (void);
static void     printFileMenu           (void);
static void     printBooksMenu          (void);
static void     printClientsMenu        (void);
static void     standardOperations      (void);
static void     printConsultBooksMenu   (void);
static void     printConsultClientsMenu (void);
static void     printOrdersMenu         (void);
static void     printOperationsMenu     (void);
static ssize_t  getOption               (void);
static void     consultClient           (void);
static uint64_t computeMemoryWaste      (void);

/**
 * Prints the main menu
 */
static void printMainMenu(void){
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

/**
 * Prints the file menu
 */
static void printFileMenu(void){
  printf("========================================\n");
  printf("|     ========= FILE MENU =========    |\n");
  printf("|                                      |\n");
  printf("|               1-New Data Structures  |\n");
  printf("|               2-New Files            |\n");
  printf("|               3-Open                 |\n");
  printf("|               4-Save                 |\n");
  printf("|               0-Go Back              |\n");
  printf("|                                      |\n");
  printf("========================================\n");
}

/**
 * Prints the books menu
 */
static void printBooksMenu(void){
  printf("========================================\n");
  printf("|    ========= BOOKS MENU =========    |\n");
  standardOperations();
}
/**
 * Prints the clients menu
 */
static void printClientsMenu(void){
  printf("========================================\n");
  printf("|   ========= CLIENTS MENU =========   |\n");
  standardOperations();
}

/**
 * Prints the standard operations used in both the clients and books menus
 */
static void standardOperations(void){
  printf("|                                      |\n");
  printf("|               1-Insert               |\n");
  printf("|               2-Remove               |\n");
  printf("|               3-Change               |\n");
  printf("|               4-Consult              |\n");
  printf("|               0-Go Back              |\n");
  printf("|                                      |\n");
  printf("========================================\n");  
}

/**
 * Prints books' consult menu
 */
static void printConsultBooksMenu(void){
  printf("========================================\n");
  printf("|   ========= CONSULT BOOK =========   |\n");
  printf("|                                      |\n");
  printf("|              1-BY ISBN               |\n");
  printf("|              2-BY TITLE              |\n");
  printf("|              3-BY AUTHOR AND YEAR    |\n");
  printf("|              4-ALL BOOKS             |\n");
  printf("|              0-Go Back               |\n");
  printf("|                                      |\n");
  printf("========================================\n");  
}

/**
 * Prints books' change menu
 */
static void printChangeBooksMenu(void){
  printf("========================================\n");
  printf("|   ========= Change BOOK =========    |\n");
  printf("|                                      |\n");
  printf("|              1-Change Book           |\n");
  printf("|              2-Restock By ISBN       |\n");
  printf("|              0-Go Back               |\n");
  printf("|                                      |\n");
  printf("========================================\n");  
}

/**
 * Prints clients' consult menu
 */
static void printConsultClientsMenu(void){
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

/**
 * Prints orders menu
 */
static void printOrdersMenu(void){
  printf("========================================\n");
  printf("|    ========= ORDER MENU =========    |\n");
  printf("|                                      |\n");
  printf("|              1-Insert                |\n");
  printf("|              2-Remove                |\n");
  printf("|              0-Go Back               |\n");
  printf("|                                      |\n");
  printf("========================================\n");  
}

/**
 * Prints the operations menu
 */
static void printOperationsMenu(void){
  printf("======================================================================\n");
  printf("|                    ======== OPERATIONS ========                    |\n");
  printf("|                                                                    |\n");
  printf("|                             1-Num of Books sold at date            |\n");
  printf("|                             2-Latest date of the specified ISBN    |\n");
  printf("|                             3-Number of Books by client            |\n");
  printf("|                             4-Recent books of a cientific area     |\n");
  printf("|                             5-Show Best Selling Books              |\n");
  printf("|                             6-Cientific area with more books       |\n");
  printf("|                             7-Client with most books               |\n");
  printf("|                             8-Show clients by num of purchases dec |\n");
  printf("|                             9-Year with more books                 |\n");
  printf("|                             10-Client that wasted more             |\n");
  printf("|                             11-Check memory wasted                 |\n");
  printf("|                             12-Show clients starting with char     |\n");
  printf("|                             13-Number of orders left to fulfill    |\n");
  printf("|                             14-Show most expensive Book            |\n");
  printf("|                             15-Operation                           |\n");
  printf("|                             0-Go Back                              |\n");
  printf("|                                                                    |\n");
  printf("======================================================================\n");  
}

/**
 * Gets the option of the menu
 * @return the chosen option or -1 in case of invalid option
 */
static ssize_t getOption(void){
  printPrompt();
  ssize_t option;
  if(scanf("%zd",&option)==EOF){
    if(ferror(stdin)){
      perror("\tERROR: There was an error reading the option!");
    }
    option=-1;
  }
  getchar(); 
  return option; 
}

/**
 * Handles the main menu
 */
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
        fprintf(stderr,"\tERROR: Invalid option!\n");
        break;
    } 
  }
}

/**
 * Handles file menu
 */
void fileMenu(void){
  bool exit=false;
  ssize_t option;
  while(!exit){
    printFileMenu();
    option=getOption();
    switch(option){
      case 1:
        newDataStructures();
        break;
      case 2:
        newFile();
        break;
      case 3:
        openFile();
        break;
      case 4:
        saveFile();
        break;
      case 0:
        exit=true;
        break;
      default:
        fprintf(stderr,"\tERROR: Invalid option!\n");
        break;
    }
  }
}

/**
 * Handles book menu
 */
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
        if(!getISBN(&ISBN)){
          fprintf(stderr,"\tACTION CANCELED: No book was changed!\n");
          continue;
        }
        Books=removeBook(Books, ISBN);
        break;
      case 3:
        bookChangeMenu();
        break;
      case 4:
        booksubMenuShow();
        break;
      case 0:
        exit=true;
        break;
      default:
        fprintf(stderr,"\tERROR: Invalid option!\n");
        break;
    }
  }
}

/**
 * Handles the book consult menu
 */
void booksubMenuShow(void){
  bool exit=false;
  ssize_t option;
  long int ISBN;
  int yearPublish;
  char title[100], firstAuthor[100];
  while(!exit){
    printConsultBooksMenu();
    option=getOption();
    switch(option){
      case 1:
        if(!getISBN(&ISBN)){
          fprintf(stderr,"\tACTION CANCELED: No ISBN read!\n");
          continue;
        }
        PesquisarABPISBN(Books, ISBN);
        break;
      case 2:
        printf("     What's the Title? (0 to CANCEL) \n");
        getString(title, 100);
        if(strcmp(title, "0")==0){
          fprintf(stderr,"\tACTION CANCELED: No title read!\n");
          break;
        }
        PesquisarABPTitle(Books, title);
        break;
      case 3:
        printf("     What's the First Author? (0 to CANCEL) \n");
        getString(firstAuthor, 100);
        if(strcmp(firstAuthor, "0")==0){
          fprintf(stderr,"\tACTION CANCELED: No first author read!\n");
          break;
        }
        if(!getPublicationYear(&yearPublish)){
          fprintf(stderr,"\tACTION CANCELED: No year read!\n");
          continue;
        }
        PesquisarABPAuthorYear(Books, firstAuthor,yearPublish);
        break;
      case 4:
        showALL(Books);
        break;
      case 0:
        exit=true;
        break;
      default:
        fprintf(stderr,"\tERROR: Invalid option!\n");
        break;
    }
  }
}

/**
 * Handles the book change menu
 */
void bookChangeMenu(void){
  bool exit=false;
  int stock;
  ssize_t option;
  long int ISBN;
  while(!exit){
    printChangeBooksMenu();
    option=getOption();
    switch(option){
      case 1:
        if(!getISBN(&ISBN)){
          fprintf(stderr,"\tACTION CANCELED: No book was changed!\n");
          continue;
        }
        Books=changeBookISBN(Books, ISBN);
        break;
      case 2:
        if(getISBN(&ISBN) && getStock(&stock)){
          if(PesquisarABP(Books,(LIVRO){.ISBN=ISBN})!=1){
            unregisteredBookWarning();
          }else{
            restockBook(Books, ISBN, stock);
          }
        }
        break;
      case 0:
        exit=true;
        break;
      default:
        fprintf(stderr,"\tERROR: Invalid option!\n");
        break;
    }
  }
}

/**
 * Handles the clients' menu
 */
void clientMenu(void){
  bool exit=false;
  ssize_t option;
  clientNODE *clientToChange;
  CLIENT client;
  uint32_t NIF;
  while(!exit){
    printClientsMenu();
    option=getOption();
    switch(option){
      case 1:
        client=newClient();
        if(client.NIF!=0){
          if(isemptylist(clientlist)){
            clientlist=createLinked(client);
          }
          else{
            eappendlinked(clientlist,client);
          }
          printf("\tClient added with success!\n");
        }
        break;
      case 2:
        if(!getNIF(&NIF)){
          fprintf(stderr,"\tACTION CANCELED: No user was removed!\n");
          continue;
        }
        if(removeClient(&clientlist,NIF)){
          printf("\tClient removed with success!\n");
        }
        else{
          fprintf(stderr,"\tNo client with the specified NIF is on the system!\n");
        }
        break;
      case 3:
        if(!getNIF(&NIF)){
          fprintf(stderr,"\tACTION CANCELED: No user was changed!\n");
          continue;
        }
        clientToChange=getSearchlinked(clientlist,NIF);
        if(clientToChange==NULL){
          fprintf(stderr,"\tERROR: The specified user's NIF is not on the system!\n");
          continue;
        }
        changeClient(clientlist,clientToChange->data);
        printf("\tClient changed with success!\n");
        break;
      case 4:
        consultClient();
        break;
      case 0:
        exit=true;
        break;
      default:
        fprintf(stderr,"\tERROR: Invalid option!\n");
        break;
    }
  }
}

/**
 * Handles the consult clients' menu
 */
static void consultClient(void){
  bool exit=false;
  ssize_t option;
  uint32_t NIF;
  char name[255],address[255];
  while(!exit){
    printConsultClientsMenu();
    option=getOption();
    switch(option){
      case 1:
        if(!getNIF(&NIF)){
          fprintf(stderr,"\tACTION CANCELED: No user was consulted!\n");
          continue;
        }
        consultClientNIF(clientlist,NIF);
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
        fprintf(stderr,"\tERROR: Invalid option!\n");
        break;
    }
  }
}

/**
 * Handles the order menu
 */
void orderMenu(void){
  bool exit=false;
  ssize_t option;
  ORDER orderTemp;
  while(!exit){
    printOrdersMenu();
    option=getOption();
    switch(option){
      case 1:
        orderTemp=newOrder();
        if(orderTemp.NIF!=0){
          if(isemptyqueue(orderQueue)){
            orderQueue=createqueue(orderTemp);
          }
          else{
            enqueue(&orderQueue,orderTemp);
          }
          printf("\tOrder added with success!\n");
        }
        break;
      case 2:
        if(isemptyqueue(orderQueue)){
          fprintf(stderr,"\tERROR: There are no orders!\n");
        }
        else{
          //remove from queue
          ORDER orderRemoved=dequeue(&orderQueue);
          //update the client with the specified NIF's orders
          clientNODE *client=getSearchlinked(clientlist,orderRemoved.NIF);
          updateClientOrders(client->data.NIF,orderRemoved);
          printf("\tOrder removed with success!\n");
        }
        break;
      case 0:
        exit=true;
        break;
      default:
        fprintf(stderr,"\tERROR: Invalid option!\n");
        break;
    }
  }
}

/**
 * Handles the operation menu
 */
void operationMenu(void){
  bool exit=false;
  ssize_t option;
  uint64_t memWastedBytes;
  char yearTemp[255],monthTemp[255];
  uint16_t year;
  uint8_t month;
  uint32_t NIF;
  long int ISBN;
  int totalStock=0;
  float stockValue=0;
  LIVRO X;
  while(!exit){
    printOperationsMenu();
    option=getOption();
    switch(option){
      case 1:
        getYear(yearTemp,&year);
        getMonth(monthTemp,&month);
        printf("\t======= %zu books were sold on %"PRIu8"/%"PRIu16" =======\n",getNumOfBooks(monthTemp,yearTemp),month,year);
        break;
      case 2:
        if(!getISBN(&ISBN)){
          fprintf(stderr,"\tACTION CANCELED: No dates were consulted!\n");
          continue;
        }
        latestDateByBook(ISBN);
        break;
      case 3:
        if(!getNIF(&NIF)){
          fprintf(stderr,"\tACTION CANCELED: No books were consulted!\n");
          continue;
        }
        numBooksByClient(NIF);
        break;
      case 4:
        showMostRecentCientificArea(Books);
        break;
      case 5:
        showBestSoldBooks(clientlist,3);
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
        printClient(clientWithMostBooks());
        break;
      case 8:
        showClientsDec();
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
        getYear(yearTemp,&year);
        getMonth(monthTemp,&month);
        clientThatWastedMore(month,year);
        break;
      case 11:
        memWastedBytes=computeMemoryWaste();
        printf("\t======= This program has wasted %"PRIu64" bytes (~= %.3lfkb, ~= %.3lfmb, ~= %.3lfgb) of memory =======\n",
          memWastedBytes,
          (double)memWastedBytes/1024,
          (double)memWastedBytes/1024/1024,
          (double)memWastedBytes/1024/1024/1024
        );
        break;
      case 12:
        clientsThatStartWithChar();
        break;
      case 13:
        printf("\t======= %zu orders are left to fulfill =======\n",getOrdersLeftToFulfill(&orderQueue));
        break;
      case 14:
        X=getMostExpensiveBook(Books);
        if(X.ISBN==-1){
          emptybookstreeWarning();
        }else{
          showBook(X);
        }
        break;
      case 15:
        getTotalStockandStockValue(Books,&totalStock,&stockValue);
        printf("\t======= Total Stock: %d. Total Value of Stock %.2f € =======\n",totalStock, stockValue);
        break;
      case 0:
        exit=true;
        break;
      default:
        fprintf(stderr,"\tERROR: Invalid option!\n");
        break;
    }
  }
}

/**
 * Computes the memory waste of the program
 * @return the memory waste of the program in bytes
 */
static uint64_t computeMemoryWaste(void){
  uint64_t memoryWasteBytes=0;
  memoryWasteBytes+=getMemoryWasteClients(clientlist);
  //TODO: compute the rest of the memory waste
  return memoryWasteBytes;
}