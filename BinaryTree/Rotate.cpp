#include <stdio.h>
#include <math.h>
#include <windows.h>

#define WIDTH 40       // �ܼ� â �ʺ�
#define HEIGHT 20      // �ܼ� â ����
#define WIDTH_RECT 11  // ���簢�� ���� ����
#define HEIGHT_RECT 5  // ���簢�� ���� ����
#define ANGLE_STEP 10  // ���� ������ (ȸ�� �ӵ�)
#define ROTATION_TIME 3000 // 3�� (3000ms) ���� ȸ��

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// 2D ���� ����
typedef struct {
    float x, y, w;  // x, y ��ǥ�� ���� ��ǥ w
} vec3;

// 3x3 ��� ����
typedef struct {
    float m[3][3];
} Matrix3x3;

// ȸ�� ��� ����
Matrix3x3 createRotationMatrix(float angle) {
    Matrix3x3 mat;
    float radian = angle * M_PI / 180.0;
    mat.m[0][0] = cos(radian);
    mat.m[0][1] = -sin(radian);
    mat.m[0][2] = 0;
    mat.m[1][0] = sin(radian);
    mat.m[1][1] = cos(radian);
    mat.m[1][2] = 0;
    mat.m[2][0] = 0;
    mat.m[2][1] = 0;
    mat.m[2][2] = 1;
    return mat;
}

// ���Ϳ� ����� ����
vec3 Mul(vec3 a, Matrix3x3 b) {
    vec3 result;
    result.x = b.m[0][0] * a.x + b.m[0][1] * a.y + b.m[0][2] * a.w;
    result.y = b.m[1][0] * a.x + b.m[1][1] * a.y + b.m[1][2] * a.w;
    result.w = a.w;
    return result;
}

// ȭ�� ����� �Լ�
void clearScreen() {
    system("cls");
}

// �� �� ���簢���� �ֿܼ� ���
void drawFilledRectangle(float angle) {
    clearScreen();
    char screen[HEIGHT][WIDTH]; // ȭ���� 2D �迭�� ����

    // ȭ�� �ʱ�ȭ
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            screen[y][x] = ' ';
        }
    }

    // �簢���� ��� �ȼ��� ä���
    for (float y = -HEIGHT_RECT; y < HEIGHT_RECT; y += 0.25) {
        for (float x = -WIDTH_RECT; x < WIDTH_RECT; x += 0.25) {
            // ȸ�� ��ȯ�� ����
            vec3 fillVertex = { x, y, 1 };
            vec3 rotatedFillVertex = Mul(fillVertex, createRotationMatrix(angle));

            int fillX = (int)(rotatedFillVertex.x + WIDTH / 2);
            int fillY = (int)(rotatedFillVertex.y + HEIGHT / 2);

            // ȭ�� ���� ������ '*'�� ǥ��
            if (fillX >= 0 && fillX < WIDTH && fillY >= 0 && fillY < HEIGHT) {
                screen[fillY][fillX] = '*';
            }
        }
    }

    // ȭ�� ���
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            printf("%c", screen[y][x]);
        }
        printf("\n");
    }
}

int main() {
    float totalRotation = 0.0f;
    float rotationSpeed = 360.0f / (ROTATION_TIME / 100); // 3�� ���� ȸ���� ����

    while (totalRotation < 360.0f) {
        drawFilledRectangle(totalRotation);   // ���� ������ ȸ���� �� �� ���簢���� �׸�
        totalRotation += rotationSpeed;        // ���� ����
        Sleep(100);                             // 0.1�� ��� (�ִϸ��̼� ȿ��)
    }

    return 0;
}
