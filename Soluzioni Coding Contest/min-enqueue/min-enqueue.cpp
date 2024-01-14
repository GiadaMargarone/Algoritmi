#include<iostream>
#include<fstream>

using namespace std;

template <class T>
class Heap{

    int arraysize;
    int heapsize;
    T* A;

    int parent(int i){
        return i >> 1;
    }

    int left(int i){
        return i << 1;
    }

    int right(int i){
        return (i << 1) | 1;
    }

    void swap(int i, int j){
        T temp = this->A[i];
        this->A[i] = this->A[j];
        this->A[j] = temp;
    }

    void heapify(int i){
        int l = left(i);
        int r = right(i);
        int max = i;
        if(l <= heapsize-1 && A[l] < A[max]){
            max = l;
        }
        if(r <= heapsize-1 && A[r] < A[max]){
            max = r;
        }
        if(max != i){
            swap(max, i);
            heapify(max);
        }
    }

    public:

        Heap(int size){
            this->heapsize = 1;
            this->arraysize = size+1;
            this->A = new T[arraysize];
        }

        void enqueue(T k){
            if(heapsize > arraysize){
                return;
            }
            int i = this->heapsize;
            while(i>1 && A[parent(i)] > k){
                A[i] = A[parent(i)];
                i = parent(i);
            }
            A[i] = k;
            this->heapsize++;
        }

        void print(fstream &out){
            for(int i = 1; i < this->heapsize; i++){
                out << this->A[i] << " ";
            }
            out << endl;
        }   

};

int main(){
    fstream input, output;
    input.open("input.txt", fstream::in);
    output.open("output.txt", fstream::out);

    string type;
    int size;

    while(!input.eof()){

        input >> type >> size;
        if (!input.eof())
        {
            if (type == "int"){
                Heap<int> *h = new Heap<int>(size);
                int x;
                for(int i = 0; i < size; i++){
                    input >> x;
                    h->enqueue(x);
                }
                h->print(output);
            }    
            if (type == "bool"){
                Heap<bool> *h = new Heap<bool>(size);
                bool x;
                for(int i = 0; i < size; i++){
                    input >> x;
                    h->enqueue(x);
                }
                h->print(output);
            } 
            if (type == "double"){
                Heap<double> *h = new Heap<double>(size);
                double x;
                for(int i = 0; i < size; i++){
                    input >> x;
                    h->enqueue(x);
                }
                h->print(output);
            } 
            if (type == "char"){
                Heap<char> *h = new Heap<char>(size);
                char x;
                for(int i = 0; i < size; i++){
                    input >> x;
                    h->enqueue(x);
                }
                h->print(output);
            } 
        }
    }

    input.close();
    output.close();
}