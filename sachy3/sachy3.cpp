// sachy3.cpp: Definuje vstupní bod pro aplikaci.
//

#include "sachy3.h"
#include <stdlib.h>
#include <stdio.h>

int kralPoloha[2][2] = { {8,3}, {0,3} };
int moznePohyby[64][2] = { {} };
int moznePohybyIndex = 0;
int konec = 0;

// sachovnice (nemenne)
// 0 - cerna, 1 - bila 
int sachovnice[8][8] = {
	{1,0,1,0,1,0,1,0},
	{0,1,0,1,0,1,0,1},
	{1,0,1,0,1,0,1,0},
	{0,1,0,1,0,1,0,1},
	{1,0,1,0,1,0,1,0},
	{0,1,0,1,0,1,0,1},
	{1,0,1,0,1,0,1,0},
	{0,1,0,1,0,1,0,1},
};

// barvy figurek na policku
// 0 - cerna, 1 - bila, 2 - prazne
int barvy[8][8] = {
	{1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1},
	{2,2,2,2,2,2,2,2},
	{2,2,2,2,2,2,2,2},
	{2,2,2,2,2,2,2,2},
	{2,2,2,2,2,2,2,2},
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0},
};

// prvotni rozestaveni figurek na zacatku hry
char figurky[8][8] = {
	{'V','H','S','K','Q','S','H','V'},
	{'P','P','P','P','P','P','P','P'},
	{' ',' ',' ',' ',' ',' ',' ',' '},
	{' ',' ',' ',' ',' ',' ',' ',' '},
	{' ',' ',' ',' ',' ',' ',' ',' '},
	{' ',' ',' ',' ',' ',' ',' ',' '},
	{'P','P','P','P','P','P','P','P'},
	{'V','H','S','K','Q','S','H','V'},
};

void vypisSachovnice(char figurky[8][8], int barvy[8][8]) {
	printf("   ");
	for (int i = 0; i < 8; i++) {
		printf(" %c ", i + 97);
	}

	int g = 0;

	for (int i = 0; i < 8; i++) {
		printf("\n");
		printf(" %d ", i + 1);
		g++;
		for (int j = 0; j < 8; j++) {
			g++;
			if (g % 2) {
				if (barvy[i][j]) {
					printf("\033[36m\033[40m");
					printf(" %c ", figurky[i][j]);
				}
				else {
					printf("\033[31m\033[40m");
					printf(" %c ", figurky[i][j]);
				}
				printf("\033[0m");
			}
			else {
				if (barvy[i][j]) {
					printf("\033[36m\033[47m");
					printf(" %c ", figurky[i][j]);
				}
				else {
					printf("\033[31m\033[47m");
					printf(" %c ", figurky[i][j]);
				}
				printf("\033[0m");
			}
		}
	}
}

int existencePolicka(int x, int y) {
	if ((x >= 0) && (x < 8)) {
		if ((y >= 0) && (y < 8)) {
			return 1;
		}
	}
	return 0;
}

