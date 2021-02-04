#include <iostream>
#include <string.h>
using namespace std;

typedef struct GreaterInt
{
    int data;
    GreaterInt(int _data)
    {
        data = _data;
    }
    GreaterInt()
    {
        data = 0;
    }
    bool operator==(const GreaterInt b)
    {
        if (data == b.data)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    bool operator!=(const GreaterInt b)
    {
        if (data == b.data)
        {
            return false;
        }
        else
        {
            return true;
        }
    }
    bool operator<(const GreaterInt b)
    {
        if (b.data > data)
        {
            return false;
        }
        else
        {
            return true;
        }
    }
    bool operator>(const GreaterInt b)
    {
        if (b.data < data)
        {
            return false;
        }
        else
        {
            return true;
        }
    }
} GreaterInt;

template <typename Comparable>
class BinaryHeap
{
  public:
    BinaryHeap(int capacity)
    {
        array = new Comparable[capacity + 1];
        currentSize = 0;
    }
    //explicit BinaryHeap(const vector<Comparable> &items);

    bool isEmpty();              //推断二叉堆是否为空
    const Comparable &findMin(); //查找最小元素

    void insert(Comparable &x);    //插入元素x
    void deleteMin();                    //删除最小元素
    void deleteMin(Comparable &minItem); //删除最小元素。并以引用的方式返回该最小元素
    void makeEmpty();                    //清空该二叉堆
    void print();                  //打印该堆元素

  private:
    Comparable *array; //存储二叉堆的节点
    int currentSize;   //当前二叉堆中的节点数目
  private:
    void buildHeap();             //将元素移动到合适的位置
    void percolateDown(int hole); //下移动
};

/****************************************************************
*   函数名称：print() const
*   功能描写叙述: 打印该堆元素 
*   參数列表: 无 
*   返回结果：无
*****************************************************************/
template <typename Comparable>
void BinaryHeap<Comparable>::print()
{
    cout << "二叉堆的元素: " << endl;
    for (int i = 1; i <= currentSize; ++i)
        cout << array[i] << " ";
    cout << endl;
}

/****************************************************************
*   函数名称：BinaryHeap(const vector<Comparable> & items)
*   功能描写叙述: 构造函数
*   參数列表: items 是构造二叉堆须要的数据
*   返回结果：无
*****************************************************************/
/*template <typename Comparable>
BinaryHeap<Comparable>::BinaryHeap(const vector<Comparable> &items) : array(items.size() + 10), currentSize(items.size())
{
    for (unsigned i = 0; i < items.size(); ++i)
        array[i + 1] = items[i];

    buildHeap();
}*/
/****************************************************************
*   函数名称：buildHeap()
*   功能描写叙述: 将元素移动到合适的位置，满足堆序
*   參数列表: 无
*   返回结果：void
*****************************************************************/
template <typename Comparable>
void BinaryHeap<Comparable>::buildHeap()
{
    for (int i = currentSize / 2; i > 0; --i)
        percolateDown(i);
}

/****************************************************************
*   函数名称：findMin()
*   功能描写叙述: 查找最小元素
*   參数列表: 无
*   返回结果：返回最小元素的引用
*****************************************************************/
template <typename Comparable>
const Comparable &BinaryHeap<Comparable>::findMin()
{
    return array[1];
}

/****************************************************************
*   函数名称：insert(const Comparable & x)
*   功能描写叙述: 删除最小元素
*   參数列表: 无
*   返回结果：void 
*****************************************************************/
template <typename Comparable>
void BinaryHeap<Comparable>::insert(Comparable &x)
{
    //获得空穴的位置
    int hole = ++currentSize;

    //上滤
    for (; hole > 1 && x < array[hole / 2]; hole /= 2)
        array[hole] = array[hole / 2];
    //将x插入到合适的位置
    array[hole] = x;
}

/****************************************************************
*   函数名称：deleteMin()
*   功能描写叙述: 删除最小元素
*   參数列表: 无
*   返回结果：void 
*****************************************************************/
template <typename Comparable>
void BinaryHeap<Comparable>::deleteMin()
{
    if (isEmpty())
    {
        //cout << "BinaryHeap is empty." << endl;
        return;
    }

    array[1] = array[currentSize]; //将最后一个元素移动到最小元素的位置
    currentSize--;                 //元素总数减去1
    //将最后一个元素移动到合适的位置
    percolateDown(1);
}

/****************************************************************
*   函数名称：percolateDown(int hole)
*   功能描写叙述: 将array(hole)处的值向下移动 
*   參数列表: hole为堆中元素的位置标号
*   返回结果：void 
*****************************************************************/
template <typename Comparable>
void BinaryHeap<Comparable>::percolateDown(int hole)
{
    int child;
    //先保存array[hole]的值
    Comparable temp = array[hole];

    for (; hole * 2 <= currentSize; hole = child)
    {
        child = hole * 2;

        //child != currentSize,表明此时空穴有右儿子
        //array[child] > array[child+1] 表明此时空穴有右儿子小于左儿子
        if (child != currentSize && array[child] > array[child + 1])
            child++; //此时child表示为空穴的右儿子

        //空穴的右儿子小于array[hole]
        if (array[child] < temp)
            array[hole] = array[child];
        else
            break;
    }

    array[hole] = temp;
}
/****************************************************************
*   函数名称：deleteMin(Comparable & minItem)
*   功能描写叙述: 删除最小元素
*   參数列表: minItem 将最小元素赋值给引用minItem
*   返回结果：void 
*****************************************************************/
template <typename Comparable>
void BinaryHeap<Comparable>::deleteMin(Comparable &minItem)
{
    if (isEmpty())
    {
        //cout << "binaryHeap is empty." << endl;
        return;
    }

    minItem = array[1];

    array[1] = array[currentSize--];
    percolateDown(1);
}

/****************************************************************
*   函数名称：makeEmpty()
*   功能描写叙述: 情况二叉堆
*   參数列表: 无
*   返回结果：void 
*****************************************************************/
template <typename Comparable>
void BinaryHeap<Comparable>::makeEmpty()
{
    currentSize = 0;
}

/****************************************************************
*   函数名称：isEmpty()
*   功能描写叙述: 推断二叉堆是否为空
*   參数列表: 无
*   返回结果：假设为空，则返回true。否则返回false
*****************************************************************/
template <typename Comparable>
bool BinaryHeap<Comparable>::isEmpty()
{
    return currentSize == 0;
}

int main()
{
    int n, k;
    fread(&n, sizeof(int), 1, stdin);
    fread(&k, sizeof(int), 1, stdin);

    int tmp;
    GreaterInt G_tmp(0);
    int max;
    BinaryHeap<GreaterInt> binaryHeap(k);
    for (int i = 0; i < k; i++)
    {
        fread(&tmp, sizeof(int), 1, stdin);
        G_tmp.data = tmp;
        binaryHeap.insert(G_tmp);
    }
    for (int i = 0; i < n - k; i++)
    {
        fread(&tmp, sizeof(int), 1, stdin);
        if (tmp < binaryHeap.findMin().data)
        {
            G_tmp.data = tmp;
            binaryHeap.deleteMin();
            binaryHeap.insert(G_tmp);
        }
    }

    cout << binaryHeap.findMin().data << endl;

    return 0;
}