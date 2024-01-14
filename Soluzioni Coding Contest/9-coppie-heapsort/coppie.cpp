#include <iostream>
#include <fstream>
#include <typeinfo>

using namespace std;

template <typename T>
struct Coppia
{
    T x;
    T y;
    Coppia() {}
    Coppia(T l, T r)
    {
        x = l;
        y = r;
    }
};

template <typename T>
ofstream &operator<<(ofstream &o, Coppia<T> c)
{
    o << "(" << c.x << " " << c.y << ")";
    return o;
}
template <typename T>
ostream &operator<<(ostream &o, Coppia<T> c)
{
    o << "(" << c.x << " " << c.y << ")";
    return o;
}

template <typename T>
bool operator>(Coppia<T> c1, Coppia<T> c2)
{
    if (c1.x > c2.x)
        return true;
    if (c1.x == c2.x)
    {
        if (c1.y > c2.y)
            return true;
    }
    return false;
}

template <typename T>
T cast(string val)
{
    if (typeid(T) == typeid(int) || typeid(T) == typeid(bool))
    {
        return stoi(val);
    }
    else if (typeid(T) == typeid(char))
    {
        return val[0];
    }
    else if (typeid(T) == typeid(double))
    {
        return stod(val);
    }
    return 0;
}

template <class T>
class MaxHeap
{
private:
    T *heap;
    int heapsize;
    int size;
    int heapifyCall;

    int left(int i)
    {
        return i << 1;
    }
    int right(int i)
    {
        return (i << 1) + 1;
    }

    void swap(int i, int j)
    {
        T tmp = heap[i];
        heap[i] = heap[j];
        heap[j] = tmp;
    }

public:
    MaxHeap(T *arr, int size) : heapsize(size), size(size)
    {
        heap = arr;
        heap--;
        heapifyCall = 0;
    }
    void heapify(int i)
    {
        if (size >= 1)
            heapifyCall++;
        int max = i;
        int l = left(i);
        int r = right(i);
        if (l <= size && heap[l] > heap[max])
            max = l;
        if (r <= size && heap[r] > heap[max])
            max = r;
        if (i != max)
        {
            swap(i, max);
            heapify(max);
        }
    }
    void builMaxHeap()
    {
        for (int i = size / 2; i >= 1; i--)
            heapify(i);
    }
    void extractMax()
    {
        swap(1, size);
        size--;
        heapify(1);
    }
    void heapsort()
    {
        builMaxHeap();
        int elements = size;
        for (int i = 1; i <= elements; i++)
        {
            extractMax();
        }
        size = elements;
    }
    void printArray(ofstream &o)
    {
        o << heapifyCall << " ";
        for (int i = 1; i <= size; i++)
        {
            o << heap[i] << " ";
        }
        o << endl;
    }
};

string next(string &line)
{
    string val = line.substr(0, line.find(" "));
    line = line.substr(val.length() + 1);
    return val;
}

template <typename T>
void performOp(int dim, string &line, ofstream &o)
{
    Coppia<T> arr[dim];
    for (int i = 0; i < dim; i++)
    {
        string values = line.substr(0, line.find(")") + 1);
        line = line.substr(values.length() + 1);
        int gap = min(values.find(" "), values.find(","));
        T x = cast<T>(values.substr(1, gap - 1));
        T y = cast<T>(values.substr(gap + 1, values.length() - gap - 1));
        arr[i].x = x;
        arr[i].y = y;
    }
    MaxHeap<Coppia<T>> h(arr, dim);
    h.heapsort();
    h.printArray(o);
}

int main()
{
    ifstream f;
    f.open("input.txt");
    ofstream o;
    o.open("output.txt");
    string line;
    while (getline(f, line))
    {
        line.append(" ");
        string type = next(line);
        int dim = stoi(next(line));
        if (type == "int" || type == "bool")
        {
            performOp<int>(dim, line, o);
        }
        else if (type == "double")
        {
            performOp<double>(dim, line, o);
        }
        else if (type == "char")
        {
            performOp<char>(dim, line, o);
        }
    }
    // int a[] = {46, 5, 79, 72, 53, 78, 18, 20, 19, 74};
    // MaxHeap<int>h (a, 10);
    // h.heapsort();
    return 0;
}