/*
FRANKENSTEIN'S BEJEWLED
VERS�O: 1.4.9.2 - Vers�o Desenvolvimento Pr�via 1.5
�LTIMA ATUALIZACAO: 20/12/2006
AUTORES: Francisco Viegas Vianna, Jonas Ar�as Fragozo de Souza e Rafael Oliveira Lopes.
PARA INFORMA��ES SOBRE O JOGO, CONSULTAR MANUAL

IT'S ALIVE! FRANKENSTEIN'S ALIVE!
*/

/* Bibliotecas */

#include <allegro.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "abertura.h"

/* Constantes */

#define VIDEO              		 GFX_AUTODETECT
#define LARGURA				     1024
#define ALTURA				     768
#define CORES              		 32
#define TAM_GRADE			     10
#define TAM_CELULA			 	 50
#define ESPESSURA_MARCACAO 		 3
#define POS_X_INIC				 466
#define POS_Y_INIC				 200
#define L_JOIA             		 48
#define A_JOIA             		 48

/*Posicao dos pontos no jogo */
#define INICIO_X_PONTOS			 152
#define INICIO_Y_PONTOS			 415
#define FIM_X_PONTOS			 306
#define FIM_Y_PONTOS			 469
#define MEIO_X_PONTOS			 (INICIO_X_PONTOS + FIM_X_PONTOS)/2
#define MEIO_Y_PONTOS      		 (INICIO_Y_PONTOS + FIM_Y_PONTOS)/2

/*Posicao do Tempo no jogo */
#define INICIO_X_TEMPO			 152
#define INICIO_Y_TEMPO			 545
#define FIM_X_TEMPO				 306
#define FIM_Y_TEMPO				 599
#define MEIO_X_TEMPO			 (INICIO_X_TEMPO + FIM_X_TEMPO)/2
#define MEIO_Y_TEMPO			 (INICIO_Y_TEMPO + FIM_Y_TEMPO)/2
#define TAMANHO_X_TEMPO			 (FIM_X_TEMPO - INICIO_X_TEMPO)
#define TAMANHO_Y_TEMPO		     (FIM_Y_TEMPO - INICIO_X_TEMPO)

/*Posicao do Nome no jogo */
#define INICIO_X_NOME			 202
#define INICIO_Y_NOME			 217

/*Posicoes de recordes na tela de Recordes */
#define INICIO_X_REC_NOME    	 80
#define INICIO_Y_REC_NOME    	 256
#define INICIO_X_REC_RECORDE	 564
#define INICIO_Y_REC_RECORDE	 256

/*Quantidade Jogadores*/
#define NUMERO_JOGADORES		 8

typedef struct _JOGADOR
{
	char nome[15];
	int pontuacao;
} JOGADOR;

/* Vari�veis globais */

volatile int tempo;

BITMAP *aux;
JOGADOR jog_atual;
FILE *recorde;

FONT *fonte_dado;
PALLETE *palleta_dado;
FONT *fonte_nome;
PALLETE *palleta_nome;
FONT *fonte_recordes;
PALLETE *palleta_recordes;

BITMAP *fundo_creditos;
BITMAP *fundo_menu;
BITMAP *fundo_jogo;
BITMAP *fundo_gameover;
BITMAP *fundo_instrucoes;
BITMAP *fundo_recordes;
BITMAP *fundo_pause;
BITMAP *tela_recorde_novo;
BITMAP *tela_nome;
BITMAP *tela_pause;
BITMAP *joia_vermelha;
BITMAP *joia_branca;
BITMAP *joia_laranja;
BITMAP *joia_rosa;
BITMAP *joia_verde;
BITMAP *joia_azul;
BITMAP *joia_amarela;
BITMAP *joia_vazio;
BITMAP *buffer_tempo;

SAMPLE *som_erro;


/* Prototipos de Fun��es */

void Abre_Arquivo(int opcao);
void Apaga (int lin, int col, int joias[TAM_GRADE][TAM_GRADE], int temp[TAM_GRADE][TAM_GRADE]);
void Apaga_Depois_de_cair(int lin, int col, int joias[TAM_GRADE][TAM_GRADE]);
void Apaga_Recordes(void);
int  Arquivo_Recordes(void);
void Atualiza_Ranking(JOGADOR jogador[NUMERO_JOGADORES], int posicao);
void Avisar_Erro (void);
void Caem_Joias (int joias[TAM_GRADE][TAM_GRADE]);
void Completar_Matriz (int joias[TAM_GRADE][TAM_GRADE]);
void Creditos(void);
void Desenha (int joias[TAM_GRADE][TAM_GRADE]);
void Desenha_Tempo(void);
void Desliga_Temporizadores_Tempo(void);
void Dica (int joias[TAM_GRADE][TAM_GRADE]);
void Diminui_Segundos(void);
int  Eh_Vizinha (int cel1[2], int cel2[2]);
void Escolher_Joia (int nro, int i, int j, BITMAP *joia);
int  Espera_Clique (int joias[TAM_GRADE][TAM_GRADE]);
void Fecha_Arquivo(void);
void Finalizar (void);
int  Game_Over(void);
void Inicia_aux (void);
int  Iniciar (void);
void Instrucoes(void);
void Jogo (void);
void Jogo_Pausado(int joias[TAM_GRADE][TAM_GRADE]);
void Liga_Temporizadores_Tempo(void);
void Marcar_Celula (int cel[2]);
void Nome (void);
void PiscaTela(void);
void Preencher_Matriz (int joias[TAM_GRADE][TAM_GRADE]);
void Prepara_Para_Apagar(int lin1, int col1, int lin2, int col2, int joias[TAM_GRADE][TAM_GRADE]);
void Programa (void);
void Recordes(void);
void Recordes_Na_Tela(void);
void Recupera_Recordes(JOGADOR jogador[NUMERO_JOGADORES]);
void Salva_Recordes(JOGADOR jogador[NUMERO_JOGADORES]);
void Troca_Valores (int cel1[2], int cel2[2], int joias[TAM_GRADE][TAM_GRADE]);
int  Trocas_Possiveis(int joias[TAM_GRADE][TAM_GRADE], int dica);
int  Verifica_Depois_de_cair(int joias[TAM_GRADE][TAM_GRADE]);
int  Verifica_Posicao_Ranking(JOGADOR jogador[NUMERO_JOGADORES]);
int  Verifica_Sequencia (int lin, int col, int joias[TAM_GRADE][TAM_GRADE]);
int  Verifica_Sequencia_temp (int lin, int col, int temp[TAM_GRADE][TAM_GRADE]);
void Carrega_Tudo(void);
void Fecha_Tudo(void);

/* ------------------------------------------------------------------------------------- */

/*
FUN��O: main
AUTOR: Francisco, Jonas e Rafael
UTILIDADE: Fun��o principal do programa.
PARAMETROS: void
*/

int main (void)
{
	srand (time(NULL));

	if (!(Iniciar()))
	{
		Finalizar();
		return -1;
	}

	Abertura();

	Carrega_Tudo();

	Programa();

	Fecha_Tudo();

	Finalizar();

	return 0;
}

END_OF_MAIN()

/* ------------------------------------------------------------------------------------- */

