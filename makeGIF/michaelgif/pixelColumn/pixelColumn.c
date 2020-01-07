#include <stdio.h>
#include <stdlib.h>

typedef struct pixelColumn_{
    int columnIndex;
    int * column;
}PixelColumn;

void lackOfMemoryError(){
    printf("Not enough RAM memory! Exiting!\n");
    exit(1);
}

int * createColumn(int columnSize){
    int * column = (int *) malloc(sizeof(int) * columnSize);

    if(column == NULL) lackOfMemoryError();
    else return column;
}

PixelColumn * createPixelColumn(int columnIndex, int columnSize){
    PixelColumn * pixelColumn = (PixelColumn *) malloc(sizeof(PixelColumn));

    if(pixelColumn == NULL) lackOfMemoryError();

    pixelColumn -> columnIndex = columnIndex;
    pixelColumn -> column = createColumn(columnSize);

    return pixelColumn;

}

PixelColumn ** createPixelMatrix(int numberOfRows, int columnsize){
    PixelColumn ** pixelMatrix = (PixelColumn **) malloc(sizeof(PixelColumn *) * numberOfRows);

    if(pixelMatrix == NULL) lackOfMemoryError();

    for(int i = 0; i < numberOfRows; i++){
        pixelMatrix[i] = createPixelColumn(i, columnsize);
    }
}

void deleteColumn(int ** column){
    printf("c\n");
    free(*column);

    return;
}

void deletePixelColumn(PixelColumn ** pixelColumn){
    deleteColumn(&((*pixelColumn) -> column));
    printf("b\n");
    free(*pixelColumn);

    return;
}

void deletePixelMatrix(PixelColumn *** pixelMatrix, int rowSize){
    for(int i = 0; i < rowSize; i++){
        printf("column index = %d\n", (*pixelMatrix)[i] -> columnIndex);
        deletePixelColumn(&((*pixelMatrix)[i]));
    }
    printf("a\n");

    free(*pixelMatrix);

    return;
}

void copyArrayToPixelColumn(int array[], PixelColumn * pixelColumn, int arraySize){
    if(pixelColumn == NULL) return;

    for(int i = 0; i < arraySize; i++){
        pixelColumn -> column[i] = array[i];
    }

    return;
}

void printMatrix(PixelColumn ** pixelMatrix, int rowSize, int columnSize){
    for(int i = 0; i < columnSize; i++){
        for(int j = 0; rowSize; j++){
            printf("%d ", (pixelMatrix[i]) -> column[j]);
        }
        printf("\n");
    }
    printf("\n");
}