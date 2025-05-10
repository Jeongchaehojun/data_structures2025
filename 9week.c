#include <stdio.h>
#include <stdlib.h>

typedef char Telement;

typedef struct TreeNode
{
    Telement data;
    struct TreeNode* left; //왼쪽 자식 노드
    struct TreeNode* right; //오른쪽 자식 노드
}TreeNode;

TreeNode* makeNode(Telement data, TreeNode* left, TreeNode* right)
{
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->data = data;
    node->left = left;
    node->right = right;

    return node;
} //일반 이진트리는 이렇게 만들어야 함

void preOrder(TreeNode* root) //전위 순회 구조
{
    if(root != NULL)
    {
        printf("[%c]", root -> data);
        preOrder(root->left);
        preOrder(root->right);
    }
}

void inOrder(TreeNode* root)
{
    if(root != NULL)
    {
        inOrder(root->left);
        printf("[%c]", root->data);
        inOrder(root->right);
    }
}

void postOrder(TreeNode* root)
{
    if(root != NULL)
    {
        postOrder(root->left);
        postOrder(root->right);
        printf("[%c]", root->data);
    }
}

int main()
{
    TreeNode* N4 = makeNode('D', NULL, NULL);
    TreeNode* N5 = makeNode('E', NULL, NULL);
    TreeNode* N6 = makeNode('F', NULL, NULL);
    TreeNode* N2 = makeNode('B', N4, N5);
    TreeNode* N3 = makeNode('C', N6, NULL);
    TreeNode* N1 = makeNode('A', N2, N3);
    //TreeNode* N2 = makeNode('B',) //1번 다음으로 뒤에다가 이렇게 만들면 에러가 남. c언어는 위에서부터 해석하니까

    printf("pre :"); preOrder(N1); printf("\n"); //루트로 방문 
    printf("in :"); inOrder(N1); printf("\n");
    printf("post :"); postOrder(N1); printf("\n");
    /*
    A B D E C F
    D B E A F C
    D E B F C A
    */
}