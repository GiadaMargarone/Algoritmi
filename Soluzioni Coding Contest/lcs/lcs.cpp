#include<iostream>
#include<fstream>

using namespace std;

int lcs(string A, int n, string B, int m){
    int **M = new int*[n + 1];
    for(int i = 0; i <= n; i++){
        M[i] = new int [m + 1];        
    }
    for(int i = 0; i <= n; i++){
        M[i][0] = 0;        
    }
    for(int i = 1; i <= m; i++){
        M[0][i] = 0;
    }
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            if(A[i-1] == B[j-1])
            {
                M[i][j] = M[i-1][j-1] + 1;
            }else{
                if (M[i - 1][j] > M[i][j - 1])
                {
                    M[i][j] = M[i - 1][j];
                }
                else if (M[i - 1][j] < M[i][j - 1])
                {
                    M[i][j] = M[i][j - 1];
                }
                else
                {
                    M[i][j] = M[i - 1][j];
                }
            }
        }
    }
    int r = M[n][m];

    return r;
}

int main(){
    ifstream in; in.open("input.txt");
    ofstream out; out.open("output.txt");

    int n=0, m=0;
    string A="", B="";
    for(int i = 0; i < 100; i++){
        in >> n >> m >> A >> B;
        out << lcs(A, n, B, m) << endl;
    }
}