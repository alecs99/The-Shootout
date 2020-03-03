#ifndef PROIECT_2_GAME_H
#define PROIECT_2_GAME_H
const int height = 25;
const int length = 25;

class Weapon;

class Agent;

class Game {
    Agent *agents;
    char **map;
    int alive_agents, nr_agents , armours ;

public:
    Game();

    void drop_armours();

    void drop_agents();

    void initial_situation();

    void print_map();

    int find_enemy(Agent &agent) const;

    void attack_simulator();

    void round_simulator(int nr_rounds);

    void start_game(int agent,int armour);
};

#endif
