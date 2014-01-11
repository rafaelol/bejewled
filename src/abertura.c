#include "abertura.h"

void Abertura (void)
{
	BITMAP *buffer;
	SAMPLE *som, *grito, *som2, *som3;

	buffer = create_bitmap(LARGURA, ALTURA);

	carregaSom_Abertura(&som3, "../audio/thunder.wav");
	play_sample(som3, 255, 128, 1000, FALSE);
	rest (1000);

	carregaImg_Abertura(&buffer, "../grafics/img01.tga");
	highcolor_fade_in_Abertura(buffer, 3);

	carregaSom_Abertura(&som, "../audio/00.wav");
	play_sample(som, 255, 128, 1000, FALSE);

	carregaSom_Abertura(&som2, "../audio/a_thunder.wav");
	play_sample(som2, 255, 128, 1000, FALSE);
	rest (2500);

	carregaImg_Abertura(&buffer, "../grafics/img02.tga");

	play_sample(som, 255, 128, 1000, FALSE);

	carregaSom_Abertura(&som, "../audio/01.wav");
	play_sample(som, 1000, 128, 1000, FALSE);

	carregaSom_Abertura(&grito, "../audio/scream05.wav");
	play_sample(grito, 255, 128, 1000, FALSE);

	blit(buffer,screen,0,0,0,0,LARGURA,ALTURA);
	highcolor_fade_out_Abertura (5);
	rest(1000);

	destroy_sample(som);
	destroy_sample(som2);
	destroy_sample(som3);
	destroy_sample(grito);
	destroy_bitmap(buffer);
}

/* -------------------------------------------------------------------------------------- */

void highcolor_fade_in_Abertura(BITMAP *bmp_orig, int speed)
{
	BITMAP *bmp_buff;

	if ((bmp_buff = create_bitmap(SCREEN_W, SCREEN_H)))
	{
		int a;
		if (speed <= 0) speed = 16;

		for (a = 0; a < 256; a+=speed)
		{
			clear(bmp_buff);
			set_trans_blender(0,0,0,a);
			draw_trans_sprite(bmp_buff, bmp_orig, 0, 0);
			vsync();
			blit(bmp_buff, screen, 0,0, 0,0, SCREEN_W, SCREEN_H);
		}
		destroy_bitmap(bmp_buff);
	}

	blit(bmp_orig, screen, 0,0, 0,0, SCREEN_W, SCREEN_H);
}

/* -------------------------------------------------------------------------------------- */

void highcolor_fade_out_Abertura(int speed)
{
	BITMAP *bmp_orig, *bmp_buff;

	if ((bmp_orig = create_bitmap(SCREEN_W, SCREEN_H)))
	{
		if ((bmp_buff = create_bitmap(SCREEN_W, SCREEN_H)))
		{
			int a;
			blit(screen, bmp_orig, 0,0, 0,0, SCREEN_W, SCREEN_H);
			if (speed <= 0) speed = 16;

			for (a = 255-speed; a > 0; a-=speed)
			{
				clear(bmp_buff);
				set_trans_blender(0,0,0,a);
				draw_trans_sprite(bmp_buff, bmp_orig, 0, 0);
				vsync();
				blit(bmp_buff, screen, 0,0, 0,0, SCREEN_W, SCREEN_H);
			}
			destroy_bitmap(bmp_buff);
		}
		destroy_bitmap(bmp_orig);
	}
}

/* -------------------------------------------------------------------------------------- */

void carregaSom_Abertura (SAMPLE **s, char arq[])
{
	*s = load_sample (arq);
	if (*s == NULL)
	{
		printf ("file not found: %s", arq);
		exit(1);
	}
}

/* -------------------------------------------------------------------------------------- */

void carregaImg_Abertura (BITMAP **b, char arq[])
{
	*b = load_bitmap (arq, NULL);
	if (*b == NULL)
	{
		printf ("file not found: %s", arq);
		exit(1);
	}
}
