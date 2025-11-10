#include <iostream>
#include "statblock.h"
#include "pointwell.h"
#include "player.h"
#include <cstdint>
#include <memory>

int main() {

    Player player;
    player.setEntityName("MIKE");
    player.isDead();

    std::cout << player.getEntityName() << '\n';

    return 0;
}
