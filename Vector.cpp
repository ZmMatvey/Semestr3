#include <iostream>
#include <stdexcept>
#include "Vector.h"

Vector::Vector(): v(new double[3]), N(3) {}

Vector::Vector(unsigned int a): v(new double[a]), N(a) {}

Vector::Vector(const Vector& b): Vector(b.N) {
    int N = this->N;
    for (int i = 0; i < N; i++) {
        v[i] = b.v[i];
    }
}

Vector::Vector(Vector&& b): N(b.N), v(b.v) {
    b.v = NULL;
}

int Vector::get_N()const {
    return N;
}

double* Vector::get_v() {
    return v;
}

void Vector::set_fill() {
    int N = this->N;
    for (int i = 0; i < N; i++) {
        std::cin>>v[i];
    }
}

void Vector::set_fill(double* x) {
    int N = this->N;
    for (int i = 0; i < N; i++) {
        v[i] = x[i];
    }
}

void Vector::cout_Vector() {
    int P = this->N - 1;
    std::cout<<"||";
    for (int i = 0; i < P; i++) {
        std::cout<<v[i]<<" ";
    }
    std::cout<<v[P];
    std::cout<<"||"<<std::endl;
}

Vector& Vector::operator= (const Vector& b) {
    int N = this->N;
    if (N != b.N) {
        throw(std::runtime_error("=Vector not correct, the sizes do not match"));
    }
    if (this == &b) {
        return *this;
    }
    for (int i = 0; i < N; i++) {
        v[i] = b.v[i];
    }
    return *this;
}

Vector& Vector::operator= (Vector&& b) {
    std::swap(N, b.N);
    std::swap(v, b.v);
    return *this;
}

double& Vector::operator[](unsigned int i) {
    return v[i];
}

Vector Vector::operator+ (const Vector& b) {
    int N = this->N;
    if (N != b.N) {
        throw(std::runtime_error("Vector+Vector not correct, the sizes do not match"));
    }
    Vector c = Vector(N);
    for (int i = 0; i < N; i++) {
        c.v[i] = v[i] + b.v[i];
    }
    return c;
}

Vector Vector::operator- () {
    return *this * (-1);
}

Vector Vector::operator- (const Vector& b) {
    int N = this->N;
    if (N != b.N) {
        throw(std::runtime_error("Vector-Vector not correct, the sizes do not match"));
    }
    Vector c = Vector(N);
    for (int i = 0; i < N; i++) {
        c.v[i] = v[i] - b.v[i];
    }
    return c;
}

Vector Vector::operator* (double a) {
    int N = this->N;
    Vector c = Vector(N);
    for (int i = 0; i < N; i++) {
        c.v[i] = v[i] * a ;
    }
    return c;
}

Vector Vector::operator/ (double a) {
    return *this * (1.0/a);
}

bool Vector::operator== (const Vector& b) {
    int N = this->N;
    bool q = true;
    if (N == b.N) {
        for (int i = 0; i < N; i++) {
            q = q && (v[i] == b.v[i]);
        }
        return q;
    }
    return false;
}

bool Vector::operator!= (const Vector& b) {
    return !(*this == b);
}

Vector::~Vector () {
    delete []v;
}

Vector operator* (double a, Vector& b) {
    return b * a;
}

Vector o(unsigned int a) {
    Vector c = Vector(a);
    for (int i = 0; i < a; i++) {
        c[i] = 0;
    }
    return c;
}
