#include "sachy3.h"
#include <stdlib.h>
#include <stdio.h>

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
	for (int i = 1; i < 8; i++) {
		if (existencePolicka(x, y + i)) {
			if (figurky[x][y + i] != ' ') {
				if ((figurky[x][y + i] == 'V' || figurky[x][y + i] == 'Q') && barvy[x][y + i] != barva) {
					return 1;
				}
				break;
			}
		}

		if (existencePolicka(x, y - i)) {
			if (figurky[x][y - i] != ' ') {
				if ((figurky[x][y - i] == 'V' || figurky[x][y - i] == 'Q') && barvy[x][y - i] != barva) {
					return 1;
				}
				break;
			}
		}
	}
	//printf("dvx");
	// vez a dama y
	for (int i = 1; i < 8; i++) {
		if (existencePolicka(x + i, y)) {
			if (figurky[x + i][y] != ' ') {
				if ((figurky[x + i][y] == 'V' || figurky[x + i][y] == 'Q') && barvy[x + i][y] != barva) {
					return 1;
				}
				break;
			}
		}

		if (existencePolicka(x - i, y)) {
			if (figurky[x - i][y] != ' ') {
				if ((figurky[x - i][y] == 'V' || figurky[x - i][y] == 'Q') && barvy[x - i][y] != barva) {
					return 1;
				}
				break;
			}
		}
	}
	//printf("dvy");
	// strelec a dama /
	for (int i = 1; i < 8; i++) {
		if (existencePolicka(x - i, y + i)) {
			if (figurky[x - i][y + i] != ' ') {
				if ((figurky[x - i][y + i] == 'S' || figurky[x - i][y + i] == 'Q') && barvy[x - i][y + i] != barva) {
					return 1;
				}
				break;
			}
		}

		if (existencePolicka(x + i, y - i)) {
			if (figurky[x + i][y - i] != ' ') {
				if ((figurky[x + i][y - i] == 'S' || figurky[x + i][y - i] == 'Q') && barvy[x + i][y - i] != barva) {
					return 1;
				}
				break;
			}
		}
	}
	//printf("dsx");
	// strelec a dama \/
	for (int i = 1; i < 8; i++) {
		if (existencePolicka(x - i, y - i)) {
			if (figurky[x - i][y - i] != ' ') {
				if ((figurky[x - i][y - i] == 'S' || figurky[x - i][y - i] == 'Q') && barvy[x - i][y - i] != barva) {
					return 1;
				}
				break;
			}
		}

		if (existencePolicka(x + i, y + i)) {
			if (figurky[x + i][y + i] != ' ') {
				if ((figurky[x + i][y + i] == 'S' || figurky[x + i][y + i] == 'Q') && barvy[x + i][y + i] != barva) {
					return 1;
				}
				break;
			}
		}
	}
	//printf("dsy");
	// pesak
	if (existencePolicka(x + 1, y + 1)) {
		if (figurky[x + 1][y + 1] == 'P' && barvy[x + 1][y + 1] != barva) {
			return 1;
		}
	}
	if (existencePolicka(x - 1, y - 1)) {
		if (figurky[x - 1][y - 1] == 'P' && barvy[x - 1][y - 1] != barva) {
			return 1;
		}
	}
	//printf("p");

	// kun
	if (existencePolicka(x + 1, y + 2)) {
		if (figurky[x + 1][y + 2] == 'H' && barvy[x + 1][y + 2] != barva) {
			return 1;
		}
	}
	if (existencePolicka(x + 2, y - 1)) {
		if (figurky[x + 2][y - 1] == 'H' && barvy[x + 2][y - 1] != barva) {
			return 1;
		}
	}
	if (existencePolicka(x - 1, y + 2)) {
		if ((figurky[x - 1][y + 2] == 'H') && barvy[x - 1][y + 2] != barva) {
			return 1;
		}
	}
	if (existencePolicka(x - 2, y - 1)) {
		if ((figurky[x - 1][y - 1] == 'H') && barvy[x - 1][y - 1] != barva) {
			return 1;
		}
	}
	if (existencePolicka(x - 1, y - 2)) {
		if ((figurky[x - 1][y - 2] == 'H') && barvy[x - 1][y - 2] != barva) {
			return 1;
		}
	}
	if (existencePolicka(x - 2, y + 1)) {
		if ((figurky[x - 2][y + 1] == 'H') && barvy[x - 2][y + 1] != barva) {
			return 1;
		}
	}
	if (existencePolicka(x + 1, y - 2)) {
		if ((figurky[x + 1][y - 2] == 'H') && barvy[x + 1][y - 2] != barva) {
			return 1;
		}
	}
	if (existencePolicka(x + 2, y + 1)) {
		if ((figurky[x + 2][y + 1] == 'H') && barvy[x + 2][y + 1] != barva) {
			return 1;
		}
	}
	//printf("h");
	return 0;
}