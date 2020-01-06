#include "../../gifenc-master/gifenc.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARGVMAX 20

#define boolean int
#define TRUE 1
#define FALSE 0

FILE * criaPastaParaLeitura(const char * nomeDaPasta){
    FILE * pasta = fopen(nomeDaPasta, "r");
    if(pasta == NULL){
        printf("Não foi possível abrir a pasta!\n");
        exit(1);
    }
    return pasta;
}

void destroiPasta(FILE ** pasta){
    fclose(*pasta);
    return;
}

int calculaTamanhoDaPasta(const char * nomeDaPasta){
    FILE * pasta = criaPastaParaLeitura(nomeDaPasta);

    int tamanhoDaPasta = 0;
    uint8_t armazenadorDeEntradasTemporario;

    fscanf(pasta, " %hhu,", &armazenadorDeEntradasTemporario);
    while(!feof(pasta)){
        tamanhoDaPasta++;
        fscanf(pasta, " %hhu,", &armazenadorDeEntradasTemporario);
    }

    destroiPasta(&pasta);

    return tamanhoDaPasta;
}

uint8_t * paleta(){
    const char nomeDaPasta[] = "./paleta/paleta.txt";

    int tamanhoDaPasta = calculaTamanhoDaPasta(nomeDaPasta);

    FILE * pastaDaPaleta = criaPastaParaLeitura(nomeDaPasta);

    uint8_t * paleta = (uint8_t*) malloc(sizeof(uint8_t) * tamanhoDaPasta);
    if(paleta == NULL) return NULL;

    for(int i = 0; i < tamanhoDaPasta; i++)
        fscanf(pastaDaPaleta, " %hhu,", &paleta[i]);

    destroiPasta(&pastaDaPaleta);
    return paleta;
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
    int totalOfNumbers = calculaTamanhoDaPasta(stepsFileName);
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

int main(int argc, char * argv[]){
    treatInvalidArgs(argc);
    char * stepsFileName = calculateStepsFilePath(argv[1]);
    int i, j;
    uint8_t * paletaDeCores = paleta();
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
    int pixel;
    int willThisFrameBePrinted = TRUE;
    for (i = 0; i < numberOfSteps; i++) {
        for (j = 0; j < width; j ++){
            scanf(" %d, ", &pixel);
            insertPixelsOnFrame(gif, height, width, pixel, j);
        }
        if(willThisFrameBePrinted) willThisFrameBePrinted = FALSE;
        else willThisFrameBePrinted = TRUE;
        if(willThisFrameBePrinted)
            ge_add_frame(gif, 1);
    }
    /* remember to close the GIF */
    ge_close_gif(gif);

    free(stepsFileName);
    return 0;
}
