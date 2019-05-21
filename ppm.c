// ppm.c
// Řešení IJC-DU1, příklad b), 27.3.2017
// Autor: Michal Šajdík, FIT 
// Přeloženo: gcc 6.1.1

#include "ppm.h"

//maximalne rozmery obrazku
#define MAX_X 1000
#define MAX_Y 1000
struct ppm * ppm_read(const char * filename)
{
	FILE * ffile;
	unsigned int x;
	unsigned int y;
	int range;
	int reading;

	ffile=fopen(filename, "r"); //nacitanie suboru s overenim
	if(ffile == NULL)
	{
		warning_msg("Chyba pri otvoreni souboru.\n");
		fclose(ffile);
		return NULL;
	}

	reading=fscanf(ffile,"P6 %u %u %d%*c", &x, &y, &range); //overenie formatu
	if(reading != 3)
	{
		warning_msg("Súbor nejde načítať\n");
		fclose(ffile);
		return NULL;
	}
	if(range > 255) // overenie rozsahu 255 
	{
		warning_msg("RGB ma maximale 255 hodnot pre jednu farbu\n");
		fclose(ffile);
		return NULL;
	}
	//allokacia pamete
	struct ppm *image=(struct ppm*) malloc(sizeof(struct ppm)+3*x*y); 
	if (image == NULL)
	{
		warning_msg("Chyba pri alokacii pamete\n");
		fclose(ffile);
		return NULL;
	}
	image->xsize=x;
	image->ysize=y;
	
	if(x > MAX_X)
	{
		warning_msg("Obrazok je širší ako 1000 pixelov\n");
		free(image);
		fclose(ffile);
		return NULL;
	}
	if(y > MAX_Y)
	{
		warning_msg("Obrazok je vyšší ako 1000 pixelov\n");
		free(image);
		fclose(ffile);
		return NULL;
	}
	
	//nacitanie RGB zloziek do struktury 
	reading=fread(image->data, 1, 3*x*y, ffile);
	
	//overenie poctu RGB zloziek
	if(reading != 3*x*y)
	{
		warning_msg("Chyba pri nacitani RGB prvkov");
		free(image);
		fclose(ffile);
		return NULL;
	}
	fclose(ffile);
	return image;
}

int ppm_write(struct ppm *ppmFile, const char * filename)
{
	FILE *ffile;
	int reading;
	//vytvorenie a overenie vytvorenia
	ffile=fopen(filename, "wb"); 
	if(ffile == NULL)
	{
		warning_msg("Chyba pri nacitani suboru\n");
		return -1;
	}

	//zapis "hlavicky" .ppm suboru
	fprintf(ffile,"P6\n%u %u\n255\n",ppmFile->xsize,ppmFile->ysize);
	
	//zapis RGB zloziek do suboru
	reading=fwrite(ppmFile->data,1,3 * ppmFile->xsize * ppmFile->ysize, ffile);
	//overenie ci sa zapisali vsetky RGB zlozky
	if(reading != 3 * ppmFile->xsize * ppmFile->ysize)
	{
		warning_msg("Nepodarilo sa zapísať správny počet RGB prvkov");
		return -1;
	}
	fclose(ffile);
	return 0;
}
