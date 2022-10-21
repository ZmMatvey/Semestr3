#include <iostream>
#include <assert.h>
#include "Matrix.h"

Matrix::Matrix (int m, int n): m(m), n(n) {
    void * memory = operator new (sizeof(Vector) * m);
    V = (Vector*)memory;
    for (auto begin = V, end = V + m; begin != end; ++begin)
    new (begin) Vector(n);
    
}

Matrix::Matrix(const Matrix& B): Matrix(B.m, B.n)  {
    for (int i = 0; i < m; i++) {
        V[i] = B.V[i];
    }
}

Matrix::Matrix(Matrix&& B): m(B.m), n(B.n), V(B.V) {}

int Matrix::GetM_m() {
    return m;
}

int Matrix::GetM_n() {
    return n;
}

void Matrix::SetM_fill() {
    for (int i = 0; i < m; i++) {
        V[i].Set_fill();
    }
}

void Matrix::SetM_fill(Vector* X) {
    for (int i = 0; i < m; i++) {
        V[i] = X[i];
    }
}

void Matrix::Cout_Matrix() {
    for (int i = 0; i < m; i++) {
        V[i].Cout_Vector();
    }
    std::cout<<'\n';
}

void Matrix::stringij(int i, int j) {
    if (i != j) {
        std::swap(V[i], V[j]);
    }
}

void Matrix::columnij(int i, int j) {
    if (i != j) {
        double c;
        for (int t = 0; t < m; i++) {
            c = V[t][i];
            V[t][i] = V[t][j];
            V[t][j] = c;
        }
    }
}

Matrix Matrix::T() {
    Matrix X = Matrix(n, m);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            X[j][i] = V[i][j];
        }
    }
    return X;
}

Matrix Matrix::inverse() {
    assert(det(*this) != 0);
    Matrix X = E(n);
    Matrix A = Matrix(n, n);
    A = *this;
    for (int j = 0; j < n; j++) {
        int i = j;
        while (i < n && A[i][j] == 0) {
            i++;
        }
        X.stringij(i, j);
        A.stringij(i, j);
        X[j] = X[j]/A[j][j];
        A[j] = A[j]/A[j][j];
        i++;
        while (i < n) {
            X[i] = X[i] - A[i][j]* X[j];
            A[i] = A[i] - A[i][j]* A[j];
            i++;
        }
    }
    for (int j = n - 1; j > 0; j--) {
        int i = j - 1;
        while (i >= 0) {
            X[i] = X[i] - A[i][j]*X[j];
            i--;
        }
    }
    return X;
}

double Matrix::xi(double x) {
    assert (n == m);
    return det((*this) - x*E(n));
}

Matrix& Matrix::operator= (const Matrix& B) {
    assert (m == B.m && n == B.n);
    if (this == &B) {
        return *this;
    }
    for (int i = 0; i < m; i++) {
        V[i] = B.V[i];
    }
    return *this;
}

Matrix& Matrix::operator= (Matrix&& B) {
    this->m = B.m;
    this->n = B.n;
    this->V = B.V;
    return *this;
}

Matrix::~Matrix () {
    for (auto begin = V, end = V + m; begin != end; ++begin) {
        (begin)->~Vector();
    }
    delete V;
}

Vector& Matrix::operator[] (int i) {
    return V[i];
}

Matrix E(int n) {
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

Matrix O(int m, int n) {
    Matrix A = Matrix(m, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            A[i][j] = 0;
        }
    }
    return A;
}

double tr(Matrix A) {
    int n = A.GetM_n();
    int m = A.GetM_m();
    assert (n == m);
    double x = 0;
    for (int i = 0; i < n; i++) {
        x = x + A[i][i];
    }
    return x;
}

