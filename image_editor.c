#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

//functie de ignorare a comentariilor dinaintea matricei
void ignorarecom(FILE *fisier)
{
	//sare peste caractere pana ajunge la "\n", ca sa ajung la o noua linie
	while (getc(fisier) != '\n')
		continue;
	//daca linia incepe cu "#", sar peste caractere pana se termina linia
	while (getc(fisier) == '#')
		while (getc(fisier) != '\n')
			continue;
	//ma duc cu o pozitie in spate
	fseek(fisier, -1, SEEK_CUR);
}

//structura pentru valorile pixelilor
typedef struct {
	unsigned char rosu, verde, albastru;
} pixel;

//structura pentru matricea imaginilor
typedef struct imagine {
	pixel **info;
	int tip;
	int coloane;
	int linii;
	//intensitatea maxima
	int valoare;
} imag;

//citire pentru tip P2
void citirep2(imag *img, imag *copie1, imag *copie2, FILE *fisier)
{
	int valculoare, i, j;
	//pentru fiecare pixel citesc valoarea culorii si ii atribui fiecarei
	//culori ale pixelului (rosu, verde si albastru) aceeasi valoare pentru ca
	//imaginea e in tonuri de gri
	for (i = 0; i < img->linii; ++i)
		for (j = 0; j < img->coloane; ++j) {
			fscanf(fisier, "%d", &valculoare);
			img->info[i][j].rosu = valculoare;
			img->info[i][j].verde = valculoare;
			img->info[i][j].albastru = valculoare;
			//pun aceeasi valoare si pentru copii
			copie1->info[i][j].rosu = valculoare;
			copie1->info[i][j].verde = valculoare;
			copie1->info[i][j].albastru = valculoare;
			copie2->info[i][j].rosu = valculoare;
			copie2->info[i][j].verde = valculoare;
			copie2->info[i][j].albastru = valculoare;
		}
}

//citirea pentru tipul P5
void citirep5(imag *img, imag *copie1, imag *copie2, FILE *fisier)
{
	int i, j;
	char caracter;
	//citesc caractere pana ajunge la linie noua
	while (fgetc(fisier) != '\n')
		continue;
	//pentru fiecare pixel citesc valoarea culorii si ii atribui fiecarei
	//culori ale pixelului (rosu, verde si albastru) aceeasi valoare pentru ca
	//imaginea e in tonuri de gri
	for (i = 0; i < img->linii; ++i)
		for (j = 0; j < img->coloane; ++j) {
			caracter = fgetc(fisier);
			img->info[i][j].rosu = caracter;
			img->info[i][j].verde = caracter;
			img->info[i][j].albastru = caracter;
			//atribui valoarea si copiilor
			copie1->info[i][j].rosu = caracter;
			copie1->info[i][j].verde = caracter;
			copie1->info[i][j].albastru = caracter;
			copie2->info[i][j].rosu = caracter;
			copie2->info[i][j].verde = caracter;
			copie2->info[i][j].albastru = caracter;
		}
}

//citirea pentru tipul P3
void citirep3(imag *img, imag *copie1, imag *copie2, FILE *fisier)
{
	int valculoare, i, j;
	//citesc pe rand valorile pixelului pentru fiecare culoare si le retin
	// atat in imaginea principala, cat si in copii
	for (i = 0; i < img->linii; ++i)
		for (j = 0; j < img->coloane; ++j) {
			fscanf(fisier, "%d", &valculoare);
			img->info[i][j].rosu = valculoare;
			copie1->info[i][j].rosu = valculoare;
			copie2->info[i][j].rosu = valculoare;
			fscanf(fisier, "%d", &valculoare);
			img->info[i][j].verde = valculoare;
			copie1->info[i][j].verde = valculoare;
			copie2->info[i][j].verde = valculoare;
			fscanf(fisier, "%d", &valculoare);
			img->info[i][j].albastru = valculoare;
			copie1->info[i][j].albastru = valculoare;
			copie2->info[i][j].albastru = valculoare;
		}
}

// citire pentru tipul P6
void citirep6(imag *img, imag *copie1, imag *copie2, FILE *fisier)
{
	int i, j, caracter;
	// ma asigur ca am ajuns la o linie noua, prima a matricei imaginii
	while (fgetc(fisier) != '\n')
		continue;
	// citesc valorile pentru cele 3 culori pe rand pentru fiecare pixel
	// si le retin in imaginea principala si in copii
	for (i = 0; i < img->linii; ++i)
		for (j = 0; j < img->coloane; ++j) {
			caracter = fgetc(fisier);
			img->info[i][j].rosu = caracter;
			caracter = fgetc(fisier);
			img->info[i][j].verde = caracter;
			caracter = fgetc(fisier);
			img->info[i][j].albastru = caracter;
			copie1->info[i][j].rosu =  img->info[i][j].rosu;
			copie1->info[i][j].verde =  img->info[i][j].verde;
			copie1->info[i][j].albastru =  img->info[i][j].albastru;
			copie2->info[i][j].rosu =  img->info[i][j].rosu;
			copie2->info[i][j].verde =  img->info[i][j].verde;
			copie2->info[i][j].albastru =  img->info[i][j].albastru;
		}
}

// functia pentru incarcarea unei imagini in memorie
void citire(imag *img, imag *copie1, imag *copie2,
			char *nume, int *c, int *ok)
{
	FILE *fisier;
	char caracter;
	int i;
	//deschid fisierul pentru a citi din el si verific daca a functionat
	fisier = fopen(nume, "rb");
	if (!fisier) {
		printf("Failed to load %s\n", nume);
		*ok = 0;
		return;
	}
	// aflu tipul imaginii
	caracter = fgetc(fisier);
	caracter = fgetc(fisier);
	// scad 48 pentru a ajunge la un intreg din caracter
	img->tip = caracter - 48;
	// ignor comentariile si citesc caracteristicile imaginii
	ignorarecom(fisier);
	fscanf(fisier, "%d %d", &img->coloane, &img->linii);
	ignorarecom(fisier);
	fscanf(fisier, "%d", &img->valoare);
	// atribui caracteristicile imaginii initiale copiilor
	copie1->coloane = img->coloane;
	copie1->linii = img->linii;
	copie1->valoare = img->valoare;
	copie2->coloane = img->coloane;
	copie2->linii = img->linii;
	copie2->valoare = img->valoare;
	// aloc memorie pentru pixeli
	img->info = (pixel **)malloc(img->linii * sizeof(pixel *));
	for (i = 0; i < img->linii; ++i)
		img->info[i] = (pixel *)malloc(img->coloane * sizeof(pixel));
	copie1->info = (pixel **)malloc(copie1->linii * sizeof(pixel *));
	for (i = 0; i < copie1->linii; ++i)
		copie1->info[i] = (pixel *)malloc(copie1->coloane * sizeof(pixel));
	copie2->info = (pixel **)malloc(copie2->linii * sizeof(pixel *));
	for (i = 0; i < copie2->linii; ++i)
		copie2->info[i] = (pixel *)malloc(copie2->coloane * sizeof(pixel));
	// citesc in functie de tipul imaginii
	if (img->tip == 2)
		citirep2(img, copie1, copie2, fisier);
	if (img->tip == 5)
		citirep5(img, copie1, copie2, fisier);
	if (img->tip == 3)
		citirep3(img, copie1, copie2, fisier);
	if (img->tip == 6)
		citirep6(img, copie1, copie2, fisier);
	// initializez capetele imaginii
	c[0] = 0;
	c[1] = img->coloane;
	c[2] = 0;
	c[3] = img->linii;
	// inchid fisierul
	fclose(fisier);
	printf("Loaded %s\n", nume);
}

