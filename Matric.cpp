#include "Vector.cpp"
#include "Matric.h"

Matric::Matric (unsigned int a, unsigned int b): m(a), n(b), V (new Vector[a]) {
    for (unsigned int i = 0; i < a; i++) {
        V[i] = Vector(b);
    }
}

Matric::Matric(const Matric& B): Matric(B.m, B.n)  {
    for (unsigned int i = 0; i < m; i++) {
        V[i] = B.V[i];
    }
}

unsigned int Matric::GetM_m() {
    return m;
}

unsigned int Matric::GetM_n() {
    return n;
}

void Matric::SetM_fill() {
    for (unsigned int i = 0; i < m; i++) {
        V[i].Set_fill();
    }
}

void Matric::SetM_fill(Vector* X) {
    for (unsigned int i = 0; i < m; i++) {
        V[i] = X[i];
    }
}

void Matric::Cout_Matric() {
    for (unsigned int i = 0; i < m; i++) {
        V[i].Cout_Vector();
    }
    cout<<'\n';
}

void Matric::stringij(unsigned int i, unsigned int j) {
    Vector c = V[i];
    V[i] = V[j];
    V[j] = c;
}

void Matric::columnij(unsigned int i, unsigned int j) {
    double c;
    for (unsigned int t = 0; t < m; i++) {
        c = V[t].v[i];
        V[t].v[i] = V[t].v[j];
        V[t].v[j] = c;
    }
}

Matric Matric::T() {
    Matric X = Matric(n, m);
    for (unsigned int i = 0; i < m; i++) {
        for (unsigned int j = 0; j < n; j++) {
            X.V[j].v[i] = V[i].v[j];
        }
    }
    return X;
}

Matric Matric::inverseA() {
    if (det(*this) != 0) {
        Matric X = E(n);
        Matric A = Matric(n, n);
        A = *this;
        for (unsigned int j = 0; j < n; j++) {
            unsigned int i = 0;
            while (A.V[i+j].v[j] == 0 && i+j < n) {
                i++;
            }
            X.stringij(i+j, j);
            A.stringij(i+j, j);
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
    else {
        cout<<"det = 0"<<endl;
    }
}

double Matric::xi(double x) {
    if (n == m) {
        return det((*this) - x*E(n));
    }
}

Matric& Matric::operator= (const Matric& B) {
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

Matric::~Matric () {
    delete []V;
}

Matric E(unsigned int n) {
    Matric A = Matric(n, n);
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

Matric O(unsigned int m, unsigned int n) {
    Matric A = Matric(m, n);
    for (unsigned int i = 0; i < n; i++) {
        for (unsigned int j = 0; j < n; j++) {
            A.V[i].v[j] = 0;
        }
    }
    return A;
}

double tr(Matric A) {
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

double det(Matric A) {
    unsigned int n = A.GetM_n();
    unsigned int m = A.GetM_m();
    double x = 1;
    if (n == m) {
        for (unsigned int j = 0; j < n; j++) {
            unsigned int i = 0;
            while (A.V[i+j].v[j] == 0 && i+j < n) {
                i++;
            }
            if (i+j == n) {
                return 0;
            }
            else {
                if (i+j != j) {
                    A.stringij(i+j, j);
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

Matric operator+ (Matric A, Matric B) {
    unsigned int x = A.GetM_m();
    unsigned int y = B.GetM_m();
    unsigned int x1 = A.GetM_n();
    unsigned int y1 = B.GetM_n();
    if (x == y && x1 == y1) {
        Matric C = Matric(x, x1);
        for (unsigned int i = 0; i < x; i++) {
            C.V[i] = A.V[i] + B.V[i];
        }
    return C;
    }
}

Matric operator- (Matric A, Matric B) {
    unsigned int x = A.GetM_m();
    unsigned int y = B.GetM_m();
    unsigned int x1 = A.GetM_n();
    unsigned int y1 = B.GetM_n();
    if (x == y && x1 == y1) {
        Matric C = Matric(x, x1);
        for (unsigned int i = 0; i < x; i++) {
            C.V[i] = A.V[i] - B.V[i];
        }
    return C;
    }
}

bool operator== (Matric A, Matric B) {
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

Matric operator* (double a, Matric B) {
    unsigned int x = B.GetM_m();
    for (unsigned int i = 0; i < x; i++) {
        B.V[i] = a*B.V[i];
    }
    return B;
}

Vector operator* (Vector a, Matric B) {
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

Vector operator* (Matric A, Vector b) {
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

Matric operator* (Matric A, Matric B) {
    unsigned int x = A.GetM_m();
    unsigned int y = A.GetM_n();
    unsigned int x1 = B.GetM_m();
    unsigned int y1 = B.GetM_n();
    if (y == x1) {
        Matric T = Matric(x, y1);
        for (unsigned int i = 0; i < x; i++) {
            T.V[i] = A.V[i]*B;
        }
        return T;
    }
}

Matric operator/ (Matric B, double a) {
    return (1.0/a)*B;
}

