#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define boolean int
#define TRUE 1
#define FALSE 0

int isNumberInArray(int array[], int number, int i){
  for(int j = 0; j < i; j++){
    if(array[j] == number) return 1;
  }
  return 0;
}

int number(int array[], int sizeOfArray, int i){
  srand(time(NULL));
  int number = rand() % sizeOfArray;
  while(isNumberInArray(array, number, i))
    number = (number + rand() % 10) % sizeOfArray;
  return number;
}

boolean isArgcValid(int argc){
  if(argc == 2) return TRUE;
  return FALSE;
}

void treatInvalidArgs(int argc){
  if(isArgcValid(argc)) return;
  else{
    printf("Invalid argument to main! The program must have exactly one argument, the test number!\n");
    printf("Argc = %d", argc);
    exit(1);
  }
}
  
int main(int argc, char * argv[]){
  treatInvalidArgs(argc);
  int arraySize = atoi(argv[1]);
  int i;
  int array[arraySize];

  printf("%d ", arraySize);

  for(i = 0; i < arraySize; i++){
    array[i] = number(array, arraySize, i);
    printf("%d ", array[i]);
  }
  
  return 0;
}