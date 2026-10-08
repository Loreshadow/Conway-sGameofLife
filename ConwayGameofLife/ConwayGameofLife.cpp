

#include <iostream>
#include <Windows.h>
#include <string>

// init le tableau a false partout ( toutes les cellules morte par défaut)
void initArray(bool* array, int size) {
	for (int i = 0; i < size; i++) {
		array[i] = 0;
	}
}

// crée et initialise la grid dans la console.
void displayGrid(bool* grid, int sizeX, int sizeY) {

		for (int collumn = 0; collumn < sizeY; collumn++) {
			for (int line = 0; line < sizeX; line++) {

				if (grid[collumn * sizeX + line] == 0) {
					std::cout << "□";
				}
				else { 
					std::cout << "■"; 
				}
			}
			std::cout << "\n";
		}
}
// check des voisins dans toutes les direction
int checkCells(bool* array, int x, int y, int sizeX, int sizeY) {
	int nb = 0;
	for (int dirY = -1; dirY <= 1; dirY++) {
		for (int dirX = -1; dirX <= 1; dirX++) {
			if (dirY == 0 && dirX == 0) continue; // on ignore la cellule au centre qui est donc nous dans ce contexte

			// check pour les bord de la grid.
			int bx = x + dirX;
			int by = y + dirY;
			if (bx >= 0 && bx < sizeX && by >= 0 && by < sizeY) {
				if (array[by * sizeX + bx]) {
					nb++;
				}
			}
		}
	}
	return nb;
}
// utilise le check des voisins et met la jour la grid en utilisant nextGrid
void updateGrid(bool* current, bool* next, int sizeX, int sizeY) {
	for (int y = 0; y < sizeY; y++) {
		for (int x = 0; x < sizeX; x++) {
			int number = checkCells(current, x, y, sizeX, sizeY);
			bool alive = current[y * sizeX + x];
			if (alive) {
				next[y * sizeX + x] = (number == 2 || number == 3);
			}
			else {
				next[y * sizeX + x] = (number == 3);
			}
		}
	}
}



int main()
{
	// console UTF-8
	SetConsoleOutputCP(65001);


	int sizeY = 0, sizeX = 0;
	// choix taille par l'utilisateur
	std::cout << "Choisissez la taille du tableau pour le jeu de la vie.";
	std::cout << "Taille X";
	std::cin >> sizeX;
	std::cout << "Taille Y";
	std::cin >> sizeY;
	int totalSize = sizeY * sizeX;


	// définition des grid	
	bool* currentGrid = new bool[totalSize];
	bool* nextGrid = new bool[totalSize];
	// initialisation des grids.
	initArray(currentGrid, totalSize);
	initArray(nextGrid, totalSize);

	// Gosper Glider Gun 
	currentGrid[5 * sizeX + 24] = true;

	currentGrid[6 * sizeX + 22] = true;
	currentGrid[6 * sizeX + 24] = true;

	currentGrid[7 * sizeX + 12] = true;
	currentGrid[7 * sizeX + 13] = true;
	currentGrid[7 * sizeX + 20] = true;
	currentGrid[7 * sizeX + 21] = true;
	currentGrid[7 * sizeX + 34] = true;
	currentGrid[7 * sizeX + 35] = true;

	currentGrid[8 * sizeX + 11] = true;
	currentGrid[8 * sizeX + 15] = true;
	currentGrid[8 * sizeX + 20] = true;
	currentGrid[8 * sizeX + 21] = true;
	currentGrid[8 * sizeX + 34] = true;
	currentGrid[8 * sizeX + 35] = true;

	currentGrid[9 * sizeX + 0] = true;
	currentGrid[9 * sizeX + 1] = true;
	currentGrid[9 * sizeX + 10] = true;
	currentGrid[9 * sizeX + 16] = true;
	currentGrid[9 * sizeX + 20] = true;
	currentGrid[9 * sizeX + 21] = true;

	currentGrid[10 * sizeX + 0] = true;
	currentGrid[10 * sizeX + 1] = true;
	currentGrid[10 * sizeX + 10] = true;
	currentGrid[10 * sizeX + 14] = true;
	currentGrid[10 * sizeX + 16] = true;
	currentGrid[10 * sizeX + 17] = true;
	currentGrid[10 * sizeX + 22] = true;
	currentGrid[10 * sizeX + 24] = true;

	currentGrid[11 * sizeX + 10] = true;
	currentGrid[11 * sizeX + 16] = true;
	currentGrid[11 * sizeX + 24] = true;

	currentGrid[12 * sizeX + 11] = true;
	currentGrid[12 * sizeX + 15] = true;

	currentGrid[13 * sizeX + 12] = true;
	currentGrid[13 * sizeX + 13] = true;






	//displayGrid(currentGrid, sizeX, sizeY);

	//loop de jeu 
	while (true) {
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0, 0 }); // replace la souris en haut au début du terminal
		//std::system("cls"); // vient de la lib windows.h sert a clear la console.
		displayGrid(currentGrid, sizeX, sizeY);
		updateGrid(currentGrid, nextGrid, sizeX, sizeY);

		bool* temp = currentGrid;
		currentGrid = nextGrid;
		nextGrid = temp;
		Sleep(50);
	}
	


	delete[] currentGrid;
	currentGrid = nullptr;
	delete[] nextGrid;
	nextGrid = nullptr;

	return 0;	
}