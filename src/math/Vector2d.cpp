#include <cmath>

namespace GumsEngine
{

    struct Vector2
    {
        float x, y;

        // construtores //
        Vector2() : x(0), y(0) {}
        Vector2(float x, float y) : x(x), y(y) {}

        // Operadores //
        // Soma entre vetores//
        Vector2 operator+(const Vector2 &other) const
        {
            return Vector2(x + other.x, y + other.y);
        }

        // subtracao entre vetores
        Vector2 operator-(const Vector2 &other) const
        {
            return Vector2(x - other.x, y - other.y);
        }

        Vector2 operator-() const
        {
            return Vector2(-x, -y);
        }

        // Escalar (vetor x escalar)
        Vector2 operator*(float scalar) const
        {
            return Vector2(x * scalar, y * scalar);
        }

        Vector2 operator/(float scalar) const
        {
            return Vector2(x / scalar, y / scalar);
        }

        // Produto escalar (vetor x vetor)
        float operator*(const Vector2 &other) const
        {
            return x * other.x + y * other.y;
        }

        Vector2 &operator+=(const Vector2 &other)
        {
            x += other.x;
            y += other.y;
            return *this;
        }

        Vector2 &operator-=(const Vector2 &other)
        {
            x -= other.x;
            y -= other.y;
            return *this;
        }

        Vector2 &operator*=(float scalar)
        {
            x *= scalar;
            y *= scalar;
            return *this;
        }

        Vector2 &operator/=(float scalar)
        {
            x /= scalar;
            y /= scalar;
            return *this;
        }

        bool operator==(const Vector2 &other) const
        {
            return x == other.x && y == other.y;
        }

        bool operator!=(const Vector2 &other) const
        {
            return x != other.x && y != other.y;
        }

        float magnitude() const
        {
            return std::sqrt(x * x + y * y);
        }

        Vector2 normalized() const
        {
            float mag = magnitude();
            if (mag > 0)
                return Vector2(x / mag, y / mag);
            return Vector2(0, 0);
        }

        static float distance(const Vector2 a, const Vector2 b)
        {
            return (a - b).magnitude();
        }
    };

}