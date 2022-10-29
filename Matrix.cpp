#include <iostream>
#include <stdexcept>
#include "Matrix.h"

Matrix::Matrix (unsigned int m, unsigned int n): m(m), n(n) {
    void* memory = operator new (sizeof(Vector) * m);
    V = (Vector*)memory;
    for (auto begin = V, end = V + m; begin != end; ++begin) {
        new (begin) Vector(n);
    }
    if (n < 6)
    R = 10000000;
    else
    if (n < 11)
    R = 1000000;
    else
    if (n < 21)
    R = 100000;
    else
    if (n < 41)
    R = 10000;
    else
    if (n < 76)
    R = 1000;
    else
    R = 100;
}

Matrix::Matrix(const Matrix& B): Matrix(B.m, B.n)  {
    int m = this->m;
    for (int i = 0; i < m; i++) {
        V[i] = B.V[i];
    }
}

Matrix::Matrix(Matrix&& B): m(B.m), n(B.n), R(B.R), V(B.V) {
    B.m = 0;
    B.V = NULL;
}

int Matrix::get_m()const {
    return m;
}

int Matrix::get_n()const {
    return n;
}

int Matrix::get_R()const {
    return R;
}

Vector* Matrix::get_V() {
    return V;
}

void Matrix::set_fill() {
    int m = this->m;
    for (int i = 0; i < m; i++) {
        V[i].set_fill();
    }
    std::cout<<'\n';
}

void Matrix::set_fill(Vector* X) {
    int m = this->m;
    for (int i = 0; i < m; i++) {
        V[i] = X[i];
    }
}

void Matrix::cout_Matrix() {
    int m = this->m;
    for (int i = 0; i < m; i++) {
        V[i].cout_Vector();
    }
    std::cout<<'\n';
}

void Matrix::stringij(unsigned int i, unsigned int j) {
    if (i != j) {
        std::swap(V[i], V[j]);
    }
}

void Matrix::columnij(unsigned int i, unsigned int j) {
    if (i != j) {
        int m = this->m;
        double c;
        for (int t = 0; t < m; t++) {
            c = V[t][i];
            V[t][i] = V[t][j];
            V[t][j] = c;
        }
    }
}

Matrix Matrix::T() {
    int m = this->m;
    int n = this->n;
    Matrix X = Matrix(n, m);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            X.V[j][i] = V[i][j];
        }
    }
    return X;
}

Matrix Matrix::inverse() {
    if(det(*this) == 0) {
        throw(std::logic_error("det(Matrix) = 0, not inverse"));
    }
    int n = this->n;
    Matrix X = E(n);
    Matrix A = *this;
    for (int j = 0; j < n; j++) {
        int i = j;
        while (i < n && A.V[i][j] == 0) {
            i++;
        }
        X.stringij(i, j);
        A.stringij(i, j);
        X.V[j] = X.V[j]/A.V[j][j];
        A.V[j] = A.V[j]/A.V[j][j];
        i++;
        while (i < n) {
            X.V[i] = X.V[i] - A.V[i][j] * X.V[j];
            A.V[i] = A.V[i] - A.V[i][j] * A.V[j];
            i++;
        }
    }
    for (int j = n - 1; j > 0; j--) {
        int i = j - 1;
        while (i >= 0) {
            X.V[i] = X.V[i] - A.V[i][j] * X.V[j];
            i--;
        }
    }
    return X;
}

double Matrix::xi(double x) {
    if (n != m) {
        throw(std::logic_error("the matrix has no characteristic polynomial"));
    }
    return det((*this) - E(n) * x);
}

Matrix& Matrix::operator= (const Matrix& B) {
    int m = this->m;
    int n = this->n;
    if (m != B.m || n != B.n) {
        throw(std::logic_error("= not correct, the sizes do not match"));
    }
    if (this == &B) {
        return *this;
    }
    for (int i = 0; i < m; i++) {
        V[i] = B.V[i];
    }
    return *this;
}

Matrix& Matrix::operator= (Matrix&& B) {
    std::swap(m, B.m);
    std::swap(n, B.n);
    std::swap(R, B.R);
    std::swap(V, B.V);
    return *this;
}

Vector& Matrix::operator[] (unsigned int i) {
    return V[i];
}

Matrix Matrix::operator+ (const Matrix& B) {
    int m = this->m;
    int n = this->n;
    if (m != B.m && n != B.n) {
        throw(std::logic_error("+ not correct, the sizes do not match"));
    }
    Matrix C = Matrix(m, n);
    for (int i = 0; i < m; i++) {
        C.V[i] = V[i] + B.V[i];
    }
    return C;
}

Matrix Matrix::operator- () {
    return *this * (-1);
}

Matrix Matrix::operator- (const Matrix& B) {
    int m = this->m;
    int n = this->n;
    if (m != B.m && n != B.n) {
        throw(std::logic_error("- not correct, the sizes do not match"));
    }
    Matrix C = Matrix(m, n);
    for (int i = 0; i < m; i++) {
        C.V[i] = V[i] - B.V[i];
    }
    return C;
}

Vector Matrix::operator* (Vector& b) {
    int m = this->m;
    int n = this->n;
    if (b.get_N() != n) {
        throw(std::logic_error("Matrix*Vector not correct, the sizes do not match"));
    }
    Vector t = o(m);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            t[i] = t[i] + V[i][j]*b[j];
        }
    }
    return t;
}

Matrix Matrix::operator* (double a) {
    int m = this->m;
    Matrix C = Matrix(m, n);
    for (int i = 0; i < m; i++) {
        C.V[i] = a * V[i];
    }
    return C;
}

