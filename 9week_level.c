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


#define N 10
typedef TreeNode* element;

typedef struct QueueType
{
    int front, rear;
    element data[N];

}QueueType;

void init(QueueType* Q)
{
    Q->front = Q->rear = 0;

}

int isEmpty(QueueType* Q)
{
    return Q->front == Q->rear;

}

int isFull(QueueType* Q)
{
    return Q->front == (Q->rear + 1) %N;

}

void enqueue(QueueType* Q, element e)
{
    if(!isFull(Q))
    {
        Q->rear = (Q->rear+1) %N;
        Q->data[Q->rear] = e;
    }

}

element dequeue(QueueType* Q)
{
    element e = NULL;

    if(!isEmpty(Q))
    {
        Q->front = (Q->front +1) %N;
        e = Q->data[Q->front];
    }
    return e;
}

void levelOrder(TreeNode* root)
{
    QueueType Q;
    init(&Q);

    enqueue(&Q, root);
    while(!isEmpty(&Q))
    {
        root = dequeue(&Q);
        printf("[%c]", root->data);
        if(root->left != NULL)
            enqueue(&Q, root->left);
        if(root->right != NULL)
            enqueue(&Q, root->right);
    }
    printf("\n");
}

int nodeCount(TreeNode* root) //새로운 문제 전체 노드 개수 구하기
{
    if(root == NULL)
        return 0;
    else
        return 1 + nodeCount(root->left) + nodeCount(root->right); //null이 아니면 해야함
}

int isExternal(TreeNode* root)
{
    return(root->left == NULL && root->right == NULL);
}

//단말노드 개수 구하기 
int leafnodeCount(TreeNode* root) 
{
    if(root == NULL)
        return 0;
    else
    {
        if(isExternal(root))
            return 1;
        else
            return leafnodeCount(root->left) + nodeCount(root->right); //null이 아니면 해야함
    }    
}

//트리의 높이 구하기 **직접 해보아라 그래야 이해가 된다**
#define MAX(a, b) ((a)>(b) ? (a) : (b)) //매크로 함수이다. 하나하나 괄호 하면 됨

int height(TreeNode* root)
{
    if(root == NULL)
        return 0;
    else 
        return 1 + MAX(height(root->left), height(root->right));
}

//트리 뒤집기. 트리 리버스
void treeReverse(TreeNode* root)
{
    if(root != NULL)
    {
        TreeNode* tmp = root->left;
        root->left = root->right;
        root->right = tmp;

        treeReverse(root->left);
        treeReverse(root->right);


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

    printf("level :"); levelOrder(N1); printf("\n");
    //A B C D E F 
    printf("Node Count : %d\n"); nodeCount(N1); printf("\n"); // 6개
    printf("leaf Node Count : %d\n"); leafnodeCount(N1); printf("\n"); // 3개 DEF
    printf("Tree Height : %d\n"); height(N1); printf("\n"); // 3 높이

    treeReverse(N1);
    printf("pre :"); preOrder(N1); printf("\n"); //ACFBED 뒤집힌 것입니다.
}