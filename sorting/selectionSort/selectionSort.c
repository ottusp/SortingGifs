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

void printArray(int unsortedArray[], int arraySize){
  for(int i = 0; i < arraySize; i++){
    printf("%d ", unsortedArray[i]);
  }
  printf("\n");
}

void swap(int * a, int * b){
  int temporary = *a;
  *a = *b;
  *b = temporary;
  return;
}

void continuousSwap(int unsortedArray[], int i, int arraySize, boolean testMode){
  for(int j = i; j > 0 && unsortedArray[j] < unsortedArray[j-1]; j--){
    if(!testMode)
      printArray(unsortedArray, arraySize);
    swap(&unsortedArray[j], &unsortedArray[j-1]);
  }

  return;
}

void selectionSort(int unsortedArray[], int arraySize, boolean testMode){
  for(int i = 0; i < arraySize; i++){
    continuousSwap(unsortedArray, i, arraySize, testMode);
  }
}

int main(int argc, char * argv[]){
  treatInvalidArgs(argc);
  boolean testMode = atoi(argv[1]);
  int arraySize;
  scanf("%d", &arraySize);

  int unsortedArray[arraySize];
  for(int i = 0; i < arraySize; i++) scanf("%d", &unsortedArray[i]);

  selectionSort(unsortedArray, arraySize, testMode);

  printArray(unsortedArray, arraySize);
  
  return 0;
}