// souradnice krale dane barvy
// vraci 1 pokud je sach
int kontrolaSachu(int x, int y, int barva) {
	// vez a dama x
	for (int i = 0; i < 7; i++) {
		if (existencePolicka(x, y + i)) {
			if (figurky[x][y + i] != ' ') {
				if ((figurky[x][y + i] == 'V' || figurky[x][y + i] == 'Q') && barvy[x][y + i] == barva) {
					return 1;
				}
				break;
			}
		}

		if (existencePolicka(x, y - i)) {
			if (figurky[x][y - i] != ' ') {
				if ((figurky[x][y - i] == 'V' || figurky[x][y - i] == 'Q') && barvy[x][y - i] == barva) {
					return 1;
				}
				break;
			}
		}
	}
	//printf("dvx");
	// vez a dama y
	for (int i = 0; i < 7; i++) {
		if (existencePolicka(x + i, y)) {
			if (figurky[x + i][y] != ' ') {
				if ((figurky[x + i][y] == 'V' || figurky[x + i][y] == 'Q') && barvy[x + i][y] == barva) {
					return 1;
				}
				break;
			}
		}

		if (existencePolicka(x - i, y)) {
			if (figurky[x - i][y] != ' ') {
				if ((figurky[x - i][y] == 'V' || figurky[x - i][y] == 'Q') && barvy[x - i][y] == barva) {
					return 1;
				}
				break;
			}
		}
	}
	//printf("dvy");
	// strelec a dama /
	for (int i = 0; i < 7; i++) {
		if (existencePolicka(x + i, y + i)) {
			if (figurky[x + i][y + i] != ' ') {
				if ((figurky[x + i][y + i] == 'V' || figurky[x + i][y + i] == 'Q') && barvy[x + i][y + i] == barva) {
					return 1;
				}
				break;
			}
		}

		if (existencePolicka(x - i, y - i)) {
			if (figurky[x - i][y - i] != ' ') {
				if ((figurky[x - i][y - i] == 'V' || figurky[x - i][y - i] == 'Q') && barvy[x - i][y - i] == barva) {
					return 1;
				}
				break;
			}
		}
	}
	//printf("dsx");
	// strelec a dama \/
	for (int i = 0; i < 7; i++) {
		if (existencePolicka(x + i, y - i)) {
			if (figurky[x + i][y - i] != ' ') {
				if ((figurky[x + i][y - i] == 'V' || figurky[x + i][y - i] == 'Q') && barvy[x + i][y - i] == barva) {
					return 1;
				}
				break;
			}
		}

		if (existencePolicka(x - i, y + i)) {
			if (figurky[x + i][y - i] != ' ') {
				if ((figurky[x - i][y + i] == 'V' || figurky[x - i][y + i] == 'Q') && barvy[x - i][y + i] == barva) {
					return 1;
				}
				break;
			}
		}
	}
	//printf("dsy");
	// pesak
	if (existencePolicka(x + 1, y + 1)) {
		if (figurky[x + 1][y + 1] == 'P' && !barvy[x + 1][y + 1]) {
			return 1;
		}
	}
	if (existencePolicka(x - 1, y - 1)) {
		if (figurky[x - 1][y - 1] == 'P' && !barvy[x - 1][y - 1]) {
			return 1;
		}
	}
	//printf("p");

	// kun
	if (existencePolicka(x + 1, y + 2)) {
		if (figurky[x + 1][y + 2] == 'H' && barvy[x + 1][y + 2] == barva) {
			return 1;
		}
	}
	if (existencePolicka(x + 2, y - 1)) {
		if (figurky[x + 2][y - 1] == 'H' && barvy[x + 2][y - 1] == barva) {
			return 1;
		}
	}
	if (existencePolicka(x - 1, y + 2)) {
		if ((figurky[x - 1][y + 2] == 'H') && barvy[x - 1][y + 2] == barva) {
			return 1;
		}
	}
	if (existencePolicka(x - 2, y - 1)) {
		if ((figurky[x - 1][y - 1] == 'H') && barvy[x - 1][y - 1] == barva) {
			return 1;
		}
	}
	if (existencePolicka(x - 1, y - 2)) {
		if ((figurky[x - 1][y - 2] == 'H') && barvy[x - 1][y - 2] == barva) {
			return 1;
		}
	}
	if (existencePolicka(x - 2, y + 1)) {
		if ((figurky[x - 2][y + 1] == 'H') && barvy[x - 2][y + 1] == barva) {
			return 1;
		}
	}
	if (existencePolicka(x + 1, y - 2)) {
		if ((figurky[x + 1][y - 2] == 'H') && barvy[x + 1][y - 2] == barva) {
			return 1;
		}
	}
	if (existencePolicka(x + 2, y + 1)) {
		if ((figurky[x + 2][y + 1] == 'H') && barvy[x + 2][y + 1] == barva) {
			return 1;
		}
	}
	//printf("h");
	return 0;
}

