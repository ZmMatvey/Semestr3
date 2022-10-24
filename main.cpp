#include <iostream>
#include "Matrix.h"
using namespace std;

int main()
{
    Matrix A = Matrix(4, 2);
    A.set_fill();
    Matrix B = Matrix(2, 4);
    B.set_fill();
    Matrix C = A*B; //rg(C) <= min(rg(A);rg(B))< 4 -> det(C) = 0;
    cout<<det(C)<<endl;
    cout<<rg(C);
    return 0;
}
