#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;

template <typename T>
class Queue
{
  public:
    Queue(int c);
    ~Queue();
    bool enqueue(T data);
    T dequeue();
    T front();
    bool isEmpty();
    bool isFull();
    int size();
    T *queue_;
    int rear_;
    int front_;

  private:
    int capacity_;
};

template <typename T>
Queue<T>::Queue(int c) : capacity_(c),
                         front_(0),
                         rear_(0),
                         queue_(NULL)
{
    queue_ = new T[c];
}

template <typename T>
Queue<T>::~Queue()
{
    if (queue_)
    {
        delete[] queue_;
    }
}

template <typename T>
bool Queue<T>::enqueue(T data)
{
    if (isFull())
    {
        return false;
    }

    queue_[rear_] = data;
    rear_ = (rear_ + 1) % capacity_;

    return true;
}

template <typename T>
T Queue<T>::dequeue()
{
    T data;

    if (isEmpty())
    {
        exit(-1);
    }

    data = queue_[front_];
    front_ = (front_ + 1) % capacity_;

    return data;
}

template <typename T>
T Queue<T>::front()
{
    if (isEmpty())
    {
        exit(-1);
    }

    return queue_[front_];
}

template <typename T>
bool Queue<T>::isEmpty()
{
    return (front_ == rear_);
}

template <typename T>
bool Queue<T>::isFull()
{
    return (((rear_ + 1) % capacity_) == front_);
}

template <typename T>
int Queue<T>::size()
{
    return ((rear_ - front_ + capacity_) % capacity_);
}

template <typename T>
class Queap
{
public:
    Queap(int c);
    ~Queap();
    Queue<T> P;
    Queue<T> Q;
    T getMax();
    void enqueap(T);
    void dequeap();
    int getSize();
};

template <typename T>
Queap<T>::Queap(int c) : P(Queue<T>(c)),Q(Queue<T>(c))
{
}

template <typename T>
Queap<T>::~Queap()
{
}

template <typename T>
T Queap<T>::getMax()
{
    return P.front();
}

template <typename T>
void Queap<T>::enqueap(T t)
{
    Q.enqueue(t);
    P.enqueue(t);
    
    if (P.rear_ > 1) 
    {
        for (int i = P.rear_ - 2; (i >= P.front_) && (P.queue_[i] < t); i--)
        {
            P.queue_[i] = t;
        }
    }
}

template <typename T>
void Queap<T>::dequeap()
{
    Q.dequeue();
    P.dequeue();
}

template <typename T>
int Queap<T>::getSize()
{
    return Q.size();
}

int main()
{
    setvbuf(stdin, new char[1 << 20], _IOFBF, 1 << 20);
    setvbuf(stdout, new char[1 << 20], _IOFBF, 1 << 20);
    int n;
    scanf("%d", &n);
    Queap<int> q(n);
    int value;
    char c;
    while (n--)
    {
        while (scanf("%c", &c) && c != 'E' && c != 'D');
        switch (c)
        {
        case 'E':
            scanf("%d", &value);
            q.enqueap(value);
            printf("%lld\n",(long long int)q.getMax() * q.getSize());
            break;
        case 'D':
            q.dequeap();
            printf("%lld\n", (long long int)q.getMax() * q.getSize());
            break;
        }
    }
    return 0;
}