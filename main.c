#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define W_SIZE_X 10
#define W_SIZE_Y 10

void world_init(bool world[W_SIZE_X][W_SIZE_Y]);
void world_print(bool world[W_SIZE_X][W_SIZE_Y]);
void world_step(bool world[W_SIZE_X][W_SIZE_Y], bool worldAux[W_SIZE_X][W_SIZE_Y]);
int world_count_neighbors(bool world[W_SIZE_X][W_SIZE_Y], int coordx, int coordy);
bool world_get_cell(bool world[W_SIZE_X][W_SIZE_Y], int coordx, int coordy);
void world_copy(bool wordTarget[W_SIZE_X][W_SIZE_Y], bool worldSource[W_SIZE_X][W_SIZE_Y]);

int main()
{
	int i = 0;
	// TODO: Declara dos mundos

	// TODO: inicializa el mundo
		
	do {
		printf("\033cIteration %d\n", i++);
		// TODO: Imprime el mundo
		// TODO: Itera
	} while (getchar() != 'q');

	return EXIT_SUCCESS;
}

void world_init(bool world[W_SIZE_X][W_SIZE_Y])
{
	int i, j;

	// Poner el mundo a false
	for(i = 0; i < W_SIZE_X; i++) {
		for(j = 0; j < W_SIZE_Y; j++) {
			world[i][j] = false;
		}
	}

	/* Inicializar con el patrón del glider:
	 *           . # .
	 *           . . #
	 *           # # #
	 */
	 
	world[0][1] = true;
	world[1][2] = true;
	world[2][0] = true;
	world[2][1] = true;
	world[2][2] = true;
}

void world_print(bool world[W_SIZE_X][W_SIZE_Y])
{
	// Imprimir el mundo por consola. Sugerencia:
	/*
	 *     . # . . . . . . . .
	 *     . . # . . . . . . .
	 *     # # # . . . . . . .
	 *     . . . . . . . . . .
	 *     . . . . . . . . . .
	 *     . . . . . . . . . .
	 *     . . . . . . . . . .
	 *     . . . . . . . . . .
	 *     . . . . . . . . . .
	 *     . . . . . . . . . .
	 */
	 
	 int i, j;
	 
	 for(i = 0; i < W_SIZE_X; i++) {
		for(j = 0; j < W_SIZE_Y; j++) {
			world[i][j] ? printf("# ") : printf(". ");
		}
		printf("\n");
	 }
}

void world_step(bool world[W_SIZE_X][W_SIZE_Y], bool worldAux[W_SIZE_X][W_SIZE_Y])
{	 
	int i, j;	
	
	//Recorrer el mundo célula por célula
	for (i = 0; i < W_SIZE_X; i++) {
		for (j = 0; j < W_SIZE_Y; j++) {
			//Va copiando el siguiente estado de cada célula en worldAux
			worldAux[i][j] = world_get_cell(world, i, j);
		}
	}
	
	//Copia worldAux en world
	world_copy(world, worldAux);
}

int world_count_neighbors(bool world[W_SIZE_X][W_SIZE_Y], int coordx, int coordy)
{

	int i, j, x, y;
	int counter = 0;
	
	// Recorremos todas las células que rodean las coordenadas i, j
	for (i = coordx-1; i <= coordx+1; i++) {
		for (j = coordy-1; j <= coordy+1; j++) {
		
			x = i;
			y = j;	
			
			if (i < 0) { // El índice se sale por arriba
				x = i + W_SIZE_X;
			} else if (i > 4) { // El índice se sale por abajo
				x = i - W_SIZE_X;
			}
			
			if (j < 0) { // El índice se sale por la izquierda
				y = j + W_SIZE_Y;
			} else if (j > 4) { // El índice se sale por la derecha
				y = j - W_SIZE_Y;
			}
			
			// La célula central no se cuenta. Además solo se cuentan células si están vivas
			if(!(x==coordx && y==coordy) && world[x][y]) {
				printf("-");
				counter++;
			}
		}
	}
	
	return counter;
}

bool world_get_cell(bool world[W_SIZE_X][W_SIZE_Y], int coordx, int coordy)
{

	bool res;
	
	// Devuelve el estado de la célula de posición indicada
	if (!world[coordx][coordy] && world_count_neighbors(world, coordx, coordy) == 3) {
		res = true;
	} else if (world[coordx][coordy] && (world_count_neighbors(world, coordx, coordy) == 2 || world_count_neighbors(world, coordx, coordy) == 3)) {
		res = true;
	} else {
		res = false;
	}
}

void world_copy(bool wordTarget[W_SIZE_X][W_SIZE_Y], bool worldSource[W_SIZE_X][W_SIZE_Y])
{
	int i, j;

	// Copia el mundo segundo mundo sobre el primero
	for (i = 0; i < W_SIZE_X; i++) {
		for (j = 0; j < W_SIZE_Y; j++) {
			wordTarget[i][j] = worldSource[i][j];
		}
	}
}