// souradnice figurky
void pohybVez(int x, int y, int barva) {
	for (int i = 1; i < 8; i++) {
		// x
		if (existencePolicka(x + i, y)) {
			if (figurky[x + i][y] == ' ') {
				moznePohyby[moznePohybyIndex][0] = x + i;
				moznePohyby[moznePohybyIndex][1] = y;
				moznePohybyIndex++;
			}
			else {
				if (barvy[x + i][y] != barva) {
					moznePohyby[moznePohybyIndex][0] = x + i;
					moznePohyby[moznePohybyIndex][1] = y;
					moznePohybyIndex++;
					break;
				}
				break;
			}
		}
	}
	for (int i = 1; i < 8; i++) {
		if (existencePolicka(x - i, y)) {
			if (figurky[x - i][y] == ' ') {
				moznePohyby[moznePohybyIndex][0] = x - i;
				moznePohyby[moznePohybyIndex][1] = y;
				moznePohybyIndex++;
			}
			else {
				if (barvy[x - i][y] != barva) {
					moznePohyby[moznePohybyIndex][0] = x - i;
					moznePohyby[moznePohybyIndex][1] = y;
					moznePohybyIndex++;
					break;
				}
				break;
			}
		}
	}
	for (int i = 1; i < 8; i++) {
		// y
		if (existencePolicka(x, y + i)) {
			if (figurky[x][y + i] == ' ') {
				moznePohyby[moznePohybyIndex][0] = x;
				moznePohyby[moznePohybyIndex][1] = y + i;
				moznePohybyIndex++;
			}
			else {
				if (barvy[x][y + 1] != barva) {
					moznePohyby[moznePohybyIndex][0] = x;
					moznePohyby[moznePohybyIndex][1] = y + i;
					moznePohybyIndex++;
					break;
				}
				break;
			}
		}
	}
	for (int i = 1; i < 8; i++) {
		if (existencePolicka(x, y - i)) {
			if (figurky[x][y - i] == ' ') {
				moznePohyby[moznePohybyIndex][0] = x;
				moznePohyby[moznePohybyIndex][1] = y - i;
				moznePohybyIndex++;
			}
			else {
				if (barvy[x][y - 1] != barva) {
					moznePohyby[moznePohybyIndex][0] = x;
					moznePohyby[moznePohybyIndex][1] = y - i;
					moznePohybyIndex++;
					break;
				}
				break;
			}
		}
	}
}

void pohybStrelec(int x, int y, int barva) {
	for (int i = 1; i < 8; i++) {
		if (existencePolicka(x + i, y + i)) {
			if (figurky[x + i][y + i] == ' ') {
				moznePohyby[moznePohybyIndex][0] = x + i;
				moznePohyby[moznePohybyIndex][1] = y + i;
				moznePohybyIndex++;
			}
			else {
				if (barvy[x + i][y + i] != barva) {
					moznePohyby[moznePohybyIndex][0] = x + i;
					moznePohyby[moznePohybyIndex][1] = y + i;
					moznePohybyIndex++;
					break;
				}
				break;
			}
		}
	}
	for (int i = 1; i < 8; i++) {
		if (existencePolicka(x - i, y + i)) {
			if (figurky[x - i][y + i] == ' ') {
				moznePohyby[moznePohybyIndex][0] = x - i;
				moznePohyby[moznePohybyIndex][1] = y + i;
				moznePohybyIndex++;
			}
			else {
				if (barvy[x - i][y + i] != barva) {
					moznePohyby[moznePohybyIndex][0] = x - i;
					moznePohyby[moznePohybyIndex][1] = y + i;
					moznePohybyIndex++;
					break;
				}
				break;
			}
		}
	}
	for (int i = 1; i < 8; i++) {
		if (existencePolicka(x + i, y - i)) {
			if (figurky[x + i][y - i] == ' ') {
				moznePohyby[moznePohybyIndex][0] = x + i;
				moznePohyby[moznePohybyIndex][1] = y - i;
				moznePohybyIndex++;
			}
			else {
				if (barvy[x + i][y - i] != barva) {
					moznePohyby[moznePohybyIndex][0] = x + i;
					moznePohyby[moznePohybyIndex][1] = y - i;
					moznePohybyIndex++;
					break;
				}
				break;
			}
		}
	}
	for (int i = 1; i < 8; i++) {
		if (existencePolicka(x - i, y - i)) {
			if (figurky[x - i][y - i] == ' ') {
				moznePohyby[moznePohybyIndex][0] = x - i;
				moznePohyby[moznePohybyIndex][1] = y - i;
				moznePohybyIndex++;
			}
			else {
				if (barvy[x - i][y - i] != barva) {
					moznePohyby[moznePohybyIndex][0] = x - i;
					moznePohyby[moznePohybyIndex][1] = y - i;
					moznePohybyIndex++;
					break;
				}
				break;
			}
		}
	}
}

void pohybKralovna(int x, int y, int barva) {
	pohybVez(x, y, barva);
	pohybStrelec(x, y, barva);
}

