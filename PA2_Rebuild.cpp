#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;

//栈类
template <class T>
class Stack
{
  public:
    Stack(int n);
    ~Stack();

    void push(T t);
    T top();
    T pop();
    int size();
    bool isEmpty();

  private:
    T *arr;
    int count;
};

template <class T>
Stack<T>::Stack(int n)
{
    arr = new T[n];
    count = 0;
    if (!arr)
    {
        exit(-1);
    }
}

template <class T>
Stack<T>::~Stack()
{

}

template <class T>
void Stack<T>::push(T t)
{
    arr[count++] = t;
}

template <class T>
T Stack<T>::top()
{
    return arr[count - 1];
}

template <class T>
T Stack<T>::pop()
{
    T ret = arr[count - 1];
    count--;
    return ret;
}

template <class T>
int Stack<T>::size()
{
    return count;
}

template <class T>
bool Stack<T>::isEmpty()
{
    return size() == 0;
}

//二叉树的节点
typedef struct BinNode
{
    BinNode *lchild;
    BinNode *rchild;
    int data;
} BinNode;

//用于初始化nodes数组里的新Node
BinNode *NewNode(BinNode *nodes, int &index)
{
    nodes[index].lchild = nodes[index].rchild = NULL;
    return &nodes[index++];
}

//根据前序和后序建立一棵树
BinNode *buildTree(int s1, int e1, int s2, int e2, int *PreorderTraversal, int *PostorderTraversal, BinNode *nodes, int &index) //前序序列[s1,e1]，后序序列[s2,e2]
{ 
    BinNode *root = NewNode(nodes, index);
    root->data = PreorderTraversal[s1];
    int rootIdx;
    if (s2 == e2)
        return root;
    for (int i = s2; i <= e2; i++) // 寻找左子树树根结点在后序序列的位置
    {
        if (PostorderTraversal[i] == PreorderTraversal[s1 + 1]) // PreorderTraversal[s1+1]：左子树树根
        {
            rootIdx = i;
            break;
        }
    }
    root->lchild = buildTree(s1 + 1, rootIdx - s2 + s1 + 1, s2, rootIdx, PreorderTraversal, PostorderTraversal, nodes, index);
    root->rchild = buildTree(rootIdx - s2 + s1 + 2, e1, rootIdx + 1, e2 - 1, PreorderTraversal, PostorderTraversal, nodes, index);
    return root;
}

int main()
{
    setvbuf(stdin, new char[1 << 20], _IOFBF, 1 << 20);
    setvbuf(stdout, new char[1 << 20], _IOFBF, 1 << 20);

    int n;
    int index = 0;
    scanf("%d", &n);
    int *PreorderTraversal = new int[n];
    int *PostorderTraversal = new int[n];
    BinNode *nodes = new BinNode[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &PreorderTraversal[i]);
    }
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &PostorderTraversal[i]);
    }
    BinNode *tree = buildTree(0, n - 1, 0, n - 1, PreorderTraversal, PostorderTraversal, nodes, index);
    //利用栈中序遍历输出tree
    Stack<BinNode *> nodeStack(n);
    BinNode *p = nodes;
    while (p != NULL || !nodeStack.isEmpty())
    {
        while (p != NULL)
        {
            nodeStack.push(p);
            p = p->lchild;
        }
        if (!nodeStack.isEmpty())
        {
            p = nodeStack.top();
            printf("%d ", p->data);
            nodeStack.pop();
            p = p->rchild;
        }
    }
    return 0;
}
