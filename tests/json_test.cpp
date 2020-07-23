//
// Created by nunwan on 20/07/2020.
//

#include <iostream>
#include <fstream>
#include "nlohmann/json.hpp"
using json = nlohmann::json;

int main() {
    json j;
    std::ifstream ifs("data/monsters.json");
    ifs >> j;
    std::cout << j.size();
    for (auto i = j.rbegin(); i != j.rend(); i++) {
        std::cout << i.key() << std::endl;
        for (auto monster = i->rbegin(); monster != i->rend(); monster++) {
            std::cout << monster.key() << " : " << monster.value() << std::endl;
        }
    }
}

