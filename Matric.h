class Matric
{
private:
unsigned int m; //количество вектор строк

unsigned int n; //количество вектор столбцов

public:
Vector* const V; //указатель на массив вектор строк

Matric (unsigned int a, unsigned int b);//создаЄт матрицу axb

Matric(const Matric& B);//правило Ѕольшой тройки-1 конструктор копировани€

unsigned int GetM_m();

unsigned int GetM_n();

void SetM_fill(); //заполнение матрицы вручную

void SetM_fill(Vector* X); //заполнение матрицы при помощи массива векторов

void Cout_Matric(); //вывод матрицы

void stringij(unsigned int i, unsigned int j); //мен€ет местами i, j строки

void columnij(unsigned int i, unsigned int j); //мен€ет местами i, j столбцы

Matric T(); //транспонированна€ матрица

Matric inverseA();//обратна€ матрица

//int* p(); //положительный и отрицательный индексы инерции

double xi(double x); //характеристический многочлен от x

Matric& operator= (const Matric& B); //правило Ѕольшой тройки-2 оператор присваивани€

~Matric ();//правило Ѕольшой тройки-3 деструктор
};

Matric E(unsigned int n); //единична€ матрица размера n
Matric O(unsigned int m, unsigned int n);//нулева€ матрица размерами mxn
double det(Matric A); //определитель матрицы A
double tr(Matric A); //след матрицы A
//int rg(Matric A); //ранг матрицы A
//Matric FDS(Matric A);//‘—– линейного матричного уравнени€
//Matric EXP(Matric A); //матрична€ экспонента
Matric operator+ (Matric A, Matric B); //A+B
Matric operator- (Matric A, Matric B); //A-B
bool operator== (Matric A, Matric B); //A == B
Matric operator* (double a, Matric B); //умножение матрицы b на скал€р а
Vector operator* (Vector a, Matric B); //умножение вектор строки на матрицу
Vector operator* (Matric A, Vector b); //умножение матрицы на вектор столбец
Matric operator* (Matric A, Matric B); //A*B
Matric operator/ (Matric B, double a); //B/a
//Matric operator[] (Matric A, Matric B);//[A,B] = A*B-B*A
//Matric operator^ (Matric A, int n); //A^n возведение матрицы в степень

