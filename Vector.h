class Vector
{
protected:
unsigned int N; //������ �������

public:
double* const v;

Vector();

Vector(const Vector& b);//������� ������� ������ 1-����������� �����������

Vector (unsigned int a);//������ ������ �� R^a

unsigned int Get_N();

void Set_fill();//���������� ������� �������

void Set_fill(double* x);//���������� ������� ��� ������ �������

void Cout_Vector(); //����� �������

Vector& operator= (const Vector& b);//������� ������� ������ 2-�������� ������������

~Vector ();//������� ������� ������ 3-����������

};

Vector o(unsigned int a); //������� ������
Vector operator+ (Vector a, Vector b); //a+b
Vector operator- (Vector a, Vector b); //a-b
bool operator== (Vector a, Vector b); //a == b
Vector operator* (double a, Vector b); //��������� ������� b �� ������ �
Vector operator/ (Vector b, double a); //b/a
