// sachy3.cpp: Definuje vstupní bod pro aplikaci.
//

#include "sachy3.h"
#include <stdlib.h>
#include <stdio.h>

#include "sachovnice.h"
#include "pohyby.h"
#include "ui.h"

int konec = 0;

int main() {
	menu:
	system("cls");
	int cisloTahu = 1;
	menu(&cisloTahu);
	system("cls");

	while (!konec) {
		int patInt = 0;
		sach:
		vypisSachovnice(figurky, barvy);
		int xs, xe;
		char ys, ye;
		int end = 1;
		moznePohybyIndex = 0;

		int aktualniBarva = cisloTahu % 2;

		if (aktualniBarva) {
			printf("\033[36m\033[40m");
			printf("\nhraje %s", hrac1Jmeno);
			printf("\033[0m");
		}
		else {
			printf("\033[31m\033[40m");
			printf("\nhraje %s", hrac2Jmeno);
			printf("\033[0m");
		}
		
		if (kontrolaSachu(kralPoloha[aktualniBarva][0], kralPoloha[aktualniBarva][1], aktualniBarva)) {
			printf("\nmas SACH");
		}

		while (true) {
			printf("\nzadejte policko, ze ktereho tahnete: ");
			scanf(" %c%d", &ys, &xs);
			if (ys == 'm') {
				if (aktualniBarva) {
					printf("\nhru vyhrava \033[31m\033[40m%s\033[0m\n", hrac2Jmeno);
				}
				else {
					printf("\nhru vyhrava \033[36m\033[40m%s\033[0m\n", hrac2Jmeno);
				}
				getchar();
				getchar();
				goto menu;
			}
			if (ys == 's') {
				ulozitHru(xs, aktualniBarva);
				end = 0;
				goto menu;
			}
			if (ys == 'q') {
				goto menu;
			}
			if (ys == 'k') {
				pat:
				cisloTahu++;
				if (patInt) {
					char patChar;
					printf("\nchcete ukoncit hru patem (a/n): ");
					scanf(" %c", &patChar);
					if (patChar == 'k') {
						goto menu;
					}
					else {
						system("cls");
						goto sach;
					}
				}
				patInt++;
				goto pat;
			}
			xs = xs - 1;
			ys = ys - 97;
			printf("\n");
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
		if (!moznePohybyIndex) {
			printf("\ns touto figurkou nemuzes hnout\n");
			continue;
		}

		printf("\nmozny tah:");
		for (int i = 0; i < moznePohybyIndex; i++) {
			printf(" %c%d ", moznePohyby[i][1]+97, moznePohyby[i][0]+1);
		}
		printf("\n");

		while (end) {
			printf("\nzadejte policko, na ktere tahnete: ");
			scanf(" %c%d", &ye, &xe);
			xe = xe - 1;
			ye = ye - 97;
			if (existencePolicka(xe, ye)) {
				if (aktualniBarva != barvy[xe][ye]) {
					for (int i = 0; i < moznePohybyIndex; i++) {
						if (moznePohyby[i][0] == xe && moznePohyby[i][1] == ye) {						
							if (pohyb(xs, ys, xe, ye, aktualniBarva)) {
								end = 0;
								break;
							}
							else {
								system("cls");
								goto sach;
							}
							break;
						}
						// upravit
						else {
							//printf("\ntah nelze provest");
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
		}
		//system("cls");
		printf("\n");
		cisloTahu++;
	}
}
