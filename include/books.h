#ifndef BOOKS_H
#define BOOKS_H

typedef struct{
    int ISBN;
    char title[100];
    char language[50];
    char firstAuthor[100];
    char secondAuthor[100];
    char editor[100];
    int yearPublish;
    char cientificArea[100];
    float price;
    int qtdStock;
}LIVRO;

typedef struct{
    char cientificArea[100];
    int qtd;
}CIENTIFIC_QTD;

LIVRO createBook(void);

void showBook(LIVRO book);

int CompareBooks(LIVRO X, LIVRO Y);

int  CompareBooksISBN (LIVRO X, int ISBN);

int  CompareBooksTitle (LIVRO X, char * title);

int  CompareBooksFirstAuthorYear (LIVRO X, char firstAuthor[100], int yearPublish);

int CompareBooksEditorCientificArea(LIVRO X, char editor[100], char cientificArea[100]);

#endif