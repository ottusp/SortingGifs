#include "../gifenc-master/gifenc.h"
#include "../sorting/selectionSort/sorting/selectionSort.h"
#include <stdio.h>
#include <stdlib.h>

#define WIDTH 33
#define HEIGHT 33

FILE * criaPastaParaLeitura(const char * nomeDaPasta){
    FILE * pasta = fopen(nomeDaPasta, "r");
    if(pasta == NULL){
        printf("Não foi possível abrir a pasta! Sem memória dinâmica disponível!\n");
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
    const char nomeDaPasta[] = "paleta.txt";

    int tamanhoDaPasta = calculaTamanhoDaPasta(nomeDaPasta);

    FILE * pastaDaPaleta = criaPastaParaLeitura(nomeDaPasta);

    uint8_t * paleta = (uint8_t*) malloc(sizeof(uint8_t) * tamanhoDaPasta);
    if(paleta == NULL) return NULL;

    for(int i = 0; i < tamanhoDaPasta; i++)
        fscanf(pastaDaPaleta, " %hhu,", &paleta[i]);

    destroiPasta(&pastaDaPaleta);
    return paleta;
}

int main(){
    int i, j;
    int pixel;
    uint8_t * paletaDeCores = paleta();

    /* create a GIF */
    ge_GIF *gif = ge_new_gif(
        "teste4.gif",  /* file name */
        WIDTH, HEIGHT,           /* canvas size */
        paletaDeCores,  /* color pallete */
        7,              /* palette depth == log2(# of colors) */
        0               /* infinite loop */
    );
    /* draw some frames */
    for (i = 0; i < 270; i++) {
        for (j = 0; j < WIDTH; j ++){
            scanf(" %d,", &pixel);
            for(int k = 0; k < HEIGHT; k++)
                gif -> frame[j + k*HEIGHT] = (((pixel % 33) + pixel / 33) - k + 66) % 33;
        }
        ge_add_frame(gif, 5);
    }
    /* remember to close the GIF */
    ge_close_gif(gif);
    return 0;
}
