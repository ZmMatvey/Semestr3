#include <iostream>
#include <stdexcept>
#include "Vector.h"

Vector::Vector() : v(new double[3]), size(3) {}

Vector::Vector(unsigned int a) : v(new double[a]), size(a) {}

Vector::Vector(const Vector& b) : Vector(b.size) {
    int N = this->size;
    for (int i = 0; i < N; i++) {
        v[i] = b.v[i];
    }
}

Vector::Vector(Vector&& b) : size(b.size), v(b.v) {
    b.v = NULL;
}

int Vector::get_size() const {
    return size;
}

void Vector::fill_Vector() {
    int N = this->size;
    for (int i = 0; i < N; i++) {
        std::cin >> v[i];
    }
}

void Vector::print_Vector() const {
    int P = this->size - 1;
    std::cout << "||";
    for (int i = 0; i < P; i++) {
        std::cout << v[i] << " ";
    }
    std::cout << v[P];
    std::cout << "||" << std::endl;
}

Vector& Vector::operator= (const Vector& b) {
    int N = this->size;
    if (N != b.size) {
        throw(std::logic_error("=Vector not correct, the sizes do not match"));
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
    std::swap(size, b.size);
    std::swap(v, b.v);
    return *this;
}

Vector& Vector::operator+= (const Vector& b) {
    int N = this->size;
    if (N != b.size) {
        throw(std::logic_error("Vector+Vector not correct, the sizes do not match"));
    }
    for (int i = 0; i < N; i++) {
        v[i] += b.v[i];
    }
    return *this;
}

Vector& Vector::operator-= (const Vector& b) {
    int N = this->size;
    if (N != b.size) {
        throw(std::logic_error("Vector-Vector not correct, the sizes do not match"));
    }
    for (int i = 0; i < N; i++) {
        v[i] -= b.v[i];
    }
    return *this;
}

Vector& Vector::operator*= (double b) {
    int N = this->size;
    for (int i = 0; i < N; i++) {
        v[i] *= b;
    }
    return *this;
}

Vector& Vector::operator/= (double b) {
    int N = this->size;
    for (int i = 0; i < N; i++) {
        v[i] /= b;
    }
    return *this;
}

double& Vector::operator[](unsigned int i) {
    return v[i];
}

Vector Vector::operator+ (const Vector& b) const {
    int N = this->size;
    if (N != b.size) {
        throw(std::logic_error("Vector+Vector not correct, the sizes do not match"));
    }
    Vector c = Vector(N);
    for (int i = 0; i < N; i++) {
        c.v[i] = v[i] + b.v[i];
    }
    return c;
}

Vector Vector::operator- () const {
    return *this * (-1);
}

Vector Vector::operator- (const Vector& b) const {
    int N = this->size;
    if (N != b.size) {
        throw(std::logic_error("Vector-Vector not correct, the sizes do not match"));
    }
    Vector c = Vector(N);
    for (int i = 0; i < N; i++) {
        c.v[i] = v[i] - b.v[i];
    }
    return c;
}

Vector Vector::operator* (double a) const {
    int N = this->size;
    Vector c = Vector(N);
    for (int i = 0; i < N; i++) {
        c.v[i] = v[i] * a;
    }
    return c;
}

Vector Vector::operator/ (double a) const {
    return *this * (1.0 / a);
}

bool Vector::operator== (const Vector& b) const {
    int N = this->size;
    bool q = true;
    if (N == b.size) {
        for (int i = 0; i < N; i++) {
            q = q && (v[i] == b.v[i]);
        }
        return q;
    }
    return false;
}

bool Vector::operator!= (const Vector& b) const {
    return !(*this == b);
}

Vector::~Vector()
{
    delete []v;
}

Vector operator* (double a, const Vector& b) {
    return b * a;
}

Vector o(unsigned int a) {
    Vector c = Vector(a);
    for (int i = 0; i < a; i++) {
        c[i] = 0;
    }
    return c;
}
