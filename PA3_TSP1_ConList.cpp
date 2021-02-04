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

typedef struct Node
{
    int data;
    Node *next;
    int price;
} Node;

class List
{
  public:
    Node *head;
    Node *p;
    Node *q;
    int length;

    List()
    {
        head = NULL;
        length = 0;
        p = NULL;
    }
    void add(int t, int price)
    {
        if (head == NULL)
        {
            q = new Node;
            q->data = t;
            q->next = NULL;
            q->price = price;
            length++;
            head = q;
            p = head;
        }
        else
        {
            q = new Node;
            q->data = t;
            q->next = NULL;
            q->price = price;
            length++;
            p->next = q;
            p = q;
        }
    }

    void remove(int n)
    {
        if (n >= length)
        {
            return;
        }
        length--;

        //删除头节点
        if (n == 0)
        {
            q = head;
            head = head->next;
            delete (q);
        }
        else
        {
            q = head;
            for (int i = 0; i < n - 1; i++)
            {
                q = q->next;
            }
            Node *t = q->next;
            q->next = q->next->next;
            delete (t);
        }

        //
        p = head;
        if (p != NULL)
        {
            while (p->next != NULL)
            {
                p = p->next;
            }
        }
    }

    int getSize()
    {
        return length;
    }

    int get(int n)
    {
        q = head;
        for (int i = 0; i < n; i++)
        {
            q = q->next;
        }
        return q->data;
    }

    int getPrice(int t)
    {
        if (length != 0)
        {
            q = head;
            for (int i = 0; i < length - 1; i++)
            {
                if (q->data == t)
                {
                    return q->price;
                }
                q = q->next;
            }
            if (q->data == t)
            {
                return q->price;
            }
            return 0;
        }
        else
        {
            return 0;
        }
    }

    void changePrice(int to, int newPrice)
    {
        q = head;
        for (int i = 0; i < length - 1; i++)
        {
            if (q->data == to)
            {
                q->price = newPrice;
                return;
            }
            q = q->next;
        }
        if (q->data == to)
        {
            q->price = newPrice;
        }
    }
};

List *edgeList;

template <class T>
class AVLTreeNode
{
  public:
    T key;              // 关键字(键值)
    int value;          // 值
    int height;         // 高度
    AVLTreeNode *left;  // 左孩子
    AVLTreeNode *right; // 右孩子

    AVLTreeNode(T key, int value, AVLTreeNode *l, AVLTreeNode *r) : key(key), value(value), height(0), left(l), right(r) {}
};

template <class T>
class AVLTree
{
  public:
    AVLTreeNode<T> *mRoot; // 根结点

    AVLTree();
    ~AVLTree();

    void preOrder(AVLTreeNode<T> *tree, int *inDegree, Stack<int> *s);

    // 获取树的高度
    int height();
    // 获取树的高度
    int max(int a, int b);

    // (递归实现)查找"AVL树"中键值为key的节点
    AVLTreeNode<T> *search(T key);
    // (非递归实现)查找"AVL树"中键值为key的节点
    AVLTreeNode<T> *iterativeSearch(T key);

    // 查找最小结点：返回最小结点的键值。
    T minimum();
    // 查找最大结点：返回最大结点的键值。
    T maximum();

    // 将结点(key为节点键值)插入到AVL树中
    void insert(T key, int value);

    // 删除结点(key为节点键值)
    void remove(T key);

    // 获取树的高度
    int height(AVLTreeNode<T> *tree);

    // (递归实现)查找"AVL树x"中键值为key的节点
    AVLTreeNode<T> *search(AVLTreeNode<T> *x, T key) const;
    // (非递归实现)查找"AVL树x"中键值为key的节点
    AVLTreeNode<T> *iterativeSearch(AVLTreeNode<T> *x, T key) const;

    // 查找最小结点：返回tree为根结点的AVL树的最小结点。
    AVLTreeNode<T> *minimum(AVLTreeNode<T> *tree);
    // 查找最大结点：返回tree为根结点的AVL树的最大结点。
    AVLTreeNode<T> *maximum(AVLTreeNode<T> *tree);

    // LL：左左对应的情况(左单旋转)。
    AVLTreeNode<T> *leftLeftRotation(AVLTreeNode<T> *k2);

    // RR：右右对应的情况(右单旋转)。
    AVLTreeNode<T> *rightRightRotation(AVLTreeNode<T> *k1);

