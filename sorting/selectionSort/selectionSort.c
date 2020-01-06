#include <stdio.h>
#include "selectionSort.h"

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

void continuousSwap(int unsortedArray[], int i, int arraySize){
  for(int j = i; j > 0 && unsortedArray[j] < unsortedArray[j-1]; j--){
    printArray(unsortedArray, arraySize);
    swap(&unsortedArray[j], &unsortedArray[j-1]);
  }

  return;
}

void selectionSort(int unsortedArray[], int arraySize){
  for(int i = 0; i < arraySize; i++){
    continuousSwap(unsortedArray, i, arraySize);
  }
}

int main(){
  int arraySize;
  scanf("%d", &arraySize);

  int unsortedArray[arraySize];
  for(int i = 0; i < arraySize; i++) scanf("%d", &unsortedArray[i]);

  selectionSort(unsortedArray, arraySize);

  printArray(unsortedArray, arraySize);
  
  return 0;
}