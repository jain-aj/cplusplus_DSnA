#include <cstdio>
#include <iostream>
#include <sstream>
#include <limits>
#include <cstdlib>
#include <string>
#include "optimalBST.h"
using namespace std;

OptimalBST::OptimalBST(size_t n) {
   _costMatrix = (float*) malloc(n * n * sizeof(float));
   _indexMatrix = (size_t*) malloc(n * n * sizeof(size_t));
   _cum_p = (float*) malloc(n * sizeof(float));
   _cum_q = (float*) malloc((n + 1) * sizeof(float));
   if (!_costMatrix || !_indexMatrix || !_cum_p || !_cum_q) {
      cerr<<"Memory allocation failed"<<endl;
      exit(1);
   }
}

OptimalBST::~OptimalBST() {
   free(_costMatrix);
   free(_indexMatrix);
   free(_cum_p);
   free(_cum_q);
}

float OptimalBST::optimize(
   const float* const p, 
   const float* const q, 
   size_t n
) {
   _cum_p[0] = p[0];
   _cum_q[0] = q[0];
   for (size_t i=1; i<n; i++) {
      _cum_p[i] = _cum_p[i - 1] + p[i];
      _cum_q[i] = _cum_q[i - 1] + q[i];
   }
   _cum_q[n] = _cum_q[n - 1] + q[n];

   for (size_t i=0; i<n; i++) {
      size_t x = 0, y = i;
      for (y; y<n; x++, y++) {
         size_t index = x * n + y;
         if (x==y) _costMatrix[index] = p[x] + 2 * (q[x] + q[x + 1]);
         else {
            float min = numeric_limits<float>::max();
            float sum = _cum_p[y] - _cum_p[x] + p[x] + _cum_q[y+1] - _cum_q[x] + q[x];
            for (size_t s=x; s<=y; s++) {
               static float cost = 0.0;
               if (s==x) cost = sum + q[s] + _costMatrix[index + n];
               else if (s==y) cost = sum + q[s+1] + _costMatrix[index - 1]; 
               else cost = sum + _costMatrix[index - y + s - 1] + _costMatrix[index + (s + 1 - x) * n];
               if (cost < min) {
                  min = cost;
                  _costMatrix[index] = cost;
                  _indexMatrix[index] = s;
               } 
            }
         }
      }
   }
   return _costMatrix[n - 1];   
}

string OptimalBST::printTree(
   size_t x, 
   size_t y, 
   size_t n
) const {
   stringstream ss;
   size_t index = x * n + y;
   if (x==y) {
      ss<<" "<<x;
   }
   else {
      ss<<" "<<_indexMatrix[index];
      if (_indexMatrix[index]!=x) {
         ss<<printTree(x, _indexMatrix[index] - 1, n);
      }
      if (_indexMatrix[index]!=y) {
         ss<<printTree(_indexMatrix[index] + 1, y, n);
      }
   }
   return ss.str();
}

void OptimalBST::drawTree(
   size_t x, 
   size_t y, 
   size_t n, 
   string indent, 
   bool isRight
) const {
   size_t index = x * n + y;

   if (x==y) {
      cout<<indent;
      printf("+-p%ld\n", x);
   }
   else {
      string nextIndent = indent;
      if (_indexMatrix[index]!=y) {
         if (!isRight && indent.size()) nextIndent = indent + "|   ";
         else nextIndent = indent + "    ";
         drawTree(_indexMatrix[index] + 1, y, n, nextIndent, true);
      }
      cout<<indent;
      printf("+-p%ld\n", _indexMatrix[index]);
      if (_indexMatrix[index]!=x) {
         if (isRight && indent.size()) nextIndent = indent + "|   ";
         else nextIndent = indent + "    ";
         drawTree(x, _indexMatrix[index] - 1, n, nextIndent, false);
      }
   }
   return;
}
