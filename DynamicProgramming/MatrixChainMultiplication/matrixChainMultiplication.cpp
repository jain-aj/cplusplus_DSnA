#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <limits>
#include <sstream>
#include "matrixChainMultiplication.h"
using namespace std;

MatrixChainMultiplication::MatrixChainMultiplication(size_t N) {
   _matrixNum = 0;
   _matrixSpace = N * N * sizeof(int);
   _costMatrix = (int*) malloc(_matrixSpace);
   _indexMatrix = (int*) malloc(_matrixSpace);
   if (!_costMatrix || !_indexMatrix ) {
      cerr<<"Memory allocation error"<<endl;
      if (_costMatrix) free(_costMatrix);
      if (_indexMatrix) free(_indexMatrix);
      exit(1);
   }
}

MatrixChainMultiplication::~MatrixChainMultiplication() {
   free(_costMatrix);
   free(_indexMatrix);
}

int MatrixChainMultiplication::optimize (
   const matrix* const matrixChain,
   size_t matrixNum
) {
   _matrixNum = matrixNum;
   memset(_costMatrix, 0, _matrixSpace);
   memset(_indexMatrix, 0, _matrixSpace);
  
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
   return _costMatrix[matrixNum - 1];
}

string MatrixChainMultiplication::printOrder(int x, int y) const {
   stringstream ss;
   int index = x * _matrixNum + y; 
   if (x==y) ss<<"A"<<x;
   else if ((x+1)==y) ss<<"(A"<<x<<'A'<<y<<')';
   else {
      ss<<"(";
      ss<<printOrder(x, _indexMatrix[index]);
      ss<<printOrder(_indexMatrix[index] + 1, y);
      ss<<")";
   }
   return ss.str();
}
