#include<iostream>
#include<vector>
#include<chrono>

#define N 10000000  //Este N es solo para el cálculo de posiciones de las medianas a tomar, no afecta en nada al funcionamiento correcto
                    //del programa, solo al output de las medianas, para el cual no se piden estrictamente ciertas posiciones de
                    //medianas, solo que sean 10.
                    //El verdadero N es el tamaño del vector nums (línea 202).

using namespace std;
using namespace std::chrono;

class HeapMin
{
private:
   vector<int> heap;
   void downwards(int index)
   {
      int nextInd=index;
      if(2*index+1 < heap.size() && heap[nextInd] > heap[2*index + 1]) nextInd = 2*index+1;
      if(2*index+2 < heap.size() && heap[nextInd] > heap[2*index + 2]) nextInd = 2*index+2;
      if (nextInd != index)
      {
         swap(heap[index], heap[nextInd]);
         downwards(nextInd);
      }
      return;
   }

public:
   bool isEmpty()
   {
      return (heap.size() <= 0);
   }
   void insert(int val)
   {
      int index = heap.size();
      heap.push_back(val);
      while (index > 0 && val < heap[(index-1)/2])
      {
         heap[index] = heap[(index-1)/2];
         index = (index-1)/2;
      }
      heap[index] = val;
   }
   int extract()
   {
      int val = heap[0];
      heap[0] = heap[heap.size()-1];
      heap.pop_back();
      if (!isEmpty()) downwards(0);
      return val;
   }
   int top()
   {
      return heap[0];
   }
   int size()
   {
      return heap.size();
   }
};

class HeapMax
{
private:
   vector<int> heap;
   void downwards(int index)
   {
      int nextInd=index;
      if(2*index+1 < heap.size() && heap[nextInd] < heap[2*index + 1]) nextInd = 2*index+1;
      if(2*index+2 < heap.size() && heap[nextInd] < heap[2*index + 2]) nextInd = 2*index+2;
      if (nextInd != index)
      {
         swap(heap[index], heap[nextInd]);
         downwards(nextInd);
      }
      return;
   }

public:
   bool isEmpty()
   {
      return (heap.size() <= 0);
   }
   void insert(int val)
   {
      int index = heap.size();
      heap.push_back(val);
      while (index > 0 && val > heap[(index-1)/2])
      {
         heap[index] = heap[(index-1)/2];
         index = (index-1)/2;
      }
      heap[index] = val;
   }
   int extract()
   {
      int val = heap[0];
      heap[0] = heap[heap.size()-1];
      heap.pop_back();
      if (!isEmpty()) downwards(0);
      return val;
   }
   int top()
   {
      return heap[0];
   }
   int size()
   {
      return heap.size();
   }
};

class Line
{
private:
   float med;
   HeapMax hmx;
   HeapMin hmn;

public:
   Line() : med(0){} //inicializar la mediana en cero
   void insert(float val)
   {
      int mxs = hmx.size(), mns = hmn.size();
      if (mxs>mns)
      {
         if (val<med)
         {
            hmn.insert(hmx.extract());
            hmx.insert(val);
         }
         else hmn.insert(val);
         med = (float)(hmn.top()+hmx.top())/2;
      }
      else if (mxs<mns)
      {
         if (val>med)
         {
            hmx.insert(hmn.extract());
            hmn.insert(val);
         }
         else hmx.insert(val);
         med = (float)(hmn.top()+hmx.top())/2;
      }
      else
      {
         if (val<med)
         {
            hmx.insert(val);
            med = hmx.top();
         }
         else
         {
            hmn.insert(val);
            med = hmn.top();
         }
      }
   }
   float getMed()
   {
      return med;
   }
};

void getMeds(int n, vector<int> nums, vector<float> &medians)
{
   Line ln;
   for (int i = 0; i<n; i++)
   {
      ln.insert(nums[i]);
      switch(i)
      {           //Las 10 posiciones que seleccioné para las medianas a mostrar (-1 porque i empieza en cero)
         case 2:
         case 4:
         case 9:
         case 49:
         case 99:
         case N/5 - 1:
         case N/3 - 1:
         case N/2 - 1:
         case 3*(N/4) - 1:
         case N - 1:
            medians.push_back(ln.getMed());
            break;
      }
   }
}

int main()
{
   vector<int> nums;
   vector<float> medians;
   int tmp;
   int n;
   const int maxshow = 50;
   const int nshowpos = 10;
   int showpos[] = {3,5,10,50,100,N/5,N/3,N/2,3*(N/4),N};

   while (cin>>tmp) nums.push_back(tmp);
   n = nums.size();
   cout<<endl<<"N = "<<n<<endl;
   if (n>maxshow) cout<<"Primeros "<<maxshow<<" numeros:"<<endl;
   for (int i = 0; i<min(maxshow,n); i++) cout<<nums[i]<<' ';

   auto start = high_resolution_clock::now();
   getMeds(n,nums,medians);
   auto stop = high_resolution_clock::now();
   auto duration = duration_cast<milliseconds>(stop - start);

   for (int i = 0; i<nshowpos; i++)
      cout<<endl<<"Mediana en insercion no. "<<showpos[i]<<": "<<medians[i];

   cout<<endl<<"Duracion: "<<duration.count()<<" millisegundos"<<endl;

   return 0;
}
