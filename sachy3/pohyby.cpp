#include <stdlib.h>
#include <stdio.h>

#include "sachovnice.h"

int kralPoloha[2][2] = { {7,3}, {0,3} };
int moznePohyby[64][2] = { {} };
int moznePohybyIndex = 0;

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
			if (x == 1) {
				moznePohyby[moznePohybyIndex][0] = x + 2;
				moznePohyby[moznePohybyIndex][1] = y;
				moznePohybyIndex++;
			}
		}
		if (existencePolicka(x + 1, y - 1)) {
			if (figurky[x + 1][y - 1] != ' ' && !barvy[x + 1][y - 1]) {
				moznePohyby[moznePohybyIndex][0] = x + 1;
				moznePohyby[moznePohybyIndex][1] = y - 1;
				moznePohybyIndex++;
			}
		}
		if (existencePolicka(x + 1, y + 1)) {
			if (figurky[x + 1][y + 1] != ' ' && !barvy[x + 1][y + 1]) {
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
			if (x == 6) {
				moznePohyby[moznePohybyIndex][0] = x - 2;
				moznePohyby[moznePohybyIndex][1] = y;
				moznePohybyIndex++;
			}
		}
		if (existencePolicka(x - 1, y - 1)) {
			if (figurky[x - 1][y - 1] != ' ' && barvy[x - 1][y - 1]) {
				moznePohyby[moznePohybyIndex][0] = x - 1;
				moznePohyby[moznePohybyIndex][1] = y - 1;
				moznePohybyIndex++;
			}
		}
		if (existencePolicka(x - 1, y + 1)) {
			if (figurky[x - 1][y + 1] != ' ' && barvy[x - 1][y + 1]) {
				moznePohyby[moznePohybyIndex][0] = x - 1;
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

	if (figurky[xs][ys] == 'K') {
		kralPoloha[barva][0] = xe;
		kralPoloha[barva][1] = ye;
	}

	temp = figurky[xe][ye];
	figurky[xe][ye] = figurky[xs][ys];
	figurky[xs][ys] = ' ';

	int tempBarva;
	tempBarva = barvy[xe][ye];
	barvy[xe][ye] = barvy[xs][ys];
	barvy[xs][ys] = 2;

	if (kontrolaSachu(kralPoloha[barva][0], kralPoloha[barva][1], barva)) {
		figurky[xs][ys] = figurky[xe][ye];
		figurky[xe][ye] = temp;
		barvy[xs][ys] = barvy[xe][ye];
		barvy[xe][ye] = tempBarva;
		if (figurky[xs][ys] == 'K') {
			kralPoloha[barva][0] = xs;
			kralPoloha[barva][1] = ys;
		}
		return 0;
	}
	return 1;
}