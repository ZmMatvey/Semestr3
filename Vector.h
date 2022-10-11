class Vector
{
protected:
unsigned int N; //vector size

public:
double* const v; //double array

Vector();  //not finalized, not consistent with the matrix class

Vector(const Vector& b); //rule of three 1-copy constructor

Vector (unsigned int a); //creates a vector from R^a

unsigned int Get_N();

void Set_fill(); //filling in the vector manually

void Set_fill(double* x); //filling a vector with an array

void Cout_Vector(); //vector output

Vector& operator= (const Vector& b); //rule of three 2-assignment operator

~Vector (); //rule of three 3-destructor

};

Vector o(unsigned int a); //zero vector
Vector operator+ (Vector a, Vector b); //a+b
Vector operator- (Vector a, Vector b); //a-b
bool operator== (Vector a, Vector b); //a == b
Vector operator* (double a, Vector b); //a*b
Vector operator/ (Vector b, double a); //b/a
