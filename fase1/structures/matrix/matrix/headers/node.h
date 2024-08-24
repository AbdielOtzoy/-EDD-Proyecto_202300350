#include <string>
using namespace std;
class MatrixNode
{
private:
  /* data */
public:
  MatrixNode(string row, string col, int value);

  string row;
  string col;
  int value;
  MatrixNode *up;
  MatrixNode *bottom;
  MatrixNode *right;
  MatrixNode *left;
};
