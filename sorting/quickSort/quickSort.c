#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define boolean int
#define TRUE 1
#define FALSE 0

#define ARRAY_OF_INDEXES_MAX 3

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

boolean isIMarked(int i, int * analyzedElements){
  if(analyzedElements == NULL) return FALSE;

  for(int j = 0; j < ARRAY_OF_INDEXES_MAX; j++){
    if(i == analyzedElements[j])
      return TRUE;
  }
  return FALSE;
}

void printArray(int unsortedArray[], int arraySize, int * indexesOfAnalyzedElements){
  for(int i = 0; i < arraySize; i++){
    if(isIMarked(i, indexesOfAnalyzedElements))
      printf("-1 ");
    else
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

int * setIndexes( int min, int mid, int max){
  int * array;
  array = (int*) malloc(sizeof(int) * ARRAY_OF_INDEXES_MAX);
  if(array == NULL){
    printf("Not enough RAM memory! Exiting!\n");
    exit(1);
  }

  array[0] = min;
  array[1] = mid;
  array[2] = max;
  return array;
}

int partition (int array[], int low, int high, int arraySize, boolean testMode){  
  int pivot = array[high];  
  int smallerElementIndex = (low - 1);  
  int * indexesArray;

  for (int j = low; j <= high - 1; j++){
    indexesArray = setIndexes(smallerElementIndex, pivot, high);
    printArray(array, arraySize, indexesArray);
    free(indexesArray);

    if (array[j] < pivot){  
      smallerElementIndex++;
      swap(&array[smallerElementIndex], &array[j]);
    }  
  }  
  swap(&array[smallerElementIndex + 1], &array[high]);  
  return (smallerElementIndex + 1);  
} 

void quickSort(int array[], int low, int high, int arraySize, boolean testMode){  
  if (low < high){  
    int partitioningIndex = partition(array, low, high, arraySize, testMode);  

    quickSort(array, low, partitioningIndex - 1, arraySize, testMode);  
    quickSort(array, partitioningIndex + 1, high, arraySize, testMode);  
  }  
} 


int main(int argc, char * argv[]){
  treatInvalidArgs(argc);
  boolean testMode = atoi(argv[1]);

  int arraySize;
  scanf("%d", &arraySize);

  int unsortedArray[arraySize];
  for(int i = 0; i < arraySize; i++) scanf("%d", &unsortedArray[i]);

  quickSort(unsortedArray, 0, arraySize, arraySize, testMode);

  printArray(unsortedArray, arraySize, NULL);
  
  return 0;
}