// operatia de selectare
void selectare(imag *img, imag *copie1, int *cpt, int x1, int *ok)
{
	int x2, y1, y2, i, j, aux;
	// citesc capatul din stanga al selectiei pentru linii
	scanf("%d", &y1);
	char a = fgetc(stdin);
	// verific daca a fost incarcata o imagine, daca parametrii nu sunt doar 2
	if (a == '\n') {
		if (*ok == 0) {
			printf("No image loaded\n");
		return;
		}
		printf("Invalid command\n");
		return;
	}
	a = fgetc(stdin);
	if (a == 'a') {
		fseek(stdin, -1, SEEK_CUR);
		printf("Invalid command\n");
		return;
	}
	fseek(stdin, -1, SEEK_CUR);
	scanf("%d", &x2);
	a = fgetc(stdin);
	// daca sunt doar 3 parametri
	if (a == '\n') {
		printf("Invalid command\n");
		return;
	}
	a = fgetc(stdin);
	if (a == 'a') {
		fseek(stdin, -1, SEEK_CUR);
		printf("Invalid command\n");
		return;
	}
	fseek(stdin, -1, SEEK_CUR);
	scanf("%d", &y2);
	if (*ok == 0) {
		printf("No image loaded\n");
		return;
	}
	// daca nu sunt capetele in ordinea potrivita le interschimb
	if (x2 < x1) {
		aux = x1;
		x1 = x2;
		x2 = aux;
	}
	if (y2 < y1) {
		aux = y1;
		y1 = y2;
		y2 = aux;
	}
	// daca nu sunt indeplinite conditiile pentru coordonate
	if (x1 < 0 || y1 < 0 || x2 > copie1->coloane || y2 > copie1->linii) {
		printf("Invalid set of coordinates\n");
		return;
	}
	if (x1 == x2 || y1 == y2) {
		printf("Invalid set of coordinates\n");
		return;
	}
	// retin capetele selectiei
	cpt[0] = x1;
	cpt[1] = x2;
	cpt[2] = y1;
	cpt[3] = y2;
	// atribui imaginii principale caracteristicile si elementele selectiei
	// imaginea mare va fi retinuta in copii
	img->linii = y2 - y1;
	img->coloane = x2 - x1;
	for (i = y1; i < y2; ++i) {
		for (j = x1; j < x2; ++j) {
			img->info[i - y1][j - x1].rosu = copie1->info[i][j].rosu;
			img->info[i - y1][j - x1].verde = copie1->info[i][j].verde;
			img->info[i - y1][j - x1].albastru = copie1->info[i][j].albastru;
		}
	}
	printf("Selected %d %d %d %d\n", x1, y1, x2, y2);
}

//selectie totala
void seltotala(imag *img, imag *c1, int *c, int *ok, imag *c2)
{
	int i, j;
	// verific daca e vreo imagine incarcata
	if (*ok == 0) {
		printf("No image loaded\n");
		return;
	}
	// daca liniile copiei sunt egale cu ale selctiei sau daca sunt coloanele
	// selectiei sunt egale cu ale copiei inseamna ca e deja selectata total
	if (img->linii == c1->linii && img->coloane == c1->coloane)
		return;
	// pun selectia la loc in imaginea mare, pentru ca poate avea modificari
	for (i = 0; i < img->linii; ++i) {
		for (j = 0; j < img->coloane; ++j) {
			c1->info[i + c[2]][j + c[0]].rosu = img->info[i][j].rosu;
			c1->info[i + c[2]][j + c[0]].verde = img->info[i][j].verde;
			c1->info[i + c[2]][j + c[0]].albastru = img->info[i][j].albastru;
			c2->info[i + c[2]][j + c[0]].rosu = img->info[i][j].rosu;
			c2->info[i + c[2]][j + c[0]].verde = img->info[i][j].verde;
			c2->info[i + c[2]][j + c[0]].albastru = img->info[i][j].albastru;
		}
	}
	//selectia va deveni imagine mare, ii atribui caracteristicile si elementele
	img->coloane = c1->coloane;
	img->linii = c1->linii;
	for (i = 0; i < img->linii; ++i) {
		for (j = 0; j < img->coloane; ++j) {
			img->info[i][j].rosu = c1->info[i][j].rosu;
			img->info[i][j].verde = c1->info[i][j].verde;
			img->info[i][j].albastru = c1->info[i][j].albastru;
		}
	}
}

// taierea imaginii
void taiere(imag *img, imag *copie1, int *ok, int *cpt, imag *copie2)
{
	int i, j;
	// verific daca exista vreo imagine incarcata
	if (*ok == 0) {
		printf("No image loaded\n");
		return;
	}
	// daca liniile copiei sunt egale cu ale selctiei sau daca sunt coloanele
	// selectiei sunt egale cu ale copiei inseamna ca are deja dmensiuni
	if (img->linii == copie1->linii && img->coloane == copie1->coloane) {
		printf("Image cropped\n");
		return;
	}
	// aloc memorie pentru noile dimensiuni
	for (i = 0; i < copie1->linii; ++i)
		free(copie1->info[i]);
	free(copie1->info);
	for (i = 0; i < copie2->linii; ++i)
		free(copie2->info[i]);
	free(copie2->info);
	copie1->info = (pixel **)malloc(img->linii * sizeof(pixel *));
	for (i = 0; i < img->linii; ++i)
		copie1->info[i] = (pixel *)malloc(img->coloane * sizeof(pixel));
	copie2->info = (pixel **)malloc(img->linii * sizeof(pixel *));
	for (i = 0; i < img->linii; ++i)
		copie2->info[i] = (pixel *)malloc(img->coloane * sizeof(pixel));
	// copiile primesc valorile imaginii taiate, de fapt ale selectiei
	for (i = 0; i < img->linii; ++i) {
		for (j = 0; j < img->coloane; ++j) {
			copie1->info[i][j].rosu = img->info[i][j].rosu;
			copie1->info[i][j].verde = img->info[i][j].verde;
			copie1->info[i][j].albastru = img->info[i][j].albastru;
			copie2->info[i][j].rosu = img->info[i][j].rosu;
			copie2->info[i][j].verde = img->info[i][j].verde;
			copie2->info[i][j].albastru = img->info[i][j].albastru;
		}
	}
	// aloc memorie pentru noile dimensiuni
	for (i = 0; i < copie1->linii; ++i)
		free(img->info[i]);
	free(img->info);
	img->info = (pixel **)malloc(img->linii * sizeof(pixel *));
	for (i = 0; i < img->linii; ++i)
		img->info[i] = (pixel *)malloc(img->coloane * sizeof(pixel));
	// pun elementele in selectie
	for (i = 0; i < img->linii; ++i) {
		for (j = 0; j < img->coloane; ++j) {
			img->info[i][j].rosu = copie1->info[i][j].rosu;
			img->info[i][j].verde = copie1->info[i][j].verde;
			img->info[i][j].albastru = copie1->info[i][j].albastru;
		}
	}
	// retin noile valori ale capetelor
	cpt[0] = 0;
	cpt[1] = img->coloane;
	cpt[2] = 0;
	cpt[3] = img->linii;
	// copiile primesc caracteristicile selectiei
	copie1->linii = img->linii;
	copie1->coloane = img->coloane;
	copie2->linii = img->linii;
	copie2->coloane = img->coloane;
	printf("Image cropped\n");
}

