//2025.05.12 10주차 월요일
//이진 탐색 트리
#include <stdio.h>
#include <stdlib.h>

typedef int Telement;

typedef struct TreeNode
{
    Telement key;
    struct TreeNode* left;
    struct TreeNode* right; 
}TreeNode;

TreeNode* makeNode(Telement key) //여기까진 항상 비슷하대요
{
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->key = key;
    node->left = node->right = NULL; //초기화

    return node;
}


TreeNode* insertNode(TreeNode* root, Telement key) //삽입 연산
{
    if(root == NULL)
        return makeNode(key); //이 동작 원리 이해해라
    if(key < root->key)
        root->left = insertNode(root->left, key); //재귀 추적 순환 호출
    else if(key>root->key)
        root->right = insertNode(root->right, key);
    return root;
}

TreeNode* minValueNode(TreeNode* root) //계승자를 찾는 것임 postsuccessor
{
    TreeNode* p = root;
    while (p->left != NULL)
        p = p->left;
    return p;
}

TreeNode* deleteNode(TreeNode* root, Telement key) //삭제연산
{
    if(root == NULL)
        return NULL;
    if(key<root->key)
        root->left = deleteNode(root->left, key);
    else if(key>root->key)
        root->right = deleteNode(root->right, key);
    else
    {
        if(root->left == NULL) // case1 오른쪽 자식만 있음
        {
            TreeNode* temp = root->right;
            free(root);
            return temp;
        }
        else if(root->right == NULL) //case2 왼쪽 자식만 있음
        {
            TreeNode* temp = root->left;
            free(root);
            return temp;
        }
        else //case3 자식 노드가 양쪽 다 있을 때. 지우는게 아니라 단말노드랑 위치 교환한 후 단말에서 지워버림(계승자를 찾으러 감)
        //이진 탐색 트리에서 "가장 가까운 애" = "큰 애 중에 제일 작은 애" = 오른쪽 서브트리인데 그 중에 가장 왼쪽 하단 노드
        //그렇게 계승자를 찾고서 말단에 보낸 다음에 삭제시킨다.
        {
            TreeNode* temp = minValueNode(root->right);
            root->key = temp->key; //노드 'root'키를 'temp'키로 바꾸고
            root->right = deleteNode(root->right, temp->key); //계승자 노드 삭제
        }
    }
    return root;
}

void preOrder(TreeNode* root)
{
    if(root != NULL)
    {
        printf("[%2d]", root->key);
        preOrder(root->left);
        preOrder(root->right);
    }
}

//삭제연산 시뮬레이션할 때 도움된다 pdf 노드 똑같게 만들 것 35,18,7,...

int main()
{
    TreeNode* root = NULL;
    Telement keys[] = {35, 18, 7, 26, 12, 3, 68, 22, 30, 99}; //중복값 넣어도 안들어감
    for(int i = 0; i<10; i++)
    {
        root = insertNode(root, keys[i]); // 뭔가 여기서 설명 길게
        preOrder(root);
        printf("\n");
    }
    printf("\n");
    //deleteNode(root, 30); preOrder(root); printf("\n");
    //deleteNode(root, 26); preOrder(root); printf("\n"); //26없어지면 22가 18에 붙으러 가야함
    deleteNode(root,18); preOrder(root); printf("\n"); //case3
}