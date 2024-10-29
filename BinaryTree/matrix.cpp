#include <stdio.h>

typedef struct {
    float m[3][3]; // 3x3 행렬
} Matrix3x3;

// 두 3x3 행렬을 곱하는 함수
Matrix3x3 multiplyMatrices(Matrix3x3 a, Matrix3x3 b) {
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

// 행렬 출력 함수
void printMatrix(Matrix3x3 mat) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%f ", mat.m[i][j]);
        }
        printf("\n");
    }
}

int main() {
    // 첫 번째 행렬
    Matrix3x3 mat1 = { {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    } };

    // 두 번째 행렬
    Matrix3x3 mat2 = { {
        {9, 8, 7},
        {6, 5, 4},
        {3, 2, 1}
    } };

    // 행렬 곱셈 수행
    Matrix3x3 result = multiplyMatrices(mat1, mat2);

    // 결과 출력
    printf("Result of matrix multiplication:\n");
    printMatrix(result);

    return 0;
}
