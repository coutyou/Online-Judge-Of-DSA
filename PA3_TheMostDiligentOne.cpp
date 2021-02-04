#include <iostream>
#include <stdio.h>
#include <string.h>
#include <iomanip>
using namespace std;

class MyString
{
  public:
    char value[9];
    MyString(char value[9]);
    ~MyString();
    bool operator<(MyString &str2);
    bool operator>(MyString &str2);
    bool operator==(MyString &str2);
    bool operator!=(MyString &str2);
};

MyString::MyString(char Value[9])
{
    strcpy(value,Value);
}

MyString::~MyString()
{
}

bool MyString::operator<(MyString &str)
{
    return strcmp(value, str.value) < 0 ? true : false;
}

bool MyString::operator>(MyString &str)
{
    return strcmp(value, str.value) > 0 ? true : false;
}

bool MyString::operator==(MyString &str)
{
    return strcmp(value, str.value) == 0 ? true : false;
}

bool MyString::operator!=(MyString &str)
{
    return strcmp(value, str.value) != 0 ? true : false;
}

template <class T>
class BSTNode
{
  public:
    T key;           // 关键字(键值)
    int value;       // 值
    BSTNode *left;   // 左孩子
    BSTNode *right;  // 右孩子
    BSTNode *parent; // 父结点

    BSTNode(T key, int value, BSTNode *p, BSTNode *l, BSTNode *r) : key(key), value(value), parent(p), left(l), right(r) {}
};

template <class T>
class BSTree
{
  private:
    BSTNode<T> *mRoot; // 根结点

  public:
    BSTree();
    ~BSTree();

    // (非递归实现)查找"二叉树"中键值为key的节点
    BSTNode<T> *iterativeSearch(T key);

    // 将结点(key为节点键值)插入到二叉树中
    void insert(T key);

    //对每一个名字进行一次操作
    void operate(T key, int *max, MyString *result);
};

/* 
 * 构造函数
 */
template <class T>
BSTree<T>::BSTree() : mRoot(NULL)
{
}

/* 
 * 析构函数
 */
template <class T>
BSTree<T>::~BSTree()
{

}

template <class T>
BSTNode<T> *BSTree<T>::iterativeSearch(T key)
{
    BSTNode<T> *x = mRoot;

    while ((x != NULL) && (x->key != key))
    {
        if (key < x->key)
            x = x->left;
        else
            x = x->right;
    }

    return x;
}

template <class T>
void BSTree<T>::insert(T key)
{
    BSTNode<T> *z = new BSTNode<T>(key, 1, NULL, NULL, NULL);

    // 如果新建结点失败，则返回。
    if (z == NULL)
    {
        return;
    }

    BSTNode<T> *y = NULL;
    BSTNode<T> *x = mRoot;

    // 查找z的插入位置
    while (x != NULL)
    {
        y = x;
        if (z->key < x->key)
            x = x->left;
        else
            x = x->right;
    }

    z->parent = y;
    if (y == NULL)
    {
        mRoot = z;
    }
    else if (z->key < y->key)
    {
        y->left = z;
    }    
    else
    {
        y->right = z;
    }
}


template <class T>
void BSTree<T>::operate(T key, int *max, MyString *result)
{
    //查找不到就添加节点
    BSTNode<T> *node = iterativeSearch(key);
    if (node == NULL)
    {
        insert(key);
    }
    //找到节点就value++
    else
    {
        node->value++;
        //更新最大值信息
        if (node->value > *max)
        {
            *max = node->value;
            *result = node->key;
        }
    }
}

int main()
{
    setvbuf(stdin, new char[1 << 20], _IOFBF, 1 << 20);
    setvbuf(stdout, new char[1 << 20], _IOFBF, 1 << 20);

    int n;
    scanf("%d", &n);
    BSTree<MyString> bst;
    int max = 0;
    MyString result(NULL);
    char *buf = new char[9];
    MyString tmp(buf);

    for (int i = 0; i < n; i++)
    {
        scanf("%s", tmp.value);
        bst.operate(tmp.value, &max, &result);
    }

    printf("%s %d\n", result.value, max);

    return 0;
}
