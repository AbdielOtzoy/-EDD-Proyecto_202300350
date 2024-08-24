#include "./matrix/headers/matrix.h"

int main(int argc, char const *argv[])
{
  Matrix mymatrix;
  // value = 1 - relacion de amistad
  mymatrix.insert("marta", "john", 1);
  mymatrix.insert("marta", "jose", 1);
  mymatrix.insert("luis", "jose", 1);

  mymatrix.create_dot();
  return 0;
}