// histograma pentru toata imaginea
void histograma(int *apinterval, imag *img, int *ok)
{
	int i, j, k, x, y, nrstele, max = -1;
	char a;
	double interval;
	a = fgetc(stdin);
	// verific daca este vreo imagine incarcata si daca parametrii sunt corecti
	if (*ok == 0) {
		printf("No image loaded\n");
		if (a == '\n')
			return;
		scanf("%d", &x);
		a = fgetc(stdin);
		if (a == '\n')
			return;
		scanf("%d", &y);
		return;
	}
	if (a == '\n') {
		printf("Invalid command\n");
		return;
	}
	scanf("%d", &x);
	a = fgetc(stdin);
	if (a == '\n') {
		printf("Invalid command\n");
		return;
	}
	scanf("%d", &y);
	a = fgetc(stdin);
	if (a != '\n') {
		int uf;
		scanf("%d", &uf);
		printf("Invalid command\n");
		return;
	}
	// verific daca imaginea e color
	if (img->tip == 3 || img->tip == 6) {
		printf("Black and white image needed\n");
		return;
	}
	// calculez dimensiunea unui interval dupa numarul de bin-uri
	interval = img->valoare / y;
	// calculez aparitiile pentru fiecare interval, si maximul aparitiilor
	for (i = 0; i < y; ++i) {
		apinterval[i] = 0;
		for (j = 0; j < img->linii; ++j) {
			for (k = 0; k < img->coloane; ++k) {
				int val = img->info[j][k].rosu;
				if (val <= ((i + 1) * interval) && val >= (i * interval))
					apinterval[i]++;
				if (apinterval[i] > max)
					max = apinterval[i];
			}
		}
	}
	// afisez histograma
	for (i = 0; i < y; ++i) {
		nrstele = apinterval[i] * x / max;
		printf("%d	|	", nrstele);
		for (j = 0; j < nrstele; ++j)
			printf("*");
		printf("\n");
	}
}

// operatia de egalizare
void egalizare(imag *img, imag *copie1, imag *cop2, int *c, int *ap, int *ok)
{
	int i, j, k;
	double suma, arie;
	// verific daca e vreo imagine incarcata
	if (*ok == 0) {
		printf("No image loaded\n");
		return;
	}
	// verific daca imaginea e color
	if (img->tip == 3 || img->tip == 6) {
		printf("Black and white image needed\n");
		return;
	}
	// refac capetele
	if (img->linii == copie1->linii && img->coloane == copie1->coloane) {
		c[0] = 0;
		c[1] = img->coloane;
		c[2] = 0;
		c[3] = img->linii;
	}
	// initializez pentru fiecare valoare posibila a unui pixel cu 0
	for (i = 0; i < 256; ++i)
		ap[i] = 0;
	// calculez numarul de aparitii a fiecarei valori, iar pentru ca imaginea
	// e in tonuri de gri, trebuie sa fac asta doar pentru o culoare, deoarece
	// culorile au aceleasi valori in cadrul unui pixel
	for (i = 0; i < cop2->linii; ++i)
		for (j = 0; j < cop2->coloane; ++j)
			ap[cop2->info[i][j].rosu]++;
	// calculez aria imaginii in pixeli, folosesc copia 2
	arie = cop2->linii * cop2->coloane;
	// calculez valorile noilor pixeli cu ajutorul formulei, calculand suma
	// aparitiilor unei valori inmultita cu 255, totul supra arie
	for (i = 0; i < cop2->linii; ++i) {
		for (j = 0; j < cop2->coloane; ++j) {
			suma = 0;
			for (k = 0; k <= cop2->info[i][j].rosu; ++k)
				suma = suma + ap[k];
			double a = (double)(255 * suma / arie);
			// rotunjirea valorii la cel mai apropiat intreg
			double b = round(a);
			// limitarea valorilor
			if (b < 0)
				b = 0;
			if (b > 255)
				b = 255;
			// atribuirea noilor valori
			cop2->info[i][j].rosu = (unsigned int)b;
			cop2->info[i][j].verde = (unsigned int)b;
			cop2->info[i][j].albastru = (unsigned int)b;
		}
	}
	// pun la loc in selectie valorile modificate
	for (i = 0; i < img->linii; ++i) {
		for (j = 0; j < img->coloane; ++j) {
			img->info[i][j].rosu = cop2->info[i + c[2]][j + c[0]].rosu;
			img->info[i][j].verde = cop2->info[i + c[2]][j + c[0]].verde;
			img->info[i][j].albastru = cop2->info[i + c[2]][j + c[0]].albastru;
		}
	}
	// actualizez si copia 1
	for (i = 0; i < copie1->linii; ++i) {
		for (j = 0; j < copie1->coloane; ++j) {
			copie1->info[i][j].rosu = cop2->info[i][j].rosu;
			copie1->info[i][j].verde = cop2->info[i][j].verde;
			copie1->info[i][j].albastru = cop2->info[i][j].albastru;
		}
	}
	printf("Equalize done\n");
}

