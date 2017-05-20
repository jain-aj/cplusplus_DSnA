#include <utility>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <limits>
using namespace std;

typedef pair<int, int> matrix;

void printOrder(const int* const, int, int, size_t);

int matrixChainMultiplication(const vector<matrix>& matrixChain) {
   size_t matrixNum = matrixChain.size();
   size_t matrixDimension = matrixNum * matrixNum * sizeof(int);
   int* costMatrix = (int*) malloc(matrixDimension);
   int* indexMatrix = (int*) malloc(matrixDimension);
   if (!costMatrix || !indexMatrix ) {
      cerr<<"Memory allocation error"<<endl;
      return 0;
   }

   memset(costMatrix, 0, matrixDimension);
   memset(indexMatrix, 0, matrixDimension);
  
   for (size_t i=0; i < matrixNum; i++) {
      size_t x = 0, y = i;
      for (y; y < matrixNum; x++, y++) {
         size_t index = x * matrixNum + y;
         if (x==y) costMatrix[index] = 0;
         else if ((x+1)==y) {
            costMatrix[index] = matrixChain[x].first * matrixChain[x].second * matrixChain[y].second;
         }
         else {
            int min = numeric_limits<int>::max();
            for (int s=x; s<y; s++) {
               int cost = 0;
               if (x==s) cost = matrixChain[x].first * matrixChain[x].second * \
                                matrixChain[y].second + costMatrix[index + matrixNum];
               else if (s==y-1) cost = matrixChain[x].first * matrixChain[y].first * \
                                matrixChain[y].second + costMatrix[index - 1];
               else cost = matrixChain[x].first * matrixChain[s].second * \
                           matrixChain[y].second + costMatrix[index - y + s] + \
                           costMatrix[index + (s + 1 - x) * matrixNum];
               if (cost < min) {
                  costMatrix[index] = cost;
                  indexMatrix[index] = s;
                  min = cost;
               }               
            }
         }
      }
   }

   printOrder(indexMatrix, 0, matrixNum - 1, matrixNum);
   cout<<endl;
   
   int minimumCost = costMatrix[matrixNum - 1];
   free(costMatrix);
   free(indexMatrix);

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
