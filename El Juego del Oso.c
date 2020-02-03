#include <stdio.h>
#include <stdlib.h>
#include "myconio.h"
#include <time.h>
#define M 20
#define DERECHA 77
#define IZQUIERDA 75
#define ARRIBA 72
#define ABAJO 80
typedef struct{
	char nombre[20];
	int rondas_ganadas;
	int palabras_formadas;
	int puntaje;
}jugador;

typedef struct{
	int letra;
	int color;
}mapa;

typedef struct{
	jugador n[2];
	mapa m[M][M];
}tablero;

void obtener_datos(jugador *P);
void imprimir(tablero j, int filas, int columnas, int turno);
void jugar(tablero j, int filas, int columnas, int turno);
int verificar_ganar(tablero j, int filas, int columnas);

int main(int argc, char *argv[]) {
	int x, y, filas, columnas, turno;
	int dado[2];
	tablero j;
	srand(time(0));
	for(x=0;x<M;x++){
		for(y=0;y<M;y++){
			j.m[x][y].letra = 0;
			j.m[x][y].color = 0;
		}
	}
	printf("\t\tEL JUEGO DEL OSO\n\n");
	printf("-Reglas:\n1.Formar mas veces la palabra OSO que tu oponente.\n2.Si formas la palabra OSO repites turno\n3.Se puede formar la palabra OSO de forma horizontal, vertical y diagonal\n4.El juego termina cuando un jugador gana 3 rondas");
	printf("\nIntroduce el tamaño de tu mapa de juego(MIMINO 8*8 | MAXIMO 20*20)\n");	

	do{
		scanf("%d %d",&filas, &columnas);
	}while(filas < 8 || columnas < 8 || filas > M || columnas > M);
	
	for(x=0;x<2;x++){
		obtener_datos(&j.n[x]);
	}
	do{
		for(x=0;x<2;x++){
			dado[x] = rand() % 6 + 1;
		}
	}while(dado[0] == dado[1]);
	system("cls");
	for(x=0;x<2;x++){
		printf("\n\t\tNombre jugador %d: ", x+1);
		puts(j.n[x].nombre);
		printf("\t\tDado: %d", dado[x]);	
	}
	if(dado[0] > dado[1]){
		turno = 0;
	}else{
		turno = 1;
	}
	system("pause>arch");
	system("cls");
	if(dado[0] > dado [1]){
		printf("\n\t\tPrimer turno ");
		textcolor(LIGHT_GREEN);	
		puts(j.n[0].nombre);
		textcolor(WHITE);
		printf("\t\tSegundo turno ");
		textcolor(LIGHT_BLUE);
		puts(j.n[1].nombre);
	}else{
		printf("\n\t\tPrimer turno ");
		textcolor(LIGHT_BLUE);
		puts(j.n[1].nombre);
		textcolor(WHITE);
		printf("\t\tSegundo turno ");
		textcolor(LIGHT_GREEN);	
		puts(j.n[0].nombre);
	}
	system("pause>arch");
	while(1){
		jugar(j, filas, columnas, turno);
	}
	
	return 0;
}

void obtener_datos(jugador *P){
	printf("Nombre del Jugador: ");
	fflush(stdin);
	gets(P->nombre);
	P->puntaje = 0;
	P->palabras_formadas = 0;
	P->rondas_ganadas = 0;
}

void imprimir(tablero j, int filas, int columnas, int turno){
	int x, y;
	system("cls");
	gotoxy(0,0);
	for(x=0;x<filas;x++){
		for(y=0;y<columnas;y++){
			if(j.m[x][y].letra == 0){
				textcolor(LIGHT_WHITE);
				printf(" _ ", j.m[x][y]);
			}
			if(j.m[x][y].letra == 5 && turno == 0){
				textcolor(LIGHT_GREEN);
				printf(" _ ", j.m[x][y]);
			}
			if(j.m[x][y].letra == 5 && turno == 1){
				textcolor(LIGHT_BLUE);
				printf(" _ ", j.m[x][y]);
			}
			if(j.m[x][y].letra == 79 && j.m[x][y].color == 0){
				textcolor(LIGHT_RED);
				printf(" %c ", j.m[x][y]);
			}
			if(j.m[x][y].letra == 83 && j.m[x][y].color == 0){
				textcolor(LIGHT_RED);
				printf(" %c ", j.m[x][y]);
			}
			if(j.m[x][y].letra == 79 && j.m[x][y].color == 1){
				textcolor(LIGHT_GREEN);
				printf(" %c ", j.m[x][y]);
			}
			if(j.m[x][y].letra == 83 && j.m[x][y].color == 1){
				textcolor(LIGHT_GREEN);
				printf(" %c ", j.m[x][y]);
			}
			if(j.m[x][y].letra == 79 && j.m[x][y].color == 2){
				textcolor(LIGHT_BLUE);
				printf(" %c ", j.m[x][y]);
			}
			if(j.m[x][y].letra == 83 && j.m[x][y].color == 2){
				textcolor(LIGHT_BLUE);
				printf(" %c ", j.m[x][y]);
			}
		}
		printf("\n");
	}
	if(turno == 0){
		x = columnas*3+3;
		gotoxy(x,2);
		textcolor(WHITE);
		printf("Turno de ");
		textcolor(LIGHT_GREEN);
		puts(j.n[0].nombre);
		gotoxy(x,3);
		textcolor(WHITE);
		printf("Puntaje %d", j.n[0].puntaje);
	}
	if(turno == 1){
		x = columnas*3+3;
		gotoxy(x,2);
		textcolor(WHITE);
		printf("Turno de ");
		textcolor(LIGHT_BLUE);
		puts(j.n[1].nombre);
		textcolor(WHITE);
		gotoxy(x,3);
		printf("Puntaje %d", j.n[1].puntaje);
	}
}

