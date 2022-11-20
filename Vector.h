#ifndef VECTOR_H
#define VECTOR_H

class Vector
{
private:
	int size;//размер вектора

	double* v;

public:

	Vector();

	Vector(const Vector& b);//правило пяти 1-конструктор копирования

	Vector(Vector&& b);//правило пяти 2-конструктор перемещения

	Vector(unsigned int a);//создаёт вектор из R^a

	int get_size() const;

	void fill_Vector();//заполнение вектора вручную

	void print_Vector() const;//вывод вектора

	Vector& operator= (const Vector& b);//правило пяти 3-оператор присваивания

	Vector& operator= (Vector&& b);//правило пяти 4-оператор перемещения

	Vector& operator+= (const Vector& b);

	Vector& operator-= (const Vector& b);

	Vector& operator*= (double b);

	Vector& operator/= (double b);

	double& operator[] (unsigned int i);

	Vector operator+ (const Vector& b) const;

	Vector operator- () const;

	Vector operator- (const Vector& b) const;

	Vector operator* (double a) const ;//умножение вектора b на скаляр а

	Vector operator/ (double a) const;

	bool operator== (const Vector& b) const;

	bool operator!= (const Vector& b) const;

	~Vector();//правило пяти 5-деструктор

};

Vector operator* (double a, const Vector& b);

Vector o(unsigned int a);//нулевой вектор

#endif //VECTOR_H
