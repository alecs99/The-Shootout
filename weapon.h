
#ifndef PROIECT_2_WEAPON_H
#define PROIECT_2_WEAPON_H
using namespace std;

class Agent;

class Weapon {
public:
    virtual void attack(Agent &enemy) const = 0;
};

class Weapon1 : public Weapon {
public:
    int dmg = 10;

    void attack(Agent &enemy) const;
};

class Weapon2 : public Weapon {
public:
    int dmg = 20;

    void attack(Agent &enemy) const;
};

class Weapon3 : public Weapon {
public:
    int dmg = 30;

    void attack(Agent &enemy) const;
};


#endif