/*
FUN��O: Iniciar
AUTOR: Francisco, Jonas e Rafael
UTILIDADE: Inicializa componentes necess�rios para execu��o do programa.
PARAMETROS: void
*/

int Iniciar (void)
{
	allegro_init();

	if (install_keyboard() < 0)
	{
		puts("Erro ao inicializar o Teclado!");
		return FALSE;
	}

	if (install_mouse() < 0)
	{
		puts("Erro ao inicializar o Mouse!");
		return FALSE;
	}

	if (install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL) < 0)
	{
		puts("Erro ao inicializar o Som!");
		return FALSE;
	}

	set_color_depth (CORES);

	if (set_gfx_mode (VIDEO, LARGURA, ALTURA, 0, 0) < 0)
	{
		printf ("Erro ao inicializar o Modo Grafico!");
		return FALSE;
	}

	aux = create_bitmap (LARGURA, ALTURA);

	return TRUE;
}

/* ------------------------------------------------------------------------------------- */

/*
FUN��O: Finaliza
AUTOR: Francisco, Jonas e Rafael
UTILIDADE: Finaliza o programa.
PARAMETROS: void
*/
void Finalizar (void)
{
	destroy_bitmap(aux);
	remove_keyboard();
	allegro_exit();
}

/* ------------------------------------------------------------------------------------- */

/*
FUN��O: Programa
AUTOR: Francisco, Jonas e Rafael
UTILIDADE: Possui a estrutura do programa em si.
PARAMETROS: void
*/

void Programa (void)
{
	int ctrl = 0;
	int desenhado = 0;

	while (!key[KEY_ESC])
	{
		if (!desenhado)
		{
			show_mouse(NULL);
			draw_sprite (screen, fundo_menu, 0,0);
			show_mouse(screen);
			desenhado = 1;
		}

		if (ctrl ||((mouse_b == 1) && ((mouse_x >= 500 && mouse_x <= 700) && (mouse_y >= 330 && mouse_y <= 400))))
		{
			while(mouse_b == 1);
			if (!ctrl)
			{
				Instrucoes();
				Nome();
			}
			Jogo();
			desenhado = ctrl = Game_Over();
		}
		if ((mouse_b == 1) && ((mouse_x >= 470 && mouse_x <= 760) && (mouse_y >= 430 && mouse_y <= 500)))
		{
			while(mouse_b == 1);
			Recordes();
			desenhado = 0;
		}
		if ((mouse_b == 1) && ((mouse_x >= 490 && mouse_x <= 740) && (mouse_y >= 520 && mouse_y <= 590)))
		{
			while(mouse_b == 1);
			Creditos();
			desenhado = 0;
		}
		if ((mouse_b == 1) && ((mouse_x >= 540 && mouse_x <= 690) && (mouse_y >= 605 && mouse_y <= 670)))
		{
			while(mouse_b == 1);
			return;
		}
	}
}

/* ------------------------------------------------------------------------------------- */

/*
FUN��O: Jogo
AUTOR: Francisco, Jonas e Rafael
UTILIDADE: Possui a estrutura do jogo em si.
PARAMETROS: void
*/

void Jogo (void)
{
	int joias[TAM_GRADE][TAM_GRADE];
	int cel1[2], cel2[2];

	jog_atual.pontuacao = 0;
	tempo = 60;

	Preencher_Matriz(joias);
	Desenha(joias);

	Liga_Temporizadores_Tempo();

	while (!key[KEY_ESC] && (tempo > 0) && (Trocas_Possiveis(joias, 0)))
	{
		if (!Espera_Clique(joias)) break;
		Marcar_Celula(cel1);

		if (!Espera_Clique(joias)) break;
		Marcar_Celula(cel2);

		if (Eh_Vizinha(cel1, cel2))
		{
			Desliga_Temporizadores_Tempo();
			Troca_Valores(cel1, cel2, joias);
			Desenha(joias);
			Prepara_Para_Apagar(cel1[0], cel1[1], cel2[0], cel2[1], joias);
			Desenha(joias);
			while(Verifica_Depois_de_cair(joias));
			Liga_Temporizadores_Tempo();
		}
		else
		{
			Avisar_Erro();
		}

		Desenha(joias);
	}

	Desliga_Temporizadores_Tempo();

	while (key[KEY_ESC]);
}

/* ------------------------------------------------------------------------------------- */

/*
FUN��O: Desenha
AUTOR: Francisco
UTILIDADE: Desenha a grade com suas j�ias, devidamente preenchidas pela Escolher_Joia
PARAMETROS: joias[TAM_GRADE][TAM_GRADE] -> Matriz de j�ias.
*/

void Desenha (int joias[TAM_GRADE][TAM_GRADE])
{
	int i,j;
	BITMAP *buffer;

	buffer = load_bitmap("../grafics/fundo-jogo-oficial.tga",NULL);
	if (buffer == NULL) exit(1);

	for (i=0; i<TAM_GRADE; i++)
	{
		for (j=0; j<TAM_GRADE; j++)
		{
			Escolher_Joia (joias[i][j], i, j, buffer);
		}
	}

	Inicia_aux();
	textprintf_centre_ex (aux, fonte_dado, MEIO_X_PONTOS, MEIO_Y_PONTOS -8, makecol(255, 255, 255),makecol (255,0,255),"%d", jog_atual.pontuacao);
	textprintf_ex (aux, fonte_nome, INICIO_X_NOME, INICIO_Y_NOME-4, makecol(255,255,0),makecol (255,0,255), jog_atual.nome);
	textprintf_centre_ex (aux, fonte_dado, MEIO_X_TEMPO, MEIO_Y_TEMPO -8, makecol(255, 255, 255),makecol (255,0,255),"%02d:%02d", tempo/60, tempo%60);
	draw_sprite (buffer, aux, 0,0);

	show_mouse(NULL);
	blit (buffer,screen,0,0,0,0,LARGURA,ALTURA);
	show_mouse(screen);

	destroy_bitmap(buffer);
}

/* ------------------------------------------------------------------------------------- */

/*
FUN��O: Preencher_Matriz
AUTOR: Francisco e Rafael
UTILIDADE: Preenche os valores da matriz com n�meros que ser�o relacionados � sua joia.
PARAMETROS: joias[TAM_GRADE][TAM_GRADE] -> Matriz de j�ias.
*/

void Preencher_Matriz (int joias[TAM_GRADE][TAM_GRADE])
{
	int i,j;

	for (i=0; i<TAM_GRADE; i++)
	{
		for (j=0; j<TAM_GRADE; j++)
		{
			/* A condicao deste do-while faz que n�o aparecam 3 joias iguais em
			   sequencia na vertical nem na horizontal. */
			do
			{
				joias[i][j] = (rand() % 7) + 1;
			}
			while (   ((i >= 2) && ((joias[i][j] == joias[i-1][j]) && (joias[i][j] == joias[i-2][j]))) ||
				      ((j >= 2) && ((joias[i][j] == joias[i][j-1]) && (joias[i][j] == joias[i][j-2])))
				  );
		}
	}
}

/* ------------------------------------------------------------------------------------- */

/*
FUN��O: Marcar_Celula
AUTOR: Francisco
UTILIDADE: Marca as bordas da celula selecionada com a cor vermelha
PARAMETROS: cel[2] -> Valor da linha e coluna da c�lula selecionada
*/

