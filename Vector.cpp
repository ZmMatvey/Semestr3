#include <iostream>
#include <assert.h>
#include "Vector.h"

Vector::Vector (): v(new double[3]), N(3) {}

Vector::Vector (int a): v(new double[a]), N(a) {}

Vector::Vector(const Vector& b): Vector(b.N) {
    for (int i = 0; i < N; i++) {
        v[i] = b.v[i];
    }
}

Vector::Vector(Vector&& b): N(b.N), v(b.v) {}

int Vector::Get_N() {
    return N;
}

void Vector::Set_fill() {
    for (int i = 0; i < N; i++) {
        std::cin>>v[i];
    }
}

void Vector::Set_fill(double* x) {
    for (int i = 0; i < N; i++) {
        v[i] = x[i];
    }
}

void Vector::Cout_Vector() {
    std::cout<<"||";
    for (int i = 0; i < N-1; i++) {
        std::cout<<v[i]<<" ";
    }
    std::cout<<v[N-1];
    std::cout<<"||"<<std::endl;
}

Vector& Vector::operator= (const Vector& b) {
    assert (N == b.N);
    if (this == &b) {
        return *this;
    }
    for (int i = 0; i < N; i++) {
        v[i] = b.v[i];
    }
    return *this;
}

Vector& Vector::operator= (Vector&& b) {
    this->N = b.N;
    this->v = b.v;
    return *this;
}

Vector::~Vector () {
    delete []v;
}

double& Vector::operator[](int i) {
    return v[i];
}

Vector o(int a) {
    Vector c = Vector(a);
    for (int i = 0; i < a; i++) {
        c[i] = 0;
    }
    return c;
}

Vector operator+ (Vector a, Vector b){
    int x = a.Get_N();
    int y = b.Get_N();
    assert (x == y);
    Vector c = Vector(x);
    for (int i = 0; i < x; i++) {
        c[i] = a[i] + b[i];
    }
    return c;
}

Vector operator- (Vector a, Vector b) {
    int x = a.Get_N();
    int y = b.Get_N();
    assert (x == y);
    Vector c = Vector(x);
    for (int i = 0; i < x; i++) {
        c[i] = a[i] - b[i];
    }
    return c;
}

bool operator== (Vector a, Vector b) {
    int x = a.Get_N();
    int y = b.Get_N();
    if (x == y) {
        bool q = true;
        for (int i = 0; i < x; i++) {
            q = q && (a[i] == b[i]);
        }
        return q;
    }
    return false;
}

Vector operator* (double a, Vector b) {
    int x = b.Get_N();
    Vector c = Vector(x);
    for (int i = 0; i < x; i++) {
        c[i] = a*b[i];
    }
    return c;
}

Vector operator/ (Vector b, double a) {
    return (1.0/a)*b;
}
