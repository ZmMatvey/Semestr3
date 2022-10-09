class Vector
{
protected:
unsigned int N; //размер вектора

public:
double* const v;

Vector();

Vector(const Vector& b);//правило Ѕольшой тройки 1-конструктор копировани€

Vector (unsigned int a);//создаЄт вектор из R^a

unsigned int Get_N();

void Set_fill();//заполнение вектора вручную

void Set_fill(double* x);//заполнение вектора при помощи массива

void Cout_Vector(); //вывод вектора

Vector& operator= (const Vector& b);//правило Ѕольшой тройки 2-оператор присваивани€

~Vector ();//правило Ѕольшой тройки 3-деструктор

};

Vector o(unsigned int a); //нулевой вектор
Vector operator+ (Vector a, Vector b); //a+b
Vector operator- (Vector a, Vector b); //a-b
bool operator== (Vector a, Vector b); //a == b
Vector operator* (double a, Vector b); //умножение вектора b на скал€р а
Vector operator/ (Vector b, double a); //b/a