void Marcar_Celula (int cel[2])
{
	int i;

	/* Recebe o valor da linha e da coluna da c�lula selecionada */
	cel[0] = (mouse_x - POS_X_INIC)/TAM_CELULA;
	cel[1] = (mouse_y - POS_Y_INIC)/TAM_CELULA;

	/* Desenha as bordas vermelhas */
	show_mouse (NULL);
	for (i=0; i<ESPESSURA_MARCACAO; i++)
	{
		rect (screen, POS_X_INIC + cel[0] * TAM_CELULA + i,
					  POS_Y_INIC + cel[1] * TAM_CELULA + i,
					  POS_X_INIC + cel[0] * TAM_CELULA + TAM_CELULA - i,
					  POS_Y_INIC + cel[1] * TAM_CELULA + TAM_CELULA - i,
					  makecol(255,0,0));
	}
	show_mouse (screen);
}

/* ------------------------------------------------------------------------------------- */

/*
FUN��O: Troca_Valores
AUTOR: Francisco, Jonas e Rafael
UTILIDADE: Troca os valores na matriz relacionados �s duas c�lulas selecionadas para trocar.
PARAMETROS: cel1[2] -> Valores da linha e coluna da primeira c�lula selecionada
			cel2[2] -> Valores da linha e coluna da segunda c�lula selecionada.
			joias[TAM_GRADE][TAM_GRADE] -> Matriz de j�ias.
*/

void Troca_Valores (int cel1[2], int cel2[2], int joias[TAM_GRADE][TAM_GRADE])
{
	int temp;

	temp = joias[cel1[0]][cel1[1]];
	joias[cel1[0]][cel1[1]] = joias[cel2[0]][cel2[1]];
	joias[cel2[0]][cel2[1]] = temp;
}

/* ------------------------------------------------------------------------------------- */

/*
FUN��O: Avisar_Erro
AUTOR: Francisco
UTILIDADE: Toca um som para avisar de que n�o houve troca.
PARAMETROS: som -> Som que representa o erro.
*/

void Avisar_Erro (void)
{
	play_sample (som_erro, 255, 128, 1000, FALSE);
}

/* ------------------------------------------------------------------------------------- */

/*
FUN��O: Espera_Clique
AUTOR: Francisco, Jonas e Rafael
UTILIDADE: Aguarda um clique do usu�rio em uma posicao valida da tela do jogo.
           Evita que clique fora dos limites e nas linhas.
PARAMETROS: joias[TAM_GRADE][TAM_GRADE] -> Matriz de J�ias
*/

int Espera_Clique (int joias[TAM_GRADE][TAM_GRADE])
{
	int a = POS_X_INIC + TAM_GRADE * TAM_CELULA;
	int b = POS_Y_INIC + TAM_GRADE * TAM_CELULA;

	while (1)
	{
		if ((key[KEY_ESC]) || (tempo < 0))
			return 0;
		if ((mouse_b == 1) && ((mouse_x > 83 && mouse_x < 147) && (mouse_y > 685 && mouse_y < 716)))
			return 0; /* sair */
		if (mouse_b == 1 && ((mouse_x > 183 && mouse_x < 273) && (mouse_y > 685 && mouse_y < 716)))
			Jogo_Pausado(joias);
		if (mouse_b == 1 && ((mouse_x > 305 && mouse_x < 376) && (mouse_y > 685 && mouse_y < 716)))
			Dica(joias);
		if((mouse_b == 1) && ((mouse_x > POS_X_INIC) && (mouse_x < a) && (mouse_y > POS_Y_INIC) && (mouse_y < b)) && (mouse_x % TAM_CELULA != 0))
			break;
	}
	while (mouse_b == 1);
	return 1;
}

/* ------------------------------------------------------------------------------------- */

/*
FUN��O: Eh_Vizinha
AUTOR: Francisco
UTILIDADE: Verifica se duas celulas s�o vizinhas na matriz.
PARAMETROS: cel1[2] -> Linha e coluna da primeira c�lula
			cel2[2] -> Linha e coluna da segunda c�lula
*/

int Eh_Vizinha (int cel1[2], int cel2[2])
{
	if ( (((cel1[0] - cel2[0]==1) || (cel2[0] - cel1[0]==1)) && (cel1[1] - cel2[1]==0)) ||
	     (((cel1[1] - cel2[1]==1) || (cel2[1] - cel1[1]==1)) && (cel1[0] - cel2[0]==0))	)
		return 1;
	else
		return 0;
}

/* ------------------------------------------------------------------------------------- */

/*
FUN��O: Escolher_Joia
AUTOR: Jonas e Francisco
UTILIDADE: Relaciona o valor da matriz com o desenho da joia, e depois desenha na tela a joia.
PARAMETROS: nro  -> numero do valor na matriz
			col  -> Valor da coluna da c�lula selecionada
			lin  -> Valor da linha da c�lula selecionada
			joia  -> Bitmap de buffer para armazenar a j�ia.
*/

void Escolher_Joia (int nro, int col, int lin, BITMAP *joia)
{
	switch (nro)
	{
		case 1:
		{
			draw_sprite (joia, joia_vermelha, POS_X_INIC + col*TAM_CELULA + (TAM_CELULA - L_JOIA)/2,
						   POS_Y_INIC + lin*TAM_CELULA + (TAM_CELULA - A_JOIA)/2);
			break;
		}
		case 2:
		{
			draw_sprite (joia, joia_branca, POS_X_INIC + col*TAM_CELULA + (TAM_CELULA - L_JOIA)/2,
						   POS_Y_INIC + lin*TAM_CELULA + (TAM_CELULA - A_JOIA)/2);
			break;
		}
		case 3:
		{
			draw_sprite (joia, joia_laranja, POS_X_INIC + col*TAM_CELULA + (TAM_CELULA - L_JOIA)/2,
						   POS_Y_INIC + lin*TAM_CELULA + (TAM_CELULA - A_JOIA)/2);
			break;
		}
		case 4:
		{
			draw_sprite (joia, joia_rosa, POS_X_INIC + col*TAM_CELULA + (TAM_CELULA - L_JOIA)/2,
						   POS_Y_INIC + lin*TAM_CELULA + (TAM_CELULA - A_JOIA)/2);
			break;
		}
		case 5:
		{
			draw_sprite (joia, joia_verde, POS_X_INIC + col*TAM_CELULA + (TAM_CELULA - L_JOIA)/2,
						   POS_Y_INIC + lin*TAM_CELULA + (TAM_CELULA - A_JOIA)/2);
			break;
		}
		case 6:
		{
			draw_sprite (joia, joia_azul, POS_X_INIC + col*TAM_CELULA + (TAM_CELULA - L_JOIA)/2,
						   POS_Y_INIC + lin*TAM_CELULA + (TAM_CELULA - A_JOIA)/2);
			break;
		}
		case 7:
		{
			draw_sprite (joia, joia_amarela, POS_X_INIC + col*TAM_CELULA + (TAM_CELULA - L_JOIA)/2,
						   POS_Y_INIC + lin*TAM_CELULA + (TAM_CELULA - A_JOIA)/2);
			break;
		}

		default: draw_sprite (joia, joia_vazio, POS_X_INIC + col*TAM_CELULA + (TAM_CELULA - L_JOIA)/2,
						       POS_Y_INIC + lin*TAM_CELULA + (TAM_CELULA - A_JOIA)/2);
	}
}

