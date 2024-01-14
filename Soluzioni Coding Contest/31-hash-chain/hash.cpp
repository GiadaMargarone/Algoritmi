#include <iostream>
#include <fstream>
#include <typeinfo>
using namespace std;

class Hash
{
private:
    int *table;
    int dim;

public:
    Hash(int dim) : dim(dim)
    {
        table = new int[dim];
        for (int i = 0; i < dim; i++)
            table[i] = 0;
    }
    void insert(int k)
    {
        table[k % dim]++;
    }
    void writeRes(ostream &o)
    {
        for (int i = 0; i < dim; i++)
            o << table[i] << " ";
        o << endl;
    }
};

string getType(string &line)
{
    string t = line.substr(0, line.find(" "));
    line = line.substr(t.length() + 1);
    return t;
}
int getTableDim(string &line)
{
    string dim = line.substr(0, line.find(" "));
    line = line.substr(dim.length() + 1);
    return stoi(dim);
}
int getElemNumber(string &line)
{
    string n = line.substr(0, line.find(" "));
    line = line.substr(n.length() + 1);
    return stoi(n);
}

template <typename T>
T *getValues(string &line, int n)
{
    T *a = new T[n];
    for (int i = 0; i < n - 1; i++)
    {
        T val;
        string sVal = line.substr(0, line.find(" "));
        line = line.substr(sVal.length() + 1);
        if (typeid(T) == typeid(int) || typeid(T) == typeid(bool))
        {
            val = stoi(sVal);
        }
        else if (typeid(T) == typeid(char))
        {
            val = sVal[0];
        }
        else if (typeid(T) == typeid(double))
        {
            val = stod(sVal);
        }
        a[i] = val;
    }
    if (typeid(T) == typeid(int) || typeid(T) == typeid(bool))
    {
        a[n - 1] = stoi(line);
    }
    else if (typeid(T) == typeid(char))
    {
        a[n - 1] = line[0];
    }
    else if (typeid(T) == typeid(double))
    {
        a[n - 1] = stod(line);
    }
    return a;
}

template <typename T>
void performOp(string &line, int num, int tableSize, ostream &o)
{
    T *a = getValues<T>(line, num);
    Hash t(tableSize);
    for (int i = 0; i < num; i++)
    {
        // cout << a[i] << " ";
        t.insert((int)a[i]);
    }
    t.writeRes(o);
}

int main()
{
    ifstream f;
    ofstream o;
    f.open("input.txt");
    o.open("output.txt");
    string line;
    while (getline(f, line))
    {
        string type = getType(line);
        int tableDim = getTableDim(line);
        int numElem = getElemNumber(line);
        if (type == "int" || type == "bool")
        {
            performOp<int>(line, numElem, tableDim, o);
        }
        else if (type == "char")
        {
            performOp<char>(line, numElem, tableDim, o);
        }
        else if (type == "double")
        {
            performOp<double>(line, numElem, tableDim, o);
        }
    }
    return 0;
}