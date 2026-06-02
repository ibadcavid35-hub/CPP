#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

#define sizec 10
#define targetsize 100
int comrow[targetsize];
int comcol[targetsize];
int targetcompcount = 0;

//Simvollar

char water = '~';
char ship = 'S';
char hit = 'X';
char miss = 'O';

//Shipgrid

void drawBoard(char** shipgrid) {
	cout << "  ";
	for (int i = 0;i < sizec;i++)
		cout << i << ' ';
	cout << endl;
	for (int i = 0;i < sizec;i++) {
		cout << i << ' ';
		for (int j = 0;j < sizec;j++) {
			char c = shipgrid[i][j];
			if (c == water) cout << "\033[94m" << c << "\033[0m" << ' ';
			else if (c == ship) cout << "\033[32m" << c << "\033[0m" << ' ';
			else if (c == hit) cout << "\033[31m" << c << "\033[0m" << ' ';
			else if (c == miss) cout << "\033[93m" << c << "\033[0m" << ' ';
			
		}
		cout << endl;
	}
}

//Place ship

bool placeShips(char** shipgrid, int row, int col, int shipsize, int secim) {
	if (secim == 1) {
		if (!(row >= 0 && row <= 9 && col >= 0 && col <= 9)) return false;
		if (col + shipsize > sizec) return false;
		for (int i = 0;i < shipsize;i++) {
			if (shipgrid[row][col + i] != water) return false;
		}
		for (int i = 0;i < shipsize;i++) {
			shipgrid[row][col + i] = ship;
		}
	}
	else if (secim == 2) {
		if (!(row >= 0 && row <= 9 && col >= 0 && col <= 9)) return false;
		if (row + shipsize > sizec) return false;
		for (int i = 0;i < shipsize;i++) {
			if (shipgrid[row + i][col] != water) return false;
		}
		for (int i = 0;i < shipsize;i++) {
			shipgrid[row + i][col] = ship;
		}
	}
	else {
		cout << "Yanlish secim!" << endl;
		return false;
	}
	return true;
}

//Attack

bool attack(char** shipgrid, int row, int col) {
	if (!(row >= 0 && row <= 9 && col >= 0 && col <= 9)) return false;
	if (shipgrid[row][col] == water) {
		shipgrid[row][col] = miss;
		cout << "\n\033[93mBosa cixdi.\033[0m\n";
		return false;
	}
	if (shipgrid[row][col] == hit || shipgrid[row][col] == miss) {
		cout << "\n\033[93mBu yere ates acilmisdi.\033[0m\n";
		return false;
	}
	
	if (shipgrid[row][col] == ship) {
		shipgrid[row][col] = hit;
		cout << "\n\033[31mVuruldu!\033[0m\n";
		return true;
	}
	return false;
}

//Komp vurus

void addcomptarget(int row, int col,char** shipgrid) {
	if (row >= 0 && row <= 9 && col >= 0 && col <= 9) {
		 
		if (shipgrid[row][col] == hit || shipgrid[row][col] == miss) return;

		if (targetcompcount < targetsize) {
			comrow[targetcompcount] = row;
			comcol[targetcompcount] = col;
			targetcompcount++;
		}
	}
}

//Comp Board

void comppboard(char** shipgrid) {
	cout << "  ";
	for (int i = 0;i < sizec;i++)
		cout << i << ' ';
	cout << endl;
	for (int i = 0;i < sizec;i++) {
		cout << i << ' ';
		for (int j = 0;j < sizec;j++) {
			char c1 = shipgrid[i][j];
			if (c1 == ship) cout << "\033[94m" << water << "\033[0m" << ' ';
			else if (c1 == hit) cout << "\033[31m" << c1 << "\033[0m" << ' ';
			else if (c1 == miss) cout << "\033[93m" << c1 << "\033[0m" << ' ';
			else if(c1 == water) cout << "\033[94m" << c1 << "\033[0m" << ' ';
			
		}
		cout << endl;
	}
}