// functie pentru rotire la 90 de grade
void osingurarotire(imag *img, imag *c1, int *c)
{
	int **aux1, **aux2, **aux3, i, j;
	// aloc dinamic matricile auxiliare
	aux1 = (int **)malloc(img->coloane * sizeof(int *));
	for (i = 0; i < img->coloane; ++i)
		aux1[i] = (int *)malloc(img->linii * sizeof(int));
	aux2 = (int **)malloc(img->coloane * sizeof(int *));
	for (i = 0; i < img->coloane; ++i)
		aux2[i] = (int *)malloc(img->linii * sizeof(int));
	aux3 = (int **)malloc(img->coloane * sizeof(int *));
	for (i = 0; i < img->coloane; ++i)
		aux3[i] = (int *)malloc(img->linii * sizeof(int));
	// pun valorile in matricea auxiliara corespunzatoare culorii pentru
	// a o roti la 90 de grade
	// in matricele auxiliare vor fi valorile culorilor imaginii rotite
	for (i = 0; i < img->linii; ++i)
		for (j = 0; j < img->coloane; ++j) {
			aux1[j][img->linii - i - 1] = img->info[i][j].rosu;
			aux2[j][img->linii - i - 1] = img->info[i][j].verde;
			aux3[j][img->linii - i - 1] = img->info[i][j].albastru;
		}
	if (img->linii == c1->linii && img->coloane == c1->coloane) {
		// aloc memorie pentru noile dimensiuni
		for (i = 0; i < c1->linii; ++i)
			free(img->info[i]);
		free(img->info);
		img->info = (pixel **)malloc(img->coloane * sizeof(pixel *));
		for (i = 0; i < img->coloane; ++i)
			img->info[i] = (pixel *)malloc(img->linii * sizeof(pixel));
		for (i = 0; i < c1->linii; ++i)
			free(c1->info[i]);
		free(c1->info);
		c1->info = (pixel **)malloc(img->coloane * sizeof(pixel *));
		for (i = 0; i < img->coloane; ++i)
			c1->info[i] = (pixel *)malloc(img->linii * sizeof(pixel));
	}
	// daca liniile selectiei sunt egale cu ale copiei schimb intre ele
	// capetele si dimensiunile pozei
	int a = img->linii;
	int b = img->coloane;
	if (img->linii == c1->linii && img->coloane == c1->coloane) {
		c1->linii = b;
		c1->coloane = a;
		c[1] = a;
		c[3] = b;
	}
	// interschimb dimensiunile
	img->linii = b;
	img->coloane = a;
	// atribui noile valori din matricele auxiliare imaginii/selectiei
	for (i = 0; i < img->linii; ++i) {
		for (j = 0; j < img->coloane; ++j) {
			img->info[i][j].rosu = aux1[i][j];
			img->info[i][j].verde = aux2[i][j];
			img->info[i][j].albastru = aux3[i][j];
		}
	}
	// daca liniile copiei sunt egale cu liniile selectiei, la fel si pentru
	// coloane, copia 1 va primi
	if (img->linii == c1->linii && img->coloane == c1->coloane) {
		for (i = 0; i < img->linii; ++i) {
			for (j = 0; j < img->coloane; ++j) {
				c1->info[i][j].rosu = img->info[i][j].rosu;
				c1->info[i][j].verde = img->info[i][j].verde;
				c1->info[i][j].albastru = img->info[i][j].albastru;
			}
		}
	}
	for (i = 0; i < img->linii; ++i)
		free(aux1[i]);
	free(aux1);
	for (i = 0; i < img->linii; ++i)
		free(aux2[i]);
	free(aux2);
	for (i = 0; i < img->linii; ++i)
		free(aux3[i]);
	free(aux3);
}

void rotire(imag *img, int *ok, imag *c1, int *c)
{
	int grad;
	char semn;
	semn = fgetc(stdin);
	semn = fgetc(stdin);
	if (semn != '-')
		fseek(stdin, -1, SEEK_CUR);
	scanf("%d", &grad);
	if (*ok == 0) {
		printf("No image loaded\n");
		return;
	}
	if (grad != 0 && grad != 360 && grad != 90 && grad != 180 && grad != 270)
		printf("Unsupported rotation angle\n");
	if (grad == 360 || grad == 0) {
		if (semn == '-')
			printf("Rotated -%d\n", grad);
		else
			printf("Rotated %d\n", grad);
		// daca unghiul e 360 sau 0 imaginea e de fapt cea originala
		return;
	}
	// acelasi caz pentru -90 si 270
	if ((semn != '-' && grad == 90) || (semn == '-' && grad == 270)) {
		osingurarotire(img, c1, c);
		if (semn == '-')
			printf("Rotated -%d\n", grad);
		else
			printf("Rotated %d\n", grad);
		return;
	}
	// acelasi caz pentru 90 si -270
	if ((semn != '-' && grad == 270) || (semn == '-' && grad == 90)) {
		osingurarotire(img, c1, c);
		osingurarotire(img, c1, c);
		osingurarotire(img, c1, c);
		if (semn == '-')
			printf("Rotated -%d\n", grad);
		else
			printf("Rotated %d\n", grad);
		return;
	}
	// pentru 180 e la fel si daca e pozitiv si daca e negativ unghiul
	if (grad == 180) {
		osingurarotire(img, c1, c);
		osingurarotire(img, c1, c);
		if (semn == '-')
			printf("Rotated -%d\n", grad);
		else
			printf("Rotated %d\n", grad);
		return;
	}
}

// eliberarea resurselor
void iesire(imag *img, imag *c1, imag *c2, char *o,
			int *a1, int *a2, int *c, int *ok)
{
	int i;
	// daca nu este o imagine in memorie eliberez doar vectorii alocati
	// inainte de incarcare
	if (*ok == 0) {
		printf("No image loaded\n");
		free(a1);
		free(a2);
		free(c);
		free(o);
		return;
	}
	// eliberez toate resursele
	for (i = 0; i < c1->linii; ++i)
		free(img->info[i]);
	free(img->info);
	for (i = 0; i < c1->linii; ++i)
		free(c1->info[i]);
	free(c1->info);
	for (i = 0; i < c2->linii; ++i)
		free(c2->info[i]);
	free(c2->info);
	free(a1);
	free(a2);
	free(c);
	free(o);
	free(c1);
	free(c2);
	free(img);
}