    // LR：左右对应的情况(左双旋转)。
    AVLTreeNode<T> *leftRightRotation(AVLTreeNode<T> *k3);

    // RL：右左对应的情况(右双旋转)。
    AVLTreeNode<T> *rightLeftRotation(AVLTreeNode<T> *k1);

    // 将结点(z)插入到AVL树(tree)中
    AVLTreeNode<T> *insert(AVLTreeNode<T> *&tree, T key, int value);

    // 删除AVL树(tree)中的结点(z)，并返回被删除的结点
    AVLTreeNode<T> *remove(AVLTreeNode<T> *&tree, AVLTreeNode<T> *z);
};

/* 
 * 构造函数
 */
template <class T>
AVLTree<T>::AVLTree() : mRoot(NULL)
{
}

/* 
 * 析构函数
 */
template <class T>
AVLTree<T>::~AVLTree()
{
}

/*
 * 获取树的高度
 */
template <class T>
int AVLTree<T>::height(AVLTreeNode<T> *tree)
{
    if (tree != NULL)
        return tree->height;

    return 0;
}

template <class T>
int AVLTree<T>::height()
{
    return height(mRoot);
}
/*
 * 比较两个值的大小
 */
template <class T>
int AVLTree<T>::max(int a, int b)
{
    return a > b ? a : b;
}

/*
 * (递归实现)查找"AVL树x"中键值为key的节点
 */
template <class T>
AVLTreeNode<T> *AVLTree<T>::search(AVLTreeNode<T> *x, T key) const
{
    if (x == NULL || x->key == key)
        return x;

    if (key < x->key)
        return search(x->left, key);
    else
        return search(x->right, key);
}

template <class T>
AVLTreeNode<T> *AVLTree<T>::search(T key)
{
    return search(mRoot, key);
}

/*
 * (非递归实现)查找"AVL树x"中键值为key的节点
 */
