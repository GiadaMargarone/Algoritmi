#include<iostream>
#include<fstream>

using namespace std;

template <class T>
class MinHeap{

    int arraysize;
    int heapsize;
    T* A;
    int heapifytimes;

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
        heapifytimes++;
        int l = left(i);
        int r = right(i);
        int min = i;
        if(l <= heapsize-1 && A[l] < A[min]){
            min = l;
        }
        if(r <= heapsize-1 && A[r] < A[min]){
            min = r;
        }
        if(min != i){
            swap(min, i);
            heapify(min);
        }
    }

    public:

        MinHeap(int size){
            this->heapsize = 1;
            this->arraysize = size+1;
            this->A = new T[arraysize];
            this->heapifytimes = 0;
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

        T* extractMin(){
            if(heapsize - 1){
                T min = A[1];
                A[1] = A[heapsize-1];
                heapsize--;
                if(heapsize - 1){
                    heapify(1);
                    return new T(min);
                }
            }
            return NULL;
        }

        void print(fstream &out){
            out << heapifytimes << " ";
            for(int i = 1; i < this->heapsize; i++){
                out << this->A[i] << " ";
            }
            out << endl;
        }   

};

template<class T>
void process(int size, fstream &in, fstream &out){
    MinHeap<T> heap(size);
    char ch;
    string outfill;

    for(int i = 0; i < size; i++){
        in >> ch >> ch;
        if ( ch == 'x'){
            heap.extractMin();
            in >> outfill;
        }else{
            T key;
            in >> key;
            heap.enqueue(key);
        }
    }
    heap.print(out);

}

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
            if (type == "int")
                process<int>(size, input, output);
            if (type == "char")
                process<char>(size, input, output);
            if (type == "bool")
                process<bool>(size, input, output);
            if (type == "double")
                process<double>(size, input, output);
        }
    }

    input.close();
    output.close();
}