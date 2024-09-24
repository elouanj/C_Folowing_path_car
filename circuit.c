#include <stdio.h>
#include <stdlib.h>

#define column 99
//other: 49     map2 : 99
#define line 29
//other : 16    map2 : 29
#define stroke 8
int map[column][line];
int distanceMap[column][line];

typedef struct _car{
  int x;
  int y;
  int Vx;
  int Vy;
} _car;
struct _car car;

typedef struct _arrival{
  int x;
  int y;
} _arrival;
struct _arrival arrival;

int main(void){
    int moves = 0;
    car.Vx = 0;
    car.Vy = 0;
    initialize();
    printf("start : %d %d \n", car.x, car.y);
    printf("arrival : %d %d \n", arrival.x, arrival.y);
    display();
    printf("distance : %d Vx = %d, Vy = %d (%d,%d) \n\n", distanceMap[car.x][car.y], car.Vx, car.Vy, car.x, car.y);
    move(moves);
}

int stop(struct _car strokeCar){
    while(strokeCar.Vx != 0 && strokeCar.Vy != 0){
        if(strokeCar.Vx > 0){
            strokeCar.Vx--;
        }
        else if(strokeCar.Vx < 0){
            strokeCar.Vx++;
        }
        if(strokeCar.Vy > 0){
            strokeCar.Vy--;
        }
        else if(strokeCar.Vy < 0){
            strokeCar.Vy++;
        }
        strokeCar.x+=strokeCar.Vx;
        strokeCar.y+=strokeCar.Vy;
        if(map[strokeCar.x][strokeCar.y] == '-' || strokeCar.x < 0 || strokeCar.y < 0 || strokeCar.x > column || strokeCar.y > line){
            return 0;
        }
    }
    return 1;
}


void calcul(int strokeToDo, struct _car strokeCar, int *bestVx, int *bestVy, int *bestDistance, int firstStrokeVx, int firstStrokeVy, int *numberStroke){
    for(int i=-1; i<=1; i++){
        strokeCar.Vx+=i;
        for(int j=-1; j<=1; j++){
            strokeCar.Vy+=j;
            strokeCar.x+=strokeCar.Vx;
            strokeCar.y+=strokeCar.Vy;
            if(strokeToDo == stroke - 1){
                firstStrokeVx = strokeCar.Vx;
                firstStrokeVy = strokeCar.Vy;
            }
            //printf("%d %d %d\n", *bestVx, *bestVy, *bestDistance);
            //printf("%d %d\n", firstStrokeVx, firstStrokeVy);   (distanceMap[strokeCar.x][strokeCar.y] == 0 && strokeToDo > *numberStroke) || (      // && (firstStrokeVx != 0 || firstStrokeVy != 0)){
            if(map[strokeCar.x][strokeCar.y] != '-' && strokeCar.x >= 0 && strokeCar.y >= 0 && strokeCar.x < column && strokeCar.y < line){
                if((distanceMap[strokeCar.x][strokeCar.y] == 0 && strokeToDo > *numberStroke) || (distanceMap[strokeCar.x][strokeCar.y] == *bestDistance && strokeToDo > *numberStroke)){
                    //if(stop(strokeCar)){
                        *numberStroke = strokeToDo;
                        *bestDistance = distanceMap[strokeCar.x][strokeCar.y];
                        *bestVx = firstStrokeVx;
                        *bestVy = firstStrokeVy;
                        //printf("best %d %d %d\n", *bestVx, *bestVy, *bestDistance);
                        //printf("%d %d\n", firstStrokeVx, firstStrokeVy);
                    //}
                }
                else if(strokeToDo == 0){
                    if(distanceMap[strokeCar.x][strokeCar.y] < *bestDistance){
                        //if(stop(strokeCar)){
                            *numberStroke = strokeToDo;
                            *bestDistance = distanceMap[strokeCar.x][strokeCar.y];
                            *bestVx = firstStrokeVx;
                            *bestVy = firstStrokeVy;
                            //printf("default %d %d %d\n", *bestVx, *bestVy, *bestDistance);
                            //printf("%d %d\n", firstStrokeVx, firstStrokeVy);
                        //}
                    }
                }
                else{
                    calcul(strokeToDo-1, strokeCar, bestVx, bestVy, bestDistance, firstStrokeVx, firstStrokeVy, numberStroke);
                }
            }

            strokeCar.x-=strokeCar.Vx;
            strokeCar.y-=strokeCar.Vy;
            strokeCar.Vy-=j;
        }
           strokeCar.Vx-=i;
    }
}

