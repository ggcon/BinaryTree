#include <stdio.h>

typedef struct {
    float m[3][3]; // 3x3 ���
} Matrix3x3;

// �� 3x3 ����� ���ϴ� �Լ�
Matrix3x3 multiplyMatrices(Matrix3x3 a, Matrix3x3 b) {
    Matrix3x3 result;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            result.m[i][j] = 0; // ��� ��� �ʱ�ȭ
            for (int k = 0; k < 3; k++) {
                result.m[i][j] += a.m[i][k] * b.m[k][j]; // ��� ����
            }
        }
    }
    return result;
}

// ��� ��� �Լ�
void printMatrix(Matrix3x3 mat) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%f ", mat.m[i][j]);
        }
        printf("\n");
    }
}

int main() {
    // ù ��° ���
    Matrix3x3 mat1 = { {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    } };

    // �� ��° ���
    Matrix3x3 mat2 = { {
        {9, 8, 7},
        {6, 5, 4},
        {3, 2, 1}
    } };

    // ��� ���� ����
    Matrix3x3 result = multiplyMatrices(mat1, mat2);

    // ��� ���
    printf("Result of matrix multiplication:\n");
    printMatrix(result);

    return 0;
}
