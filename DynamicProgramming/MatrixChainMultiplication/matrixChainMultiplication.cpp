#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <limits>
#include "matrixChainMultiplication.h"
using namespace std;

MatrixChainMultiplication(size_t N) {
   _matrixSpace = N * N * sizeof(int);
   _costMatrix = (int*) malloc(matrixSpace);
   _indexMatrix = (int*) malloc(matrixSpace);
   if (!costMatrix || !indexMatrix ) {
      cerr<<"Memory allocation error"<<endl;
      if (_costMatrix) free(_costMatrix);
      if (_indexMatrix) free(_indexMatrix);
      return 0;
   }
}

~MatrixChainMultiplication() {
   free(_costMatrix);
   free(_indexMatrix);
}

int MatrixChainMultiplication::matrixChainMultiplication (
   const matrix* const matrixChain,
   size_t matrixNum
) {
   _maxtrixNum = matrixNum;
   memset(costMatrix, 0, matrixSpace);
   memset(indexMatrix, 0, matrixSpace);
  
   for (size_t i=0; i < _matrixNum; i++) {
      size_t x = 0, y = i;
      for (y; y < _matrixNum; x++, y++) {
         size_t index = x * _matrixNum + y;
         if (x==y) _costMatrix[index] = 0;
         else if ((x+1)==y) {
            _costMatrix[index] = matrixChain[x].first * matrixChain[x].second * matrixChain[y].second;
         }
         else {
            int min = numeric_limits<int>::max();
            for (int s=x; s<y; s++) {
               int cost = 0;
               if (x==s) cost = matrixChain[x].first * matrixChain[x].second * \
                                matrixChain[y].second + _costMatrix[index + _matrixNum];
               else if (s==y-1) cost = matrixChain[x].first * matrixChain[y].first * \
                                matrixChain[y].second + _costMatrix[index - 1];
               else cost = matrixChain[x].first * matrixChain[s].second * \
                           matrixChain[y].second + _costMatrix[index - y + s] + \
                           _costMatrix[index + (s + 1 - x) * _matrixNum];
               if (cost < min) {
                  _costMatrix[index] = cost;
                  _indexMatrix[index] = s;
                  min = cost;
               }               
            }
         }
      }
   }

   printOrder(indexMatrix, 0, matrixNum - 1, matrixNum);
   cout<<endl;
   
   int minimumCost = costMatrix[matrixNum - 1];

   return minimumCost;
}

void printOrder(const int* const indexMatrix, int x, int y, size_t matrixNum) {
   int index = x * matrixNum + y; 
   if (x==y) cout<<"A"<<x;
   else if ((x+1)==y) cout<<"(A"<<x<<'A'<<y<<')';
   else {
      cout<<"(";
      printOrder(indexMatrix, x, indexMatrix[index], matrixNum);
      printOrder(indexMatrix, indexMatrix[index] + 1, y, matrixNum);
      cout<<")";
   }
   return;
}

int main(int argc, char** argv) {
   if (argc != 2) return 1;
   int num = 0, matrix_num = 0;

   FILE* in = fopen(argv[1], "r");
   fscanf(in, "%d", &num);
   for (int i=0; i<num; i++) {
      fscanf(in, "%d", &matrix_num);
      vector<matrix> testcase;
      for (int j=0; j<matrix_num; j++) {
         int first = 0, second = 0;
         fscanf(in, "%d,%d", &first, &second);
         testcase.push_back(make_pair(first, second));
      }
      cout<<matrixChainMultiplication(testcase)<<endl;
      testcase.clear();
   }
   fclose(in);
   return 0;
}