//
void blurare(imag *img, int *c, imag *c1)
{
int i, j, k, l;
double **r, **v, **a;
// aloc memorie pentru matricile auxiliare
r = (double **)malloc(img->linii * sizeof(double *));
for (i = 0; i < img->linii; ++i)
	r[i] = (double *)malloc(img->coloane * sizeof(double));
v = (double **)malloc(img->linii * sizeof(double *));
for (i = 0; i < img->linii; ++i)
	v[i] = (double *)malloc(img->coloane * sizeof(double));
a = (double **)malloc(img->linii * sizeof(double *));
for (i = 0; i < img->linii; ++i)
	a[i] = (double *)malloc(img->coloane * sizeof(double));
int lin = c1->linii - 1;
int col = c1->coloane - 1;
// ma asigur ca selectia e corecta
img->linii = c[3] - c[2];
img->coloane = c[1] - c[0];
for (i = 0; i < img->linii; ++i) {
	for (j = 0; j < img->coloane; ++j) {
		img->info[i][j].rosu = c1->info[i + c[2]][j + c[0]].rosu;
		img->info[i][j].verde = c1->info[i + c[2]][j + c[0]].verde;
		img->info[i][j].albastru = c1->info[i + c[2]][j + c[0]].albastru;
	}
}

// am luat doua foruri ca sa calculez noua valoare pentru fiecare pixel
for (i = 0; i < img->linii; ++i) {
	for (j = 0; j < img->coloane; ++j) {
		r[i][j] = 0;
		v[i][j] = 0;
		a[i][j] = 0;
		// daca e pe marginea pozei mari, pixelul ramane la fel
		if (i > -c[2] && j > -c[0] && i + c[2] < lin && j + c[0] < col) {
			// pentru cei 9 pixeli din jurul pixelului principal, inclusiv el
			for (k = i - 1; k <= i + 1; ++k) {
				for (l = j - 1; l <= j + 1; ++l) {
					// inmultesc cu kernelul
					r[i][j] = r[i][j] + c1->info[k + c[2]][l + c[0]].rosu;
					v[i][j] = v[i][j] + c1->info[k + c[2]][l + c[0]].verde;
					a[i][j] = a[i][j] + c1->info[k + c[2]][l + c[0]].albastru;
				}
			}
			r[i][j] = (double)(r[i][j] / 9);
			v[i][j] = (double)(v[i][j] / 9);
			a[i][j] = (double)(a[i][j] / 9);
		} else {
			// raman la fel daca n-au destui vecini
			r[i][j] = c1->info[i + c[2]][j + c[0]].rosu;
			v[i][j] = c1->info[i + c[2]][j + c[0]].verde;
			a[i][j] = c1->info[i + c[2]][j + c[0]].albastru;
		}
	}
}

// introduc noile valori
for (i = 0; i < img->linii; ++i) {
	for (j = 0; j < img->coloane; ++j) {
		img->info[i][j].rosu = round(r[i][j]);
		img->info[i][j].verde = round(v[i][j]);
		img->info[i][j].albastru = round(a[i][j]);
	}
}

// adaug selectia modificata in copie
for (i = 0; i < img->linii; ++i) {
	for (j = 0; j < img->coloane; ++j) {
		c1->info[i + c[2]][j + c[0]].rosu = img->info[i][j].rosu;
		c1->info[i + c[2]][j + c[0]].verde = img->info[i][j].verde;
		c1->info[i + c[2]][j + c[0]].albastru = img->info[i][j].albastru;
	}
}

for (i = 0; i < img->linii; ++i)
	free(r[i]);
free(r);
for (i = 0; i < img->linii; ++i)
	free(v[i]);
free(v);
for (i = 0; i < img->linii; ++i)
	free(a[i]);
free(a);
printf("APPLY BLUR done\n");
}

void calculvaloriedge(imag *c1, int i, int j, int **r, int **v, int **a, int *c)
{
	int lin = c1->linii - 1;
	int col = c1->coloane - 1;
	// daca e pe marginea pozei mari, pixelul ramane la fel
	if (i > -c[2] && j > -c[0] && i + c[2] < lin && j + c[0] < col) {
		// inmultesc cu kernelul
		// pentru rosu
		r[i][j] = c1->info[i + c[2]][j + c[0]].rosu * 8;
		r[i][j] = r[i][j] - c1->info[i - 1 + c[2]][j + c[0]].rosu;
		r[i][j] = r[i][j] - c1->info[i + 1 + c[2]][j + c[0]].rosu;
		r[i][j] = r[i][j] - c1->info[i + c[2]][j + 1 + c[0]].rosu;
		r[i][j] = r[i][j] - c1->info[i + c[2]][j - 1 + c[0]].rosu;
		r[i][j] = r[i][j] - c1->info[i - 1 + c[2]][j - 1 + c[0]].rosu;
		r[i][j] = r[i][j] - c1->info[i + 1 + c[2]][j - 1 + c[0]].rosu;
		r[i][j] = r[i][j] - c1->info[i + 1 + c[2]][j + 1 + c[0]].rosu;
		r[i][j] = r[i][j] - c1->info[i - 1 + c[2]][j + 1 + c[0]].rosu;
		// pentru verde
		v[i][j] = c1->info[i + c[2]][j + c[0]].verde * 8;
		v[i][j] = v[i][j] - c1->info[i - 1 + c[2]][j + c[0]].verde;
		v[i][j] = v[i][j] - c1->info[i + 1 + c[2]][j + c[0]].verde;
		v[i][j] = v[i][j] - c1->info[i + c[2]][j + 1 + c[0]].verde;
		v[i][j] = v[i][j] - c1->info[i - 1 + c[2]][j - 1 + c[0]].verde;
		v[i][j] = v[i][j] - c1->info[i + 1 + c[2]][j - 1 + c[0]].verde;
		v[i][j] = v[i][j] - c1->info[i + c[2]][j - 1 + c[0]].verde;
		v[i][j] = v[i][j] - c1->info[i + 1 + c[2]][j + 1 + c[0]].verde;
		v[i][j] = v[i][j] - c1->info[i - 1 + c[2]][j + 1 + c[0]].verde;
		// pentru albastru
		a[i][j] = c1->info[i + c[2]][j + c[0]].albastru * 8;
		a[i][j] = a[i][j] - c1->info[i - 1 + c[2]][j + c[0]].albastru;
		a[i][j] = a[i][j] - c1->info[i + 1 + c[2]][j + c[0]].albastru;
		a[i][j] = a[i][j] - c1->info[i + c[2]][j + 1 + c[0]].albastru;
		a[i][j] = a[i][j] - c1->info[i - 1 + c[2]][j - 1 + c[0]].albastru;
		a[i][j] = a[i][j] - c1->info[i + 1 + c[2]][j - 1 + c[0]].albastru;
		a[i][j] = a[i][j] - c1->info[i + c[2]][j - 1 + c[0]].albastru;
		a[i][j] = a[i][j] - c1->info[i + 1 + c[2]][j + 1 + c[0]].albastru;
		a[i][j] = a[i][j] - c1->info[i - 1 + c[2]][j + 1 + c[0]].albastru;
	} else {
		// raman la fel daca n-au destui vecini
		r[i][j] = c1->info[i + c[2]][j + c[0]].rosu;
		v[i][j] = c1->info[i + c[2]][j + c[0]].verde;
		a[i][j] = c1->info[i + c[2]][j + c[0]].albastru;
	}
}

