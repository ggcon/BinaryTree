#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h> // 윈도우 환경에서 Sleep() 함수 사용

#define WIDTH 40   // 콘솔 창 가로 길이
#define HEIGHT 20  // 콘솔 창 세로 길이
#define CENTER_X (WIDTH / 2)
#define CENTER_Y (HEIGHT / 2)
#define RADIUS 15   // 공전 반지름
#define SPEED 0.1  // 공전 속도

void gotoxy(int x, int y) {
    COORD pos = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void draw() {
    float angle = 0.0;

    while (1) {
        // 콘솔 초기화
        system("cls");

        // 별 중심 그리기
        gotoxy(CENTER_X, CENTER_Y);
        printf("@");

        // 공전 궤도 계산
        int orbitX = CENTER_X + (int)(RADIUS * cos(angle));
        int orbitY = CENTER_Y + (int)(RADIUS * 0.5 * sin(angle)); // 세로 방향 반지름 조정

        // 공전하는 기호 그리기
        gotoxy(orbitX, orbitY);
        printf("--#--\n");

        // 각도 업데이트
        angle += SPEED;

        // 지연 시간
        Sleep(100); // 100 밀리초 대기
    }
}

int main() {
    draw();
    return 0;
}
