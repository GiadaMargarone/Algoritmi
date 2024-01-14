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
    for(int i = 0; i <= m; i++){
        M[0][i] = 0;
    }
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            if(A[i-1] == B[j-1]){
                M[i][j] = M[i-1][j-1] + 1;
            }else if(M[i][j-1] <= M[i-1][j]){
                M[i][j] = M[i-1][j];
            }else{
                M[i][j] = M[i][j-1];
            }
        }
    }
    return M[n][m];
}

int main(){
    fstream in; in.open("input.txt", fstream::in);
    fstream out; out.open("output.txt", fstream::out);

    int n, m;
    string A, B;
    while(!in.eof()){
        in >> n >> m >> A >> B;
        out << lcs(A, n, B, m) << endl;
    }
}