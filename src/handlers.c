//global includes
#include<stdlib.h>
#include<signal.h>
#include<string.h>
#include<unistd.h>
//project includes
#include"handlers.h"
#include"librorithm.h"

/**
 * Prints an exit message upon exiting the program
 */
void printExitMessage(void){
  //unbuffered io needed for signal handling, as it's a reentrant function
  const char *inBar         ="\n\n==========================================\n";
  const char *thanksMessage ="|     Thanks for using the librorithm!   |\n";
  const char *madebyMessage ="|     Made by:                           |\n";
  const char *duarte        ="|     Duarte Arribas, a44585             |\n";
  const char *bruno         ="|     Bruno Monteiro, a43994             |\n";
  const char *outBar        ="==========================================\n\n";
  write(STDOUT_FILENO,inBar,strlen(inBar));
  write(STDOUT_FILENO,thanksMessage,strlen(thanksMessage));
  write(STDOUT_FILENO,madebyMessage,strlen(madebyMessage));
  write(STDOUT_FILENO,bruno,strlen(bruno));
  write(STDOUT_FILENO,duarte,strlen(duarte));
  write(STDOUT_FILENO,outBar,strlen(outBar));
}

/**
 * Signal handler
 * @param signo the signal to handle
 */
void handleSignals(const int signo){
  //gracefully exit
  if(signo==SIGINT||signo==SIGQUIT){
    cleanup();
    exit(0);
  }
}