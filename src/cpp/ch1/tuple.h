class Tuple {
    public:
        float x;  // Attribute
        float y;  // Attribute
        float z;  // Attribute
        float w;  // Attribute
        Tuple(float x, float y, float z, float w);
        bool isPoint();
        bool isVector();
        bool operator== (Tuple & rhs);
        Tuple operator+(Tuple & rhs);
        Tuple operator-(Tuple & rhs);
        Tuple operator-();
};

bool equalByEpsilon(float a, float b, float epsilon = 0.00001);

// Functions to create tuples
Tuple point(float x, float y, float z);

Tuple vector(float x, float y, float z);

