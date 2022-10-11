#include "Vector.cpp"
#include "Matrix.h"

Matrix::Matrix (unsigned int a, unsigned int b): m(a), n(b), V (new Vector[a]) {}

Matrix::Matrix(const Matrix& B): Matrix(B.m, B.n)  {
    for (unsigned int i = 0; i < m; i++) {
        V[i] = B.V[i];
    }
}

unsigned int Matrix::GetM_m() {
    return m;
}

unsigned int Matrix::GetM_n() {
    return n;
}

void Matrix::SetM_fill() {
    for (unsigned int i = 0; i < m; i++) {
        V[i].Set_fill();
    }
}

void Matrix::SetM_fill(Vector* X) {
    for (unsigned int i = 0; i < m; i++) {
        V[i] = X[i];
    }
}

void Matrix::Cout_Matrix() {
    for (unsigned int i = 0; i < m; i++) {
        V[i].Cout_Vector();
    }
    cout<<'\n';
}

void Matrix::stringij(unsigned int i, unsigned int j) {
    if (i != j) {
        Vector c = V[i];
        V[i] = V[j];
        V[j] = c;
    }
}

void Matrix::columnij(unsigned int i, unsigned int j) {
    if (i != j) {
        double c;
        for (unsigned int t = 0; t < m; i++) {
            c = V[t].v[i];
            V[t].v[i] = V[t].v[j];
            V[t].v[j] = c;
        }
    }
}

Matrix Matrix::T() {
    Matrix X = Matrix(n, m);
    for (unsigned int i = 0; i < m; i++) {
        for (unsigned int j = 0; j < n; j++) {
            X.V[j].v[i] = V[i].v[j];
        }
    }
    return X;
}

Matrix Matrix::inverse() {
    if (det(*this) != 0) {
        Matrix X = E(n);
        Matrix A = Matrix(n, n);
        A = *this;
        for (unsigned int j = 0; j < n; j++) {
            unsigned int i = j;
            while (A.V[i].v[j] == 0 && i+j < n) {
                i++;
            }
            X.stringij(i, j);
            A.stringij(i, j);
            X.V[j] = X.V[j]/A.V[j].v[j];
            A.V[j] = A.V[j]/A.V[j].v[j];
            i = 1;
            while (i+j < n) {
                X.V[i+j] = X.V[i+j] - A.V[i+j].v[j]* X.V[j];
                A.V[i+j] = A.V[i+j] - A.V[i+j].v[j]* A.V[j];
                i++;
            }
        }
        for (int j = n - 1; j > 0; j--) {
            int i = j - 1;
            while (i >= 0) {
                X.V[i] = X.V[i] - A.V[i].v[j]*X.V[j];
                i--;
            }
        }
        return X;
    }
}

double Matrix::xi(double x) {
    if (n == m) {
        return det((*this) - x*E(n));
    }
}

Matrix& Matrix::operator= (const Matrix& B) {
    if (m == B.m && n == B.n) {
        if (this == &B) {
            return *this;
        }
        for (unsigned int i = 0; i < m; i++) {
            V[i] = B.V[i];
        }
        return *this;
    }
}

Matrix::~Matrix () {
    delete []V;
}

Matrix E(unsigned int n) {
    Matrix A = Matrix(n, n);
    for (unsigned int i = 0; i < n; i++) {
        for (unsigned int j = 0; j < n; j++) {
            if (i == j) {
                A.V[i].v[j] = 1;
            }
            else {
                A.V[i].v[j] = 0;
            }
        }
    }
    return A;
}

Matrix O(unsigned int m, unsigned int n) {
    Matrix A = Matrix(m, n);
    for (unsigned int i = 0; i < n; i++) {
        for (unsigned int j = 0; j < n; j++) {
            A.V[i].v[j] = 0;
        }
    }
    return A;
}

double tr(Matrix A) {
    unsigned int n = A.GetM_n();
    unsigned int m = A.GetM_m();
    if (n == m) {
        double x = 0;
        for (unsigned int i = 0; i < n; i++) {
            x = x + A.V[i].v[i];
        }
        return x;
    }
}

