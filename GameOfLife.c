//Conway's Game of Life

#include <stdio.h>
#include <time.h>
#define ROWS 50 
#define COLS 100

int generation = 0;
int population = 0;
int populationMax = 0;
int populationMin = 0;
int tempGrid[ROWS][COLS];

int getUserInput();
void initGrid(int, int, int[ROWS][COLS]); // # of rows, # of columns, array size
void processGeneration(int, int, int[ROWS][COLS]); // # of rows, # of columns, array size
int countNeighbors(int, int, int[ROWS][COLS], int, int); // # of rows, # of columns, array size
void printGrid(int, int, int[ROWS][COLS]); // # of rows, # of columns, array size
void sleep(unsigned int); // sleep between each generation iteration

int main() {
	srand((unsigned int) time(NULL));
	int grid[ROWS][COLS];
	initGrid(ROWS, COLS, grid);
	printGrid(ROWS, COLS, grid);
	
	int i, g;
	g = getUserInput();
	
	for (i = 0; i < g; i++) {
		generation++;
		processGeneration(ROWS, COLS, grid);
		printGrid(ROWS, COLS, grid);
		sleep(100000);
	}
	
	return 0;
}

//*********************************************************************
int getUserInput() {
	int g;
	printf("Thanks for playing The Game of Life!\n");
	printf("How many generations do you want to watch: ");
	scanf("%d", &g);
	return g;
}

//*********************************************************************
void initGrid(int rows, int cols, int g[rows][cols]) {
	int i, j, k;
	for(i = 0; i < rows; i++) {
		for(j = 0; j < cols; j++) {
			/*
			
			we have a border of -1's.  makes it easier to iterate through our grid
			
			[-1][-1][-1][-1][-1]
			[-1]	[][][]	[-1]
			[-1]	[][][]	[-1]			
			[-1]	[][][]	[-1]
			[-1][-1][-1][-1][-1]									
			*/
			if(i == 0 || i == (rows -1) || j == 0 || j == (cols -1)) {
				g[i][j] = -1;
			} else {
				k = rand() % 3;
				if(k == 0) {
					g[i][j] = 1;
					population++;
				} else {
					g[i][j] = 0;
				}
			} 
		}
	}
	processGeneration(rows, cols, g);
}

//*********************************************************************
void processGeneration(int rows, int cols, int g[rows][cols]) {
	int i, j, neighbors;
	for(i = 0; i < rows; i++) {
		for(j = 0; j < cols; j++) {
			if(g[i][j] == -1) continue;
			neighbors = countNeighbors(rows, cols, g, i, j); // count neighbors
			
			if(g[i][j] == 1 && (neighbors < 2 || neighbors > 3))
				tempGrid[i][j] = 0;
			else if((g[i][j] == 0) && (neighbors == 3))
				tempGrid[i][j] = 1;
		}
	}
	
	population = 0;
	for(i = 0; i < rows; i++) {
		for(j = 0; j < cols; j++) {
			if(g[i][j] == -1) continue; // if it's the border... do nothing
			if(tempGrid[i][j] == 1) population++;
			g[i][j] = tempGrid[i][j]; // update actual grid
		}
		
		// keep track of Population Min and Max
		if(population > populationMax)
			populationMax = population;
		if(population < populationMin || populationMin == 0)
			populationMin = population;
	}
}

//*********************************************************************
int countNeighbors(int rows, int cols, int g[rows][cols], int x, int y) {  // rows, cols, array, x position, y position
	/*  To count neighbors, iterate through each row, one at a time...
		row 1: [	]	[	]	[	]
		row 2: [	]	[ x ]	[	]
		row 3: [	]	[	]	[	]
	*/
	
	int n = 0, i, j;
	for (j = y - 1; j < y + 2; j++) {
		for(i = x - 1; i < x + 2; i++) {
			if(i == x && j == y) continue; // if it's our current element, do nothing and continue
			if(g[i][j] != -1) { // if it's not -1 (the border outside our 9 cells), then add up neighbors
				n += g[i][j];
			} 
		}
	}
	return n;
}

//*********************************************************************
void printGrid(int rows, int cols, int g[rows][cols]) {
	system("clear");  // unix, for windows use system("cls");
	printf("Welcome to the Game of Life -- Generation: %d\n", generation);
	printf("Population: %d (MAX: %d MIN: %d)\n", population
											  , populationMax
											  , populationMin);
	
	int i, j;
	for (i = 0; i < rows; i++) {
		for (j = 0; j < cols; j++) {
			switch(g[i][j]) {
				case -1: putchar('+'); break;
				case  0: putchar(' '); break;
				case  1: putchar('*'); break;
				default: break;
			}
		}
		putchar('\n');
	}
}

//*********************************************************************
void sleep(unsigned int mill) { // milliseconds
	clock_t start = clock();
	while(clock() - start < mill) { }
}





