Matrix Matrix::operator* (Matrix& B) {
    int m = this->m;
    int n = this->n;
    int m1 = B.m;
    int n1 = B.n;
    if (n != m1) {
        throw(std::logic_error("Matrix*Matrix not correct, the sizes do not match"));
    }
    Matrix T = Matrix(m, n1);
    for (int i = 0; i < m; i++) {
        T.V[i] = V[i] * B;
    }
    return T;
}

Matrix Matrix::operator/ (double a) {
    return *this * (1.0/a);
}

Matrix Matrix::operator^ (const int n) {
    if (m != n) {
        throw(std::logic_error("Matrix^N not correct, the sizes do not match"));
    }
    Matrix C = *this;
    if (n < 0) {
        Matrix B = C.inverse();
        C = B;
        for (int i = n + 1; i < 0; i++) {
            C = C*B;
        }
        return C;
    }
    if (n == 0) {
        return E(n);
    }
    Matrix B = C;
    for (int i = n - 1; i > 0; i--) {
        C = C*B;
    }
    return C;
}

bool Matrix::operator== (const Matrix& B) {
    int m = this->m;
    bool q = true;
    if (m == B.m) {
        for (int i = 0; i < m; i++) {
            q = q && (V[i] == B.V[i]);
        }
        return q;
    }
    return false;
}

bool Matrix::operator!= (const Matrix& B) {
    return !(*this == B);
}

Matrix::~Matrix() {
    for (auto begin = V, end = V + m; begin != end; ++begin) {
        (begin)->~Vector();
    }
    operator delete(V);
}

Vector operator* (Vector& a, Matrix& B) {
    int N = a.get_N();
    int m = B.get_m();
    int n = B.get_n();
    if (N != m) {
        throw(std::logic_error("Vector*Matrix not correct, the sizes do not match"));
    }
    Vector t = o(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            t[i] = t[i] + a[j] * B[j][i];
        }
    }
    return t;
}

Matrix operator* (double a, Matrix& B) {
    return B * a;
}

Matrix E(unsigned int n) {
    Matrix A = Matrix(n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                A[i][j] = 1;
            }
            else {
                A[i][j] = 0;
            }
        }
    }
    return A;
}

Matrix O(unsigned int m, unsigned int n) {
    Matrix A = Matrix(m, n);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            A[i][j] = 0;
        }
    }
    return A;
}

double tr(Matrix& A) {
    int n = A.get_n();
    int m = A.get_m();
    if (n != m) {
        throw(std::logic_error("tr(Matrix) not correct, the sizes do not match"));
    }
    double x = 0;
    for (int i = 0; i < n; i++) {
        x = x + A[i][i];
    }
    return x;
}

double det(Matrix A) {
    int n = A.get_n();
    int m = A.get_m();
    int R = A.get_R();
    double x = 1;
    if (n == m) {
        for (int j = 0; j < n; j++) {
            int i = j;
            while (i < n && (int)(A[i][j]*R)/10 == 0) {
                i++;
            }
            if (i == n) {
                return 0;
            }
            if (i != j) {
                A.stringij(i, j);
                x = x * (-1);
            }
            x = x * A[j][j];
            A[j] = A[j]/A[j][j];
            i++;
            while (i < n) {
                A[i] = A[i] - A[i][j]* A[j];
                i++;
            }
        }
        return x;
    }
    return 0;
}

int rg(Matrix A) {
    int x = 0;
    int n = A.get_n();
    int m = A.get_m();
    int R = A.get_R();
    for (int j = 0; j < n; j++) {
        int i = x;
        while (i < m && (int)(A[i][j]*R)/10 == 0) {
            i++;
        }
        if (i < m) {
            A.stringij(i, x);
            A[x] = A[x]/A[x][j];
            i++ ;
            while (i < m) {
                A[i] = A[i] - A[i][j]* A[x];
                i++;
            }
            x++;
        }
    }
    return x;
}

Matrix SOL(Matrix& A, Vector& b) {
    int N = b.get_N();
    int n = A.get_n();
    int m = A.get_m();
    if(N != m) {
        throw(std::logic_error("SOL not correct, the sizes do not match"));
    }
    Matrix B = Matrix(m,n+1);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            B[i][j] = A[i][j];
        }
        B[i][n] = b[i];
    }
    int k = rg(A);
    int g = rg(B);
    if (k != g) {
        throw(std::logic_error("SOL not correct, rg(A) != rg(A,b)"));
    }
    int x = 0;
    int j = 0;
    Vector c = Vector(k);
    while (x != k) {
        int i = x;
        while (i < m && B[i][j] == 0) {
            i++;
        }
        if (i < m) {
            B.stringij(i, x);
            B[x] = B[x]/B[x][j];
            i++;
            while (i < m) {
                B[i] = B[i] - B[i][j]* B[x];
                i++;
            }
            for (i = 0; i < x; i++) {
                B[i] = B[i] - B[i][j]* B[x];
            }
            c[x] = j;
            x++;
        }
        j++;
    }
    for (int i = 0; i < k; i++) {
        B.columnij(i, c[i]);
    }
    int p = n-k+1;
    Matrix F = Matrix(n, p);
    for (int i = 0; i < n; i++) {
        if (i < k) {
            F[i][0] = B[i][n];
        }
        else {
            F[i][0] = 0;
        }
    }
    for (int j = 1; j < p; j++) {
        for (int i = 0; i < k; i++) {
            F[i][j] = -B[i][j-1+k];
        }
        for (int i = k; i < n; i++) {
            if (j-1 == i-k) {
                F[i][j] = 1;
            }
            else {
                F[i][j] = 0;
            }
        }
    }
    for (int i = k-1; i >=0; i--) {
        F.stringij(i, c[i]);
    }
    return F;
}
