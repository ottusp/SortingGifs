#include <stdio.h>
#include <stdlib.h>

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

void bubbleSort(int UnsortedArray[], int arraySize){
  int maximumNumberIndex;
  int i, j;

  for(j = arraySize - 1; j >= 0; j--){
    maximumNumberIndex = 0;
    for(i = 0; i <= j; i++){
      if(UnsortedArray[i] > UnsortedArray[maximumNumberIndex])
        maximumNumberIndex = i;
      printArray(UnsortedArray, arraySize, i);
    }
    swap(UnsortedArray, maximumNumberIndex, j);
  }
}

int main(){
  int arraySize;
  scanf("%d", &arraySize);

  int unsortedArray[arraySize];
  for(int i = 0; i < arraySize; i++) scanf("%d", &unsortedArray[i]);

  bubbleSort(unsortedArray, arraySize);

  printArray(unsortedArray, arraySize, -1);
  
  return 0;
}

// vazamento de memória!