class Matric
{
private:
unsigned int m; //���������� ������ �����

unsigned int n; //���������� ������ ��������

public:
Vector* const V; //��������� �� ������ ������ �����

Matric (unsigned int a, unsigned int b);//������ ������� axb

Matric(const Matric& B);//������� ������� ������-1 ����������� �����������

unsigned int GetM_m();

unsigned int GetM_n();

void SetM_fill(); //���������� ������� �������

void SetM_fill(Vector* X); //���������� ������� ��� ������ ������� ��������

void Cout_Matric(); //����� �������

void stringij(unsigned int i, unsigned int j); //������ ������� i, j ������

void columnij(unsigned int i, unsigned int j); //������ ������� i, j �������

Matric T(); //����������������� �������

Matric inverseA();//�������� �������

//int* p(); //������������� � ������������� ������� �������

double xi(double x); //������������������ ��������� �� x

Matric& operator= (const Matric& B); //������� ������� ������-2 �������� ������������

~Matric ();//������� ������� ������-3 ����������
};

Matric E(unsigned int n); //��������� ������� ������� n
Matric O(unsigned int m, unsigned int n);//������� ������� ��������� mxn
double det(Matric A); //������������ ������� A
double tr(Matric A); //���� ������� A
//int rg(Matric A); //���� ������� A
//Matric FDS(Matric A);//��� ��������� ���������� ���������
//Matric EXP(Matric A); //��������� ����������
Matric operator+ (Matric A, Matric B); //A+B
Matric operator- (Matric A, Matric B); //A-B
bool operator== (Matric A, Matric B); //A == B
Matric operator* (double a, Matric B); //��������� ������� b �� ������ �
Vector operator* (Vector a, Matric B); //��������� ������ ������ �� �������
Vector operator* (Matric A, Vector b); //��������� ������� �� ������ �������
Matric operator* (Matric A, Matric B); //A*B
Matric operator/ (Matric B, double a); //B/a
//Matric operator[] (Matric A, Matric B);//[A,B] = A*B-B*A
//Matric operator^ (Matric A, int n); //A^n ���������� ������� � �������

