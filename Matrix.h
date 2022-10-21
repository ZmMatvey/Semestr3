#include "Vector.h"

class Matrix
{
protected:
int m; //number of strings

int n; //number of columns

Vector* V; //pointer to an array of vector strings

public:

Matrix (int m, int n); //creates a matrix with m - strings, n - columns

Matrix(const Matrix& B); //rule of five - 1 copy constructor

Matrix(Matrix&& B); //rule of five - 2 move constructor

int GetM_m();

int GetM_n();

void SetM_fill(); //filling in the matrix manually

void SetM_fill(Vector* X); //filling the matrix with an array of vectors

void Cout_Matrix(); 

void stringij(int i, int j); //swaps i, j string

void columnij(int i, int j); //swaps i, j columns element by element
//therefore, it is better to use stringij whenever possible, the code will be faster

Matrix T(); //transposed matrix

Matrix inverse(); //inverse matrix

double xi(double x); //the characteristic polynomial of x

Matrix& operator= (const Matrix& B); //rule of five - 3 assignment operator

Matrix& operator= (Matrix&& B); // rule of five - 4 move operator

Vector& operator[] (int i);

~Matrix (); //rule of five - 5 destructor

};

Matrix E(int n); 

Matrix O(int m, int n);

double tr(Matrix A);

double det(Matrix A);

int rg(Matrix A);

Matrix SOL(Matrix A, Vector b); //solutions of a linear matrix equation of the form A*x=b 
//returns the matrix 1 column - a partial solution, the rest - the basis of solutions of a homogeneous equation

Matrix operator+ (Matrix A, Matrix B); //A+B

Matrix operator- (Matrix A, Matrix B); //A-B

bool operator== (Matrix A, Matrix B); //A == B

Matrix operator* (double a, Matrix B); //multiplication of matrix b by scalar a

Vector operator* (Vector a, Matrix B); //multiplying a matrix by a string vector

Vector operator* (Matrix A, Vector b); //multiplying a matrix by a column vector

Matrix operator* (Matrix A, Matrix B); // A*B

Matrix operator/ (Matrix B, double a); // B/a

Matrix operator^ (Matrix A, int n); //A^n exponentiation of the matrix
