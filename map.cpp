#include <map.h>
#include <stdexcept>

Map::Map() {
    vertices = std::vector<QPointF>({QPointF(0, 0), QPointF(0, 100), QPointF(100, 100), QPointF(100, 0)});
    wallHeight = 3;
}

Map::Map(std::vector<QPointF> newVertices, double newWallHeight) {
    if (newVertices.size() != 4) {
        throw std::invalid_argument("Field should consist of 4 vertices");
    }
    vertices = newVertices;
    wallHeight = newWallHeight;
}

const std::vector<QPointF>& Map::getVertices() const {
    return vertices;
}

double Map::getWallHeight() const {
    return wallHeight;
}
