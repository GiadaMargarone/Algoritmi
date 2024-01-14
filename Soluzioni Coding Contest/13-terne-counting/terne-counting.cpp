#include <iostream>
#include <fstream>
#include <typeinfo>

using namespace std;

struct Terna
{
    double x;
    double y;
    double z;
    Terna() {}
    Terna(double l, double r, double k)
    {
        x = l;
        y = r;
        z = k;
    }
};

void countingsort(Terna *A, int dim, ofstream &o)
{
    // normalize first componenet values
    for (int i = 0; i < dim; i++)
        A[i].x *= 10;
    // find dim B
    double max = A[0].x;
    double min = A[0].x;
    for (int i = 1; i < dim; i++)
    {
        if (A[i].x > max)
            max = A[i].x;
        else if (A[i].x < min)
            min = A[i].x;
    }
    int gap = max - min + 1;
    // init B
    int B[gap];
    for (int i = 0; i < gap; i++)
        B[i] = 0;
    // counting
    for (int i = 0; i < dim; i++)
        B[(int)(A[i].x - min)]++;
    for (int i = 1; i < gap; i++)
        B[i] = B[i] + B[i - 1];

    // sorting
    Terna C[dim];
    for (int i = dim - 1; i >= 0; i--)
    {
        C[B[(int)(A[i].x - min)] - 1] = A[i];
        B[(int)(A[i].x - min)]--;
    }
    cout << endl;

    // denormalize first component values
    for (int i = 0; i < dim; i++)
        C[i].x /= 10;
    for (int i = 0; i < gap; i++)
        o << B[i] << " ";
    for (int i = 0; i < dim; i++)
        o << "(" << C[i].x << " " << C[i].y << " " << C[i].z << ") ";
    o << endl;
}

void performOp(int dim, string &line, ofstream &o)
{
    Terna terne[dim];
    // carico array
    for (int i = 0; i < dim; i++)
    {
        string values = line.substr(0, line.find(")") + 1);
        line = line.substr(values.length() + 1);
        int gap = min(values.find(" "), values.find(","));
        int gap2 = min(values.find(" ", gap + 1), values.find(",", gap + 1));
        string x = values.substr(1, gap - 1);
        string y = values.substr(gap + 1, gap2 - gap - 1);
        string z = values.substr(gap2 + 1);
        z.pop_back();
        terne[i].x = stod(x);
        terne[i].y = stod(y);
        terne[i].z = stod(z);
    }
    countingsort(terne, dim, o);
}

int main()
{
    ifstream i;
    i.open("input.txt");
    ofstream o;
    o.open("output.txt");
    string line;
    while (getline(i, line))
    {
        line.append(" ");
        string sNum = line.substr(0, line.find(" "));
        line = line.substr(sNum.length() + 1);
        int dim = stoi(sNum);
        performOp(dim, line, o);
    }
}