#include <utility>
#include <string>
using namespace std;

typedef pair<int, int> matrix;

class MatrixChainMultiplication {
   public:
      MatrixChainMultiplication(size_t): _matrixNum(0);
      ~MatrixChainMultiplication();

      int optimize(const matrix* const, size_t);
      string printOrder(int, int) const;

   private:
      size_t _matrixNum, _matrixSpace;
      int* _costMatrix;
      int* _indexMatrix;
};