void move(int moves){
    int strokeToDo = stroke;
    int numberStroke = 0;
    struct _car strokeCar = car;
    int bestVx = car.Vx, bestVy = car.Vy, bestDistance = distanceMap[car.x][car.y];
    int firstStrokeVx, firstStrokeVy;
    calcul(strokeToDo-1, strokeCar, &bestVx, &bestVy, &bestDistance, firstStrokeVx, firstStrokeVy, &numberStroke);
    printf("Choice : %d %d %d\n", bestVx, bestVy, bestDistance);
    car.Vx = bestVx;
    car.Vy = bestVy;
    car.x+=car.Vx;
    car.y+=car.Vy;
    moves++;
    printf("Move number : %d \n", moves);
    display();
    printf("distance : %d Vx = %d, Vy = %d (%d,%d) \n\n", distanceMap[car.x][car.y], car.Vx, car.Vy, car.x, car.y);

    if(map[car.x][car.y] == '-' || car.x < 0 || car.y < 0 || car.x > column || car.y > line){
        printf("YOU CRASH :(");
    }
    else if (distanceMap[car.x][car.y] != 0){
        move(moves);
    }
    else{
       printf("YOU WON IN %d MOVES !!!", moves);
    }
}

void initialize(){
    FILE* fichier;
    int ch;
    int px = 0, py = 0;
    fichier = fopen("map3.txt", "r");

    while((ch=fgetc(fichier))!=EOF){
        if(ch == '\n'){
            py++;
            px=0;
        }
        else{
            if(ch == 'S'){
                car.x = px;
                car.y = py;
            }
            else if(ch == 'X'){
                arrival.x = px;
                arrival.y = py;
            }
            map[px][py] = ch;
            px++;
        }

    }

    fclose(fichier);

    for(int j=0; j<line; j++){
        for(int i=0; i<column; i++){
            if(map[i][j] == '0' || map[i][j] == 'S'){
                distanceMap[i][j] = 1;
            }
            else if(map[i][j] == 'X'){
                distanceMap[i][j] = 0;
            }
            else{
                distanceMap[i][j] = -1;
            }

        }
    }

    int number = 2;
    int boolean = 1;
    int ok = 0;
    int pointX = arrival.x, pointY = arrival.y;
    while(boolean){
        boolean = 0;
        for(int pointY=0; pointY<line; pointY++){
            for(int pointX=0; pointX<column; pointX++){
                if(distanceMap[pointX][pointY] == number - 1){
                    ok = 0;
                    for(int j=-1; j<=1; j++){
                        for(int i=-1; i<=1; i++){
                            if(distanceMap[pointX+i][pointY+j] == number - 2){
                                ok = 1;
                            }
                        }
                    }
                    if(ok == 0){
                        distanceMap[pointX][pointY] = number;
                        boolean = 1;
                    }
                }
            }
        }
        number++;
    }
}


void display(){
    for(int j=0; j<line; j++){
        for(int i=0; i<column; i++){
            if(i == car.x && j == car.y){
                printf("+");
            }
            else{
                printf("%c", map[i][j]);
            }
            /*if(distanceMap[i][j] == -1){
                printf("   ");
            }
            else if(distanceMap[i][j] < 10){
                printf("%d  ", distanceMap[i][j]);
            }
            else{
                printf("%d ", distanceMap[i][j]);
            }*/
        }
        printf("\n");
    }
}
