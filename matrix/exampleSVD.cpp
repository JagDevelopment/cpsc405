//
// Example of the use of Matrix and Vector classes
// Showing Singular Value Decomposition of a Matrix
// 
// Donald H. House
// 8/25/2010
// School of Computing
// Clemson University
//

#include "Matrix.h"

using namespace std;

int main(){
  int i;

  Matrix U, V, Winv;
  Vector Wsqr;
  Vector x;

  double bvect[3]={3, 2, 1};  
  Vector b(3, bvect);
  cout << "b "; b.print(); cout << endl;

  double coeff[9]={1, 2, 3, 6, 5, 4, 3, 1, 2};
  Matrix A(3, 3, coeff);
  cout << "A\n"; A.print(); cout << endl;

  Matrix C(3, 3);
  C = A.transpose() * A;
  cout << "C\n"; C.print(); cout << endl;

  C.svd(U, Wsqr, V);
  cout << "U\n"; U.print(); cout << endl;
  cout << "Wsqr "; Wsqr.print(); cout << "\n" << endl;
  cout << "V\n"; V.print(); cout << endl;

  Matrix IU = U.transpose() * U;
  cout << "U^ * U\n"; IU.print(); cout << endl;
  Matrix IV = V.transpose() * V;
  cout << "V^ * V\n"; IV.print(); cout << endl;
 
  Winv = diag(Wsqr);
  for(i = 0; i < 3; i++)
    Winv[i][i] = 1 / Wsqr[i];
  cout << "Winv\n"; Winv.print(); cout << endl;
  
  x = V * Winv * V.transpose() * b;
  cout << "x "; x.print(); cout << "\n" << endl;
  
  x = C.inv() * b;
  cout << "x "; x.print(); cout << "\n" << endl;

  return 0;
}
