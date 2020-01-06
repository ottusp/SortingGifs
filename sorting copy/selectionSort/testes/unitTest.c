#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define boolean int
#define TRUE 1
#define FALSE 0
#define MAX_SIZE 50
#define MAX_NUMBER_OF_TEST 4

FILE * openFileForReading(const char * fileName){
    FILE * file = fopen(fileName, "r");
    if(file == NULL){
      printf("File name: %s\n", fileName);
      printf("It was not possible to open the file!\n");
      exit(1);
    }
    return file;
}

void destroyFile(FILE ** file){
    fclose(*file);
    return;
}

int calculateFileSize(const char * fileName){
    FILE * file = openFileForReading(fileName);

    int fileSize = -1;
    int temporaryBuffer;

    while(!feof(file)){
      fileSize++;
      fscanf(file, " %d,", &temporaryBuffer);
    }

    destroyFile(&file);

    return fileSize;
}

int * fileContent(const char * fileName){

    int fileSize = calculateFileSize(fileName);

    FILE * file = openFileForReading(fileName);

    int * fileContent = (int*) malloc(sizeof(int) * fileSize);
    if(fileContent == NULL) return NULL;

    for(int i = 0; i < fileSize; i++)
        fscanf(file, " %d,", &fileContent[i]);

    destroyFile(&file);
    return fileContent;
}


boolean isArgcValid(int argc){
  if(argc == 2) return TRUE;
  return FALSE;
}

char * filePath(char * testNumber){
  char * pathName;
  if((pathName = (char *) malloc(sizeof(char) * MAX_SIZE)) == NULL){
    printf("No RAM Memory available!\n");
    exit(1);
  }

  strcat(pathName, "./testInAndOut/teste.out/teste");
  strcat(pathName, testNumber);
  strcat(pathName, ".out");

  return pathName;
}

int * programOutputData(int amountOfNumbersToBeRead){
  int * programOutput;
  if((programOutput = (int *) malloc(sizeof(int) * amountOfNumbersToBeRead)) == NULL){
    printf("No RAM Memory available!\n");
    exit(1);
  }

  for(int i = 0; i < amountOfNumbersToBeRead; i++){
    scanf("%d", &programOutput[i]);
  }

  return programOutput;
}

void treatInvalidArgc(int argc){
  if(isArgcValid(argc)) return;
  else{
    printf("Invalid argument to main! The program must have exactly one argument, the test number!\n");
    printf("Argc = %d", argc);
    exit(1);
  }
}

boolean areArraysEqual(int * correctTestOutput, int * programOutput, int sizeOfOutputs){
  for(int i = 0; i < sizeOfOutputs; i++){
    if(correctTestOutput[i] != programOutput[i]) return FALSE;
  }
  return TRUE;
}

void compareTestToProgram(int * correctTestOutput, int * programOutput, int sizeOfOutputs){
  if(areArraysEqual(correctTestOutput, programOutput, sizeOfOutputs))
    printf("Sorting passed on the test!\n");
  else printf("Sorting failed the test");
  return;
}

int main(int argc, char * argv[]){
  treatInvalidArgc(argc);
  char * testPath = filePath(argv[1]);
  int sizeOfOutputs = calculateFileSize(testPath);
  int * correctTestOutput = fileContent(testPath);
  int * programOutput = programOutputData(sizeOfOutputs);

  compareTestToProgram(correctTestOutput, programOutput, sizeOfOutputs);

  free(testPath);
  free(programOutput);
  free(correctTestOutput);
  return 0;
}