/* ------------------------------------------------------------------------------------- */

/*
FUN��O: Verifica_Sequencia
AUTOR: Francisco, Jonas e Rafael
UTILIDADE: Verifica qual a sequ�ncia (e se essa ocorreu) formada ap�s a troca.
PARAMETROS: lin   -> Valor da linha da c�lula verificada
			col   -> Valor da coluna da c�lula verificada
			joias[TAM_GRADE][TAM_GRADE] -> Matriz de joias com os valores de joias
*/

int Verifica_Sequencia (int lin, int col, int joias[TAM_GRADE][TAM_GRADE])
{
	int k;

	k = lin-2;
	if (k<0) k = 0;

	for (; ((k <= lin+2) && (k < TAM_GRADE)); k++)
	{
		if (((joias[k][col] == joias[k+1][col]) && (joias[k][col] == joias[k+2][col])) && (k+2 < TAM_GRADE))
		{
			if ((joias[k][col] == joias[k+3][col]) && (k+3 < TAM_GRADE))
			{
				if ((joias[k][col] == joias[k+4][col]) && (k+4 < TAM_GRADE))
				{
					return 1;
				}
				return 1;
			}
			return 1;
		}
	}

	k = col-2;
	if (k<0) k = 0;

	for (; ((k <= col+2) && (k < TAM_GRADE)); k++)
	{
		if (((joias[lin][k] == joias[lin][k+1]) && (joias[lin][k] == joias[lin][k+2]))  && (k+2 < TAM_GRADE))
		{
			if ((joias[lin][k] == joias[lin][k+3]) && (k+3 < TAM_GRADE))
			{
				if ((joias[lin][k] == joias[lin][k+4])  && (k+4 < TAM_GRADE))
				{
					return 1;
				}
				return 1;
			}
			return 1;
		}
	}
	return 0;
}

/* ------------------------------------------------------------------------------------- */

/*
FUN��O: Apaga
AUTOR: Francisco, Jonas e Rafael
UTILIDADE: Marca na matriz tempor�ria quais s�o as j�ias vizinhas que possuem mesma j�ia, para que depois sejam apagadas.
PARAMETROS: lin   -> Valor da linha da c�lula verificada
			col   -> Valor da coluna da c�lula verificada
			joias[TAM_GRADE][TAM_GRADE] -> Matriz de joias com os valores de joias
			temp[TAM_GRADE][TAM_GRADE]  -> matriz temporaria para marcar as joias a serem apagadas.
*/

void Apaga (int lin, int col, int joias[TAM_GRADE][TAM_GRADE], int temp[TAM_GRADE][TAM_GRADE])
{
	int k;

	k = lin-2;
	if (k<0) k = 0;

	for (; ((k <= lin+2) && (k < TAM_GRADE)); k++)
	{
		if (((joias[k][col] == joias[k+1][col]) && (joias[k][col] == joias[k+2][col])) && (k+2 < TAM_GRADE))
		{
			if ((joias[k][col] == joias[k+3][col]) && (k+3 < TAM_GRADE))
			{
				if ((joias[k][col] == joias[k+4][col]) && (k+4 < TAM_GRADE))
				{
					temp[k+4][col] = 1;
				}
				temp[k+3][col] = 1;
			}
			temp[k][col] = temp[k+1][col] = temp[k+2][col] = 1;
		}
	}

	k = col-2;
	if (k<0) k = 0;

	for (; ((k <= col+2) && (k < TAM_GRADE)); k++)
	{
		if (((joias[lin][k] == joias[lin][k+1]) && (joias[lin][k] == joias[lin][k+2]))  && (k+2 < TAM_GRADE))
		{
			if ((joias[lin][k] == joias[lin][k+3]) && (k+3 < TAM_GRADE))
			{
				if ((joias[lin][k] == joias[lin][k+4])  && (k+4 < TAM_GRADE))
				{
					temp[lin][k+4] = 1;
				}
				temp[lin][k+3] = 1;
			}
			temp[lin][k] = temp[lin][k+1] = temp[lin][k+2] = 1;
		}
	}
}

/* ------------------------------------------------------------------------------------- */

/*
FUN��O: Prepara_Para_Apagar
AUTOR: Rafael e Jonas
UTILIDADE: Cria uma matriz tempor�ria para armazenar os vizinhos que sumir�o, usando o Verifica_Sequencia e em seguida o Apaga.
           Logo ap�s, "apaga" a j�ia colocando valor 0 na posi��o da matriz
PARAMETROS: lin1 -> Valor da linha do primeiro quadrado selecionado
			col1 -> Valor da coluna do primeiro quadrado selecionado
			lin2 -> Valor da linha do segundo quadrado selecionado
			col2 -> Valor da coluna do segundo quadrado selecionado
			joias[TAM_GRADE][TAM_GRADE] -> Matriz de j�ias
*/

void Prepara_Para_Apagar(int lin1, int col1, int lin2, int col2, int joias[TAM_GRADE][TAM_GRADE])
{
	int temp[TAM_GRADE][TAM_GRADE];
	int i, j;
	int cel1[2], cel2[2];

	cel1[0] = lin1;
	cel1[1] = col1;
	cel2[0] = lin2;
	cel2[1] = col2;

	/* Inicia a matriz temporaria */
	for (i = 0; i<TAM_GRADE; i++)
	{
		for (j = 0; j<TAM_GRADE; j++)
		{
			temp[i][j] = 0;
		}
	}

	if (Verifica_Sequencia(lin1 , col1 , joias) || (Verifica_Sequencia(lin2 , col2 , joias)))
	{
		Apaga(lin1 , col1 , joias , temp);
		Apaga(lin2 , col2 , joias , temp);
	}
	else
	{
		Troca_Valores(cel1, cel2, joias);
		return;
	}

	/* Zera a matriz joias nas posicoes indicadas pela matriz temp */
	for (i = 0; i<TAM_GRADE; i++)
	{
		for (j = 0; j<TAM_GRADE; j++)
		{
			if (temp[i][j])
			{
				joias[i][j] = 0;
				jog_atual.pontuacao += 5;
				tempo++;
			}
		}
	}

	Desenha(joias);
	Caem_Joias(joias);
	Completar_Matriz(joias);
}

/* ------------------------------------------------------------------------------------- */

/*
FUN��O: Diminui_Segundos
AUTOR: Rafael
UTILIDADE: Diminui um segundo na contagem do jogo.
PARAMETROS: void
*/

void Diminui_Segundos(void)
{
	tempo--;
}

/* ------------------------------------------------------------------------------------- */

/*
FUN��O: Desenha_Tempo
AUTOR: Rafael
UTILIDADE: Desenha o tempo na tela.
PARAMETROS: void
*/

void Desenha_Tempo(void)
{
	draw_sprite(buffer_tempo, fundo_jogo, 0,0);

	show_mouse(NULL);
	Inicia_aux();
	textprintf_centre_ex (aux, fonte_dado, MEIO_X_TEMPO, MEIO_Y_TEMPO -8, makecol(255, 255, 255),makecol (255,0,255),"%02d:%02d", tempo/60, tempo%60);
	draw_sprite (buffer_tempo, aux, 0,0);
	blit (buffer_tempo, screen, INICIO_X_TEMPO, INICIO_Y_TEMPO, INICIO_X_TEMPO, INICIO_Y_TEMPO, TAMANHO_X_TEMPO, TAMANHO_Y_TEMPO);
	show_mouse(screen);
}

