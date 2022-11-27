#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define LENGTH 20
#define PERCENTAGE 10

void DisplayGrid(int grid[LENGTH][LENGTH], int mask[LENGTH][LENGTH]);
void ClearScreen(void);
void RecursiveUnmask(int x, int y);

int grid[LENGTH][LENGTH];
int mask[LENGTH][LENGTH];	

int main(void)
{
	srand(time(NULL)); // Initialize

	// Set grid to all zeros

	for (int i = 0; i < LENGTH; i++)
	{
		for (int j = 0; j < LENGTH; j++)
		{
			grid[i][j] = 0;
			mask[i][j] = 0;
		}
	}
	
	int MINES = (int) LENGTH * 1.6;

	// Plant mines
	printf("MINES %i\n", MINES);
	for (int i = 0; i < MINES; i++)
	{
		int x = rand() % 20;
		int y = rand() % 20;
			
		while (grid[x][y] != 0)
		{
			x = rand() % 20;
			y = rand() % 20;
		}	
		
		grid[x][y] = -1;
		if (x < 19)
		{
			if (y < 19) grid[x+1][y+1] += 1;
			if (y > 0) grid[x+1][y-1] += 1;
			grid[x+1][y] += 1; 
		}

		if (x > 0)
		{
			if (y < 19) grid[x-1][y+1] += 1;
			if (y > 0) grid[x-1][y-1] += 1;
			grid[x-1][y] += 1;
		}

		if (y > 0) grid[x][y-1] += 1;
		if (y < 19) grid[x][y+1] += 1;
	}


	// Display grid
	while (1) {
	
		DisplayGrid(grid, mask);
		int xcoord = -1;
		int ycoord = -1;
		char mode = 'X';
		
		while (xcoord < 0 || xcoord > 19 || ycoord < 0 || ycoord > 19 || (mode != 'M' && mode != 'F'))
		{
			DisplayGrid(grid, mask);
			printf("\n\n\n");	
			printf("Enter Input (Format: XX YY M) >> ");
			scanf("%i %i %c", &xcoord, &ycoord, &mode);
		}
		
		if (mode == 'M')
		{
			if (grid[xcoord][ycoord] == -1)
			{
				ClearScreen();
				printf("YOU LOSE!!\n");
				return 1;
			}
			else if (grid[xcoord][ycoord] > 0)
			{
				mask[xcoord][ycoord] = 1;
			}
			else 
			{
				RecursiveUnmask(xcoord, ycoord);
			}
		}
	}
}

void RecursiveUnmask(int x, int y)
{
	if (grid[x][y] != 1 && mask[x][y] == 0)
	{
		mask[x][y] = 1;

		if (grid[x][y] != 0) return;

		if (x > 0)
		{	
			RecursiveUnmask(x - 1, y);
		}
		
		if (x < 19)
		{	
			RecursiveUnmask(x + 1, y);
		}	
		
		if (y > 0)
		{
			RecursiveUnmask(x, y - 1);
		}
			
		if (y < 19)
		{
			RecursiveUnmask(x, y + 1);
		}
	}	
}

void ClearScreen(void)
{
	for (int i = 0; i < 50; i++)
	{
		printf("\n");
	}
}

void DisplayGrid(int grid[LENGTH][LENGTH], int mask[LENGTH][LENGTH])
{
	ClearScreen();

	char string[LENGTH + sizeof(char)];
	int count = 0;

	printf("  ");
	for (int i = 0; i < LENGTH; i++)
	{
		if (count >= 10) count = 0;
		printf(" %i ", count);
		count ++;
	}
	printf("\n");
	
	count = 0;
	for (int i = 0; i < LENGTH; i++)
	{	
		if (count >= 10) count = 0;
		printf("%i ", count);
		for (int j = 0; j < LENGTH; j++)
		{	
			if (mask[i][j] == 0) printf("[ ]"); 
			else
			{
				if (grid[i][j] == -1) printf("[█]");
				else if (grid[i][j] == 0) printf("   ");
				else printf("[%i]", grid[i][j]);
			}
		}
		printf("\n");
		count ++;
	}
}
