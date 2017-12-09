#include <fstream>
#include <iostream>
using namespace std;

fstream mapa;
short tab[20][20];
short tablista[20][20];
float heurystyka[20][20];
int koszt[20][20];
float suma[20][20];
short kierunek[20][20];

bool LO_niep() {
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			if (tablista[i][j] == 1) return true;
		}
	}

	return false;
}

void wypiszSciezke() {

}

int main() {
	mapa.open("grid.txt");
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			mapa >> tab[i][j];
			heurystyka[i][j] = sqrt((float)(i - 19)*(i - 19) + (float)(j - 19)*(j - 19));
			tablista[i][j] = 0;
		}
	}

	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			cout << tab[i][j] << " ";
		}
		cout << endl;
	}

	tablista[0][0] = 1;
	koszt[0][0] = 0;
	suma[0][0] = koszt[0][0] + heurystyka[0][0];
	kierunek[0][0] = 0;

	while (LO_niep()) {
		float min = 50000.0f;
		int bX, bY;
		for (int i = 0; i < 20; i++) {
			for (int j = 0; j < 20; j++) {
				if (tablista[i][j] == 1) {
					if (min > suma[i][j]) {
						min = suma[i][j];
						bY = j;
						bX = i;
					}
				}
			}
		}

		if (min == 50000.0f) {
			cout << "Nie ma sciezki.";
			getchar();
			return 0;
		}
		else if (bX == 19 && bY == 19) {


			cout << "Znaleziona sciezka: (19, 19) ";
			do {
				tab[bX][bY] = 3;
				if (kierunek[bX][bY] == 1) bX--;
				else if (kierunek[bX][bY] == 3) bX++;
				else if (kierunek[bX][bY] == 2) bY--;
				else if (kierunek[bX][bY] == 4) bY++;
				cout << "-> (" << bX << ", " << bY << ")";
			} while (!(bX == 0 && bY == 0));

			cout << endl << endl;
			tab[bX][bY] = 3;
			for (int i = 0; i < 20; i++)
			{
				for (int j = 0; j < 20; j++)
				{
					cout << tab[i][j] << " ";
				}

				cout << endl;
			}
			getchar();
			return 0;
		}
		else {
			tablista[bX][bY] = 2;
			if (bX > 0) {
				if (tab[bX - 1][bY] == 0 && (tablista[bX - 1][bY] == 0 || (tablista[bX - 1][bY] == 1 && (koszt[bX - 1][bY] > koszt[bX][bY] + 1)))) {
					tablista[bX - 1][bY] = 1;
					koszt[bX - 1][bY] = koszt[bX][bY] + 1;
					suma[bX - 1][bY] = koszt[bX - 1][bY] + heurystyka[bX - 1][bY];
					kierunek[bX - 1][bY] = 3;
				}
			}

			if (bX < 19) {
				if (tab[bX + 1][bY] == 0 && (tablista[bX + 1][bY] == 0 || (tablista[bX + 1][bY] == 1 && (koszt[bX + 1][bY] > koszt[bX][bY] + 1)))) {
					tablista[bX + 1][bY] = 1;
					koszt[bX + 1][bY] = koszt[bX][bY] + 1;
					suma[bX + 1][bY] = koszt[bX + 1][bY] + heurystyka[bX + 1][bY];
					kierunek[bX + 1][bY] = 1;
				}
			}
			if (bY > 0) {
				if (tab[bX][bY - 1] == 0 && (tablista[bX][bY - 1] == 0 || (tablista[bX][bY + 1] == 1 && (koszt[bX][bY + 1] > koszt[bX][bY] + 1)))) {
					tablista[bX][bY - 1] = 1;
					koszt[bX][bY - 1] = koszt[bX][bY] + 1;
					suma[bX][bY - 1] = koszt[bX][bY - 1] + heurystyka[bX][bY - 1];
					kierunek[bX][bY - 1] = 4;
				}
			}
			if (bY < 19) {
				if (tab[bX][bY + 1] == 0 && (tablista[bX][bY + 1] == 0 || (tablista[bX][bY + 1] == 1 && (koszt[bX][bY + 1] > koszt[bX][bY] + 1)))) {
					tablista[bX][bY + 1] = 1;
					koszt[bX][bY + 1] = koszt[bX][bY] + 1;
					suma[bX][bY + 1] = koszt[bX][bY + 1] + heurystyka[bX][bY + 1];
					kierunek[bX][bY + 1] = 2;
				}
			}
		}
	}
}