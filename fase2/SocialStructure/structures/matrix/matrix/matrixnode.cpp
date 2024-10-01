#include "matrixnode.h"

#include <iostream>
#include <string>
using namespace std;

// row es strng y col es string
MatrixNode::MatrixNode(string row, string col, int value)
{
    this->row = row;
    this->col = col;
    this->value = value;
    this->up = nullptr;
    this->bottom = nullptr;
    this->right = nullptr;
    this->left = nullptr;
}
