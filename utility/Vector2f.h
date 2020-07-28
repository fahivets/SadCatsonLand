#ifndef B42B_VECTOR2F_H_INCLUDE
#define B42B_VECTOR2F_H_INCLUDE

/*
    TODO check and change methods: 
    - multiply
    - divide Vec1/Vec2 -> bag: divide lhv vectors
*/

struct Vector2f
{
    // Variables
    float x;
    float y;

    // Constructors/Destructors
    constexpr Vector2f(float xValue = 0.0f, float yValue = 0.0f);
    constexpr Vector2f(const Vector2f& rVec);
    constexpr Vector2f(Vector2f&& rrVec) noexcept = default;
    ~Vector2f() = default;

    Vector2f& operator=(const Vector2f& rVec) = default;
    Vector2f& operator=(Vector2f&& rrVec) noexcept = default;

    // Functions
    float magnitudeSqrt() const;
    float magnitude() const;
    Vector2f normalize();
    
    // Operators
    Vector2f& operator+=(const Vector2f& rVec);
    Vector2f& operator-=(const Vector2f& rVec);
    Vector2f& operator*=(const Vector2f& rVec);
    Vector2f& operator/=(const Vector2f& rVec);
    
    friend Vector2f operator+(Vector2f& rVec1, const Vector2f& rVec2);
    friend Vector2f operator-(Vector2f& rVec1, const Vector2f& rVec2);
    friend Vector2f operator*(Vector2f& rVec1, const Vector2f& rVec2);
    friend Vector2f operator/(Vector2f& rVec1, const Vector2f& rVec2);
    friend std::ostream& operator<<(std::ostream& out, const Vector2f& vec);

    Vector2f& operator+=(const float& rVal);
    Vector2f& operator-=(const float& rVal);
    Vector2f& operator*=(const float& rVal);
    Vector2f& operator/=(const float& rVal);

    friend Vector2f operator+(Vector2f& rVec1, const float& rVal);
    friend Vector2f operator-(Vector2f& rVec1, const float& rVal);
    friend Vector2f operator*(Vector2f& rVec1, const float& rVal);
    friend Vector2f operator/(Vector2f& rVec1, const float& rVal);
};

#endif