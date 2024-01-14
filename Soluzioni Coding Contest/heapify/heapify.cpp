#include<iostream>
#include<cmath>
#include<fstream>

using namespace std;

template<class T>
class Heap{
    private:
        int arraysize;
        int heapsize;
        T *A;
        int heapifytimes;

        int left(int i){return i << 1;}
        int right(int i){return (i << 1) | 1;}
        int parent(int i){return i >> 1;}

        void heapify(int i){
            heapifytimes++;
            int l = left(i);
            int r = right(i);
            int max = i;
            if(l < heapsize && A[l]>A[max]){
                max=l;
            }
            if(r < heapsize && A[r]>A[max]){
                max=r;
            }
            if(max != i){
                T temp = A[i];
                A[i]=A[max];
                A[max] = temp;
                heapify(max);
            }
        }

        public:
            Heap(int size){
                heapsize = 1;
                arraysize = size + 1;
                A = new T[arraysize];
                heapifytimes = 0;
            }

            void insert(T k){
                if(heapsize <= arraysize){
                    A[heapsize] = k;
                    heapsize++;
                }
            }

            void buildmaxheap(){
                for(int i = floor((heapsize-1)/2); i >= 1; i--){
                    heapify(i);
                }
            }

            void print(ofstream &out){
                out << heapifytimes << endl;
            }

            void extractMax(){
                if(heapsize-1){
                    A[1] = A[heapsize-1];
                    heapsize--;
                    if(heapsize-1){
                        heapify(1);
                    }
                }
            }
};

int main(){
    ifstream in;
    in.open("input.txt");
    ofstream out;
    out.open("output.txt");
    string t = "";
    int N = 0;
    for (int i = 0; i < 100; i++)
    {
        in >> t;
        if (t == "char")
        {
            in >> N;
            Heap<char> *h = new Heap<char>(N);
            char x = ' ';
            for (int i = 0; i < N; i++)
            {
                in >> x;
                h->insert(x);
            }
            h->buildmaxheap();
            for (int i = 0; i < N; i++)
            {
                h->extractMax();
            }
            h->print(out);
        }else if (t == "int")
        {
            in >> N;
            Heap<int> *h = new Heap<int>(N);
            int x = 0;
            for (int i = 0; i < N; i++)
            {
                in >> x;
                h->insert(x);
            }
            h->buildmaxheap();
            for (int i = 0; i < N; i++)
            {
                h->extractMax();
            }
            h->print(out);
        }else if (t == "bool")
        {
            in >> N;
            Heap<bool> *h = new Heap<bool>(N);
            bool x;
            for (int i = 0; i < N; i++)
            {
                in >> x;
                h->insert(x);
            }
            h->buildmaxheap();
            for (int i = 0; i < N; i++)
            {
                h->extractMax();
            }
            h->print(out);
        }
        else
        {
            in >> N;
            Heap<double> *h = new Heap<double>(N);
            double x = 0;
            for (int i = 0; i < N; i++)
            {
                in >> x;
                h->insert(x);
            }
            h->buildmaxheap();
            for (int i = 0; i < N; i++)
            {
                h->extractMax();
            }
            h->print(out);
        }
    }
    in.close();
    out.close();
    return 0;
}