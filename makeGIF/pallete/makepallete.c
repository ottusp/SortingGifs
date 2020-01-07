#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define boolean int
#define TRUE 1
#define FALSE 0

#define MAXSTEP 255

boolean isArgcValid(int argc){
  if(argc == 2) return TRUE;
  return FALSE;
}

void treatInvalidArgs(int argc){
  if(isArgcValid(argc)) return;
  else{
    printf("Invalid argument to main! Argument must be the number of steps in the steps file name!\n");
    printf("Argc = %d", argc);
    exit(1);
  }
}

int calculateDecreasingSteps(char argv[5]){
  int input = atoi(argv);
  int decreasingSteps = MAXSTEP / input;

  return decreasingSteps;
}

int main(int argc, char * argv[]){
  treatInvalidArgs(argc);
  int decreasingSteps = calculateDecreasingSteps(argv[1]);
  int squareRoot;

  FILE * file = fopen("pallete.txt", "w");

  for(int i = 255; i >= 0; i = i - decreasingSteps){
    squareRoot = sqrt(i);
    fprintf(file, "%d, %d, %d,\n",
    squareRoot, i, squareRoot);
  }
  fclose(file);

  return 0;
}