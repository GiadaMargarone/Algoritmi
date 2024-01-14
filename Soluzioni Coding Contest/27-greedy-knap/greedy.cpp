#include <iostream>
#include <fstream>
#include <typeinfo>

using namespace std;

int next(string &line)
{
    string val = line.substr(0, line.find(" "));
    line = line.substr(val.length() + 1);
    return stoi(val);
}

void sort(int *a, int dim)
{
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
        int dim = next(line);
        int sackSize = next(line);
        int obj[dim];
        for (int i = 0; i < dim; i++)
        {
            obj[i] = next(line);
        }
        for (int i = 0; i < dim; i++)
            cout << obj[i] << " ";
        cout << endl;
        for (int i = 0; i < sackSize; i++)
        {
            for (int j = 1; j < dim; j++)
            {
                if (obj[j - 1] > obj[j])
                {
                    int tmp = obj[j - 1];
                    obj[j - 1] = obj[j];
                    obj[j] = tmp;
                }
            }
        }
        int totValue = 0;
        for (int i = dim - 1; i >= dim - sackSize; i--)
            totValue += obj[i];
        o << totValue << endl;
    }

    return 0;
}