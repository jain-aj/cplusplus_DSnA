#ifndef OPTIMALBST_H
#define OPTIMALBST_H 
#include <string>
using namespace std;

class OptimalBST {
 public:
   OptimalBST(size_t);
   ~OptimalBST();

   float optimize(const float* const, const float* const, size_t);
   string printTree(size_t, size_t, size_t) const;
   void drawTree(size_t, size_t, size_t, string, bool) const;

 private:
   float* _costMatrix;
   size_t* _indexMatrix;
   float *_cum_p, *_cum_q;
};

#endif
