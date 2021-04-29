//global includes
#include<stdlib.h>
#include<signal.h>
#include<string.h>
#include<unistd.h>
//project includes
#include"handlers.h"

void printExitMessage(void){
  //unbuffered io needed for signal handling, as it's a reentrant function
  char *inBar          ="\n\n==========================================\n";
  char *thanksMessage  ="|     Thanks for using the librorithm!   |\n";
  char *madebyMessage  ="|     Made by:                           |\n";
  char *duarte         ="|     Duarte Arribas, a44585             |\n";
  char *bruno          ="|     Bruno Monteiro, a43994             |\n";
  char *outBar         ="==========================================\n\n";
  write(STDOUT_FILENO,inBar,strlen(inBar));
  write(STDOUT_FILENO,thanksMessage,strlen(thanksMessage));
  write(STDOUT_FILENO,madebyMessage,strlen(madebyMessage));
  write(STDOUT_FILENO,bruno,strlen(bruno));
  write(STDOUT_FILENO,duarte,strlen(duarte));
  write(STDOUT_FILENO,outBar,strlen(outBar));
}

void handleSignals(int signo){
  if(signo==SIGINT||signo==SIGQUIT){
    exit(0);
  }
}