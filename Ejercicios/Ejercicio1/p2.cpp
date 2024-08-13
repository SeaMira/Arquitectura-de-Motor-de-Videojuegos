// Sebastian Mira Pacheco

#include "p1.cpp"
#include <vector>
#include <algorithm>
#include <format>
#include <iostream>

template <typename T>
class Actor {
    public:
        void update(double dt) {
            posicion2D += dt * velocidad2D;
        }

    private:
        Vector2D<T> posicion2D;
        Vector2D<T> velocidad2D;
        BoundingBox<T> bounding_box;

};