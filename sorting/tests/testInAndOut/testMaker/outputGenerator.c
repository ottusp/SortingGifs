#include <stdio.h>
#include <stdlib.h>

#define boolean int
#define TRUE 1
#define FALSE 0

boolean isArgcValid(int argc){
  if(argc == 2) return TRUE;
  return FALSE;
}

void treatInvalidArgs(int argc){
  if(isArgcValid(argc)) return;
  else{
    printf("Argument must be 1 if you're on test mode, and 0 if test mode is unable\n");
    printf("Argc = %d", argc);
    exit(1);
  }
}

int main(int argc, char * argv[]){
  treatInvalidArgs(argc);
  int limitOfNumbers = atoi(argv[1]);

  for(int i = 0; i < limitOfNumbers; i++){
    printf("%d ", i);
  }
  printf("\n");

  return 0;
}