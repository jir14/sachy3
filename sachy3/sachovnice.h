#pragma once

int sachovnice[][8];
int barvy[][8];
char figurky[][8];

void vypisSachovnice(char figurky[8][8], int barvy[8][8]);
int existencePolicka(int x, int y);
int kontrolaSachu(int x, int y, int barva);