int main() {
	srand(time(0));
	//Saheler
	char** ocean_grid = new char* [sizec];
	char** comp_grid = new char* [sizec];
	int row, col, size, secim;
	//Vurus saylari
	int oceanhitcount = 0;
	int comphitcount = 0;
	int shipsizes[5] = { 5,4,3,3,2 };
	string shipnames[5] = { "Carrier","Battleship","Submarine","Cruiser","Destroyer" }; //Gemi adlari
	int ss = sizeof shipsizes / sizeof shipsizes[0];  //Gemilerin sayi


	//Ocean_Grid && Target_Grid

	for (int i = 0;i < sizec;i++) {
		ocean_grid[i] = new char[sizec];
		comp_grid[i] = new char[sizec];
	}

	//

	for (int i = 0;i < sizec;i++) {
		for (int j = 0;j < sizec;j++) {
			ocean_grid[i][j] = water;
			comp_grid[i][j] = water;
		}
	}
	//welcome
	cout << "\033[34m=============================\n";
	cout << "= WELCOME TO THE BATTLESHIP =\n";
	cout << "=============================\033[0m\n";
	cout << "\n//*Ocean Grid*\\\\\n\n";
	drawBoard(ocean_grid);
	cout << "\n//*Target Grid*\\\\\n\n";
	drawBoard(comp_grid);

	//Ocean Grid place ship

	cout << "\nOcean Grid place Ship\n";
	for (int i = 0;i < 5;i++) {
		cout << "\n\nRow and Col: ";
		cin >> row >> col;
		size = shipsizes[i];
		cout << "1-Horizantal" << endl;
		cout << "2-Vertical" << endl;
		cout << "Seciminizi edin(1/2): ";
		cin >> secim;
		cout << endl << shipnames[i] << endl;
		if (!placeShips(ocean_grid, row, col, size, secim)) {
			cout << "Yanlish yer. Yeniden yoxlayin!";
			i--;
		}
		cout << endl << endl;
		drawBoard(ocean_grid);
	}


	//Komp Grid place Ship

	for (int i = 0;i < 5;i++) {
		row = rand() % sizec;
		col = rand() % sizec;
		size = shipsizes[i];
		secim = (rand() % 2) + 1;
		if (!placeShips(comp_grid, row, col, size, secim)) {
			i--;
			continue;
		}

	}
	//start
	while (true) {
		int rowoce, coloce, rowcom, colcom;
		//Attack from Ocean player
		cout << endl << endl;
		cout << "\033[94m#############################\n";
		cout << "## Ocean Hucum ucun (row/col): \033[0m";
		cin >> rowoce >> coloce;
		if (attack(comp_grid, rowoce, coloce)) {
			oceanhitcount++;
		}
		cout << "Okean vurus sayi: " << oceanhitcount << endl;

		comppboard(comp_grid);
		cout << endl << endl;

		//Attack from Komp player
		cout << "\033[91m==============================\n";
		cout << "== Comp Hucum \033[0m";
		if (targetcompcount > 0) {
			targetcompcount--;
			rowcom = comrow[targetcompcount];
			colcom = comcol[targetcompcount];
		}
		else {
			rowcom = rand() % sizec;
			colcom = rand() % sizec;
		}
		while (ocean_grid[rowcom][colcom] == hit || ocean_grid[rowcom][colcom] == miss) {
			if (targetcompcount > 0) {
				targetcompcount--;
				rowcom = comrow[targetcompcount];
				colcom = comcol[targetcompcount];
			}
			else {
				rowcom = rand() % sizec;
				colcom = rand() % sizec;
			}
		}

		cout << "\nKompun daxil etdiyi row ve col: " << rowcom << " " << colcom << endl;

		if (attack(ocean_grid, rowcom, colcom)) {
			comphitcount++;

			addcomptarget(rowcom + 1, colcom, ocean_grid);
			addcomptarget(rowcom - 1, colcom, ocean_grid);
			addcomptarget(rowcom, colcom + 1, ocean_grid);
			addcomptarget(rowcom, colcom - 1, ocean_grid);
		}

		cout << "Comp vurus sayi: " << comphitcount << endl;
		drawBoard(ocean_grid);
		cout << endl << endl;
		//winner ocean

		if (oceanhitcount == 17) {
			cout << "\033[92m========================\n";
			cout << "= WINNER OCEAN PLAYER! =\n";
			cout << "========================\033[0m";
			
			return 0;
		}

		//winner kompt

		if (comphitcount == 17) {
			cout << "\033[92m========================\n";
			cout << "= WINNER KOMPT PLAYER! =\n";
			cout << "========================\033[0m";

			return 0;
		}




	}

	//delete ocean_grid & delete comp_grid

	for (int i = 0;i < 10;i++) {
		delete[] ocean_grid[i];
		delete[] comp_grid[i];
	}
	delete[] ocean_grid;
	delete[] comp_grid;

	

	return 0;
};