#include<iostream>
#include "weapon.h"
#include "agent.h"

using namespace std;

void Weapon1::attack(Agent &enemy) const {
    int enemy_hp = enemy.gethp();
    enemy.sethp(enemy_hp - dmg);
    if (enemy.gethp() < 0)
        enemy.sethp(0);
}

void Weapon2::attack(Agent &enemy) const {
    int enemy_hp = enemy.gethp();
    enemy.sethp(enemy_hp - dmg);
    if (enemy.gethp() < 0)
        enemy.sethp(0);
}

void Weapon3::attack(Agent &enemy) const {
    int enemy_hp = enemy.gethp();
    enemy.sethp(enemy_hp - dmg);
    if (enemy.gethp() < 0) {
        enemy.sethp(0);
    }
}