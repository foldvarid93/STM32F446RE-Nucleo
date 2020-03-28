#include "GameFunctions.h"
#include "S6D04D1.h"
#define N 24
#define M 40

extern int16_t Field[N][M];//N=y,M=x
extern int16_t x,y;
extern uint8_t Dir,Length, Game, FoodColor;
extern const uint32_t Colors[6];

/*******************************************/
void Random(void) {
	FoodPossibility FoodPossibilities[N*M];
	uint16_t FoodPossibilityCount=0;
	for (uint8_t i = 0; i < N; i++) {
		for (uint8_t j = 0; j < M; j++) {
			if (Field[i][j] == 0) {
				FoodPossibilities[FoodPossibilityCount].x=j;
				FoodPossibilities[FoodPossibilityCount].y=i;
				FoodPossibilityCount++;
			}
		}
	}
	//gyro_t GyroData=DRV_Gyro_GetXYZ();
    //uint16_t random1 =abs(((int16_t) GyroData.omega_y)%FoodPossibilityCount);
    //uint16_t random2 =abs(((int16_t) GyroData.omega_x)%FoodPossibilityCount);
    //uint16_t random=(random1+random2)/2;
    //FoodColor=abs(((int) GyroData.omega_z)%6);
    //Field[FoodPossibilities[random].y][FoodPossibilities[random].x] = -1;
}
/*******************************************/
void SnakeInitialization(void) {
	for (uint8_t i = 0; i < N; i++) {
		for (uint8_t j = 0; j < M; j++) {
			Field[i][j] = 0;
		}
	}
	x = 16;
	y = 2;
	Length = 3;
	Dir = 0;
	Game = 1;
	for (uint8_t i = 0; i < Length; i++) {
		Field[x][i] = i+1;
	}
	Random();
}
/*******************************************/
void Print(void) {
	LcdClear(0x0000);//DRV_Display_Clear();
	for(uint8_t i=0;i<N;i++){//sor
		for(uint8_t j=0;j<M;j++){//oszlop
			if(Field[i][j]!=0){//ha nem nulla
				for(uint16_t k=(j*10);k<(j+1)*10;k++){//x=oszlop*20->x=(oszlop+1)*20
					for(uint16_t l=(i*10);l<(i+1)*10;l++){//y=sor*20->y=(sor+1)*20
						if(Field[i][j]==-1){
							DrawPixel(k,l,0xF800);//DRV_Display_DrawPixel(k, l, Colors[FoodColor]);
						}
						else DrawPixel(k,l,0xFFFF);//DRV_Display_DrawPixel(k, l, 0xFFFFFFFF);//x,y,szín
					}
				}
			}
		}
	}
}
/*******************************************/
void SnakeGame(void) {
	if (Dir==0) {
		y++;
		if (y == M){
			y = 0;
		}
	}
	if (Dir==1) {
		x--;
		if (x == -1){
			x = N - 1;
		}
	}
	if (Dir==2) {
		y--;
		if (y == -1){
			y = M - 1;
		}
	}
	if (Dir==3) {
		x++;
		if (x == N){
			x = 0;
		}
	}
	if (Field[x][y] != 0 && Field[x][y] != -1)
		Game=0;
	else if (Field[x][y] == -1){
		Length++;
		Field[x][y]=Length;
		Random();
	}
	else{
		for (uint8_t i = 0; i < N; i++) {
			for (uint8_t j = 0; j < M; j++) {
				if (Field[i][j] != 0 && Field[i][j] != -1) {
					Field[i][j]-- ;
				}
			}
		}
		Field[x][y]=Length;
	}
	Print();
}
/*******************************************/
