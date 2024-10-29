#include <stdio.h>
#include <math.h>
#include <windows.h>

#define WIDTH 40
#define HEIGHT 20
#define PI 3.14159265358979323846

// 3D 벡터 구조체 정의
typedef struct {
    float x, y, w; // x, y 좌표와 동차 좌표 w
} vec3;

// 3x3 행렬 구조체 정의
typedef struct {
    float m[3][3]; // 3x3 행렬
} Matrix3x3;

// 3x3 행렬 초기화
void initIdentityMatrix(Matrix3x3* mat) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (i == j) {
                mat->m[i][j] = 1;
            }
            else {
                mat->m[i][j] = 0;
            }
        }
    }
}

// 이동 행렬 생성
Matrix3x3 createTranslationMatrix(float tx, float ty) {
    Matrix3x3 mat;
    initIdentityMatrix(&mat);
    mat.m[0][2] = tx; // X축 이동
    mat.m[1][2] = ty; // Y축 이동
    return mat;
}

// 회전 행렬 생성
Matrix3x3 createRotationMatrix(float angle) {
    Matrix3x3 mat;
    initIdentityMatrix(&mat);
    float radian = angle * PI / 180;
    mat.m[0][0] = cos(radian); // cos(θ)
    mat.m[0][1] = -sin(radian); // -sin(θ)
    mat.m[1][0] = sin(radian); // sin(θ)
    mat.m[1][1] = cos(radian); // cos(θ)
    return mat;
}

// 벡터와 행렬 곱셈
vec3 Mul(vec3 a, Matrix3x3 b) {
    vec3 result;
    result.x = b.m[0][0] * a.x + b.m[0][1] * a.y + b.m[0][2] * a.w; // x 좌표 계산
    result.y = b.m[1][0] * a.x + b.m[1][1] * a.y + b.m[1][2] * a.w; // y 좌표 계산
    result.w = a.w; // 동차 좌표는 그대로 유지
    return result;
}

// 행렬 곱셈
Matrix3x3 Mul(Matrix3x3 a, Matrix3x3 b) {
    Matrix3x3 result;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            result.m[i][j] = 0; // 결과 행렬 초기화
            for (int k = 0; k < 3; k++) {
                result.m[i][j] += a.m[i][k] * b.m[k][j]; // 행렬 곱셈
            }
        }
    }
    return result;
}

// 콘솔 화면 지우기
void clearScreen() {
    system("cls");
}

// 화면 그리기
void draw(float earthAngle, float moonAngle) {
    clearScreen();

    // P (태양) 위치
    int sunX = WIDTH / 2;
    int sunY = HEIGHT / 2;

    // E (지구) 위치
    vec3 earthPos = { 0.0f, 7.0f, 1.0f }; // 동차 좌표 w를 1로 설정

    // M (달) 위치
    vec3 moonPos = { 0.0f, 2.5f, 1.0f }; // 동차 좌표 w를 1로 설정

    // 지구의 회전 변환
    Matrix3x3 earthRotation = createRotationMatrix(earthAngle);
    earthPos = Mul(earthPos, earthRotation);
    earthPos.x += sunX; // 태양 중심에 위치 조정
    earthPos.y += sunY;

    // 달의 회전 변환 (지구 주위)
    Matrix3x3 moonRotation = createRotationMatrix(moonAngle);
    moonPos = Mul(moonPos, moonRotation);
    moonPos.x += earthPos.x; // 지구 중심에 위치 조정
    moonPos.y += earthPos.y;

    // 화면 그리기 (이전과 동일)
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (x == sunX && y == sunY) {
                printf("O"); // 태양 출력
            }
            else if ((int)earthPos.x == x && (int)earthPos.y == y) {
                printf("E"); // 지구 출력
            }
            else if ((int)moonPos.x == x && (int)moonPos.y == y) {
                printf("M"); // 달 출력
            }
            else {
                printf(" "); // 빈 공간 출력
            }
        }
        printf("\n");
    }
}

int main() {
    float earthAngle = 0.0f;
    float moonAngle = 0.0f;

    while (1) {
        draw(earthAngle, moonAngle); // 지구와 달 그리기
        earthAngle += 4.0f; // 지구 공전 속도
        moonAngle += 10.0f; // 달 공전 속도
        Sleep(50); // 0.05초 대기
    }

    return 0;
}
