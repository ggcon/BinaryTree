#include <stdio.h>
#include <stdlib.h>

// Node 구조체 정의
struct Node
{
    struct Node* UpNode;   // 부모 노드 포인터
    struct Node* DownNode; // 자식 노드 포인터
    int myNum;             // 노드 값
};

// 전역 변수
struct Node* root;

// 트리 설정 함수
int SetTree() {
    root = (struct Node*)malloc(sizeof(struct Node)); // 루트 노드 메모리 할당
    root->myNum = 2047; // 루트 노드 값 설정

    struct Node* childl = (struct Node*)malloc(sizeof(struct Node)); // 왼쪽 자식 노드
    struct Node* childr = (struct Node*)malloc(sizeof(struct Node)); // 오른쪽 자식 노드

    childl->myNum = 1023; // 왼쪽 자식 값 설정
    childr->myNum = 1024 + 2047; // 오른쪽 자식 값 설정

    // 자식 노드의 자식 및 부모 노드 포인터 초기화
    childl->DownNode = 0;
    childl->UpNode = 0;
    childr->DownNode = 0;
    childr->UpNode = 0;

    // 루트 노드와 자식 노드 연결
    root->DownNode = childl;
    root->UpNode = childr;

    return 0; // 성공적으로 트리 설정
}

// 트리 노드 출력 함수
void PrintTree(struct Node* node) {
    if (node != NULL) {
        printf("Node Value: %d\n", node->myNum); // 노드 값 출력
        PrintTree(node->DownNode); // 왼쪽 자식 노드 출력
        PrintTree(node->UpNode); // 오른쪽 자식 노드 출력
    }
}

// 메인 함수
int main() {
    SetTree(); // 트리 설정
    PrintTree(root); // 트리 출력
    return 0; // 프로그램 종료
}