void pohybKun(int x, int y, int barva) {
	if (existencePolicka(x + 1, y + 2)) {
		if (figurky[x + 1][y + 2] == ' ') {
			moznePohyby[moznePohybyIndex][0] = x + 1;
			moznePohyby[moznePohybyIndex][1] = y + 2;
			moznePohybyIndex++;
		}
		else {
			if (barvy[x + 1][y + 2] != barva) {
				moznePohyby[moznePohybyIndex][0] = x + 1;
				moznePohyby[moznePohybyIndex][1] = y + 2;
				moznePohybyIndex++;
			}
		}
	}
	if (existencePolicka(x - 1, y + 2)) {
		if (figurky[x - 1][y + 2] == ' ') {
			moznePohyby[moznePohybyIndex][0] = x - 1;
			moznePohyby[moznePohybyIndex][1] = y + 2;
			moznePohybyIndex++;
		}
		else {
			if (barvy[x - 1][y + 2] != barva) {
				moznePohyby[moznePohybyIndex][0] = x - 1;
				moznePohyby[moznePohybyIndex][1] = y + 2;
				moznePohybyIndex++;
			}
		}
	}
	if (existencePolicka(x + 1, y - 2)) {
		if (figurky[x + 1][y - 2] == ' ') {
			moznePohyby[moznePohybyIndex][0] = x + 1;
			moznePohyby[moznePohybyIndex][1] = y - 2;
			moznePohybyIndex++;
		}
		else {
			if (barvy[x + 1][y - 2] != barva) {
				moznePohyby[moznePohybyIndex][0] = x + 1;
				moznePohyby[moznePohybyIndex][1] = y - 2;
				moznePohybyIndex++;
			}
		}
	}
	if (existencePolicka(x - 1, y - 2)) {
		if (figurky[x - 1][y - 2] == ' ') {
			moznePohyby[moznePohybyIndex][0] = x - 1;
			moznePohyby[moznePohybyIndex][1] = y - 2;
			moznePohybyIndex++;
		}
		else {
			if (barvy[x - 1][y - 2] != barva) {
				moznePohyby[moznePohybyIndex][0] = x - 1;
				moznePohyby[moznePohybyIndex][1] = y - 2;
				moznePohybyIndex++;
			}
		}
	}
	if (existencePolicka(x + 2, y + 1)) {
		if (figurky[x + 2][y + 1] == ' ') {
			moznePohyby[moznePohybyIndex][0] = x + 2;
			moznePohyby[moznePohybyIndex][1] = y + 1;
			moznePohybyIndex++;
		}
		else {
			if (barvy[x + 2][y + 1] != barva) {
				moznePohyby[moznePohybyIndex][0] = x + 2;
				moznePohyby[moznePohybyIndex][1] = y + 1;
				moznePohybyIndex++;
			}
		}
	}
	if (existencePolicka(x + 2, y - 1)) {
		if (figurky[x + 2][y - 1] == ' ') {
			moznePohyby[moznePohybyIndex][0] = x + 2;
			moznePohyby[moznePohybyIndex][1] = y - 1;
			moznePohybyIndex++;
		}
		else {
			if (barvy[x + 2][y - 1] != barva) {
				moznePohyby[moznePohybyIndex][0] = x + 2;
				moznePohyby[moznePohybyIndex][1] = y - 1;
				moznePohybyIndex++;
			}
		}
	}
	if (existencePolicka(x - 2, y + 1)) {
		if (figurky[x - 2][y + 1] == ' ') {
			moznePohyby[moznePohybyIndex][0] = x - 2;
			moznePohyby[moznePohybyIndex][1] = y + 1;
			moznePohybyIndex++;
		}
		else {
			if (barvy[x - 2][y + 1] != barva) {
				moznePohyby[moznePohybyIndex][0] = x - 2;
				moznePohyby[moznePohybyIndex][1] = y + 1;
				moznePohybyIndex++;
			}
		}
	}
	if (existencePolicka(x - 2, y - 1)) {
		if (figurky[x - 2][y - 1] == ' ') {
			moznePohyby[moznePohybyIndex][0] = x - 2;
			moznePohyby[moznePohybyIndex][1] = y - 1;
			moznePohybyIndex++;
		}
		else {
			if (barvy[x - 2][y - 1] != barva) {
				moznePohyby[moznePohybyIndex][0] = x - 2;
				moznePohyby[moznePohybyIndex][1] = y - 1;
				moznePohybyIndex++;
			}
		}
	}
}

