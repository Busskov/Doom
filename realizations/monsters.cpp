#include <classes/monsters.h>

Monsters::Monsters() {
    monsters = std::vector<Monster>(0);
}

Monsters::Monsters(const std::vector<Monster>& newMonsters) {
    monsters = newMonsters;
}

void Monsters::addMonster(const Monster& monster) {
    monsters.push_back(monster);
}

void Monsters::removeMonster(std::size_t index) {
    monsters.erase(monsters.begin() + index);
}

std::vector<Monster>& Monsters::getMonsters() {
    return monsters;
}
