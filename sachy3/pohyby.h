#pragma once

int kralPoloha[][2];
int moznePohyby[][2];
extern int moznePohybyIndex;

void pohybVez(int x, int y, int barva);
void pohybStrelec(int x, int y, int barva);
void pohybKralovna(int x, int y, int barva);
void pohybKun(int x, int y, int barva);
void pohybPesak(int x, int y, int barva);
void pohybKral(int x, int y, int barva);
int pohyb(int xs, int ys, int xe, int ye, int barva);