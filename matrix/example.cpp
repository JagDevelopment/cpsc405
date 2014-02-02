//
// Example of the use of Vector2D classes
// 
// 
// Donald H. House
// 8/25/2010
// School of Computing
// Clemson University
//

#include "Vector.h"

using namespace std;

int main(){
  Vector2d a, c, d;

  a.set(2, 5);
  cout << "a = " << a << ", ||a|| = " << a.norm() << ", ua = " << a.normalize() << '\n';
  
  Vector2d b(1, -1);
  double bnorm = b.norm();
  Vector2d ub = b.normalize();
  cout << "b = " << b << ", ||b|| = " << bnorm << ", ub = " << ub << '\n';
  
  c = a + b;
  cout << "c = a + b = " << c << '\n';
  
  d = a - b;
  cout << "d = a - b = " << d << '\n';
  
  cout << "(c + d) / 2 = " << (c + d) / 2 << '\n';
  

  Vector2d ab = (a * ub) * ub;
  cout << "ab = " << ab << ", ||ab|| = " << ab.norm() << ", uab = " << ab.normalize() << '\n';
  
  Vector2d aperpb = a - ab;
  cout << "aperpb = " << aperpb << ", ||aperpb|| = " << aperpb.norm() << ", uaperpb = " << aperpb.normalize() << '\n';
  
  Vector2d arecons = ab + aperpb;
  cout << "arecons = " << arecons << ", ||arecons|| = " << arecons.norm() << ", uarecons = " << arecons.normalize() << endl;
  
  return 0;
}
