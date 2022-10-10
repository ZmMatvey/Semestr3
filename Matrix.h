class Matrix
{
private:
unsigned int m; //количество вектор строк

unsigned int n; //количество вектор столбцов

public:
Vector* const V; //указатель на массив вектор строк

Matrix (unsigned int a, unsigned int b);//создаЄт матрицу axb

Matrix(const Matrix& B);//правило Ѕольшой тройки-1 конструктор копировани€

unsigned int GetM_m();

unsigned int GetM_n();

void SetM_fill(); //заполнение матрицы вручную

void SetM_fill(Vector* X); //заполнение матрицы при помощи массива векторов

void Cout_Matrix(); //вывод матрицы

void stringij(unsigned int i, unsigned int j); //мен€ет местами i, j строки

void columnij(unsigned int i, unsigned int j); //мен€ет местами i, j столбцы

Matrix T(); //транспонированна€ матрица

Matrix inverseA();//обратна€ матрица

//int* p(); //положительный и отрицательный индексы инерции

double xi(double x); //характеристический многочлен от x

Matrix& operator= (const Matrix& B); //правило Ѕольшой тройки-2 оператор присваивани€

~Matrix ();//правило Ѕольшой тройки-3 деструктор
};

Matrix E(unsigned int n); //единична€ матрица размера n
Matrix O(unsigned int m, unsigned int n);//нулева€ матрица размерами mxn
double det(Matrix A); //определитель матрицы A
double tr(Matrix A); //след матрицы A
//int rg(Matrix A); //ранг матрицы A
//Matrix FDS(Matrix A);//‘—– линейного матричного уравнени€
//Matrix EXP(Matrix A); //матрична€ экспонента
Matrix operator+ (Matrix A, Matrix B); //A+B
Matrix operator- (Matrix A, Matrix B); //A-B
bool operator== (Matrix A, Matrix B); //A == B
Matrix operator* (double a, Matrix B); //умножение матрицы b на скал€р а
Vector operator* (Vector a, Matrix B); //умножение вектор строки на матрицу
Vector operator* (Matrix A, Vector b); //умножение матрицы на вектор столбец
Matrix operator* (Matrix A, Matrix B); //A*B
Matrix operator/ (Matrix B, double a); //B/a
//Matrix operator[] (Matrix A, Matrix B);//[A,B] = A*B-B*A
//Matrix operator^ (Matrix A, int n); //A^n возведение матрицы в степень

