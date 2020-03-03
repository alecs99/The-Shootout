#include <iostream>
#include "map.h"
#include "game.h"
using namespace std;
int main() {
    int nr_agents=18;
    int nr_armours=25;
    Game b;
    b.start_game(nr_agents,nr_armours);
    return 0;
}