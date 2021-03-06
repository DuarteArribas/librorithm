#ifndef BOOKS_H
#define BOOKS_H
//structs
typedef struct{
    long int ISBN;
    char     title[100];
    char     language[50];
    char     firstAuthor[100];
    char     secondAuthor[100];
    char     editor[100];
    int      yearPublish;
    char     cientificArea[100];
    float    price;
    int      qtdStock;
}LIVRO;
typedef struct{
    char cientificArea[100];
    int  qtd;
}CIENTIFIC_QTD;
typedef struct{
    int year;
    int qtd;
}PUBLISH_YEAR;
//function prototypes
LIVRO createBook                      (void);
void  getString                       (char *string, int tam);
bool  getISBN                         (long int *ISBN);
bool  getPublicationYear              (int *PublishYear);
bool  getPrice                        (float *price);
bool  getStock                        (int *stock);
void  showBook                        (LIVRO book);
int   CompareBooks                    (LIVRO X, LIVRO Y);
int   CompareBooksISBN                (LIVRO X, long int ISBN);
int   CompareBooksTitle               (LIVRO X, char * title);
int   CompareBooksFirstAuthorYear     (LIVRO X, char firstAuthor[100], int yearPublish);
int   CompareBooksEditorCientificArea (LIVRO X, char editor[100], char cientificArea[100]);
void  bookAlreadyExistsWarning        (void);
void  bookRemovedWarning              (void);
void  unregisteredBookWarning         (void);
void  cientificAreaWarning            (void);
void  emptybookstreeWarning           (void);
#endif