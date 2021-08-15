#include <iostream>
#include <limits>


void ignoreLine() {
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void printGrid(int numRows,int numCols, char grid[][3]) {
	std::cout << '\n';
	for (int row = 0; row < numRows; row++) {
		for (int col = 0; col < numCols; col++) {
			std::cout << grid[row][col];
		}
		std::cout << "\n";
	}
}

void resetGrid(char grid[][3]) {
	for (int row = 0; row <= 2; row++) {
		for (int col = 0; col <= 2; col++) {
			grid[row][col] = '.';
		}
	}

	printGrid(3, 3, grid);
}

bool askForReset(bool isRunning, char grid[][3]) {
	char resetInput = ' ';
	bool validInput = false;
	std::cout << "would you like to play again? y/n: ";
	do {
		std::cin >> resetInput;
		switch (resetInput) {
		case 'y':
		case 'Y':
			resetGrid(grid);
			isRunning = true;
			validInput = true;
			break;
		case 'n':
		case 'N':
			isRunning = false;
			validInput = true;
			break;
		default:
			std::cout << "\nInvalid input. Please try again.\ny/n: ";
			ignoreLine();
			std::cin.clear();
			validInput = false;
			break;
		}
	} while (!validInput);

	return isRunning;
}

int handleInputErrors(int newCoordinate) {
	if (std::cin.fail()) {
		std::cin.clear();
		ignoreLine();
		newCoordinate = -1;
		std::cout << "\nInvalid coordinate. Please try again. \n";
	}
	else if (newCoordinate >= 1 && newCoordinate <= 3) {
		ignoreLine();
		newCoordinate -= 1;
	}
	else {
		ignoreLine();
		newCoordinate = -1;
		std::cout << "\nInvalid coordinate. Please try again. \n";
	}

	return newCoordinate;
}

int setCoordinate() {
	int newCoordinate = 0;
	std::cin >> newCoordinate;
	newCoordinate = handleInputErrors(newCoordinate);
	return newCoordinate;
}

bool testForCollision(int rowCoordinate, int colCoordinate, char grid[][3]) {
	bool collision = false;
	if (grid[rowCoordinate][colCoordinate] == 'x' || grid[rowCoordinate][colCoordinate] == 'o') {
		std::cout << "\nA collision has been detected. Please try again.\n";
		collision = true;
	}
	return collision;
}

void addMarkToGrid(int rowCoordinate, int colCoordinate, int player, char grid[][3]) {
	if (player == 0) {
		grid[rowCoordinate][colCoordinate] = 'x';
	}
	else {
		grid[rowCoordinate][colCoordinate] = 'o';
	}
}

bool testForDiagWin(int player, char players[], char grid[][3]) {
	int colRight = 2;
	int colLeft = 0;
	int sum = 0;
	for (int row = 0; row <= 2; row++) {
		if (grid[row][colRight] != players[player] && grid[row][colLeft] != players[player]) {
			return false;
		}
		else if (grid[row][colRight] == players[player] || grid[row][colLeft] == players[player]) {
			sum += row;
		}
		colRight--;
		colLeft++;
	}

	if (sum == 3) {
		std::cout << "Player " << players[player] << " wins!\n";
		return true;
	}
	else
		return false;
}

bool testForRowWin(int rowCoordinate, int player, char players[], char grid[][3]) {
	int sum = 0;
	for (int i = 0; i <= 2; i++) {
		if (grid[rowCoordinate][i] != players[player]) {
			return false;
		}
		else if (grid[rowCoordinate][i] == players[player]) {
			sum += i;
		}
	}

	if (sum == 3) {
		std::cout << "Player " << players[player] << " wins!\n";
		return true;
	} 
	else 
		return false;
}

bool testForColWin(int colCoordinate, int player, char players[], char grid[][3]) {
	int sum = 0;
	for (int i = 0; i <= 2; i++) {
		if (grid[i][colCoordinate] != players[player]) {
			return false;
		}
		else if (grid[i][colCoordinate] == players[player]) {
			sum += i;
		}
	}

	if (sum == 3) {
		std::cout << "Player " << players[player] << " wins!\n";
		return true;
	}
	else 
		return false;
}

bool testForWin(int rowCoordinate, int colCoordinate, int player, char players[], char grid[][3]) {
	if (testForColWin(colCoordinate, player, players, grid)) {
		return true;
	}
	else if (testForRowWin(rowCoordinate, player, players, grid)) {
		return true;
	}
	else if (testForDiagWin(player, players, grid)) {
		return true;
	}
	else
		return false;
}

int main() {
	char noughtsAndCrossesGrid[3][3] = {
		{'.', '.', '.'},
		{'.', '.', '.'},
		{'.', '.', '.'},
	};
	int rowCoordinate = 0;
	int colCoordinate = 0;
	int turnCount = 0;
	char players[] = { 'x', 'o' };
	bool isRunning = true;

	printGrid(3, 3, noughtsAndCrossesGrid);
	do {
		int player = turnCount % 2;

		do {
			std::cout << "Player " << players[player] << ", please enter a row coordinate: ";
			rowCoordinate = setCoordinate();
		} while (!(rowCoordinate >= 0 && rowCoordinate <= 2));

		do {
			std::cout << "enter a column coordinate: ";
			colCoordinate = setCoordinate();
		} while (!(colCoordinate >= 0 && colCoordinate <= 2));

		if (!testForCollision(rowCoordinate, colCoordinate, noughtsAndCrossesGrid)) {
			addMarkToGrid(rowCoordinate, colCoordinate, player, noughtsAndCrossesGrid);
			++turnCount;
		}
		printGrid(3, 3, noughtsAndCrossesGrid);
		if (testForWin(rowCoordinate, colCoordinate, player, players, noughtsAndCrossesGrid)) {
			isRunning = askForReset(isRunning, noughtsAndCrossesGrid);
			turnCount = 0;
		}
	} while (isRunning);

	std::cout << "\nThank you for playing!\n";

	return 0;
}