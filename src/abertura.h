#define VIDEO GFX_AUTODETECT
#define LARGURA 1024
#define ALTURA 768
#define TAM 30
#define CORES 32

#include <allegro.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Abertura (void);
void highcolor_fade_in_Abertura(BITMAP *bmp_orig, int speed);
void highcolor_fade_out_Abertura(int speed);
void carregaSom_Abertura (SAMPLE **s, char arq[]);
void carregaImg_Abertura (BITMAP **b, char arq[]);
