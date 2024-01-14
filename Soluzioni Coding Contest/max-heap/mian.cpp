#include<iostream>
#include<math.h>
#include<fstream>
#include<stdlib.h>

using namespace std;

template<class T>
class Heap{
    public:
        int arraysize;
        T *array;
        int heapsize;
        int heapifytimes;

        int parent(int i) {return i >> 1;}
        int right(int i) {return (i << 1) | 1;}
        int left(int i) {return i << 1;}

        void swap(int i, int j){
            T tmp = array[i];
            array[i] = array[j];
            array[j] = tmp;
        }

        void heapify(int i){
            heapifytimes++;

            int l = left(i);
            int r = right(i);
            int max = i;

            if(l <= heapsize - 1 && array[l] > array[max]){
                max = l;
            }

            if(r <= heapsize - 1 && array[r] > array[max]){
                max = r;
            }

            if(max != i){
                swap(max, i);
                heapify(max);
            }
        }

        Heap(int size){
            heapsize = 1;
            arraysize = size + 1;
            array = new T[arraysize];
            heapifytimes = 0;
        }

        void insert(T k){
            if(heapsize > arraysize){
                return;
            }

            int tmp = heapsize;

            while( tmp > 1 && array[parent(tmp)] < k){
                array[tmp] = array[parent(tmp)];
                tmp = parent(tmp);
            }

            array[tmp] = k;
            heapsize++;
        }

        T* extract(){
            if(heapsize - 1 != 0){
                T max = array[1];
                array[1] = array[heapsize - 1];
                heapsize--;
                if(heapsize - 1 ){
                    heapify(1);
                    return new T(max);
                }
            }
            return NULL;
        }

        void print(fstream &out){
            out << heapifytimes << " ";
            for(int i = 1; i < heapsize; i++){
                out << array[i] << " ";
            }
            out << endl;
        }
};

template< class T >
void process(int size, fstream &in, fstream &out){
    char c;
    string s;
    Heap<T> heap(size);

    for(int i = 0; i < size; i++){
        in >> c >> c;
        if(c == 'x'){
            heap.extract();
            in >> s;
        }
        else{
            T key;
            in >> key;
            heap.insert(key);
        }
    }

    heap.print(out);
}

int main(){
    fstream in, out;
    in.open("input.txt", fstream::in);
    out.open("output.txt", fstream::out);

    string type;
    int size;

    while(!in.eof()){
        in >> type >> size;

        if(!in.eof()){
            if(type == "int")
                process<int>(size, in, out);
            if(type == "bool")
                process<bool>(size, in, out);
            if(type == "double")
                process<double>(size, in, out);
            if(type == "char")
                process<char>(size, in, out);
        }
    }

    in.close();
    out.close();
}