void jugar(tablero j, int filas, int columnas, int turno){
int f = 0, c = 0, faux = 0, caux = 0, vaux = 0, band, x, y, cont, i, aux, rondas_empatadas;
char tecla = 0;
		cont = 0;
		j.m[f][c].letra = 5;
		imprimir(j,filas,columnas,turno);
		rondas_empatadas = 0;
		while(tecla != 100){
			tecla = 0;	
			j.m[f][c].letra = vaux;
			band = 0;
			fflush(stdin);
			tecla=getch();
			tecla=toupper(tecla);
			
		if(tecla == ARRIBA){
			if((f-1) >= 0){
				f--;
			}
		}
		if(tecla == ABAJO){
			if((f+1) < filas){
				f++;
			}
		}
		if(tecla == DERECHA){
			if((c+1) < columnas){
				c++;
			}
		}
		if(tecla == IZQUIERDA){
			if((c-1) >= 0){
				c--;
			}
		}
		aux = turno + 1;
		if(tecla == 'S'){
			if(j.m[f][c].letra == 0){
				j.m[f][c].letra = 83;
				if(j.m[f-1][c].letra == 79 && j.m[f+1][c].letra == 79){
					j.m[f][c].color = aux;
					j.m[f-1][c].color = aux;
					j.m[f+1][c].color = aux;
					j.n[turno].palabras_formadas++;
					j.n[turno].puntaje++;
					band = 1;
				}
				if(j.m[f][c-1].letra == 79 && j.m[f][c+1].letra == 79){
					j.m[f][c].color = aux;
					j.m[f][c-1].color = aux;
					j.m[f][c+1].color = aux;
					j.n[turno].palabras_formadas++;
					j.n[turno].puntaje++;
					band = 1;
				}
				if(j.m[f-1][c-1].letra == 79 && j.m[f+1][c+1].letra == 79){
					j.m[f][c].color = aux;
					j.m[f-1][c-1].color = aux;
					j.m[f+1][c+1].color = aux;
					j.n[turno].palabras_formadas++;
					j.n[turno].puntaje++;
					band = 1;
				}
				if(j.m[f-1][c+1].letra == 79 && j.m[f+1][c-1].letra == 79){
					j.m[f][c].color = aux;
					j.m[f-1][c+1].color = aux;
					j.m[f+1][c-1].color = aux;
					j.n[turno].palabras_formadas++;
					j.n[turno].puntaje++;
					band = 1;
				}
				if(band == 1){
					turno = turno;
				}else if(band == 0 && turno == 0){
					turno = 1;
				}else if(band == 0 && turno == 1){
					turno = 0;
				}
			}
			
		}				
		if(tecla == 'O'){
			if(j.m[f][c].letra == 0){
				j.m[f][c].letra = 79;
				if(j.m[f-1][c].letra == 83 && j.m[f-2][c].letra == 79){
					j.m[f][c].color = aux;
					j.m[f-1][c].color = aux;
					j.m[f-2][c].color = aux;
					j.n[turno].palabras_formadas++;
					j.n[turno].puntaje++;
					band = 1;
				}
				if(j.m[f+1][c].letra == 83 && j.m[f+2][c].letra == 79){
					j.m[f][c].color = aux;
					j.m[f+1][c].color = aux;
					j.m[f+2][c].color = aux;
					j.n[turno].palabras_formadas++;
					j.n[turno].puntaje++;
					band = 1;
				}
				if(j.m[f][c-1].letra == 83 && j.m[f][c-2].letra == 79){
					j.m[f][c].color = aux;
					j.m[f][c-1].color = aux;
					j.m[f][c-2].color = aux;
					j.n[turno].palabras_formadas++;
					j.n[turno].puntaje++;
					band = 1;
				}
				if(j.m[f][c+1].letra == 83 && j.m[f][c+2].letra == 79){
					j.m[f][c].color = aux;
					j.m[f][c+1].color = aux;
					j.m[f][c+2].color = aux;
					j.n[turno].palabras_formadas++;
					j.n[turno].puntaje++;
					band = 1;
				}
				if(j.m[f-1][c-1].letra == 83 && j.m[f-2][c-2].letra == 79){
					j.m[f][c].color = aux;
					j.m[f-1][c-1].color = aux;
					j.m[f-2][c-2].color = aux;
					j.n[turno].palabras_formadas++;
					j.n[turno].puntaje++;
					band = 1;
				}
				if(j.m[f-1][c+1].letra == 83 && j.m[f-2][c+2].letra == 79){
					j.m[f][c].color = aux;
					j.m[f-1][c+1].color = aux;
					j.m[f-2][c+2].color = aux;
					j.n[turno].palabras_formadas++;
					j.n[turno].puntaje++;
					band = 1;
				}
				if(j.m[f+1][c-1].letra == 83 && j.m[f+2][c-2].letra == 79){
					j.m[f][c].color = aux;
					j.m[f+1][c-1].color = aux;
					j.m[f+2][c-2].color = aux;
					j.n[turno].palabras_formadas++;
					j.n[turno].puntaje++;
					band = 1;
				}
				if(j.m[f+1][c+1].letra == 83 && j.m[f+2][c+2].letra == 79){
					j.m[f][c].color = aux;
					j.m[f+1][c+1].color = aux;
					j.m[f+2][c+2].color = aux;
					j.n[turno].palabras_formadas++;
					j.n[turno].puntaje++;
					band = 1;
				}
				if(band == 1){
					turno = turno;
				}else if(band == 0 && turno == 0){
					turno = 1;
				}else if(band == 0 && turno == 1){
					turno = 0;
				}
			}
		}
			vaux = j.m[f][c].letra;
			j.m[f][c].letra = 5;
			imprimir(j,filas,columnas,turno);
			
			for(x=0;x<filas;x++){
				for(y=0;y<columnas;y++){
					if(j.m[x][y].letra == 79){
						cont++;
					}
					if(j.m[x][y].letra == 83){
						cont++;
					}
				}
			}
			if(vaux == 79 || vaux == 83){
				cont++;
			}
			if(cont == filas*columnas){
				system("cls");
				vaux = 0;
				cont = 0;
				if(j.n[0].puntaje > j.n[1].puntaje){
					i = 0;
					j.n[0].rondas_ganadas++;
					j.n[0].puntaje = 0;
					j.n[1].puntaje = 0;
				}else if(j.n[0].puntaje < j.n[1].puntaje){
					i = 1;
					j.n[1].rondas_ganadas++;
					j.n[0].puntaje = 0;
					j.n[1].puntaje = 0;
				}else if(j.n[0].puntaje == j.n[1].puntaje){
					i = 2;
					rondas_empatadas++;
					j.n[0].puntaje = 0;
					j.n[1].puntaje = 0;
				}
				if(i == 0){
					gotoxy(3,3);
					textcolor(WHITE);
					printf("GANADOR DE LA RONDA %d:", j.n[0].rondas_ganadas + j.n[1].rondas_ganadas + rondas_empatadas);
					gotoxy(3,5);
					textcolor(LIGHT_GREEN);
					puts(j.n[i].nombre);
				}else if(i == 1){
					gotoxy(3,3);
					textcolor(WHITE);
					printf("GANADOR DE LA RONDA %d:", j.n[0].rondas_ganadas + j.n[1].rondas_ganadas + rondas_empatadas);
					gotoxy(3,5);
					textcolor(LIGHT_BLUE);
					puts(j.n[i].nombre);
				}else if(i == 2){
					gotoxy(3,3);
					textcolor(WHITE);
					printf("EMPATE");
				}
				system("pause>arch");
					for(x=0;x<filas;x++){
						for(y=0;y<columnas;y++){
							j.m[x][y].letra = 0;
							j.m[x][y].color = 0;		
						}
					}
				if(j.n[0].rondas_ganadas + j.n[1].rondas_ganadas == 3){
					system("cls");
					gotoxy(2,3);
					textcolor(LIGHT_GREEN);
					puts(j.n[0].nombre);
					textcolor(WHITE);
					gotoxy(2,4);
					printf("Rondas ganadas: %d", j.n[0].rondas_ganadas);
					gotoxy(2,5);
					printf("Veces formada OSO: %d", j.n[0].palabras_formadas);
					gotoxy(25,3);
					textcolor(LIGHT_BLUE);
					puts(j.n[1].nombre);
					textcolor(WHITE);
					gotoxy(25,4);
					printf("Rondas ganadas: %d", j.n[1].rondas_ganadas);
					gotoxy(25,5);
					printf("Veces formada OSO: %d", j.n[1].palabras_formadas);
					gotoxy(5,8);
					if(j.n[0].rondas_ganadas > j.n[1].rondas_ganadas){
						printf("GANADOR DEL JUEGO: ");
						textcolor(LIGHT_GREEN);
						puts(j.n[0].nombre);
					}else{
						printf("GANADOR DEL JUEGO: ");
						textcolor(LIGHT_BLUE);
						puts(j.n[1].nombre);
					}
					system("pause>arch");
					exit(1);
				}
				}else{
				cont = 0;
				}
		}
}

