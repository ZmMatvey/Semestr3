class Vector
{
protected:
int N; //vector size

double* v;

public:

Vector();

Vector(const Vector& b); //rule of five 1-copy constructor

Vector(Vector&& b); //rule of five 2-move constructor
  
Vector (int a); //creates a vector from R^a

int Get_N();

void Set_fill(); //filling in the vector manually

void Set_fill(double* x); //filling a vector with an array

void Cout_Vector();

Vector& operator= (const Vector& b); //rule of five 3-assignment operator

Vector& operator= (Vector&& b); //rule of five 4-move operator

double& operator[] (int i);

~Vector (); //rule of five 5-destructor
};

Vector o(int a); //zero vector

Vector operator+ (Vector a, Vector b); //a+b

Vector operator- (Vector a, Vector b); //a-b

bool operator== (Vector a, Vector b); //a == b

Vector operator* (double a, Vector b); //a*b

Vector operator/ (Vector b, double a); //b/a
