class Matrix
{
private:
unsigned int m; //���������� ������ �����

unsigned int n; //���������� ������ ��������

public:
Vector* const V; //��������� �� ������ ������ �����

Matrix (unsigned int a, unsigned int b);//������ ������� axb

Matrix(const Matrix& B);//������� ������� ������-1 ����������� �����������

unsigned int GetM_m();

unsigned int GetM_n();

void SetM_fill(); //���������� ������� �������

void SetM_fill(Vector* X); //���������� ������� ��� ������ ������� ��������

void Cout_Matrix(); //����� �������

void stringij(unsigned int i, unsigned int j); //������ ������� i, j ������

void columnij(unsigned int i, unsigned int j); //������ ������� i, j �������

Matrix T(); //����������������� �������

Matrix inverseA();//�������� �������

//int* p(); //������������� � ������������� ������� �������

double xi(double x); //������������������ ��������� �� x

Matrix& operator= (const Matrix& B); //������� ������� ������-2 �������� ������������

~Matrix ();//������� ������� ������-3 ����������
};

Matrix E(unsigned int n); //��������� ������� ������� n
Matrix O(unsigned int m, unsigned int n);//������� ������� ��������� mxn
double det(Matrix A); //������������ ������� A
double tr(Matrix A); //���� ������� A
//int rg(Matrix A); //���� ������� A
//Matrix FDS(Matrix A);//��� ��������� ���������� ���������
//Matrix EXP(Matrix A); //��������� ����������
Matrix operator+ (Matrix A, Matrix B); //A+B
Matrix operator- (Matrix A, Matrix B); //A-B
bool operator== (Matrix A, Matrix B); //A == B
Matrix operator* (double a, Matrix B); //��������� ������� b �� ������ �
Vector operator* (Vector a, Matrix B); //��������� ������ ������ �� �������
Vector operator* (Matrix A, Vector b); //��������� ������� �� ������ �������
Matrix operator* (Matrix A, Matrix B); //A*B
Matrix operator/ (Matrix B, double a); //B/a
//Matrix operator[] (Matrix A, Matrix B);//[A,B] = A*B-B*A
//Matrix operator^ (Matrix A, int n); //A^n ���������� ������� � �������

