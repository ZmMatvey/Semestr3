#ifndef MATRIX_H
#include "Vector.h"
#define MATRIX_H

class Matrix
{
private:
	int m;//количество вектор строк

	int n;//количество вектор столбцов

	int accuracy;//точность матрицы (сколько нулей в accuracy, столько и цифр после запятой может стоять в элементе матрицы при вычислении rg, det, SOL)

	Vector* V;//указатель на массив вектор строк

public:

	Matrix(unsigned int m, unsigned int n);//создаёт матрицу axb

	Matrix(const Matrix& B);//правило пяти - 1 конструктор копирования

	Matrix(Matrix&& B);//правило пяти - 2 конструктор перемещения

	int get_m() const;

	int get_n() const;

	int get_accuracy() const;

	void fill_Matrix();//заполнение матрицы вручную

	void print_Matrix() const;//вывод матрицы

	void stringij(unsigned int i, unsigned int j);//меняет местами i, j строки

	void columnij(unsigned int i, unsigned int j);//меняет местами i, j столбцы

	Matrix T() const;//транспонированная матрица

	Matrix inverse() const;//обратная матрица

	double xi(double x) const;//характеристический многочлен от x

	Matrix& operator= (const Matrix& B);//правило пяти - 3 оператор присваивания

	Matrix& operator= (Matrix&& B);//правило пяти - 4 оператор перемещения

	Matrix& operator+= (const Matrix& B);

	Matrix& operator-= (const Matrix& B);

	Matrix& operator*= (double a);

	Matrix& operator/= (double a);

	Vector& operator[] (unsigned int i);

	Matrix operator+ (const Matrix& B) const;

	Matrix operator- () const;

	Matrix operator- (const Matrix& B) const;

	Vector operator* (Vector& b) const;//умножение матрицы на вектор столбец

	Matrix operator* (double a) const;//умножение матрицы b на скаляр а

	Matrix operator* (const Matrix& B) const;

	Matrix operator/ (double a) const;

	Matrix operator^ (int n) const;//A^n возведение матрицы в степень

	bool operator== (const Matrix& B) const;

	bool operator!= (const Matrix& B) const;

	~Matrix();//правило пяти - 5 деструктор

};

Matrix operator* (double a, const Matrix& B);//умножение матрицы b на скаляр а

Matrix operator* (Vector& a, const Matrix& B);//умножение вектор строки на матрицу

Matrix E(unsigned int n);//единичная матрица размера nxn

Matrix O(unsigned int m, unsigned int n);//нулевая матрица размерами mxn

double tr(Matrix& A);//след матрицы A

double det(Matrix A);//определитель матрицы A

int rg(Matrix A);//ранг матрицы A

Matrix SOL(Matrix& A, Vector& b);//решение линейного матричного уравнения вида A*x=b

#endif // MATRIX_H
