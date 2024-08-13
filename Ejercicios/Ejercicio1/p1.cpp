// Sebastian Mira Pacheco

#include <vector>
#include <algorithm>
#include <format>
#include <iostream>

template <typename T>
struct Vector2D
{
    T x, y;

    Vector2D<T>& operator+=(const Vector2D<T>& rhs)
    {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }

    Vector2D<T> operator+(const Vector2D<T>& rhs)
    {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }

    Vector2D<T>& operator*=(const T scale)
    {
        x *= scale;
        y *= scale;
        return *this;
    }

    Vector2D<T> operator*(const T scale)
    {
        T X = x * scale;
        T Y = y * scale;
        return Vector2D<T>{X,Y};
    }

    Vector2D<T> operator-(const Vector2D<T>& rhs)
    {
        x -= rhs.x;
        y -= rhs.y;
        return *this;
    }

};

template <typename T>
std::ostream& operator<<(std::ostream& os, const Vector2D<T>& vec)
{
    return os << "( " << vec.x << " , " << vec.y << " )";
}

template <typename T>
class BoundingBox {
    public:
        BoundingBox() {
            LDCorner = Vector2D<T>{0.0, 0.0};
            TRCorner = Vector2D<T>{0.0, 0.0};
        }

        BoundingBox(Vector2D<T> LDCorner, Vector2D<T> TRCorner) {
            this->LDCorner = LDCorner;
            this->TRCorner = TRCorner;
        }

        const Vector2D<T>& getLDCorner() const {
            return this->LDCorner;
        }

        const Vector2D<T>& getTRCorner() const {
            return this->TRCorner;
        }

        void setLDCorner(const Vector2D<T>& vec) {
            this->LDCorner = vec;
        }

        void setTRCorner(const Vector2D<T>& vec) {
            this->TRCorner = vec;
        }


    private: 
        Vector2D<T> LDCorner, TRCorner;
};

template<typename T> 
void enclose(BoundingBox<T>& box, Vector2D<T>& vec) {
    Vector2D<T> LDCorner = box.getLDCorner(), TRCorner = box.getTRCorner();
    T newLDX = LDCorner.x, newLDY = LDCorner.y, newTRX = TRCorner.x, newTRY = TRCorner.y;

    if (vec.x > TRCorner.x ) {
        newTRX = vec.x;
    } 
    else if ( vec.x < LDCorner.x ) {
        newLDX = vec.x;
    }

    if (vec.y > TRCorner.y ) {
        newTRY = vec.y;
    } 
    else if ( vec.y < LDCorner.y ) {
        newLDY = vec.y;
    }

    box.setLDCorner(Vector2D<T>{newLDX, newLDY});
    box.setTRCorner(Vector2D<T>{newTRX, newTRY});

}