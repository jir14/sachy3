#include "sachy3.h"
#include <stdlib.h>
#include <stdio.h>
#include "sachovnice.h"
#include "pohyby.h"

char hrac1Jmeno[10] = {};
char hrac2Jmeno[10] = {};

void ulozitHru(char cislo, int barva) {
	char save[150] = {};
	int ukazatel = 0;

	FILE* fptr;
	char cisloSavu[2] = { cislo + '0' };

	fptr = fopen(cisloSavu, "w");

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			save[ukazatel] = barvy[i][j] + '0';
			ukazatel++;
		}
	}
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			save[ukazatel] = figurky[i][j];
			ukazatel++;
		}
	}
	for (int i = 0; i < 9; i++) {
		if (hrac1Jmeno[i] == '\0') {
			hrac1Jmeno[i] = 32;
		}
		save[ukazatel] = hrac1Jmeno[i];
		ukazatel++;
	}
	for (int i = 0; i < 9; i++) {
		if (hrac2Jmeno[i] == '\0') {
			hrac2Jmeno[i] = 32;
		}
		save[ukazatel] = hrac2Jmeno[i];
		ukazatel++;
	}
	save[ukazatel] = barva;

	fprintf(fptr, save);

	fclose(fptr);
}

void nacistHru(int cislo, int* cisloTahu) {
	char save[150];
	int ukazatel = 0;

	FILE* fptr;
	char cisloHry[2] = { cislo + '0' };
	fptr = fopen(cisloHry, "r");

	fgets(save, 150, fptr);

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			barvy[i][j] = save[ukazatel] - 48;
			ukazatel++;
		}
	}
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			figurky[i][j] = save[ukazatel];
			ukazatel++;
		}
	}
	for (int i = 0; i < 9; i++) {
		if (hrac1Jmeno[i] == 32) {
			hrac1Jmeno[i] = '\0';
		}
		hrac1Jmeno[i] = save[ukazatel];
		ukazatel++;
	}
	for (int i = 0; i < 9; i++) {
		if (hrac2Jmeno[i] == 32) {
			hrac2Jmeno[i] = '\0';
		}
		hrac2Jmeno[i] = save[ukazatel];
		ukazatel++;
	}
	*cisloTahu = save[ukazatel];

	fclose(fptr);
}

void ovladani() {
	system("cls");
	printf("\nOvladani:");
	printf("\npat - zadani tahu jako k1");
	printf("\nulozeni - zadani tahu jako sx (x - cislo ulozeni 0-9)");
	printf("\nnacitani ulozene hry - n / nx (x - cislo ulozeni 0-9)");
	printf("\nuznani prohry (sach mat) - zadani tahu m1");
	printf("\nnavrat do menu bez ulozeni behem hry - q");
	printf("\n");
	getchar();
	getchar();
}

void menu(int* cisloTahu) {
	char volba;
zacatek:
	system("cls");
	printf("Vytejte ve hre SACHY!\n");
	printf("hrat - h\nnacist - n\novladani - o\nukoncit - q\n");
	scanf(" %c", &volba);

	if (volba == 'h') {
		printf("zadejte jmeno bileho hrace: ");
		scanf(" %s", &hrac1Jmeno);
		printf("\nzadejte jmeno cerneho hrace: ");
		scanf(" %s", &hrac2Jmeno);
	}
	if (volba == 'n') {
		int cisloHry;
		printf("zadejte cislo ulozene hry: ");
		scanf(" %d", &cisloHry);
		nacistHru(cisloHry, cisloTahu);
	}
	if (volba == 'o') {
		ovladani();
		goto zacatek;
	}
	if (volba == 'q') {
		exit(0);
	}
}