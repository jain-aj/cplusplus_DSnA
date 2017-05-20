#include <cstdio>
#include <iostream>
#include <limits>
#include <cstdlib>
#include <string>
using namespace std;

void printIndex(const size_t* const, size_t, size_t, size_t, string, bool);

float optimalBST(const float* const p, const float* const q, size_t n) {
   float* costMatrix = (float*) malloc(n * n * sizeof(float));
   size_t* indexMatrix = (size_t*) malloc(n * n * sizeof(size_t));
   float* cum_p = (float*) malloc(n * sizeof(float));
   float* cum_q = (float*) malloc((n + 1) * sizeof(float));

   cum_p[0] = p[0];
   cum_q[0] = q[0];
   for (size_t i=1; i<n; i++) {
      cum_p[i] = cum_p[i - 1] + p[i];
      cum_q[i] = cum_q[i - 1] + q[i];
   }
   cum_q[n] = cum_q[n - 1] + q[n];

   for (size_t i=0; i<n; i++) {
      size_t x = 0, y = i;
      for (y; y<n; x++, y++) {
         size_t index = x * n + y;
         if (x==y) costMatrix[index] = p[x] + 2 * (q[x] + q[x + 1]);
         else {
            float min = numeric_limits<float>::max();
            float sum = cum_p[y] - cum_p[x] + p[x] + cum_q[y+1] - cum_q[x] + q[x];
            for (size_t s=x; s<=y; s++) {
               static float cost = 0.0;
               if (s==x) cost = sum + q[s] + costMatrix[index + n];
               else if (s==y) cost = sum + q[s+1] + costMatrix[index - 1]; 
               else cost = sum + costMatrix[index - y + s - 1] + costMatrix[index + (s + 1 - x) * n];
               if (cost < min) {
                  min = cost;
                  costMatrix[index] = cost;
                  indexMatrix[index] = s;
               } 
            }
         }
      }
   }
   printIndex(indexMatrix, 0, n - 1, n, "", false);
   printf("\n"); 

   float minimum = costMatrix[n - 1];   
   free(costMatrix);
   free(indexMatrix);
   free(cum_p);
   free(cum_q);
   return minimum;
}

void printIndex(const size_t* const indexMatrix, size_t x, size_t y, size_t n, string indent, bool isRight) {
   size_t index = x * n + y;

   if (x==y) {
      cout<<indent;
      printf("+-p%ld\n", x);
   }
   else {
      string nextIndent = indent;
      if (indexMatrix[index]!=y) {
         if (!isRight && indent.size()) nextIndent = indent + "|   ";
         else nextIndent = indent + "    ";
         printIndex(indexMatrix, indexMatrix[index] + 1, y, n, nextIndent, true);
      }
      cout<<indent;
      printf("+-p%ld\n", indexMatrix[index]);
      if (indexMatrix[index]!=x) {
         if (isRight && indent.size()) nextIndent = indent + "|   ";
         else nextIndent = indent + "    ";
         printIndex(indexMatrix, x, indexMatrix[index] - 1, n, nextIndent, false);
      }
   }
   return;
}

int main(int argc, char** argv) {
   if (argc!=2) return 1;

   float* p_table = (float*) malloc(1000 * sizeof(float));
   float* q_table = (float*) malloc(1001 * sizeof(float));
   
   FILE* in = fopen(argv[1], "r");
   size_t num = 0, n = 0;
   fscanf(in, "%ld", &num);
   for (size_t i=0; i<num; i++) {
      fscanf(in, "%ld", &n);
      for (size_t j=0; j<n; j++) {
         fscanf(in, "%f", p_table + j);
      }
      for (size_t j=0; j<=n; j++) {
         fscanf(in, "%f", q_table + j);
      }
      printf("%f\n", optimalBST(p_table, q_table, n));
   }

   free(p_table);
   free(q_table);
   fclose(in);
   return 0;
}
