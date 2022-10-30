class Vector
{
protected:
	int N;//размер вектора

	double* v;

public:

	Vector();

	Vector(const Vector& b);//правило пяти 1-конструктор копирования

	Vector(Vector&& b);//правило пяти 2-конструктор перемещения

	Vector(unsigned int a);//создаёт вектор из R^a

	int get_N()const;

	double* get_v();

	void set_fill();//заполнение вектора вручную

	void cout_Vector();//вывод вектора

	Vector& operator= (const Vector& b);//правило пяти 3-оператор присваивания

	Vector& operator= (Vector&& b);//правило пяти 4-оператор перемещения

	Vector& operator+= (const Vector& b);

	Vector& operator-= (const Vector& b);

	Vector& operator*= (double b);

	Vector& operator/= (double b);

	double& operator[] (unsigned int i);

	Vector operator+ (const Vector& b);

	Vector operator- ();

	Vector operator- (const Vector& b);

	Vector operator* (double a);//умножение вектора b на скаляр а

	Vector operator/ (double a);

	bool operator== (const Vector& b);

	bool operator!= (const Vector& b);

	~Vector();//правило пяти 5-деструктор

};

Vector operator* (double a, Vector& b);

Vector o(unsigned int a);//нулевой вектор