/* ------------------------------------------------------------------------------------- */

/*
FUN��O: Creditos
AUTOR: Francisco
UTILIDADE: Chama a tela de cr�ditos.
PARAMETROS: void
*/

void Creditos(void)
{
	show_mouse(NULL);
	blit (fundo_creditos, screen, 0,0,0,0, LARGURA, ALTURA);
	show_mouse(screen);

	while(!key[KEY_ESC] && !(mouse_b == 1));
	while(key[KEY_ESC] || (mouse_b == 1));
}

/* ------------------------------------------------------------------------------------- */

/*
FUN��O: Completar_Matriz
AUTOR: Francisco
UTILIDADE: Completa a matriz onde tiver zero depois de cair
PARAMETROS: joias[TAM_GRADE][TAM_GRADE] -> Matriz de j�ias.
*/
void Completar_Matriz (int joias[TAM_GRADE][TAM_GRADE])
{
	int i,j;
	for (i=0; i<TAM_GRADE; i++)
	{
		for (j=0; j<TAM_GRADE; j++)
		{
			if (joias[i][j] == 0)
			{
				joias[i][j] = (rand() % 7) + 1;
			}
		}
	}
}

/* ------------------------------------------------------------------------------------- */

/*
FUN��O: Caem_Joias
AUTOR: Francisco
UTILIDADE: Faz os 'zeros' da matriz subirem para o topo da mesma.
PARAMETROS: joias[TAM_GRADE][TAM_GRADE] -> Matriz de j�ias.
*/
void Caem_Joias (int joias[TAM_GRADE][TAM_GRADE])
{
	int i,j,cont;

	for (i=0; i<TAM_GRADE; i++)
	{
		for (j=0; j<TAM_GRADE; j++)
		{
			if ((joias[i][j] == 0) && (j != 0))
			{
				cont = j;
				while ((cont > 0) && (joias[i][cont-1] != 0))
				{
					joias[i][cont] = joias[i][cont-1];
					joias[i][cont-1] = 0;

					cont--;
				}
			}
		}
	}
}

/* ------------------------------------------------------------------------------------- */

/*
FUN��O: Liga_Temporizadores_Tempo
AUTOR: Rafael
UTILIDADE: Volta a contar o tempo.
PARAMETROS: void
*/

void Liga_Temporizadores_Tempo(void)
{
	LOCK_VARIABLE(tempo);
	LOCK_FUNCTION(Diminui_Segundos);
	LOCK_FUNCTION(Desenha_Tempo);

	install_int(Desenha_Tempo, 1000);
	install_int(Diminui_Segundos, 1000);
}

/* ------------------------------------------------------------------------------------- */

/*
FUN��O: Desliga_Temporizadores_Tempo
AUTOR: Rafael
UTILIDADE: Para de contar o tempo.
PARAMETROS: void
*/

void Desliga_Temporizadores_Tempo(void)
{
	remove_int(Diminui_Segundos);
	remove_int(Desenha_Tempo);
}

/* ------------------------------------------------------------------------------------- */

/*
FUN��O: Jogo_Pausado
AUTOR: Jonas e Rafael
UTILIDADE: Promove a pausa do jogo, com as devidas condi��es para que o jogador n�o se aproveite dela.
PARAMETROS: joias[TAM_GRADE][TAM_GRADE] -> matriz com as joias.
*/

void Jogo_Pausado(int joias[TAM_GRADE][TAM_GRADE])
{
	Desliga_Temporizadores_Tempo();

	show_mouse(NULL);
	blit (fundo_jogo, screen, 0,0,0,0, LARGURA, ALTURA);
	draw_sprite(screen, fundo_pause, (LARGURA-444)/2,(ALTURA-194)/2);
	show_mouse(screen);

	while (mouse_b == 1);
	while (1)
	{
		if (mouse_b == 1 && ((mouse_x > 141 && mouse_x < 233) && (mouse_y > 690 && mouse_y < 716)))
			break;
	}
	while (mouse_b == 1);

	Desenha(joias);

	Liga_Temporizadores_Tempo();
}

/* ------------------------------------------------------------------------------------- */

/*
FUN��O: Verifica_Depois_de_cair
AUTOR: Jonas
UTILIDADE: Verifica se novas sequ�ncias s�o formadas depois de ca�rem as j�ias.
PARAMETROS: joias[TAM_GRADE][TAM_GRADE] -> Matriz de j�ias
*/

int Verifica_Depois_de_cair(int joias[TAM_GRADE][TAM_GRADE])
{
	int i, j;

	for (i = 0; i <TAM_GRADE; i++)
	{
		for (j = 0; j < TAM_GRADE; j++)
		{
			if (Verifica_Sequencia(i ,j, joias))
			{
				Apaga_Depois_de_cair(i, j, joias);
				Desenha(joias);
				return 1;
			}
		}
	}
	return 0;
}

/* ------------------------------------------------------------------------------------- */

/*
FUN��O: Apaga_Depois_de_cair
AUTOR: Jonas
UTILIDADE: Se novas sequ�ncias s�o formadas, apaga essas sequ�ncias e fazem as de cima destas ca�rem.
PARAMETROS: lin -> linha da j�ia sendo verificada
			col -> coluna da j�ia sendo verificada
			joias[TAM_GRADE][TAM_GRADE] -> Matriz de j�ias
*/

void Apaga_Depois_de_cair(int lin, int col, int joias[TAM_GRADE][TAM_GRADE])
{
	int temp[TAM_GRADE][TAM_GRADE];
	int i, j;

	for (i = 0; i<TAM_GRADE; i++)
	{
		for (j = 0; j<TAM_GRADE; j++)
		{
			temp[i][j] = 0;
		}
	}

	Apaga(lin , col , joias , temp);

	/* Zera a matriz joias nas posicoes indicadas pela matriz temp */
	for (i = 0; i<TAM_GRADE; i++)
	{
		for (j = 0; j<TAM_GRADE; j++)
		{
			if (temp[i][j])
			{
				joias[i][j] = 0;
				jog_atual.pontuacao += 5;
				tempo++;
			}
		}
	}
	Desenha(joias);
	Caem_Joias (joias);
	Completar_Matriz (joias);
}

/* ------------------------------------------------------------------------------------- */

/*
FUN��O: Trocas_Possiveis
AUTOR: Jonas
UTILIDADE: Verifica se ainda existem trocas poss�veis.
PARAMETROS:	joias[TAM_GRADE][TAM_GRADE] -> Matriz de j�ias
			dica -> Indica se a fun��o foi chamada apenas pra verifica��o ou se foi apertado o bot�o de dica.
*/