void margine(imag *img, int *c, imag *c1)
{
int i, j, **r, **v, **a;
// aloc memorie pentru matricile auxiliare
r = (int **)malloc(img->linii * sizeof(int *));
for (i = 0; i < img->linii; ++i)
	r[i] = (int *)malloc(img->coloane * sizeof(int));
v = (int **)malloc(img->linii * sizeof(int *));
for (i = 0; i < img->linii; ++i)
	v[i] = (int *)malloc(img->coloane * sizeof(int));
a = (int **)malloc(img->linii * sizeof(int *));
for (i = 0; i < img->linii; ++i)
	a[i] = (int *)malloc(img->coloane * sizeof(int));
// am luat doua foruri ca sa calculez noua valoare pentru fiecare pixel
for (i = 0; i < img->linii; ++i)
	for (j = 0; j < img->coloane; ++j)
		calculvaloriedge(c1, i, j, r, v, a, c);

// introduc noile valori
for (i = 0; i < img->linii; ++i) {
	for (j = 0; j < img->coloane; ++j) {
		if (r[i][j] < 0)
			r[i][j] = 0;
		if (r[i][j] > 255)
			r[i][j] = 255;
		if (v[i][j] < 0)
			v[i][j] = 0;
		if (v[i][j] > 255)
			v[i][j] = 255;
		if (a[i][j] < 0)
			a[i][j] = 0;
		if (a[i][j] > 255)
			a[i][j] = 255;
		img->info[i][j].rosu = r[i][j];
		img->info[i][j].verde = v[i][j];
		img->info[i][j].albastru = a[i][j];
		}
	}
	// adaug selectia modificata in copie
	for (i = 0; i < img->linii; ++i) {
		for (j = 0; j < img->coloane; ++j) {
			c1->info[i + c[2]][j + c[0]].rosu = img->info[i][j].rosu;
			c1->info[i + c[2]][j + c[0]].verde = img->info[i][j].verde;
			c1->info[i + c[2]][j + c[0]].albastru = img->info[i][j].albastru;
		}
	}
for (i = 0; i < img->linii; ++i)
	free(r[i]);
free(r);
for (i = 0; i < img->linii; ++i)
	free(v[i]);
free(v);
for (i = 0; i < img->linii; ++i)
	free(a[i]);
free(a);
	printf("APPLY EDGE done\n");
}

void ascutire(imag *img, int *c, imag *c1)
{
int i, j;
int **r, **v, **a;
// aloc memorie pentru matricile auxiliare
r = (int **)malloc(img->linii * sizeof(int *));
for (i = 0; i < img->linii; ++i)
	r[i] = (int *)malloc(img->coloane * sizeof(int));
v = (int **)malloc(img->linii * sizeof(int *));
for (i = 0; i < img->linii; ++i)
	v[i] = (int *)malloc(img->coloane * sizeof(int));
a = (int **)malloc(img->linii * sizeof(int *));
for (i = 0; i < img->linii; ++i)
	a[i] = (int *)malloc(img->coloane * sizeof(int));
int lin = c1->linii - 1;
int col = c1->coloane - 1;
// am luat doua foruri ca sa calculez noua valoare pentru fiecare pixel
for (i = 0; i < img->linii; ++i) {
	for (j = 0; j < img->coloane; ++j) {
		// daca e pe marginea pozei mari, pixelul ramane la fel
		if (i > -c[2] && j > -c[0] && i + c[2] < lin && j + c[0] < col) {
			// inmultesc cu kernelul
			// pentru rosu
			r[i][j] = c1->info[i + c[2]][j + c[0]].rosu * 5;
			r[i][j] = r[i][j] - c1->info[i - 1 + c[2]][j + c[0]].rosu;
			r[i][j] = r[i][j] - c1->info[i + 1 + c[2]][j + c[0]].rosu;
			r[i][j] = r[i][j] - c1->info[i + c[2]][j + 1 + c[0]].rosu;
			r[i][j] = r[i][j] - c1->info[i + c[2]][j - 1 + c[0]].rosu;
			// pentru verde
			v[i][j] = c1->info[i + c[2]][j + c[0]].verde * 5;
			v[i][j] = v[i][j] - c1->info[i - 1 + c[2]][j + c[0]].verde;
			v[i][j] = v[i][j] - c1->info[i + 1 + c[2]][j + c[0]].verde;
			v[i][j] = v[i][j] - c1->info[i + c[2]][j + 1 + c[0]].verde;
			v[i][j] = v[i][j] - c1->info[i + c[2]][j - 1 + c[0]].verde;
			// pentru albastru
			a[i][j] = c1->info[i + c[2]][j + c[0]].albastru * 5;
			a[i][j] = a[i][j] - c1->info[i - 1 + c[2]][j + c[0]].albastru;
			a[i][j] = a[i][j] - c1->info[i + 1 + c[2]][j + c[0]].albastru;
			a[i][j] = a[i][j] - c1->info[i + c[2]][j + 1 + c[0]].albastru;
			a[i][j] = a[i][j] - c1->info[i + c[2]][j - 1 + c[0]].albastru;
		} else {
			// raman la fel daca n-au destui vecini
			r[i][j] = c1->info[i + c[2]][j + c[0]].rosu;
			v[i][j] = c1->info[i + c[2]][j + c[0]].verde;
			a[i][j] = c1->info[i + c[2]][j + c[0]].albastru;
		}
	}
}

// introduc noile valori
for (i = 0; i < img->linii; ++i) {
	for (j = 0; j < img->coloane; ++j) {
		if (r[i][j] < 0)
			r[i][j] = 0;
		if (r[i][j] > 255)
			r[i][j] = 255;
		if (v[i][j] < 0)
			v[i][j] = 0;
		if (v[i][j] > 255)
			v[i][j] = 255;
		if (a[i][j] < 0)
			a[i][j] = 0;
		if (a[i][j] > 255)
			a[i][j] = 255;
		img->info[i][j].rosu = r[i][j];
		img->info[i][j].verde = v[i][j];
		img->info[i][j].albastru = a[i][j];
		}
	}
	// adaug selectia modificata in copie
	for (i = 0; i < img->linii; ++i)
		for (j = 0; j < img->coloane; ++j) {
			c1->info[i + c[2]][j + c[0]].rosu = r[i][j];
			c1->info[i + c[2]][j + c[0]].verde = v[i][j];
			c1->info[i + c[2]][j + c[0]].albastru = a[i][j];
		}
for (i = 0; i < img->linii; ++i)
	free(r[i]);
free(r);
for (i = 0; i < img->linii; ++i)
	free(v[i]);
free(v);
for (i = 0; i < img->linii; ++i)
	free(a[i]);
free(a);
printf("APPLY SHARPEN done\n");
}

