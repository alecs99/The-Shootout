#ifndef PROIECT_2_AGENT_H
#define PROIECT_2_AGENT_H

class Weapon;

class Agent {
public:
    Agent();

    ~Agent();

    void spawn(int coord_x, int coord_y);

    void get_cord(int &coord_x, int &coord_y);

    int get_fov();

    void sethp(int value);

    int gethp();

    void attack(Agent &enemy) const;

    void move(int &cord_x, int &cord_y);

    bool is_alive() const;

    bool operator!=(Agent second);

protected:
    bool alive;
    int hp;
    int fov;
    int coordinate_x, coordinate_y;
    int weapon_number = 3;
    Weapon *wep;
};

#endif