int Trocas_Possiveis(int joias[TAM_GRADE][TAM_GRADE], int dica)
{
	int i, j, a;
	int temp[TAM_GRADE][TAM_GRADE];
	int cel1[2];
	int cel2[2];

	for (i = 0; i < TAM_GRADE; i++)
	{
		for (j = 0; j < TAM_GRADE; j++)
		{
			temp[i][j] = joias[i][j];
		}
	}

	for (i = 0; i < TAM_GRADE; i++)
	{
		for (j = 0; j < TAM_GRADE; j++)
		{
			if (i < (TAM_GRADE-1))
			{
				cel1[0] = i;
				cel1[1] = j;							 /* Horizontal*/
				cel2[0] = i+1;
				cel2[1] = j;
				Troca_Valores(cel1, cel2, temp);
				if (Verifica_Sequencia(cel1[0] , cel1[1] , temp) || (Verifica_Sequencia(cel2[0] , cel2[1] , temp)))
					if (!dica)
						return 1;
					else
					{
						Troca_Valores(cel1, cel2, temp);
						show_mouse (NULL);
						for (a=1; a<=ESPESSURA_MARCACAO; a++)
						{
							rect (screen, POS_X_INIC + cel1[0] * TAM_CELULA + a,
								  POS_Y_INIC + cel1[1] * TAM_CELULA + a,
								  POS_X_INIC + cel1[0] * TAM_CELULA + TAM_CELULA - a,
								  POS_Y_INIC + cel1[1] * TAM_CELULA + TAM_CELULA - a,
								  makecol(0, 250, 100));
						}
						for (a=1; a<=ESPESSURA_MARCACAO; a++)
						{
							rect (screen, POS_X_INIC + cel2[0] * TAM_CELULA + a,
								  POS_Y_INIC + cel2[1] * TAM_CELULA + a,
								  POS_X_INIC + cel2[0] * TAM_CELULA + TAM_CELULA - a,
								  POS_Y_INIC + cel2[1] * TAM_CELULA + TAM_CELULA - a,
								  makecol(0, 250, 100));
						}
						show_mouse (screen);
						return 2;
					}
				else
					Troca_Valores(cel1, cel2, temp);      /* Para destrocar */
			}
			if (j < (TAM_GRADE-1))
			{
				cel1[0] = i;
				cel1[1] = j;							 /* Vertical*/
				cel2[0] = i;
				cel2[1] = j+1;
				Troca_Valores(cel1, cel2, temp);
				if (Verifica_Sequencia(cel1[0] , cel1[1] , temp) || (Verifica_Sequencia(cel2[0] , cel2[1] , temp)))
					if (!dica)
						return 1;
					else
					{
						Troca_Valores(cel1, cel2, temp);
						show_mouse (NULL);
						for (a=1; a<=ESPESSURA_MARCACAO; a++)
						{
							rect (screen, POS_X_INIC + cel1[0] * TAM_CELULA + a,
								  POS_Y_INIC + cel1[1] * TAM_CELULA + a,
								  POS_X_INIC + cel1[0] * TAM_CELULA + TAM_CELULA - a,
								  POS_Y_INIC + cel1[1] * TAM_CELULA + TAM_CELULA - a,
								  makecol(0, 250, 100));
						}
						for (a=1; a<=ESPESSURA_MARCACAO; a++)
						{
							rect (screen, POS_X_INIC + cel2[0] * TAM_CELULA + a,
								  POS_Y_INIC + cel2[1] * TAM_CELULA + a,
								  POS_X_INIC + cel2[0] * TAM_CELULA + TAM_CELULA - a,
								  POS_Y_INIC + cel2[1] * TAM_CELULA + TAM_CELULA - a,
								  makecol(0, 250, 100));
						}
						show_mouse (screen);
						return 2;
					}
				else
					Troca_Valores(cel1, cel2, temp);      /* Para destrocar */
			}
		}
	}
	return 0;
}

/* ------------------------------------------------------------------------------------- */

/*
FUN��O: Dica
AUTOR: Jonas, Francisco e Rafael
UTILIDADE: Indica ao usu�rio um par de joias que ele pode trocar.
PARAMETROS:	bitmap  -> Bitmap auxiliar;
			joias[TAM_GRADE][TAM_GRADE] -> Matriz de j�ias.
*/

void Dica (int joias[TAM_GRADE][TAM_GRADE])
{
	if (jog_atual.pontuacao >=10)
	{
		Trocas_Possiveis(joias, 1);
		jog_atual.pontuacao -= 10;
		rest(1000);
		Desenha(joias);
	}
}

/* ------------------------------------------------------------------------------------- */

/*
FUN��O: Recupera_Recordes
AUTOR: Rafael e Francisco
UTILIDADE: Recupera os recordes j� existentes no arquivo.
PARAMETROS:	jogador -> Vetor da estrutura jogador, que representa o n�mero de entradas existentes no arquivo.
*/

void Recupera_Recordes(JOGADOR jogador[NUMERO_JOGADORES])
{
	int i,j;
	char temp[100];
	char *p;

	for (i=0; i<NUMERO_JOGADORES; i++)
	{
		strcpy(temp,"");
		fscanf(recorde, "%d", &jogador[i].pontuacao);
		fgets(temp,100,recorde);
		temp[strlen(temp)-1]='\0';
		for(j=0;temp[j] == ' '; j++);

		p = &temp[j];
		strcpy(jogador[i].nome,p);
	}
}
/* ------------------------------------------------------------------------------------- */

/*
FUN��O: Salva_Recordes
AUTOR: Rafael
UTILIDADE: Salva novos recordes no arquivo.
PARAMETROS:	jogador -> Vetor da estrutura jogador, que representa o n�mero de entradas existentes no arquivo.
*/

void Salva_Recordes(JOGADOR jogador[NUMERO_JOGADORES])
{
	int i;

	Fecha_Arquivo();
	Abre_Arquivo(2);
	for (i=0; i<NUMERO_JOGADORES; i++)
	{
		fprintf(recorde, "%d %s\n", jogador[i].pontuacao, jogador[i].nome);
	}
}
/* ------------------------------------------------------------------------------------- */

/*
FUN��O: Verifica_Posicao_Ranking
AUTOR: Rafael
UTILIDADE: Verifica a posi��o deste novo recorde no ranking.
PARAMETROS:	jogador -> Vetor da estrutura jogador, que representa o n�mero de entradas existentes no arquivo.
*/

int Verifica_Posicao_Ranking(JOGADOR jogador[NUMERO_JOGADORES])
{
	int i;

	for (i=0; i<NUMERO_JOGADORES; i++)
	{
		if (jog_atual.pontuacao > jogador[i].pontuacao)
		{
			return i;
		}
	}

	return -1;
}
/* ------------------------------------------------------------------------------------- */

/*
FUN��O: Atualiza_Ranking
AUTOR: Rafael
UTILIDADE: Atualiza o ranking, depois de um novo recorde ter sido adicionado.
PARAMETROS:	jogador -> Vetor da estrutura jogador, que representa o n�mero de entradas existentes no arquivo.
			posicao -> Posi��o do novo recorde.
*/

void Atualiza_Ranking(JOGADOR jogador[NUMERO_JOGADORES], int posicao)
{
	int i;

	for (i=NUMERO_JOGADORES; i>posicao; i--)
	{
		jogador[i].pontuacao = jogador[i-1].pontuacao;
		strcpy(jogador[i].nome, jogador[i-1].nome);
	}
	jogador[posicao].pontuacao = jog_atual.pontuacao;
	strcpy(jogador[posicao].nome, jog_atual.nome);
}

