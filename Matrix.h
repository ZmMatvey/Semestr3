#pragma once
#include "Vector.h"

class Matrix
{
protected:
	int m;//количество вектор строк

	int n;//количество вектор столбцов

	int R;//точность матрицы (сколько нулей в R, столько и цифр после запятой может стоять в элементе матрицы при вычислении rg, det, SOL)

	Vector* V;//указатель на массив вектор строк

public:

	Matrix(unsigned int m, unsigned int n);//создаёт матрицу axb

	Matrix(const Matrix& B);//правило пяти - 1 конструктор копирования

	Matrix(Matrix&& B);//правило пяти - 2 конструктор перемещения

	int get_m()const;

	int get_n()const;

	int get_R()const;

	Vector* get_V();

	void set_fill();//заполнение матрицы вручную

	void cout_Matrix();//вывод матрицы

	void stringij(unsigned int i, unsigned int j);//меняет местами i, j строки

	void columnij(unsigned int i, unsigned int j);//меняет местами i, j столбцы

	Matrix T();//транспонированная матрица

	Matrix inverse();//обратная матрица

	double xi(double x);//характеристический многочлен от x

	Matrix& operator= (const Matrix& B);//правило пяти - 3 оператор присваивания

	Matrix& operator= (Matrix&& B);//правило пяти - 4 оператор перемещения

	Matrix& operator+= (const Matrix& B);

	Matrix& operator-= (const Matrix& B);

	Matrix& operator*= (double a);

	Matrix& operator/= (double a);

	Vector& operator[] (unsigned int i);

	Matrix operator+ (const Matrix& B);

	Matrix operator- ();

	Matrix operator- (const Matrix& B);

	Vector operator* (Vector& b);//умножение матрицы на вектор столбец

	Matrix operator* (double a);//умножение матрицы b на скаляр а

	Matrix operator* (Matrix& B);

	Matrix operator/ (double a);

	Matrix operator^ (int n);//A^n возведение матрицы в степень

	bool operator== (const Matrix& B);

	bool operator!= (const Matrix& B);

	~Matrix();//правило пяти - 5 деструктор

};

Vector operator* (Vector& a, Matrix& B);//умножение вектор строки на матрицу

Matrix operator* (double a, Matrix& B);//умножение матрицы b на скаляр а

Matrix E(unsigned int n);//единичная матрица размера nxn

Matrix O(unsigned int m, unsigned int n);//нулевая матрица размерами mxn

double tr(Matrix& A);//след матрицы A

double det(Matrix A);//определитель матрицы A

int rg(Matrix A);//ранг матрицы A

Matrix SOL(Matrix& A, Vector& b);//решение линейного матричного уравнения вида A*x=b
