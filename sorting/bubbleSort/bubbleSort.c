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

void printArray(int unsortedArray[], int arraySize, int indexOfAnalyzedElement){
  for(int i = 0; i < arraySize; i++){
    if(i == indexOfAnalyzedElement)
      printf("-1 ");
    else
      printf("%d ", unsortedArray[i]);
  }
  printf("\n");
}

void swap(int array[], int firstIndex, int secondIndex){
  int temporary = array[firstIndex];
  array[firstIndex] = array[secondIndex];
  array[secondIndex] = temporary;

  return;
}

void bubbleSort(int UnsortedArray[], int arraySize, boolean testMode){
  int maximumNumberIndex;
  int i, j;

  for(j = arraySize - 1; j >= 0; j--){
    maximumNumberIndex = 0;
    for(i = 0; i <= j; i++){
      if(UnsortedArray[i] > UnsortedArray[maximumNumberIndex])
        maximumNumberIndex = i;
      if(!testMode)
        printArray(UnsortedArray, arraySize, i);
    }
    swap(UnsortedArray, maximumNumberIndex, j);
  }
}

int main(int argc, char * argv[]){
  treatInvalidArgs(argc);
  boolean testMode = atoi(argv[1]);
  int arraySize;
  scanf("%d", &arraySize);

  int unsortedArray[arraySize];
  for(int i = 0; i < arraySize; i++) scanf("%d", &unsortedArray[i]);

  bubbleSort(unsortedArray, arraySize, testMode);

  printArray(unsortedArray, arraySize, -1);
  
  return 0;
}