void calculvaloaregauss(int *c, imag *c1, double **r, double **v,
						double **a, int i, int j)
{
int k, l;
int x = c[0];
// pentru cei 9 pixeli din jurul pixelului principal, inclusiv el
for (k = i - 1; k <= i + 1; ++k) {
	for (l = j - 1; l <= j + 1; ++l) {
		// inmultesc cu kernelul
		if (k == i && l == j) {
			r[i][j] = r[i][j] + c1->info[k + c[2]][l + c[0]].rosu * 4;
			v[i][j] = v[i][j] + c1->info[k + c[2]][l + c[0]].verde * 4;
			a[i][j] = a[i][j] + c1->info[k + c[2]][l + c[0]].albastru * 4;
		} else {
			if ((l == j && k == i - 1) || (l == j - 1 && k == i)) {
				r[i][j] = r[i][j] + c1->info[k + c[2]][l + c[0]].rosu * 2;
				v[i][j] = v[i][j] + c1->info[k + c[2]][l + c[0]].verde * 2;
				a[i][j] = a[i][j] + c1->info[k + c[2]][l + c[0]].albastru * 2;
			} else {
				if ((l == j + 1 && k == i) || (l == j && k == i + 1)) {
					r[i][j] = r[i][j] + c1->info[k + c[2]][l + c[0]].rosu * 2;
					v[i][j] = v[i][j] + c1->info[k + c[2]][l + c[0]].verde * 2;
					a[i][j] = a[i][j] + c1->info[k + c[2]][l + x].albastru * 2;
				} else {
					// pixelul ramane la fel daca n-are destui vecini
					r[i][j] = r[i][j] + c1->info[k + c[2]][l + c[0]].rosu;
					v[i][j] = v[i][j] + c1->info[k + c[2]][l + c[0]].verde;
					a[i][j] = a[i][j] + c1->info[k + c[2]][l + c[0]].albastru;
				}
			}
		}
	}
	}
}

void bluraregaussiana(imag *img, int *c, imag *c1)
{
int i, j;
double **r, **v, **a;
// aloc memorie pentru matricile auxiliare
r = (double **)malloc(img->linii * sizeof(double *));
for (i = 0; i < img->linii; ++i)
	r[i] = (double *)malloc(img->coloane * sizeof(double));
v = (double **)malloc(img->linii * sizeof(double *));
for (i = 0; i < img->linii; ++i)
	v[i] = (double *)malloc(img->coloane * sizeof(double));
a = (double **)malloc(img->linii * sizeof(double *));
for (i = 0; i < img->linii; ++i)
	a[i] = (double *)malloc(img->coloane * sizeof(double));
int lin = c1->linii - 1;
int col = c1->coloane - 1;
// am luat doua foruri ca sa calculez noua valoare pentru fiecare pixel
for (i = 0; i < img->linii; ++i) {
	for (j = 0; j < img->coloane; ++j) {
		r[i][j] = 0;
		v[i][j] = 0;
		a[i][j] = 0;
		// daca e pe marginea pozei mari, pixelul ramane la fel
		if (i > -c[2] && j > -c[0] && i + c[2] < lin && j + c[0] < col) {
			calculvaloaregauss(c, c1, r, v, a, i, j);
			r[i][j] = (double)(r[i][j] / 16);
			v[i][j] = (double)(v[i][j] / 16);
			a[i][j] = (double)(a[i][j] / 16);
		} else {
			// raman la fel daca n-au destui vecini
			r[i][j] = c1->info[i + c[2]][j + c[0]].rosu;
			v[i][j] = c1->info[i + c[2]][j + c[0]].verde;
			a[i][j] = c1->info[i + c[2]][j + c[0]].albastru;
		}
	}
}

// introduc noile valori
for (i = 0; i < img->linii; ++i) {
	for (j = 0; j < img->coloane; ++j) {
		if (r[i][j] < 0)
			r[i][j] = 0;
		if (r[i][j] > 255)
			r[i][j] = 255;
		if (v[i][j] < 0)
			v[i][j] = 0;
		if (v[i][j] > 255)
			v[i][j] = 255;
		if (a[i][j] < 0)
			a[i][j] = 0;
		if (a[i][j] > 255)
			a[i][j] = 255;
		img->info[i][j].rosu = round(r[i][j]);
		img->info[i][j].verde = round(v[i][j]);
		img->info[i][j].albastru = round(a[i][j]);
		}
	}
	// adaug selectia modificata in copie
	for (i = 0; i < img->linii; ++i) {
		for (j = 0; j < img->coloane; ++j) {
			c1->info[i + c[2]][j + c[0]].rosu = img->info[i][j].rosu;
			c1->info[i + c[2]][j + c[0]].verde = img->info[i][j].verde;
			c1->info[i + c[2]][j + c[0]].albastru = img->info[i][j].albastru;
		}
	}
for (i = 0; i < img->linii; ++i)
	free(r[i]);
free(r);
for (i = 0; i < img->linii; ++i)
	free(v[i]);
free(v);
for (i = 0; i < img->linii; ++i)
	free(a[i]);
free(a);
printf("APPLY GAUSSIAN_BLUR done\n");
}

void filtru(imag *img, int *c, imag *c1, int *ok)
{
	char *mod, op;
	mod = malloc(1000 * sizeof(char));
	// verific daca se poate efectua operatia si afisez mesajele de eroare
	if (*ok == 0) {
		printf("No image loaded\n");
		op = fgetc(stdin);
		if (op != '\n')
			scanf("%s", mod);
		free(mod);
		return;
	}
	op = fgetc(stdin);
	if (op == '\n') {
		printf("Invalid command\n");
		free(mod);
		return;
	}
	scanf("%s", mod);
	if (strcmp(mod, "SHARPEN") != 0 && strcmp(mod, "EDGE") != 0)
		if (strcmp(mod, "BLUR") != 0 && strcmp(mod, "GAUSSIAN_BLUR") != 0) {
			printf("APPLY parameter invalid\n");
			free(mod);
			return;
		}
	if (img->tip == 2 || img->tip == 5) {
		printf("Easy, Charlie Chaplin\n");
		free(mod);
		return;
	}
	// aplic filtrul in functie de parametru
	if (strcmp(mod, "BLUR") == 0)
		blurare(img, c, c1);
	if (strcmp(mod, "EDGE") == 0)
		margine(img, c, c1);
	if (strcmp(mod, "SHARPEN") == 0)
		ascutire(img, c, c1);
	if (strcmp(mod, "GAUSSIAN_BLUR") == 0)
		bluraregaussiana(img, c, c1);
	free(mod);
}

