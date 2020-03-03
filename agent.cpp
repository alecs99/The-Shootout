#include<iostream>
#include<cstdlib>
#include<cmath>
#include "weapon.h"
#include "agent.h"
#include "game.h"

using namespace std;

Agent::Agent() {
    alive = true;
    hp = 100;
    fov = 10;//aria de acoperire a agentului
    coordinate_x = coordinate_y = 0;
    switch (rand() % weapon_number) { //ii atribuim o arma la intamplare din numarul de arme
        case 0:
            wep = new Weapon1
            break;
        case 1:
            wep = new Weapon2;
            break;
        case 2:
            wep = new Weapon3;
            break;
        default:
            cout << "Nici o arma nu a fost aleasa!" << endl;
            exit(0);

    }
}

Agent::~Agent() {
    alive = false;
    hp = 0;
}

void Agent::spawn(int coord_x, int coord_y) { //ii atribuim coordonate unui agent
    coordinate_x = coord_x;
    coordinate_y = coord_y;
}

void Agent::sethp(int value) { //ii modificam viata unui agent
    hp = value;
}

int Agent::gethp() { //functie care returneaza viata unui agent
    return hp;
}

bool Agent::is_alive() const { //functia care ne spune daca un agent e in viata sau nu
    return hp > 0;

}

void Agent::move(int &cord_x, int &cord_y) {
    int step = 5; //pasii pe care ii poate un agent sa ii faca,in cazul nostru jumatate din aria sa de acoperire
    if (coordinate_y < length - 1) {//daca agentul nu se afla in marginea dreapta a mapei se tot plimba la stanga
        cord_x = coordinate_x;
        cord_y = coordinate_y + step;
    } else if (coordinate_y ==
               length - 1) {//in momentul in care a ajuns la margine acesta coboara sau urca o linie dupa caz
        if (coordinate_x == height - 1) {
            cord_x = coordinate_x - 1;
            cord_y = coordinate_y;
        } else {
            cord_x = coordinate_x + 1;
            cord_y = coordinate_y;
        }
    }
}

void Agent::get_cord(int &cord_x, int &cord_y) { //returneaza coordonatele agentului
    cord_x = coordinate_x;
    cord_y = coordinate_y;
}

int Agent::get_fov() {//returneaza aria de acoperire
    return fov;
}

void Agent::attack(Agent &enemy) const { //functia de atac a unui agent in functie de ce arma are
    wep->attack(enemy);
}

bool Agent::operator!=(
        Agent second) { //supraincarcarea operatorului != pentru a verifica daca un agent e diferit de altul acestia difera prin coordonate
    int cord_x_f, cord_y_f, cord_x_s, cord_y_s;
    this->get_cord(cord_x_f, cord_y_f);
    second.get_cord(cord_x_s, cord_y_s);
    if (cord_x_f != cord_x_s) {
        if (cord_y_f != cord_y_s)
            return true;
    }
    return false;
}