double det(Matrix A) {
    unsigned int n = A.GetM_n();
    unsigned int m = A.GetM_m();
    double x = 1;
    if (n == m) {
        for (unsigned int j = 0; j < n; j++) {
            unsigned int i = j;
            while (A.V[i].v[j] == 0 && i+j < n) {
                i++;
            }
            if (i == n) {
                return 0;
            }
            else {
                if (i != j) {
                    A.stringij(i, j);
                    x = x*(-1);
                }
            }
            x = x * A.V[j].v[j];
            A.V[j] = A.V[j]/A.V[j].v[j];
            i = 1;
            while (i+j < n) {
                A.V[i+j] = A.V[i+j] - A.V[i+j].v[j]* A.V[j];
                i++;
            }
        }
        return x;
    }
    return 0;
}

Matrix operator+ (Matrix A, Matrix B) {
    unsigned int x = A.GetM_m();
    unsigned int y = B.GetM_m();
    unsigned int x1 = A.GetM_n();
    unsigned int y1 = B.GetM_n();
    if (x == y && x1 == y1) {
        Matrix C = Matrix(x, x1);
        for (unsigned int i = 0; i < x; i++) {
            C.V[i] = A.V[i] + B.V[i];
        }
    return C;
    }
}

Matrix operator- (Matrix A, Matrix B) {
    unsigned int x = A.GetM_m();
    unsigned int y = B.GetM_m();
    unsigned int x1 = A.GetM_n();
    unsigned int y1 = B.GetM_n();
    if (x == y && x1 == y1) {
        Matrix C = Matrix(x, x1);
        for (unsigned int i = 0; i < x; i++) {
            C.V[i] = A.V[i] - B.V[i];
        }
    return C;
    }
}

bool operator== (Matrix A, Matrix B) {
    unsigned int x = A.GetM_m();
    unsigned int y = B.GetM_m();
    unsigned int x1 = A.GetM_n();
    unsigned int y1 = B.GetM_n();
    if (x == y && x1 == y1) {
        bool q = true;
        for (unsigned int i = 0; i < x; i++) {
            q = q && (A.V[i] == B.V[i]);
        }
        return q;
    }
    return false;

}

Matrix operator* (double a, Matrix B) {
    unsigned int x = B.GetM_m();
    for (unsigned int i = 0; i < x; i++) {
        B.V[i] = a*B.V[i];
    }
    return B;
}

Vector operator* (Vector a, Matrix B) {
    unsigned int x = a.Get_N();
    unsigned int y = B.GetM_m();
    unsigned int z = B.GetM_n();
    if (x == y) {
        Vector t = o(z);
        for (unsigned int i = 0; i < z; i++) {
            for (unsigned int j = 0; j < y; j++) {
                t.v[i] = t.v[i] + a.v[j]*B.V[j].v[i];
            }
        }
        return t;
    }
}

Vector operator* (Matrix A, Vector b) {
    unsigned int x = b.Get_N();
    unsigned int y = A.GetM_n();
    unsigned int z = A.GetM_m();
    if (x == y) {
        Vector t = o(z);
        for (unsigned int i = 0; i < z; i++) {
            for (unsigned int j = 0; j < y; j++) {
                t.v[i] = t.v[i] + A.V[i].v[j]*b.v[j];
            }
        }
        return t;
    }
}

Matrix operator* (Matrix A, Matrix B) {
    unsigned int x = A.GetM_m();
    unsigned int y = A.GetM_n();
    unsigned int x1 = B.GetM_m();
    unsigned int y1 = B.GetM_n();
    if (y == x1) {
        Matrix T = Matrix(x, y1);
        for (unsigned int i = 0; i < x; i++) {
            T.V[i] = A.V[i]*B;
        }
        return T;
    }
}

Matrix operator/ (Matrix B, double a) {
    return (1.0/a)*B;
}

Matrix operator^ (Matrix A, int n) {
    if (A.GetM_m() == A.GetM_n()) {
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
        if (n > 0) {
            Matrix B = A;
            for (int i = n - 1; i > 0; i--) {
                A = A*B;
            }
            return A;
        }
    }
}