double det(Matrix A) {
    int n = A.GetM_n();
    int m = A.GetM_m();
    double x = 1;
    if (n == m) {
        for (int j = 0; j < n; j++) {
            int i = j;
            while (i < n && A[i][j] == 0) {
                i++;
            }
            if (i == n) {
                return 0;
            }
            if (i != j) {
                A.stringij(i, j);
                x = x*(-1);
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
    int n = A.GetM_n();
    int m = A.GetM_m();
    for (int j = 0; j < n; j++) {
        int i = x;
        while (i < m && A[i][j] == 0) {
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

Matrix SOL(Matrix A, Vector b) {
    int n = A.GetM_n();
    int m = A.GetM_m();
    assert(b.Get_N() == m);
    Matrix B = Matrix(m,n+1);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            B[i][j] = A[i][j];
        }
        B[i][n+1] = b[i];
    }
    int k = rg(A);
    assert (k == rg(B));
    int x = 0;
    int j = 0;
    Vector c = Vector(k);
    double t;
    while (x != k) {
        int i = x;
        while (i < m && A[i][j] == 0) {
            i++;
        }
        if (i < m) {
            t = b[i];
            b[i] = b[x];
            b[x] = t;
            A.stringij(i, x);
            b[x] = b[x]/A[x][j];
            A[x] = A[x]/A[x][j];
            i++;
            while (i < m) {
                b[x] = b[i] - A[i][j]* b[x];
                A[i] = A[i] - A[i][j]* A[x];
                i++;
            }
            c[x] = j;
            x++;
        }
        j++;
    }
    for (int i = 0; i < k; i++) {
        A.columnij(i, c[i]);
    }
    int p = n-k+1;
    Matrix F = Matrix(n, p);
    for (int i = 0; i < n; i++) {
        if (i < k) {
            F[i][0] = b[i];
        }
        else {
            F[i][0] = 0;
        }
    }
    for (int j = 1; j < p; j++) {
        for (int i = 0; i < k; i++) {
            F[i][j] = -A[i][j+k];
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
    for (int i = n-1; i >=0; i--) {
        F.stringij(i, c[i]);
    }
    return F;
}

Matrix operator+ (Matrix A, Matrix B) {
    int x = A.GetM_m();
    int y = B.GetM_m();
    int x1 = A.GetM_n();
    int y1 = B.GetM_n();
    assert (x == y && x1 == y1);
    Matrix C = Matrix(x, x1);
    for (int i = 0; i < x; i++) {
        C[i] = A[i] + B[i];
    }
    return C;
}

Matrix operator- (Matrix A, Matrix B) {
    int x = A.GetM_m();
    int y = B.GetM_m();
    int x1 = A.GetM_n();
    int y1 = B.GetM_n();
    assert (x == y && x1 == y1);
    Matrix C = Matrix(x, x1);
    for (int i = 0; i < x; i++) {
        C[i] = A[i] - B[i];
    }
    return C;
}

bool operator== (Matrix A, Matrix B) {
    int x = A.GetM_m();
    int y = B.GetM_m();
    int x1 = A.GetM_n();
    int y1 = B.GetM_n();
    if (x == y && x1 == y1) {
        bool q = true;
        for (int i = 0; i < x; i++) {
            q = q && (A[i] == B[i]);
        }
        return q;
    }
    return false;
}

Matrix operator* (double a, Matrix B) {
    int x = B.GetM_m();
    for (int i = 0; i < x; i++) {
        B[i] = a*B[i];
    }
    return B;
}

Vector operator* (Vector a, Matrix B) {
    int x = a.Get_N();
    int y = B.GetM_m();
    int z = B.GetM_n();
    assert (x == y);
    Vector t = o(z);
    for (int i = 0; i < z; i++) {
        for (int j = 0; j < y; j++) {
            t[i] = t[i] + a[j]*B[j][i];
        }
    }
    return t;
}

Vector operator* (Matrix A, Vector b) {
    int x = b.Get_N();
    int y = A.GetM_n();
    int z = A.GetM_m();
    assert (x == y);
    Vector t = o(z);
    for (int i = 0; i < z; i++) {
        for (int j = 0; j < y; j++) {
            t[i] = t[i] + A[i][j]*b[j];
        }
    }
    return t;
}

Matrix operator* (Matrix A, Matrix B) {
    int x = A.GetM_m();
    int y = A.GetM_n();
    int x1 = B.GetM_m();
    int y1 = B.GetM_n();
    assert (y == x1);
    Matrix T = Matrix(x, y1);
    for (int i = 0; i < x; i++) {
        T[i] = A[i]*B;
    }
    return T;
}

Matrix operator/ (Matrix B, double a) {
    return (1.0/a)*B;
}

Matrix operator^ (Matrix A, int n) {
    assert (A.GetM_m() == A.GetM_n());
    if (n < 0) {
        Matrix B = A.inverse();
        A = B;
        for (int i = n + 1; i < 0; i++) {
            A = A*B;
        }
        return A;
    }
    if (n == 0) {
        return E(A.GetM_n());
    }
    Matrix B = A;
    for (int i = n - 1; i > 0; i--) {
        A = A*B;
    }
    return A;
}
