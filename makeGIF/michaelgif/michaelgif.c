#include "../../gifenc-master/gifenc.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARGVMAX 20

#define FRAMES_DELETED 2

#define boolean int
#define TRUE 1
#define FALSE 0

FILE * openFileForReading(const char * fileName){
    FILE * file = fopen(fileName, "r");
    if(file == NULL){
        printf("It was not possible to open file!\n");
        exit(1);
    }
    return file;
}

void closeFile(FILE ** pasta){
    fclose(*pasta);
    return;
}

int calculateFileSize(const char * fileName){
    FILE * file = openFileForReading(fileName);

    int fileSize = 0;
    uint8_t temporary;

    fscanf(file, " %hhu,", &temporary);
    while(!feof(file)){
        fileSize++;
        fscanf(file, "%hhu,", &temporary);
    }

    closeFile(&file);

    return fileSize;
}

uint8_t * pallete(){
    const char fileName[] = "../pallete/pallete.txt";

    int fileSize = calculateFileSize(fileName);

    FILE * palleteFile = openFileForReading(fileName);

    uint8_t * pallete = (uint8_t*) malloc(sizeof(uint8_t) * fileSize);
    if(pallete == NULL) return NULL;

    for(int i = 0; i < fileSize; i++)
        fscanf(palleteFile, " %hhu,", &pallete[i]);

    closeFile(&palleteFile);
    return pallete;
}

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

char * calculateStepsFilePath(char argv[15]){
    char * stepsPath;
    stepsPath = (char *) malloc(sizeof(char) * ARGVMAX);
    
    if(stepsPath == NULL){
        printf("No memory available!");
        exit(1);
    }

    strcpy(stepsPath, "steps");
    strcat(stepsPath, argv);
    return stepsPath;
}

int stringToInt(char * string){
    return atoi(string);
}

int calculateStepsFileSize(char * stepsFileName, char * numbersPerLineAsChar){
    int numbersPerLine = stringToInt(numbersPerLineAsChar);
    int totalOfNumbers = calculateFileSize(stepsFileName);
    int totalOfLines = totalOfNumbers / numbersPerLine;
    return totalOfLines;
}

int calculatePixelNumber(int height, int width, int pixel, int k){
    int pixelNumber = (((pixel % width) + pixel / width) - k + 2*width) % width;

    return pixelNumber;
}

void insertPixelsOnFrame(ge_GIF * gif, int height, int width, int pixel, int j){
    int pixelNumber;

    for(int k = 0; k < height; k++){
        if(pixel != -1)
            pixelNumber = calculatePixelNumber(height, width, pixel, k);
        else
            pixelNumber = pixel;
        
        gif -> frame[j + k*height] = pixelNumber;
    }
}

boolean willFrameBePrinted(int * counter){
    if(*counter == FRAMES_DELETED){
        *counter = 0;
        return TRUE; 
    }
    else{
        (*counter) ++;
        return FALSE;
    }
}

int main(int argc, char * argv[]){
    treatInvalidArgs(argc);
    char * stepsFileName = calculateStepsFilePath(argv[1]);
    int i, j;
    uint8_t * paletaDeCores = pallete();
    int numberOfSteps = calculateStepsFileSize(stepsFileName, argv[1]);

    //Number of steps == number of lines of the steps file

    int widthAndHeight = atoi(argv[1]);
    int width = widthAndHeight;
    int height = widthAndHeight;

    /* create a GIF */
    ge_GIF *gif = ge_new_gif(
        "michael.gif",  /* file name */
        width, height,           /* canvas size */
        paletaDeCores,  /* color pallete */
        7,              /* palette depth == log2(# of colors) */
        0               /* infinite loop */
    );
    /* draw some frames */
    int pixel, counter = 0;
    boolean willThisFrameBePrinted = TRUE;
    for (i = 0; i < numberOfSteps; i++) {
        for (j = 0; j < width; j ++){
            scanf(" %d, ", &pixel);
            insertPixelsOnFrame(gif, height, width, pixel, j);
        }
        willThisFrameBePrinted = willFrameBePrinted(&counter);
        if(willThisFrameBePrinted)
            ge_add_frame(gif, 1);
    }
    /* remember to close the GIF */
    ge_close_gif(gif);

    free(stepsFileName);
    return 0;
}
