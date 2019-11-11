#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void show(char **map, int size){
	for (int i = 0; i < size; ++i){
		printf("  %c", i+65);
	}
	printf("\n");
	for (int i = 0; i < size; ++i){
		printf("%c", i+65);
		for (int j = 0; j < size; ++j){
			printf(" %c ", map[i][j]);
		}
		printf("\n");
	}
}

void create(char **map, int size){

	srand((unsigned) time(NULL));

	char ship[5][2] = {{5,1},{4,2},{3,3},{2,4},{1,5}};

	for (int i = 0; i < 5; ++i){
		for (int j = 0; j < ship[i][1]; ++j){
			int x;
			int y;
			int freeH;
			int freeV;

			do{
				x = rand() % size;
				y = rand() % size;

				int s = rand() % 2; 

				freeH = 0;
				freeV = 0;

				if(y <= size - ship[i][0] && s){

					freeV = 1;
					for (int k = 0; k < ship[i][0]; k++){
						if(map[y+k][x] != '~'){
							freeV = 0;
						}
					}

					if(freeV){
						for (int k = 0; k < ship[i][0]; k++){
							map[y+k][x] = ship[i][0]+48;
						}
					}
				}

				if(x <= size - ship[i][0] && !s){

					freeH = 1;
					for (int k = 0; k < ship[i][0]; k++){
						if(map[y][x+k] != '~'){
							freeH = 0;
						}
					}

					if(freeH){
						for (int k = 0; k < ship[i][0]; k++){
							map[y][x+k] = ship[i][0]+48;
						}
					}

				}

			}while(!freeV && !freeH);
			
		}
	}
}

char** inimap(int size, char c){
	char **mask = (char**)malloc((sizeof(char*)*size)+1);

	for (int i = 0; i < size; ++i){
		mask[i] = (char *)malloc((sizeof(char)*size)+1);
		
		for (int j = 0; j < size; ++j){
			mask[i][j] = c;
		}

		mask[i][size] = '\0';
	}

	mask[size] = '\0';

	return mask;
}

void info(int lifes, int shots){
	printf("LIFES: %i\n", lifes);
	printf("SHOTS: %i\n\n", shots);
}

int main(){

	printf("=========================================================\n");
	printf("=                                                       =\n");
	printf("=                      BATTLESHIP                       =\n");
	printf("=                                                       =\n");
	printf("=========================================================\n\n");

	int size     = 15;
	int lifes    = 20;
	int shots    = 0;
	int gameover = 0;
	
	char **map  = inimap(size, '~');
	char **mask = inimap(size, '.');

	create(map, size);
	info(lifes, shots);
	show(mask, size);

	while(!gameover){

		char *pos = malloc(3);

		printf("\nENTER THE COORDINATES: ");
		scanf("%s", pos);

		shots++;
		mask[pos[0]-65][pos[1]-65] = map[pos[0]-65][pos[1]-65];

		if(map[pos[0]-65][pos[1]-65] == '~'){
			lifes--;
		}

		system("clear");
		info(lifes, shots);
		show(mask, size);

		if(lifes == 0){

			gameover = 1;
			printf("\nGAME OVER!!!\n"); 
		}else if(shots == 30){

			gameover = 1;
			printf("\nYOU WINS!!!\n");
		}
	}

	free(mask);
	free(map);

	return 0;
}