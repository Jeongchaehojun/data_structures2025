//2025.05.12 10주차 월요일
//힙 트리
#include <stdio.h>
#include <stdlib.h>
#define N 20


typedef int element;
typedef struct 
{
    element heap[N];
    int heapSize;
}HeapType;

void init(HeapType* H)
{
    H->heapSize = 0;
}

void upHeap(HeapType* H) //힙 삽입 연산 
{
    int i = H->heapSize; //등산해야하는 i = 11
    element key = H->heap[i]; //key = 8

    while((i != 1) && (key > H->heap[i/2]))//i == 1 이면 root node... 즉 이 조건은 부모가 있고, 내 키 값이 부모보다 크다
    {
        H->heap[i] = H->heap[i/2];
        i /= 2;
    }
    H->heap[i] = key; // key값을 최종 위치에 삽입 갈기기
}

void downHeap(HeapType* H)
{
    element key = H->heap[1];
    int parent = 1, child = 2; //왼쪽 자식 노드까지
    while(child <= H->heapSize)
    {
        if((child < H->heapSize) && (H->heap[child+1] > H->heap[child])) //잘 햇갈리는 부분 주의 1. 자식노드가 힙사이즈보다 작다?: "오른쪽 자식노드가 있다면"
            child++;

        if(key >= H->heap[child])
            break;
        H->heap[parent] = H->heap[child];
        parent = child;
        child *= 2;
    }
    H->heap[parent] = key;
}

void insertItem(HeapType* H, element key)
{
    H->heapSize++;
    H->heap[H->heapSize] = key;
    upHeap(H);
}

element deleteItem(HeapType* H)
{
    element key = H->heap[1];
    H->heap[1] = H->heap[H->heapSize];
    H->heapSize--;
    downHeap(H);

    return key;
}

void heapSort(HeapType* H) //힙정렬
{
    int n = H->heapSize;
    int A[n];

    for(int i = n-1; i>=0; i--)
        A[i] = deleteItem(H);
    
    for(int i = 0; i < n; i++)
        printf("[%d]", A[i]);

}

void printHeap(HeapType* H)
{
    for(int i = 1; i<= H->heapSize; i++)
        printf("[%d]", H->heap[i]);
    printf("\n");

}

int main()
{
    HeapType H;
    init(&H);
    insertItem(&H, 9); insertItem(&H, 7); insertItem(&H, 6);
    insertItem(&H, 5); insertItem(&H, 4); insertItem(&H, 3);
    insertItem(&H, 2); insertItem(&H, 2); insertItem(&H, 1);
    
    //insertItem(&H, 3); printHeap(&H);
    printf("Delete [%d]: ", deleteItem(&H)); printHeap(&H); 
    heapSort(&H);
}

