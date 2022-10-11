class Matrix
{
private:
unsigned int m; //number of vector strings

unsigned int n; //number of vector columns

public:
Vector* const V; //array of vector strings (Vector)

Matrix (unsigned int m, unsigned int n); //creates an mxn matrix

Matrix(const Matrix& B); //rule of three-1 copy constructor

unsigned int GetM_m();

unsigned int GetM_n();

void SetM_fill(); //filling in the matrix manually

void SetM_fill(Vector* X); //filling the matrix with an array of vectors

void Cout_Matrix(); //matrix output (not finalized, since it outputs lines with a different number of characters crookedly)

void stringij(unsigned int i, unsigned int j); //swaps i, j string

void columnij(unsigned int i, unsigned int j); //swaps i, j column

Matrix T(); //transposed matrix
  
Matrix inverseA(); //inverse matrix

//int* p(); //positive and negative inertia indices

double xi(double x); //the characteristic polynomial of x

Matrix& operator= (const Matrix& B); //rule of three-2 assignment operator
  
~Matrix (); //rule of three-3 destructor
};

Matrix E(unsigned int n); //a unit matrix of size nxn
Matrix O(unsigned int m, unsigned int n); //zero matrix with dimensions mxn
double det(Matrix A); //determinant of the matrix A
double tr(Matrix A); //the trace of the matrix A
//int rg(Matrix A); //matrix rank A
//Matrix SOL(Matrix A);//solution of a linear matrix equation of the form A*x=b
Matrix operator+ (Matrix A, Matrix B); //A+B
Matrix operator- (Matrix A, Matrix B); //A-B
bool operator== (Matrix A, Matrix B); //A == B
Matrix operator* (double a, Matrix B); //a*B
Vector operator* (Vector a, Matrix B); //multiplying a string vector by a matrix
Vector operator* (Matrix A, Vector b); //multiplying a matrix by a column vector
Matrix operator* (Matrix A, Matrix B); //A*B
Matrix operator/ (Matrix B, double a); //B/a
//Matrix operator^ (Matrix A, int n); //A^n exponentiation of the matrix

