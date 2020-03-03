#include<iostream>
#include<cmath>
#include "agent.h"
#include "weapon.h"
#include "game.h"

using namespace std;

Game::Game() { //In functia constructor generam mapa pe care vom plasa agentii si armurile
    map = new char *[length];
    for (int i = 0; i < length; i++)
        map[i] = new char[height];
    for (int i = 0; i < length; i++)
        for (int j = 0; j < height; j++)
            map[i][j] = '.';
}

void
Game::drop_armours() { //Functia care pozitioneaza pe harta armurile pe care agentii le pot ridica daca ajung pe ele
    int coordinate_x, coordinate_y;
    for (int i = 0; i < armours; i++) {
        bool occupied;
        do {
            coordinate_x = rand() % 25;
            coordinate_y = rand() % 25;
            occupied = false;
            if (map[coordinate_x][coordinate_y] == 'a')
                occupied = true;
        } while (occupied);
        map[coordinate_x][coordinate_y] = 'a';
    }
}

void Game::drop_agents() { //Functia care pozitioneaza agentii pe harta
    int coordinate_x, coordinate_y;
    agents = new Agent[nr_agents]; //creeam un vector de agenti care au proprietatile din clasa declarata in agent.h
    for (int i = 0; i < nr_agents; i++) {
        bool occupied;
        int armour = 0;
        do {
            coordinate_x = rand() % 25;
            coordinate_y = rand() % 25;
            occupied = false;
            if (map[coordinate_x][coordinate_y] == '1')
                occupied = true;
            if (map[coordinate_x][coordinate_y] == 'a')
                armour = 1;  //Daca pe pozitia pe care agentul se pozitioneaza exista o armura ii adaugam armura caracterului
        } while (occupied);
        map[coordinate_x][coordinate_y] = '1';
        agents[i].spawn(coordinate_x, coordinate_y);
        if (armour) {
            agents[i].sethp(200); //armura ii creste agentului viata cu 100
            armours--;
        }


    }
}

int Game::find_enemy(Agent &agent) const {
    int cord_x, cord_y, cord_x_e, cord_y_e, deltax, deltay, fov;
    fov = agent.get_fov();
    agent.get_cord(cord_x, cord_y);
    for (int i = 0; i < nr_agents; i++) {
        if (agents[i].is_alive()) {
            if (agent != agents[i]) {
                agents[i].get_cord(cord_x_e, cord_y_e);
                deltax = abs(cord_x -
                             cord_x_e);   //verificam daca agentul pe care il verificam se afla in aria de acoperire a agentului care cauta inamic
                deltay = abs(cord_y - cord_y_e);
                if ((deltax <= fov) && (deltay <= fov))
                    return i;

            }

        }

    }
    return -1; //daca nu exista nici un agent in aria de acoperire atunci returneaza -1 si ii permite agentului sa execute o mutare

}

void Game::attack_simulator() {
    int index_e, coordinate_x, coordinate_y, deads = 0;
    for (int i = 0; i < nr_agents; i++) {
        if (agents[i].is_alive()) { //verificam daca agentul mai e in viata
            index_e = find_enemy(agents[i]);
            if (index_e == -1) { //daca nu exista agenti in aria de acoperire a agentului executa manevra de mutare
                agents[i].get_cord(coordinate_x, coordinate_y);
                map[coordinate_x][coordinate_y] = '.';
                bool occupied;
                int armour = 0;
                do {
                    agents[i].move(coordinate_x, coordinate_y);
                    occupied = false;
                    if (map[coordinate_x][coordinate_y] == '1')
                        occupied = true;
                    if (map[coordinate_x][coordinate_y] == 'a')
                        armour = 1;
                } while (occupied);
                agents[i].spawn(coordinate_x, coordinate_y);
                cout << "agentul: " << i << "s-a mutat pe:" << coordinate_x << ' ' << coordinate_y << endl;
                map[coordinate_x][coordinate_y] = '1';
                if (armour) {
                    agents[i].sethp(200);
                    armours--;
                }
            } else { //altfel agentul il ataca pe inamicul gasit iar inamicul riposteaza
                cout << "Agentul:" << i << "il ataca pe agent:" << index_e << endl;
                agents[i].attack(agents[index_e]);
                agents[index_e].attack(agents[i]);
                if ((agents[i].is_alive()) && (!agents[index_e].is_alive())) { //daca unul dintre ei a murit afisam
                    cout << "Agentul:" << i << "il omoara pe:" << index_e << endl;
                    agents[index_e].get_cord(coordinate_x, coordinate_y);
                    map[coordinate_x][coordinate_y] = '.';
                    deads++;
                } else if ((!agents[i].is_alive()) && (agents[index_e].is_alive())) {
                    cout << "Agentul:" << index_e << "il omoara pe:" << i << endl;
                    agents[i].get_cord(coordinate_x, coordinate_y);
                    map[coordinate_x][coordinate_y] = '.';
                    deads++;
                }


            }

        }

    }
    cout << "In aceasta runda au murit:" << deads << endl;
}

void Game::initial_situation() {
    drop_armours();
    drop_agents();
    cout << "Welcome to the Shootout game:" << endl;
    cout << "This is the initial map:" << endl;
    cout << "-------------------------------------------------" << endl;
    print_map();
    cout << "-------------------------------------------------" << endl;
    cout << "Number of agents on the map:" << nr_agents << endl;
    cout << "Number of armours on the map:" << armours << endl;
}

void Game::print_map() {
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < height; j++)
            cout << map[i][j] << ' ';
        cout << endl;
    }
}

void Game::round_simulator(int nr_rounds) {
    for (int i = 0; i < nr_rounds; i++) {
        attack_simulator();

    }
    for (int i = 0; i < nr_agents; i++)
        if (agents[i].is_alive())
            alive_agents = i;


}

void Game::start_game(int agent,int armour) {
    nr_agents=agent;
    armours=armour;
    initial_situation();
    round_simulator(50);
    cout << "-------------------------------------------------" << endl;
    print_map();
    cout << "-------------------------------------------------" << endl;
    cout << "Agentul: " << alive_agents << " e castigator";
}