/* ------------------------------------------------------------------------------------- */

/*
FUN��O: Abre_Arquivo
AUTOR: Rafael
UTILIDADE: Abre o arquivo de recordes.
PARAMETROS:	opcao -> Representa como o arquivo dever� ser aberto, dependendo do caso.
*/

void Abre_Arquivo(int opcao)
{
	switch (opcao){
		case 1:
			recorde = fopen("records.bin", "r+");
			break;
		case 2:
			recorde = fopen("records.bin", "w+");
			break;
		case 3:
			recorde = fopen("records.bin", "r");
			break;
	}
	if (!recorde)
	{
		printf("Erro com o arquivo de recordes.");
		exit(1);
	}
}

/* ------------------------------------------------------------------------------------- */

/*
FUN��O: Fecha_Arquivo
AUTOR: Rafael
UTILIDADE: Fecha o do arquivo de recordes.
PARAMETROS:	void
*/

void Fecha_Arquivo(void)
{
	fclose(recorde);
}

/* ------------------------------------------------------------------------------------- */

/*
FUN��O: Arquivo_Recordes
AUTOR: Rafael
UTILIDADE: Faz a manipula��o do arquivo de recordes.
PARAMETROS:	void
*/

int Arquivo_Recordes(void)
{
	JOGADOR jogador[NUMERO_JOGADORES];
	int posicao_ranking;
	int atualizou = 0;

	Abre_Arquivo(1);
	Recupera_Recordes(jogador);

	posicao_ranking = Verifica_Posicao_Ranking(jogador);

	if (posicao_ranking >= 0)
	{
		Atualiza_Ranking(jogador, posicao_ranking);
		Salva_Recordes(jogador);
		atualizou = 1;
	}

	Fecha_Arquivo();

	return atualizou;
}

/* ------------------------------------------------------------------------------------- */

/*
FUN��O: Recordes
AUTOR: Rafael
UTILIDADE: Faz a manipula��o da tela de recordes e seus bot�es.
PARAMETROS:	void
*/

void Recordes(void)
{
	Recordes_Na_Tela();

	while(1)
	{
		if ((mouse_b == 1) && (((mouse_x >= 904) && (mouse_x <= 1014)) && ((mouse_y >= 717) && (mouse_y <= 759))))
		{
			while (mouse_b == 1);
			break;
		}
		if ((mouse_b == 1) && ((mouse_x >= 419 && mouse_x <= 628) && (mouse_y >= 722 && mouse_y <= 758 )))
		{
			while (mouse_b == 1);
			Apaga_Recordes();
			Recordes_Na_Tela();
		}
	}
}

/* ------------------------------------------------------------------------------------- */

/*
FUN��O: Recordes_Na_Tela
AUTOR: Rafael
UTILIDADE: Desenha a tela de recordes e insere os nomes nela.
PARAMETROS:	void
*/

void Recordes_Na_Tela(void)
{
	JOGADOR jogador[NUMERO_JOGADORES];
	int i, intervalo = 15;
	BITMAP *buffer;

	buffer = create_bitmap (LARGURA, ALTURA);
	if (!buffer)
	{
		printf("Erro com arquivo!");
		exit(1);
	}

	Abre_Arquivo(3);
	Recupera_Recordes(jogador);

	draw_sprite (buffer, fundo_recordes, 0,0);

	Inicia_aux();
	for (i = 0; i<NUMERO_JOGADORES; i++)
	{
		textprintf_ex(aux, fonte_recordes, INICIO_X_REC_NOME + 20, (INICIO_Y_REC_NOME + intervalo), makecol(255,255,255), makecol (255,0,255), "%s", jogador[i].nome);
		textprintf_ex(aux, fonte_recordes, INICIO_X_REC_RECORDE + 20, (INICIO_Y_REC_RECORDE + intervalo), makecol(255,255,255), makecol (255,0,255), "%d", jogador[i].pontuacao);
		intervalo += 54;
	}
	draw_sprite (buffer, aux, 0,0);

	show_mouse(NULL);
	blit(buffer, screen, 0,0,0,0, LARGURA, ALTURA);
	show_mouse(screen);

	Fecha_Arquivo();
	destroy_bitmap(buffer);
}

/* ------------------------------------------------------------------------------------- */

/*
FUN��O: Apaga_Recordes
AUTOR: Rafael
UTILIDADE: Apaga os recordes existentes.
PARAMETROS:	void
*/

void Apaga_Recordes(void)
{
	int i;

	Abre_Arquivo(2);

	for (i=0; i<NUMERO_JOGADORES; i++)
	{
		fprintf(recorde, "%d %s\n", 0, "FRANK");
	}

	Fecha_Arquivo();
}

/* ------------------------------------------------------------------------------------- */

/*
FUN��O: Instrucoes
AUTOR: Jonas
UTILIDADE: Desenha a tela de Instru��es.
PARAMETROS:	void
*/

void Instrucoes(void)
{
	show_mouse(NULL);
	blit (fundo_instrucoes, screen, 0,0,0,0, LARGURA, ALTURA);
	show_mouse(screen);

	while(mouse_b != 1);
	while(mouse_b == 1);
}

/* ------------------------------------------------------------------------------------- */

/*
FUN��O: Game_Over
AUTOR: Jonas
UTILIDADE: Desenha a tela de Game_Over.
PARAMETROS:	void
*/

int Game_Over(void)
{
	while (mouse_b == 1);
	if (Arquivo_Recordes())
	{
		draw_sprite (screen, tela_recorde_novo,210,280);
		while(!key[KEY_ENTER] && !(mouse_b == 1));
		while(key[KEY_ENTER] || (mouse_b == 1));
	}

	show_mouse(NULL);
	blit (fundo_gameover, screen, 0,0,0,0, LARGURA, ALTURA);
	show_mouse(screen);

	while(1)
	{
		if (mouse_b == 1 && ((mouse_x > 119 && mouse_x < 340) && (mouse_y > 652 && mouse_y < 683)))
		{
			while(mouse_b == 1);
			return 1;
		}
		if (mouse_b == 1 && ((mouse_x > 620 && mouse_x < 812) && (mouse_y > 652 && mouse_y < 683)))
		{
			while(mouse_b == 1);
			return 0;
		}
	}
}

/* ------------------------------------------------------------------------------------- */

/*
FUN��O: Nome
AUTOR: Francisco, Jonas e Rafael
UTILIDADE: Desenha e l� o nome do jogador.
PARAMETROS:	void
*/

