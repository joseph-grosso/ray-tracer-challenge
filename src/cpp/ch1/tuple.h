class Tuple {
    public:
        float x;  // Attribute
        float y;  // Attribute
        float z;  // Attribute
        float w;  // Attribute
        Tuple(float x, float y, float z, float w);
        bool isPoint();
        bool isVector();
};

bool equalByEpsilon(float a, float b, float epsilon = 0.00001);

// Functions to create tuples
Tuple point(float x, float y, float z);
Tuple vector(float x, float y, float z);

// Arithmetic operators
bool operator==(Tuple lhs, Tuple rhs);
Tuple operator+(Tuple lhs, Tuple rhs);
Tuple operator-(Tuple tup);
Tuple operator-(Tuple lhs, Tuple rhs);
Tuple operator*(Tuple tup, float a);
Tuple operator*(float a, Tuple tup);
Tuple operator/(Tuple tup, float a);
