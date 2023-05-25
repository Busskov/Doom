#ifndef MONSTERS_H
#define MONSTERS_H

#include <vector>
#include <classes/monster.h>

class Monsters {
public:
    Monsters();
    Monsters(const std::vector<Monster>&);

    void addMonster(const Monster&);
    void removeMonster(std::size_t index);
    std::vector<Monster>& getMonsters();

private:
    std::vector<Monster> monsters;

};

#endif // MONSTERS_H
