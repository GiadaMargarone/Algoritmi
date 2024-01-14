#include<iostream>
#include<fstream>
#include<math.h>

using namespace std;

template<class T>
void performOP(ifstream& in, ofstream& out, int size, int n){
    int hash[size];
    double  c = 0.61803;
    for(int i = 0; i < size; i++){
        hash[i] = 0;
    }
    T x;
    for(int i = 0; i < n; i++){
        in >> x;
        hash[(int) floor(fmod(double(x) * c, 1.0) * size)]++;
    }
    for(int i = 0; i < size; i++){
        out << hash[i] << " ";
    }  
    out << endl;
}

int main(){
    ifstream in;
    ofstream out;
    in.open("input.txt", fstream::in);
    out.open("output.txt", fstream::out);

    int size, n;
    string type;
    for(int i = 0; i < 100; i++){
        in >> type >> size >> n;
        cout << "Type " << type << " ";
        if(type == "int" || type == "bool"){
            performOP<int>(in, out, size, n);
        }
        else if(type == "char"){
            performOP<char>(in, out, size, n);
        }
        else if(type == "double"){
            performOP<double>(in, out, size, n);
        }
    }

    in.close();
    out.close();
    
};