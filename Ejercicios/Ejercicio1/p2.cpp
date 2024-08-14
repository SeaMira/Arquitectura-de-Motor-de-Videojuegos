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
            // std::cout << posicion2D << std::endl;
            // std::cout << velocidad2D*dt << std::endl;
            posicion2D += velocidad2D*dt;
            bounding_box.setLDCorner(bounding_box.getLDCorner() + velocidad2D*dt);
            bounding_box.setTRCorner(bounding_box.getTRCorner() + velocidad2D*dt);
        }

        const Vector2D<T>& getPos() const { return posicion2D; }

        const BoundingBox<T>& getBoundingBox() const {
            return bounding_box;
        }
        

    private:
        Vector2D<T> posicion2D;
        Vector2D<T> velocidad2D;
        BoundingBox<T> bounding_box;

};


template <typename T>
std::ostream& operator<<(std::ostream& os, const Actor<T>& actor)
{
    return os << "Pos:" << actor.getPos() << " , Bounding Box -" << actor.getBoundingBox();
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

    bool top12 = max1y >= max2y && max2y >= min1y;
    bool top21 = max2y >= max1y && max1y >= min2y;
    bool side12 = max1x >= max2x && max2y >= min1x;
    bool side21 = max2x >= max1x && max1x >= min2x;

    bool topAndSide1 = top12 && side12;
    bool topAndSide2 = top12 && side21;
    bool topAndSide3 = top21 && side12;
    bool topAndSide4 = top21 && side21;

    return topAndSide1 || topAndSide2 || topAndSide3 || topAndSide4;
}

template <typename T>
bool actorsCollide(Actor<T>& actor1, Actor<T>& actor2) {
    BoundingBox<T> b1 = actor1.getBoundingBox(), b2 = actor2.getBoundingBox();
    return boxesCollision(b1, b2);
}

int main() {
    Actor<double> actor1({5.0, 0.0}, {-1.0, 0.0}), actor2({-5.0, 0.0}, {1.0, 0.0});
    while (!actorsCollide(actor1, actor2)) {
        std::cout << "actor1 " << actor1 << std::endl;
        std::cout << "actor2 " << actor2 << std::endl;
        actor1.update(0.5);
        actor2.update(0.5);
    }
    std::cout << "actor1 " << actor1 << std::endl;
    std::cout << "actor2 " << actor2 << std::endl;
    std::cout << "Bounding Boxes Collided!" << std::endl;
    return 0;
}