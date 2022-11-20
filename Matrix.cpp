#include <iostream>
#include <stdexcept>
#include <thread>
#include "Matrix.h"

Matrix::Matrix (unsigned int m, unsigned int n): m(m), n(n) {
    void* memory = operator new (sizeof(Vector) * m);
    V = (Vector*)memory;
    for (auto begin = V, end = V + m; begin != end; ++begin) {
        new (begin) Vector(n);
    }
    if (n < 6)
        accuracy = 10000000;
    else
    if (n < 11)
        accuracy = 1000000;
    else
    if (n < 21)
        accuracy = 100000;
    else
    if (n < 41)
        accuracy = 10000;
    else
    if (n < 76)
        accuracy = 1000;
    else
        accuracy = 100;
}

Matrix::Matrix(const Matrix& B): Matrix(B.m, B.n)  {
    int m = this->m;
    for (int i = 0; i < m; i++) {
        V[i] = B.V[i];
    }
}

Matrix::Matrix(Matrix&& B): m(B.m), n(B.n), accuracy(B.accuracy), V(B.V) {
    B.m = 0;
    B.V = NULL;
}

int Matrix::get_m() const {
    return m;
}

int Matrix::get_n() const {
    return n;
}

int Matrix::get_accuracy() const {
    return accuracy;
}

void Matrix::fill_Matrix() {
    int m = this->m;
    for (int i = 0; i < m; i++) {
        V[i].fill_Vector();
    }
    std::cout<<'\n';
}

