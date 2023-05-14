#ifndef MAP_H
#define MAP_H

#include <vector>
#include <QPointF>

class Map {
public:
    Map();
    Map(std::vector<QPointF>, double);

    const std::vector<QPointF>& getVertices() const;
    double getWallHeight() const;
private:
    std::vector<QPointF> vertices;
    double wallHeight;

};

#endif // MAP_H
