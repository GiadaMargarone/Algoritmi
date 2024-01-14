#include <iostream>
#include <fstream>

using namespace std;

int max(int a, int b)
{
    if (a > b)
        return a;
    return b;
}

int **lcs(string x, int lx, string y, int ly)
{
    int **lcs = new int *[lx + 1];
    for (int i = 0; i <= lx; i++)
        lcs[i] = new int[ly + 1];
    for (int i = 0; i <= lx; i++)
        lcs[i][0] = 0;
    for (int j = 0; j <= ly; j++)
        lcs[0][j] = 0;
    for (int i = 1; i <= lx; i++)
    {
        for (int j = 1; j <= ly; j++)
        {
            if (x[i - 1] == y[j - 1])
            {
                lcs[i][j] = lcs[i - 1][j - 1] + 1;
            }
            else
            {
                lcs[i][j] = max(lcs[i - 1][j], lcs[i][j - 1]);
            }
        }
    }

    return lcs;
}

string printLcs(int **lcs, int i, int j, string x, string y)
{
    if (i == 0 || j == 0)
        return "";
    if (x[i - 1] == y[j - 1])
        return printLcs(lcs, i - 1, j - 1, x, y) += x[i - 1];
    if (lcs[i - 1][j] > lcs[i][j - 1])
        return printLcs(lcs, i - 1, j, x, y);
    return printLcs(lcs, i, j - 1, x, y);
}

string *getValues(string line)
{
    string *values = new string[4];
    values[0] = line.substr(0, line.find(" "));
    line = line.substr(values[0].length() + 1);
    values[1] = line.substr(0, line.find(" "));
    line = line.substr(values[1].length() + 1);
    values[2] = line.substr(0, line.find(" "));
    line = line.substr(values[2].length() + 1);
    values[3] = line;

    return values;
}


int main()
{
    ifstream f;
    f.open("input.txt");
    ofstream o;
    o.open("output.txt");
    if (!f.is_open() || !o.is_open())
        exit(-1);
    string line;
    while (getline(f, line))
    {
        string *values = getValues(line);
        int lx = stoi(values[0]);
        int ly = stoi(values[1]);
        string x = values[2];
        string y = values[3];
        int **lcsRes = lcs(x, lx, y, ly);
        o << printLcs(lcsRes, lx, ly, x, y) << endl;
    }
    return 0;
}