// salvarea unei imagini
void salvare(imag *img, imag *c1, int *cpt, char *nume, int *ok,
			 int *c, imag *c2)
{
	int i, j;
	char op;
	if (*ok == 0) {
		printf("No image loaded\n");
		return;
	}
	seltotala(img, c1, cpt, ok, c2);
	FILE *fisier;
	fisier = fopen(nume, "wb");
	op = fgetc(stdin);
	op = fgetc(stdin);
	// daca imaginea e in tonuri de gri si trebuie salvata ascii
	if ((img->tip == 5 || img->tip == 2) && op == 'a') {
		fprintf(fisier, "P2\n");
		fprintf(fisier, "%d %d\n", img->coloane, img->linii);
		fprintf(fisier, "%d\n", img->valoare);
		for (i = 0; i < img->linii; ++i) {
			for (j = 0; j < img->coloane; ++j)
				fprintf(fisier, "%d ", img->info[i][j].rosu);
			fprintf(fisier, "\n");
		}
	}
	// daca imaginea e in tonuri de gri si trebuie salvata binar
	if ((img->tip == 5 || img->tip == 2) && op != 'a') {
		fprintf(fisier, "P5\n");
		fprintf(fisier, "%d %d\n", img->coloane, img->linii);
		fprintf(fisier, "%d\n", img->valoare);
		for (i = 0; i < img->linii; ++i)
			for (j = 0; j < img->coloane; ++j)
				fwrite(&img->info[i][j].rosu, sizeof(char), 1, fisier);
	}
	// daca imaginea e color si trebuie salvata tip ascii
	if ((img->tip == 6 || img->tip == 3) && op == 'a') {
		fprintf(fisier, "P3\n");
		fprintf(fisier, "%d %d\n", img->coloane, img->linii);
		fprintf(fisier, "%d\n", img->valoare);
		for (i = 0; i < img->linii; ++i) {
			for (j = 0; j < img->coloane; ++j) {
				fprintf(fisier, "%d ", img->info[i][j].rosu);
				fprintf(fisier, "%d ", img->info[i][j].verde);
				fprintf(fisier, "%d ", img->info[i][j].albastru);
			}
			fprintf(fisier, "\n");
		}
	}
	// daca imaginea e color si trebuie salvata binar
	if ((img->tip == 6 || img->tip == 3) && op != 'a') {
		fprintf(fisier, "P6\n");
		fprintf(fisier, "%d %d\n", img->coloane, img->linii);
		fprintf(fisier, "%d\n", img->valoare);
		for (i = 0; i < img->linii; ++i) {
			for (j = 0; j < img->coloane; ++j) {
				fwrite(&img->info[i][j].rosu, sizeof(char), 1, fisier);
				fwrite(&img->info[i][j].verde, sizeof(char), 1, fisier);
				fwrite(&img->info[i][j].albastru, sizeof(char), 1, fisier);
			}
		}
	}
	// refac selectia pentru ca am facut select all inainte si nu trebuia
	// sa schimb dimensiunile selectiei
	img->linii = c[3] - c[2];
	img->coloane = c[1] - c[0];
	for (i = 0; i < img->linii; ++i) {
		for (j = 0; j < img->coloane; ++j) {
			img->info[i][j].rosu = c1->info[i + c[2]][j + c[0]].rosu;
			img->info[i][j].verde = c1->info[i + c[2]][j + c[0]].verde;
			img->info[i][j].albastru = c1->info[i + c[2]][j + c[0]].albastru;
		}
	}
	fseek(stdin, -1, SEEK_CUR);
	fclose(fisier);
	printf("Saved %s\n", nume);
}

// verific daca este vreo comanda invalida
void mesaj(char *op)
{
if (strcmp(op, "ROTATE") != 0  && strcmp(op, "EXIT") != 0)
	if (strcmp(op, "SAVE") != 0 && strcmp(op, "APPLY") != 0)
		if (strcmp(op, "EQUALIZE") != 0 && strcmp(op, "LOAD") != 0)
			if (strcmp(op, "HISTOGRAM") != 0 && strcmp(op, "FAULT") != 0)
				if (strcmp(op, "CROP") != 0 && strcmp(op, "SELECT") != 0)
					if (strcmp(op, "ascii") != 0 && strcmp(op, "abc") != 0)
						printf("Invalid command\n");
}

int main(void)
{
	int i, *cpt, x1, *ap, *apinterval, ok = 0;
	char *op;
	op = malloc(1000 * sizeof(char)); // comanda
	cpt = malloc(5 * sizeof(int)); // capetele selectiei
	ap = malloc(1000 * sizeof(int)); // numarul de aparitii totale
	apinterval = malloc(1000 * sizeof(int)); // numarul de aparitii pe interval
	imag *img, *copie1, *copie2;
	while (scanf("%s", op)) {
		if (strcmp(op, "A") == 0)
			scanf("%s", op);
		mesaj(op);
		if (strcmp(op, "LOAD") == 0) {
			scanf("%s", op);
			if (ok == 1) { // daca era in memorie o imagine o eliberez
				for (i = 0; i < copie1->linii; ++i)
					free(img->info[i]);
				free(img->info);
				for (i = 0; i < copie1->linii; ++i)
					free(copie1->info[i]);
				free(copie1->info);
				for (i = 0; i < copie2->linii; ++i)
					free(copie2->info[i]);
				free(copie2->info);
				free(copie1);
				free(copie2);
				free(img);
			}
			img = malloc(sizeof(imag));
			copie1 = malloc(sizeof(imag));
			copie2 = malloc(sizeof(imag));
			ok = 1;
			citire(img, copie1, copie2, op, cpt, &ok); // incarcarea
			if (ok == 0) { // daca nu a reusit eliberez ce am alocat
				free(img);
				free(copie1);
				free(copie2);
			}
		}
		if (strcmp(op, "SELECT") == 0) {
			scanf("%s", op);
			if (strcmp(op, "ALL") == 0) {
				seltotala(img, copie1, cpt, &ok, copie2);
				if (ok == 1)
					printf("Selected ALL\n");
			} else {
				int litere = strlen(op);
				if (litere == 4) { // citesc parametrul si il transform in int
					x1 = (op[0] - 48) * 1000 + (op[1] - 48) * 100;
					x1 = x1 + (op[2] - 48) * 10 + (op[3] - 48);
				}
				if (litere == 3)
					x1 = (op[0] - 48) * 100 + (op[1] - 48) * 10 + (op[2] - 48);
				if (litere == 2)
					x1 = (op[0] - 48) * 10 + (op[1] - 48);
				if (litere == 1)
					x1 = op[0] - 48;
				selectare(img, copie1, cpt, x1, &ok);
			}
		}
		if (strcmp(op, "CROP") == 0)
			taiere(img, copie1, &ok, cpt, copie2);
		if (strcmp(op, "HISTOGRAM") == 0)
			histograma(apinterval, img, &ok);
		if (strcmp(op, "EQUALIZE") == 0)
			egalizare(img, copie1, copie2, cpt, ap, &ok);
		if (strcmp(op, "ROTATE") == 0)
			rotire(img, &ok, copie1, cpt);
		if (strcmp(op, "APPLY") == 0)
			filtru(img, cpt, copie1, &ok);
		if (strcmp(op, "EXIT") == 0) {
			iesire(img, copie1, copie2, op, apinterval, ap, cpt, &ok);
			break;
		}
		if (strcmp(op, "SAVE") == 0) {
			scanf("%s", op);
			salvare(img, copie1, cpt, op, &ok, cpt, copie2);
		}
	}
	return 0;
}