void pohybPesak(int x, int y, int barva) {
	if (barva) {
		if (existencePolicka(x + 1, y)) {
			if (figurky[x + 1][y] == ' ') {
				moznePohyby[moznePohybyIndex][0] = x + 1;
				moznePohyby[moznePohybyIndex][1] = y;
				moznePohybyIndex++;
			}
		}
		if (existencePolicka(x + 1, y - 1)) {
			if (figurky[x + 1][y - 1] != ' ' && barvy[x + 1][y - 1] == 0) {
				moznePohyby[moznePohybyIndex][0] = x + 1;
				moznePohyby[moznePohybyIndex][1] = y - 1;
				moznePohybyIndex++;
			}
		}
		if (existencePolicka(x + 1, y + 1)) {
			if (figurky[x + 1][y + 1] != ' ' && barvy[x + 1][y + 1] == 0) {
				moznePohyby[moznePohybyIndex][0] = x + 1;
				moznePohyby[moznePohybyIndex][1] = y + 1;
				moznePohybyIndex++;
			}
		}
	} 
	else {
		if (existencePolicka(x - 1, y)) {
			if (figurky[x - 1][y] == ' ') {
				moznePohyby[moznePohybyIndex][0] = x - 1;
				moznePohyby[moznePohybyIndex][1] = y;
				moznePohybyIndex++;
			}
		}
		if (existencePolicka(x - 1, y - 1)) {
			if (figurky[x - 1][y - 1] != ' ' && barvy[x - 1][y - 1] == 1) {
				moznePohyby[moznePohybyIndex][0] = x - 1;
				moznePohyby[moznePohybyIndex][1] = y - 1;
				moznePohybyIndex++;
			}
		}
		if (existencePolicka(x + 1, y + 1)) {
			if (figurky[x + 1][y + 1] != ' ' && barvy[x + 1][y + 1] == 1) {
				moznePohyby[moznePohybyIndex][0] = x + 1;
				moznePohyby[moznePohybyIndex][1] = y + 1;
				moznePohybyIndex++;
			}
		}
	}
}

void pohybKral(int x, int y, int barva) {
	if (existencePolicka(x, y + 1)) {
		if ((figurky[x][y + 1] == ' ') || (barvy[x][y + 1] != barva)) {
			moznePohyby[moznePohybyIndex][0] = x;
			moznePohyby[moznePohybyIndex][1] = y + 1;
			moznePohybyIndex++;
		}
	}
	if (existencePolicka(x, y - 1)) {
		if ((figurky[x][y - 1] == ' ') || (barvy[x][y - 1] != barva)) {
			moznePohyby[moznePohybyIndex][0] = x;
			moznePohyby[moznePohybyIndex][1] = y - 1;
			moznePohybyIndex++;
		}
	}
	if (existencePolicka(x - 1, y - 1)) {
		if ((figurky[x - 1][y - 1] == ' ') || (barvy[x - 1][y - 1] != barva)) {
			moznePohyby[moznePohybyIndex][0] = x - 1;
			moznePohyby[moznePohybyIndex][1] = y - 1;
			moznePohybyIndex++;
		}
	}
	if (existencePolicka(x + 1, y + 1)) {
		if ((figurky[x + 1][y + 1] == ' ') || (barvy[x + 1][y + 1] != barva)) {
			moznePohyby[moznePohybyIndex][0] = x + 1;
			moznePohyby[moznePohybyIndex][1] = y + 1;
			moznePohybyIndex++;
		}
	}
	if (existencePolicka(x + 1, y - 1)) {
		if ((figurky[x + 1][y - 1] == ' ') || (barvy[x + 1][y - 1] != barva)) {
			moznePohyby[moznePohybyIndex][0] = x + 1;
			moznePohyby[moznePohybyIndex][1] = y - 1;
			moznePohybyIndex++;
		}
	}
	if (existencePolicka(x - 1, y + 1)) {
		if ((figurky[x - 1][y + 1] == ' ') || (barvy[x - 1][y + 1] != barva)) {
			moznePohyby[moznePohybyIndex][0] = x - 1;
			moznePohyby[moznePohybyIndex][1] = y + 1;
			moznePohybyIndex++;
		}
	}
	if (existencePolicka(x + 1, y)) {
		if ((figurky[x + 1][y] == ' ') || (barvy[x + 1][y] != barva)) {
			moznePohyby[moznePohybyIndex][0] = x + 1;
			moznePohyby[moznePohybyIndex][1] = y;
			moznePohybyIndex++;
		}
	}
	if (existencePolicka(x - 1, y)) {
		if ((figurky[x - 1][y] == ' ') || (barvy[x - 1][y] != barva)) {
			moznePohyby[moznePohybyIndex][0] = x - 1;
			moznePohyby[moznePohybyIndex][1] = y;
			moznePohybyIndex++;
		}
	}
}

