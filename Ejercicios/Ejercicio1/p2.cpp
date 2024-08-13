// Sebastian Mira Pacheco

#include "p1.cpp"
#include <vector>
#include <algorithm>
#include <format>
#include <iostream>

template <typename T>
class Actor {
    public:
        Actor(Vector2D<T> pos, Vector2D<T> vel) {
            posicion2D = pos;
            velocidad2D = vel;
            bounding_box = BoundingBox(pos-Vector2D<T>{0.5, 0.5}, pos+Vector2D<T>{0.5, 0.5});
        }

        Actor(Vector2D<T> pos, Vector2D<T> vel, T size) {
            posicion2D = pos;
            velocidad2D = vel;
            bounding_box = BoundingBox(pos-Vector2D<T>{size/2, size/2}, pos+Vector2D<T>{size/2, size/2});
        }

        Actor() {
            posicion2D = Vector2D<T>{0.0, 0.0};
            velocidad2D = Vector2D<T>{0.0, 0.0};
            bounding_box = BoundingBox(Vector2D<T>{-0.5, -0.5}, Vector2D<T>{0.5, 0.5});
        }

        void update(double dt) {
            std::cout << posicion2D << std::endl;
            std::cout << velocidad2D*dt << std::endl;
            posicion2D += velocidad2D*dt;
        }

        const BoundingBox<T>& getBoundingBox() const {
            return bounding_box;
        }

    private:
        Vector2D<T> posicion2D;
        Vector2D<T> velocidad2D;
        BoundingBox<T> bounding_box;

};


template <typename T>
bool pointInSquare(T xleft, T xright, T ybottom, T ytop, T x, T y) {
    return (xleft <= x && x <= xright) && (ybottom <= y && y <= ytop);
}


template <typename T>
bool boxesCollision(BoundingBox<T> box1, BoundingBox<T> box2) {
    Vector2D<T> LD1 = box1.getLDCorner();
    Vector2D<T> TR1 = box1.getTRCorner();
    T min1x = LD1.x, min1y = LD1.y;
    T max1x = TR1.x, max1y = TR1.y;

    Vector2D<T> LD2 = box2.getLDCorner();
    Vector2D<T> TR2 = box2.getTRCorner();
    T min2x = LD2.x, min2y = LD2.y;
    T max2x = TR2.x, max2y = TR2.y;

    return pointInSquare(min1x, max1x, min1y, max1y, min2x, min2y) ||
            pointInSquare(min1x, max1x, min1y, max1y, max2x, min2y) ||
            pointInSquare(min1x, max1x, min1y, max1y, max2x, max2y) ||
            pointInSquare(min1x, max1x, min1y, max1y, min2x, max2y) ||
            pointInSquare(min2x, max2x, min2y, max2y, min1x, min1y) ||
            pointInSquare(min2x, max2x, min2y, max2y, max1x, min1y) ||
            pointInSquare(min2x, max2x, min2y, max2y, max1x, max1y) ||
            pointInSquare(min2x, max2x, min2y, max2y, min1x, max1y);
}

int main() {
    Actor<double> actor1({5.0, 0.0}, {-1.0, 0.0}), actor2({-5.0, 0.0}, {1.0, 0.0});
    BoundingBox<double> b1 = actor1.getBoundingBox(), b2 = actor2.getBoundingBox();
    while (!boxesCollision(b1, b2)) {
        // std::cout << b1.getLDCorner() << " " << b2.getLDCorner();
        actor1.update(0.5);
        actor2.update(0.5);
        b1 = actor1.getBoundingBox(), b2 = actor2.getBoundingBox();
    }
    std::cout << "actor" << std::endl;
    return 0;
}