void Nome(void)
{
	BITMAP *tela1;
	BITMAP *tela2;
	char c;
	char nome[10];
	int pos = 0, i;

	for (i=0; i<10; i++) nome[i] = '\0';

	tela1 = load_bitmap("../grafics/fundo-jogo-oficial.tga", NULL);
	tela2 = load_bitmap("../grafics/tela-nome-oficial.tga", NULL);

	if (!tela1)
	{
		printf("Erro com imagem");
		exit(1);
	}
	if (!tela2)
	{
		printf("Erro com imagem");
		exit(1);
	}

	show_mouse(NULL);
	draw_sprite(tela1, tela2, (LARGURA-449)/2,(ALTURA-194)/2);
	blit (tela1, screen, 0,0,0,0, LARGURA, ALTURA);
	show_mouse(screen);

	while (!key[KEY_ENTER] && (pos < 9))
	{
		clear_keybuf();
	   	c = readkey();
	   	if(c == 8 && pos > 0)
		{
		    pos--;
		    nome[pos]= '\0';
        }
		if( (c > 64 && c < 93)  || (c > 96 && c < 123) )
		{
		    nome[pos] = c;
		    pos++;

        }
        tela2 = load_bitmap("../grafics/tela-nome-oficial.tga", NULL);

		if (!tela1)
		{
			printf("Erro com imagem");
			exit(1);
		}

		show_mouse(NULL);
		Inicia_aux();
        textprintf_centre_ex(aux,fonte_nome,449/2,194/2+15,makecol(255,255,255),makecol (255,0,255),"%s",nome);
		draw_sprite (tela2, aux, 0,0);
		draw_sprite(tela1, tela2, (LARGURA-449)/2,(ALTURA-194)/2);
	    blit (tela1, screen, 0,0,0,0, LARGURA, ALTURA);
	    show_mouse(screen);
	}

	strcpy (jog_atual.nome, nome);
	destroy_bitmap(tela1);
	destroy_bitmap(tela2);

}

/* ------------------------------------------------------------------------------------- */
/*
FUN��O: Inicia_aux
AUTOR: Francisco
UTILIDADE: Cria o bitmap auxiliar.
PARAMETROS:	void
*/

void Inicia_aux (void)
{
	clear_to_color (aux, makecol(255,0,255));
}

/* ------------------------------------------------------------------------------------- */

/*
FUN��O: Carrega_Tudo
AUTOR: Rafael
UTILIDADE: Carrega BITMAPS, SAMPLES e FONTS
PARAMETROS:	void
*/
void Carrega_Tudo(void)
{
    /* Carrega as imagens */
    fundo_creditos = load_bitmap("../grafics/creditos-oficial.tga", NULL);
    if (!fundo_creditos)
    {
		printf("Erro com imagem!");
		exit(1);
	}

    fundo_menu = load_bitmap("../grafics/menu-oficial.tga", NULL);
    if (!fundo_menu)
    {
		printf("Erro com imagem!");
		exit(1);
	}

    fundo_jogo = load_bitmap("../grafics/fundo-jogo-oficial.tga", NULL);
    if (!fundo_jogo)
    {
		printf("Erro com imagem!");
		exit(1);
	}

    fundo_gameover = load_bitmap("../grafics/game-over-oficial.tga", NULL);
    if (!fundo_gameover)
    {
		printf("Erro com imagem!");
		exit(1);
	}

    fundo_instrucoes = load_bitmap("../grafics/instrucoes-oficial.tga", NULL);
    if (!fundo_instrucoes)
    {
		printf("Erro com imagem!");
		exit(1);
	}

    fundo_recordes = load_bitmap("../grafics/recordes-oficial.tga", NULL);
    if (!fundo_recordes)
    {
		printf("Erro com imagem!");
		exit(1);
	}

    tela_recorde_novo = load_bitmap("../grafics/recorde-oficial.tga", NULL);
    if (!tela_recorde_novo)
    {
		printf("Erro com imagem!");
		exit(1);
	}

    tela_nome = load_bitmap("../grafics/tela-nome-oficial.tga", NULL);
    if (!tela_nome)
    {
		printf("Erro com imagem!");
		exit(1);
	}

	fundo_pause = load_bitmap("../grafics/tela-pause-oficial.tga", NULL);
    if (!fundo_pause)
    {
		printf("Erro com imagem!");
		exit(1);
	}

	joia_vermelha = load_bitmap ("../grafics/vermelha.bmp", NULL);
    if (!joia_vermelha)
    {
		printf("Erro com imagem!");
		exit(1);
	}

	joia_branca = load_bitmap ("../grafics/branca.bmp", NULL);
    if (!joia_branca)
    {
		printf("Erro com imagem!");
		exit(1);
	}

	joia_laranja = load_bitmap ("../grafics/laranja.bmp", NULL);
    if (!joia_laranja)
    {
		printf("Erro com imagem!");
		exit(1);
	}

	joia_rosa = load_bitmap ("../grafics/rosa.bmp", NULL);
    if (!joia_rosa)
    {
		printf("Erro com imagem!");
		exit(1);
	}

	joia_verde = load_bitmap ("../grafics/verde.bmp", NULL);
    if (!joia_verde)
    {
		printf("Erro com imagem!");
		exit(1);
	}

	joia_azul = load_bitmap ("../grafics/azul.bmp", NULL);
    if (!joia_azul)
    {
		printf("Erro com imagem!");
		exit(1);
	}

	joia_amarela = load_bitmap ("../grafics/amarela.bmp", NULL);
    if (!joia_amarela)
    {
		printf("Erro com imagem!");
		exit(1);
	}

	joia_vazio = load_bitmap ("../grafics/vazio.bmp", NULL);
    if (!joia_vazio)
    {
		printf("Erro com imagem!");
		exit(1);
	}

	buffer_tempo = create_bitmap(LARGURA,ALTURA);
    if (!buffer_tempo)
    {
		printf("Erro com imagem!");
		exit(1);
	}

	/* Carrega as fontes */

	fonte_dado = load_font("../fonts/fontdado.pcx", *palleta_dado, NULL);
	if (!fonte_dado)
	{
		printf("Erro com fonte1");
		exit(1);
	}

	fonte_nome = load_font("../fonts/fontnome.pcx", *palleta_nome, NULL);
	if (!fonte_nome)
	{
		printf("Erro com fonte2");
		exit(1);
	}

	fonte_recordes = load_font("../fonts/fontrec.pcx", *palleta_recordes, NULL);
	if (!fonte_recordes)
	{
		printf("Erro com fonte3");
		exit(1);
	}

	/* Carrega os sons */

	som_erro = load_sample ("../audio/Error.wav");
	if (som_erro == NULL)
	{
		printf("Erro com som");
		exit(1);
	}
}

/* ------------------------------------------------------------------------------------- */

/*
FUN��O: Fecha_Tudo
AUTOR: Rafael
UTILIDADE: Fecha BITMAPS, SAMPLES e FONTS
PARAMETROS:	void
*/
void Fecha_Tudo(void)
{
	/* Fecha Imagens */
	destroy_bitmap(fundo_creditos);
	destroy_bitmap(fundo_menu);
	destroy_bitmap(fundo_jogo);
	destroy_bitmap(fundo_gameover);
	destroy_bitmap(fundo_instrucoes);
	destroy_bitmap(fundo_recordes);
	destroy_bitmap(fundo_pause);
	destroy_bitmap(tela_recorde_novo);
	destroy_bitmap(tela_nome);
	destroy_bitmap(joia_vermelha);
	destroy_bitmap(joia_branca);
	destroy_bitmap(joia_laranja);
	destroy_bitmap(joia_rosa);
	destroy_bitmap(joia_verde);
	destroy_bitmap(joia_azul);
	destroy_bitmap(joia_amarela);
	destroy_bitmap(joia_vazio);
	destroy_bitmap(buffer_tempo);

	/* Fecha sons */
	destroy_sample(som_erro);

	/* Fecha fontes */
	destroy_font(fonte_dado);
	destroy_font(fonte_nome);
	destroy_font(fonte_recordes);
}