int pohyb(int xs, int ys, int xe, int ye, int barva) {
	char temp;
	temp = figurky[xe][ye];
	figurky[xe][ye] = figurky[xs][ys];
	figurky[xs][ys] = ' ';

	int tempBarva;
	tempBarva = barvy[xe][ye];
	barvy[xe][ye] = barvy[xs][ys];
	barvy[xs][ys] = 2;

	if (barva) {
		if (kontrolaSachu(kralPoloha[0][0], kralPoloha[0][1], 1)) {
			figurky[xs][ys] = figurky[xe][ye];
			figurky[xe][ye] = temp;
			barvy[xs][ys] = barvy[xe][ye];
			barvy[xe][ye] = tempBarva;
			return 0;
		}
		return 1;
	}
	else {
		if (kontrolaSachu(kralPoloha[1][0], kralPoloha[1][1], 0)) {
			figurky[xs][ys] = figurky[xe][ye];
			figurky[xe][ye] = temp;
			barvy[xs][ys] = barvy[xe][ye];
			barvy[xe][ye] = tempBarva;
			return 0;
		}
		return 1;
	}
}

int main() {
	int cisloTahu = 1;

	while (!konec) {
		vypisSachovnice(figurky, barvy);
		int xs, xe;
		char ys, ye;
		moznePohybyIndex = 0;

		int aktualniBarva = cisloTahu % 2;

		if (aktualniBarva) {
			printf("\nhraje bila");
		}
		else {
			printf("\nhraje cerna");
		}

		while (true) {
			printf("\nzadejte policko, ze ktereho tahnete: ");
			scanf(" %c%d", &ys, &xs);
			xs = xs - 1;
			ys = ys - 97;
			printf("\n");
			//printf("%d-%d", xs, ys);
			if (existencePolicka(xs, ys)) {
				if (aktualniBarva == barvy[xs][ys]) {
					switch (figurky[xs][ys]) {
					case 'P':
						pohybPesak(xs, ys, aktualniBarva);
						break;
					case 'V':
						pohybVez(xs, ys, aktualniBarva);
						break;
					case 'H':
						pohybKun(xs, ys, aktualniBarva);
						break;
					case 'S':
						pohybStrelec(xs, ys, aktualniBarva);
						break;
					case 'Q':
						pohybKralovna(xs, ys, aktualniBarva);
						break;
					case 'K':
						pohybKral(xs, ys, aktualniBarva);
						break;
					}
					break;
				}
			}
			printf("\nspatne zvolene policko");
		}
		//printf("\n%d", moznePohybyIndex);
		printf("\nmozny tah:");
		for (int i = 0; i < moznePohybyIndex; i++) {
			printf(" %c%d ", moznePohyby[i][1]+97, moznePohyby[i][0]+1);
		}
		printf("\n");
		
		int end = 1;

		while (end) {
			printf("\nzadejte policko, na ktere tahnete: ");
			scanf(" %c%d", &ye, &xe);
			//printf("\n%d", xe);
			xe = xe - 1;
			ye = ye - 97;
			//printf("\n aktualni %d-%d", xe, ye);
			if (existencePolicka(xe, ye)) {
				if (aktualniBarva != barvy[xe][ye]) {
					//printf("%d-%d", xe, ye);
					for (int i = 0; i < moznePohybyIndex; i++) {
						//printf("\nmozny tah: %d-%d", moznePohyby[i][0], moznePohyby[i][1]);
						if (moznePohyby[i][0] == xe && moznePohyby[i][1] == ye) {
							//printf("\n%d-%d", moznePohyby[i][0], moznePohyby[i][1]);
							if (pohyb(xs, ys, xe, ye, aktualniBarva)) {
								if (figurky[xe][ye] == 'K') {
									kralPoloha[aktualniBarva][0] = xe;
									kralPoloha[aktualniBarva][1] = ye;
								}
							}
							end = 0;
							break;
						}
						// upravit
						else {
							printf("\ntah nelze provest");
						}
					}
				}
				else {
					printf("\nspatna barva");
				}
			}
			else {
				printf("\npolicko neexistuje");
			}
			//printf("\npolicko neexistuje nebo tah nelze provest");
		}

		//printf("%d%d-%d%d", xs, ys, xe, ye);
		//printf("%d", existencePolicka(xs, ys));
		//printf("%d", existencePolicka(xe, ye));

		cisloTahu++;
	}
}