void Matrix::print_Matrix() const {
    int m = this->m;
    for (int i = 0; i < m; i++) {
        V[i].print_Vector();
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

Matrix Matrix::T() const {
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

Matrix Matrix::inverse() const {
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
        X.V[j] /= A.V[j][j];
        A.V[j] /= A.V[j][j];
        i++;
        while (i < n) {
            X.V[i] -= A.V[i][j] * X.V[j];
            A.V[i] -= A.V[i][j] * A.V[j];
            i++;
        }
    }
    for (int j = n - 1; j > 0; j--) {
        int i = j - 1;
        while (i >= 0) {
            X.V[i] -= A.V[i][j] * X.V[j];
            i--;
        }
    }
    return X;
}

double Matrix::xi(double x) const {
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
    std::swap(accuracy, B.accuracy);
    std::swap(V, B.V);
    return *this;
}

Matrix& Matrix::operator+= (const Matrix& B) {
    if (m != B.m && n != B.n) {
        throw(std::logic_error("+= not correct, the sizes do not match"));
    }
    for (int i = 0; i < m; i++) {
        V[i] += B.V[i];
    }
    return *this;
}

Matrix& Matrix::operator-= (const Matrix& B) {
    if (m != B.m && n != B.n) {
        throw(std::logic_error("-= not correct, the sizes do not match"));
    }
    for (int i = 0; i < m; i++) {
        V[i] -= B.V[i];
    }
    return *this;
}

Matrix& Matrix::operator*= (double a) {
    for (int i = 0; i < m; i++) {
        V[i] *= a;
    }
    return *this;
}

Matrix& Matrix::operator/= (double a) {
    for (int i = 0; i < m; i++) {
        V[i] /= a;
    }
    return *this;
}

Vector& Matrix::operator[] (unsigned int i) {
    return V[i];
}

Matrix Matrix::operator+ (const Matrix& B) const {
    int m = this->m;
    int n = this->n;
    if (m != B.m && n != B.n) {
        throw(std::logic_error("+ not correct, the sizes do not match"));
    }
    Matrix C = Matrix(m, n);
    for (int i = 0; i < m; i++) {
        C.V[i] = V[i];
        C.V[i] += B.V[i];
    }
    return C;
}

Matrix Matrix::operator- () const {
    return *this * (-1);
}

Matrix Matrix::operator- (const Matrix& B) const {
    int m = this->m;
    int n = this->n;
    if (m != B.m && n != B.n) {
        throw(std::logic_error("- not correct, the sizes do not match"));
    }
    Matrix C = Matrix(m, n);
    for (int i = 0; i < m; i++) {
        C.V[i] = V[i];
        C.V[i] -= B.V[i];
    }
    return C;
}

Vector Matrix::operator* (Vector& b) const {
    int N = b.get_size();
    if (N != n) {
        throw(std::logic_error("Matrix*Vector not correct, the sizes do not match"));
    }
    Matrix B = Matrix(n, 1);
    for (int i = 0; i < n; i++) {
        B[i][0] = b[i];
    }
    Matrix C = (*this * B).T();
    return C[0];
}

Matrix Matrix::operator* (double a) const {
    int m = this->m;
    Matrix C = Matrix(m, n);
    for (int i = 0; i < m; i++) {
        C.V[i] = V[i];
        C.V[i] *= a;
    }
    return C;
}

Matrix Matrix::operator* (const Matrix& B) const {
    int m = this->m;
    int n = this->n;
    int m1 = B.m;
    int n1 = B.n;
    if (n != m1) {
        throw(std::logic_error("Matrix*Matrix not correct, the sizes do not match"));
    }
    Matrix T = O(m, n1);
    if (m > 3) {
        if (m * n * n1 > 500000) {
            std::thread a = std::thread([m, n, n1, &T, &B, this]() {
                for (int i = 0; i < m / 4; i++) {
                    for (int j = 0; j < n1; j++) {
                        for (int k = 0; k < n; k++) {
                            T.V[i][j] += V[i][k] * B.V[k][j];
                        }
                    }
                }
                });
            std::thread b = std::thread([m, n, n1, &T, &B, this]() {
                for (int i = m / 4; i < m / 2; i++) {
                    for (int j = 0; j < n1; j++) {
                        for (int k = 0; k < n; k++) {
                            T.V[i][j] += V[i][k] * B.V[k][j];
                        }
                    }
                }
                });
            std::thread c = std::thread([m, n, n1, &T, &B, this]() {
                for (int i = m / 2; i < 3 * m / 4; i++) {
                    for (int j = 0; j < n1; j++) {
                        for (int k = 0; k < n; k++) {
                            T.V[i][j] += V[i][k] * B.V[k][j];
                        }
                    }
                }
                });
            std::thread d = std::thread([m, n, n1, &T, &B, this]() {
                for (int i = 3 * m / 4; i < m; i++) {
                    for (int j = 0; j < n1; j++) {
                        for (int k = 0; k < n; k++) {
                            T.V[i][j] += V[i][k] * B.V[k][j];
                        }
                    }
                }
                });
            a.join();
            b.join();
            c.join();
            d.join();
        }
        else {
            for (int i = 0; i < m; i++) {
                for (int j = 0; j < n1; j++) {
                    for (int k = 0; k < n; k++) {
                       T.V[i][j] += V[i][k] * B.V[k][j];
                    }
                }
            }
        }
    }
    else {
        if (n1 > 3) {
            if (m * n * n1 > 500000) {
                std::thread a = std::thread([m, n, n1, &T, &B, this]() {
                    for (int i = 0; i < m; i++) {
                        for (int j = 0; j < n1 / 4; j++) {
                            for (int k = 0; k < n; k++) {
                                T.V[i][j] += V[i][k] * B.V[k][j];
                            }
                        }
                    }
                    });
                std::thread b = std::thread([m, n, n1, &T, &B, this]() {
                    for (int i = 0; i < m; i++) {
                        for (int j = n1 / 4; j < n1 / 2; j++) {
                            for (int k = 0; k < n; k++) {
                                T.V[i][j] += V[i][k] * B.V[k][j];
                            }
                        }
                    }
                    });
                std::thread c = std::thread([m, n, n1, &T, &B, this]() {
                    for (int i = 0; i < m; i++) {
                        for (int j = n1 / 2; j < 3 * n1 / 4; j++) {
                            for (int k = 0; k < n; k++) {
                                T.V[i][j] += V[i][k] * B.V[k][j];
                            }
                        }
                    }
                    });
                std::thread d = std::thread([m, n, n1, &T, &B, this]() {
                    for (int i = 0; i < m; i++) {
                        for (int j = 3 * n1 / 4; j < n1; j++) {
                            for (int k = 0; k < n; k++) {
                                T.V[i][j] += V[i][k] * B.V[k][j];
                            }
                        }
                    }
                    });
                a.join();
                b.join();
                c.join();
                d.join();
            }
            else {
                for (int i = 0; i < m; i++) {
                    for (int j = 0; j < n1; j++) {
                        for (int k = 0; k < n; k++) {
                            T.V[i][j] += V[i][k] * B.V[k][j];
                        }
                    }
                }
            }
        }
        else {
            for (int i = 0; i < m; i++) {
                for (int j = 0; j < n1; j++) {
                    for (int k = 0; k < n; k++) {
                        T.V[i][j] += V[i][k] * B.V[k][j];
                    }
                }
            }
        }
    }
    return T;
}

Matrix Matrix::operator/ (double a) const {
    return *this * (1.0/a);
}

Matrix Matrix::operator^ (int n) const {
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

bool Matrix::operator== (const Matrix& B) const {
    int m = this->m;
    bool q = true;
    if (m == B.m) {
        for (int i = 0; i < m; i++) {
            q &= (V[i] == B.V[i]);
        }
        return q;
    }
    return false;
}

bool Matrix::operator!= (const Matrix& B) const {
    return !(*this == B);
}

Matrix::~Matrix() {
    for (auto begin = V, end = V + m; begin != end; ++begin) {
        (begin)->~Vector();
    }
    operator delete(V);
}

Matrix operator* (double a, const Matrix& B) {
    return B * a;
}

Matrix operator* (Vector& a, const Matrix& B) {
    int N = a.get_size();
    if (N != B.get_m()) {
        throw(std::logic_error("Vector*Matrix not correct, the sizes do not match"));
    }
    Matrix A = Matrix(1, N);
    for (int i = 0; i < N; i++) {
        A[0][i] = a[i];
    }
    return A*B;
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
        x += A[i][i];
    }
    return x;
}

double det(Matrix A) {
    int n = A.get_n();
    int m = A.get_m();
    int R = A.get_accuracy();
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
                x = -x;
            }
            x *= A[j][j];
            A[j] /= A[j][j];
            i++;
            while (i < n) {
                A[i] -= A[i][j]* A[j];
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
    int R = A.get_accuracy();
    for (int j = 0; j < n; j++) {
        int i = x;
        while (i < m && (int)(A[i][j]*R)/10 == 0) {
            i++;
        }
        if (i < m) {
            A.stringij(i, x);
            A[x] /= A[x][j];
            i++ ;
            while (i < m) {
                A[i] -= A[i][j]* A[x];
                i++;
            }
            x++;
        }
    }
    return x;
}

Matrix SOL(Matrix& A, Vector& b) {
    int N = b.get_size();
    int n = A.get_n();
    int m = A.get_m();
    if(N != m) {
        throw(std::logic_error("SOL not correct, the sizes do not match"));
    }
    Matrix B = Matrix(m, n + 1);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            B[i][j] = A[i][j];
        }
        B[i][n] = b[i];
    }
    int k;
    std::thread th([&A, &k]() {
        k = rg(A);
    });
    int g = rg(B);
    th.join();
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
            B[x] /= B[x][j];
            i++;
            while (i < m) {
                B[i] -= B[i][j]* B[x];
                i++;
            }
            for (i = 0; i < x; i++) {
                B[i] -= B[i][j]* B[x];
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