template <class T>
AVLTreeNode<T> *AVLTree<T>::iterativeSearch(AVLTreeNode<T> *x, T key) const
{
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
AVLTreeNode<T> *AVLTree<T>::iterativeSearch(T key)
{
    return iterativeSearch(mRoot, key);
}

/* 
 * 查找最小结点：返回tree为根结点的AVL树的最小结点。
 */
template <class T>
AVLTreeNode<T> *AVLTree<T>::minimum(AVLTreeNode<T> *tree)
{
    if (tree == NULL)
        return NULL;

    while (tree->left != NULL)
        tree = tree->left;
    return tree;
}

template <class T>
T AVLTree<T>::minimum()
{
    AVLTreeNode<T> *p = minimum(mRoot);
    if (p != NULL)
        return p->key;

    return (T)NULL;
}

/* 
 * 查找最大结点：返回tree为根结点的AVL树的最大结点。
 */
template <class T>
AVLTreeNode<T> *AVLTree<T>::maximum(AVLTreeNode<T> *tree)
{
    if (tree == NULL)
        return NULL;

    while (tree->right != NULL)
        tree = tree->right;
    return tree;
}

template <class T>
T AVLTree<T>::maximum()
{
    AVLTreeNode<T> *p = maximum(mRoot);
    if (p != NULL)
        return p->key;

    return (T)NULL;
}

/*
 * LL：左左对应的情况(左单旋转)。
 *
 * 返回值：旋转后的根节点
 */
template <class T>
AVLTreeNode<T> *AVLTree<T>::leftLeftRotation(AVLTreeNode<T> *k2)
{
    AVLTreeNode<T> *k1;

    k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;

    k2->height = max(height(k2->left), height(k2->right)) + 1;
    k1->height = max(height(k1->left), k2->height) + 1;

    return k1;
}

/*
 * RR：右右对应的情况(右单旋转)。
 *
 * 返回值：旋转后的根节点
 */
template <class T>
AVLTreeNode<T> *AVLTree<T>::rightRightRotation(AVLTreeNode<T> *k1)
{
    AVLTreeNode<T> *k2;

    k2 = k1->right;
    k1->right = k2->left;
    k2->left = k1;

    k1->height = max(height(k1->left), height(k1->right)) + 1;
    k2->height = max(height(k2->right), k1->height) + 1;

    return k2;
}

/*
 * LR：左右对应的情况(左双旋转)。
 *
 * 返回值：旋转后的根节点
 */
template <class T>
AVLTreeNode<T> *AVLTree<T>::leftRightRotation(AVLTreeNode<T> *k3)
{
    k3->left = rightRightRotation(k3->left);

    return leftLeftRotation(k3);
}

/*
 * RL：右左对应的情况(右双旋转)。
 *
 * 返回值：旋转后的根节点
 */
template <class T>
AVLTreeNode<T> *AVLTree<T>::rightLeftRotation(AVLTreeNode<T> *k1)
{
    k1->right = leftLeftRotation(k1->right);

    return rightRightRotation(k1);
}

/* 
 * 将结点插入到AVL树中，并返回根节点
 *
 * 参数说明：
 *     tree AVL树的根结点
 *     key 插入的结点的键值
 * 返回值：
 *     根节点
 */
template <class T>
AVLTreeNode<T> *AVLTree<T>::insert(AVLTreeNode<T> *&tree, T key, int value)
{
    if (tree == NULL)
    {
        // 新建节点
        tree = new AVLTreeNode<T>(key, value, NULL, NULL);
        if (tree == NULL)
        {
            cout << "ERROR: create avltree node failed!" << endl;
            return NULL;
        }
    }
    else if (key < tree->key) // 应该将key插入到"tree的左子树"的情况
    {
        tree->left = insert(tree->left, key, value);
        // 插入节点后，若AVL树失去平衡，则进行相应的调节。
        if (height(tree->left) - height(tree->right) == 2)
        {
            if (key < tree->left->key)
                tree = leftLeftRotation(tree);
            else
                tree = leftRightRotation(tree);
        }
    }
    else if (key > tree->key) // 应该将key插入到"tree的右子树"的情况
    {
        tree->right = insert(tree->right, key, value);
        // 插入节点后，若AVL树失去平衡，则进行相应的调节。
        if (height(tree->right) - height(tree->left) == 2)
        {
            if (key > tree->right->key)
                tree = rightRightRotation(tree);
            else
                tree = rightLeftRotation(tree);
        }
    }
    else //key == tree->key)
    {
        cout << "添加失败：不允许添加相同的节点！" << endl;
    }

    tree->height = max(height(tree->left), height(tree->right)) + 1;

    return tree;
}

template <class T>
void AVLTree<T>::insert(T key, int value)
{
    insert(mRoot, key, value);
}

/* 
 * 删除结点(z)，返回根节点
 *
 * 参数说明：
 *     tree AVL树的根结点
 *     z 待删除的结点
 * 返回值：
 *     根节点
 */
template <class T>
AVLTreeNode<T> *AVLTree<T>::remove(AVLTreeNode<T> *&tree, AVLTreeNode<T> *z)
{
    // 根为空 或者 没有要删除的节点，直接返回NULL。
    if (tree == NULL || z == NULL)
        return NULL;

    if (z->key < tree->key) // 待删除的节点在"tree的左子树"中
    {
        tree->left = remove(tree->left, z);
        // 删除节点后，若AVL树失去平衡，则进行相应的调节。
        if (height(tree->right) - height(tree->left) == 2)
        {
            AVLTreeNode<T> *r = tree->right;
            if (height(r->left) > height(r->right))
                tree = rightLeftRotation(tree);
            else
                tree = rightRightRotation(tree);
        }
    }
    else if (z->key > tree->key) // 待删除的节点在"tree的右子树"中
    {
        tree->right = remove(tree->right, z);
        // 删除节点后，若AVL树失去平衡，则进行相应的调节。
        if (height(tree->left) - height(tree->right) == 2)
        {
            AVLTreeNode<T> *l = tree->left;
            if (height(l->right) > height(l->left))
                tree = leftRightRotation(tree);
            else
                tree = leftLeftRotation(tree);
        }
    }
    else // tree是对应要删除的节点。
    {
        // tree的左右孩子都非空
        if ((tree->left != NULL) && (tree->right != NULL))
        {
            if (height(tree->left) > height(tree->right))
            {
                // 如果tree的左子树比右子树高；
                // 则(01)找出tree的左子树中的最大节点
                //   (02)将该最大节点的值赋值给tree。
                //   (03)删除该最大节点。
                // 这类似于用"tree的左子树中最大节点"做"tree"的替身；
                // 采用这种方式的好处是：删除"tree的左子树中最大节点"之后，AVL树仍然是平衡的。
                AVLTreeNode<T> *max = maximum(tree->left);
                tree->key = max->key;
                tree->left = remove(tree->left, max);
            }
            else
            {
                // 如果tree的左子树不比右子树高(即它们相等，或右子树比左子树高1)
                // 则(01)找出tree的右子树中的最小节点
                //   (02)将该最小节点的值赋值给tree。
                //   (03)删除该最小节点。
                // 这类似于用"tree的右子树中最小节点"做"tree"的替身；
                // 采用这种方式的好处是：删除"tree的右子树中最小节点"之后，AVL树仍然是平衡的。
                AVLTreeNode<T> *min = minimum(tree->right);
                tree->key = min->key;
                tree->right = remove(tree->right, min);
            }
        }
        else
        {
            AVLTreeNode<T> *tmp = tree;
            tree = (tree->left != NULL) ? tree->left : tree->right;
            delete tmp;
        }
    }

    return tree;
}

template <class T>
void AVLTree<T>::remove(T key)
{
    AVLTreeNode<T> *z;

    if ((z = search(mRoot, key)) != NULL)
        mRoot = remove(mRoot, z);
}

template <class T>
void AVLTree<T>::preOrder(AVLTreeNode<T> *curNode, int *inDegree, Stack<int> *s)
{
    if (curNode != NULL)
    {
        inDegree[curNode->key]--;
        if (inDegree[curNode->key] == 0)
        {
            s->push(curNode->key);
            inDegree[curNode->key] = -1;
        }
        preOrder(curNode->left, inDegree, s);
        preOrder(curNode->right, inDegree, s);
    }
}

void copy(AVLTreeNode<int> *tree, int from)
{
    if (tree != NULL)
    {
        copy(tree->left, from);

        edgeList[tree->key].add(from, tree->value);
        
        copy(tree->right, from);
        
    }
    
}

int main()
{
    setvbuf(stdin, new char[1 << 20], _IOFBF, 1 << 20);
    setvbuf(stdout, new char[1 << 20], _IOFBF, 1 << 20);

    //创建有向无环图的相关数组并根据输入内容进行初始化
    int n, m;
    scanf("%d %d", &n, &m);

    int *inDegree = new int[n];        //储存每个点的入度
    int *topologicalSort = new int[n]; //储存拓扑排序的结果
    int *topoIndex = new int[n];       //储存节点在拓扑数组中的下标
    int *maxPath = new int[n];         //用于保存到该节点最长路径的长度
    for (int i = 0; i < n; i++)
    {
        inDegree[i] = 0;
        maxPath[i] = 0;
    }

    //输入
    AVLTree<int> *edge = new AVLTree<int>[n];
    edgeList = new List[n];

    int from, to, price;
    AVLTreeNode<int> *searchResult;
    for (int i = 0; i < m; i++)
    {
        scanf("%d %d %d", &from, &to, &price);
        searchResult = edge[from - 1].iterativeSearch(to - 1);
        if (searchResult == NULL)
        {
            edge[from - 1].insert(to - 1, price);
            inDegree[to - 1]++;
        }
        else if (searchResult->value < price)
        {
            searchResult->value = price;
        }
    }

    for(int i = 0; i < n; i++)
    {
        copy(edge[i].mRoot, i);
    }

    //拓扑排序
    Stack<int> s(n);
    int flag = 1;
    int top;
    int index = 0;
    while (flag != 0)
    {
        flag = 0;
        for (int i = 0; i < n; i++)
        {
            if (inDegree[i] == 0)
            {
                s.push(i);
                inDegree[i] = -1;
                flag = 1;
                break;
            }
        }
        while (!s.isEmpty())
        {
            top = s.pop();
            topologicalSort[index] = top;
            topoIndex[top] = index;
            index++;
            edge[top].preOrder(edge[top].mRoot, inDegree, &s);
        }
    }

    /*
    //debug
    for (int i = 0; i < n; i++)
    {
        printf("\nfrom: %d\n", i);
        edge[i].preOrder2(edge[i].mRoot);
    }
    for (int i = 0; i < n; i++)
    {
        printf("topo[%d] = %d\n", i, topologicalSort[i]);
    }
    */

    //获得最长路径长度
    int max = 0;
    Node *link;
    for (int i = 0; i < n; i++)
    {
        to = topologicalSort[i];
        link = edgeList[to].head;
        while(link != NULL)
        {
            if (topoIndex[link->data] < topoIndex[to])
            {
                if (maxPath[link->data] + link->price > maxPath[to])
                {
                    maxPath[to] = maxPath[link->data] + link->price;
                    if (maxPath[to] > max)
                    {
                        max = maxPath[to];
                    }
                }
            }
            link = link->next;
        }
    }

    printf("%d\n", max);
    return 0;
}
