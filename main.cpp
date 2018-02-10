#include <iostream>
#include <cassert>
#include <stdlib.h>
#include "polygon.h"
#include "vertex.h"

bool check_if_initial(const Polygon<Vertex> &in);
void move_flea_a(Polygon<Vertex> &in, Flea &fin);
void move_flea_b(Polygon<Vertex> &in, Flea &fin);
Polygon<Vertex>::Iterator find_flea_a(Polygon<Vertex> &in);
Polygon<Vertex>::Iterator find_flea_b(Polygon<Vertex> &in);
void printer(const Polygon<Vertex> &in, const int moves_in);

int main(int argc, char** argv){
    int size = atoi(argv[1]);
    Polygon<Vertex> p(size);
    Flea a, b;

	p.push_back(Vertex(1, true, false));
	p.push_back(Vertex(2, false, true));
    for (int i = 3; i < size + 1; i++) {
        p.push_back(Vertex(i, false, false));
    }

    int moves = 0;

    //printer(p, moves);
    move_flea_a(p, a);
    move_flea_b(p, b);
    moves += 1;

    while (!check_if_initial(p)) {
        //printer(p, moves);
        move_flea_a(p, a);
        move_flea_b(p, b);
        moves += 1;
    }

    //printer(p, moves);
    move_flea_a(p, a);
    move_flea_b(p, b);
    std::cout << moves << std::endl;

    return 0;
}

void printer(const Polygon<Vertex> &in, const int moves_in){
    {
        auto it = in.begin();
        std::cout << "initial config" << std::endl;
        for (int i = 0; i < in.size(); i++) {
            std::cout << (*it).index  << " has flea a? " << (*it).has_flea_a  
                      << " has flea b? " << (*it).has_flea_b  
                      << " state: " << (*it).state << std::endl;
            ++it;
        }
        std::cout << "moves: " << moves_in << std::endl;
        std::cout << std::endl;
    }
}

bool check_if_initial(const Polygon<Vertex> &in){
    auto it = in.begin();
    for (int i = 0; i < in.size(); i++) {
        if ((*it).state == -1) return false;
        ++it;
    }
    return true;
}

void move_flea_a(Polygon<Vertex> &in, Flea &fin){
    auto it = in.begin();
    while (!(*it).has_flea_a) {
        ++it;
    }
    //now it has a flea
    (*it).has_flea_a = false; //flea hops off 
    //std::cout << "flea orientation: " << fin.direction << std::endl;

    if ((*it).state * fin.direction == -1) {
        if ((*it).state == -1) fin.direction *= -1;
        (*it).state *= -1; //update state
        --it; 
        (*it).has_flea_a = true;
    } else { 
        if ((*it).state == -1) fin.direction *= -1;
        (*it).state *= -1; //update state
        ++it; 
        (*it).has_flea_a = true;
    }
}

void move_flea_b(Polygon<Vertex> &in, Flea &fin){
    auto it = in.begin();
    while (!(*it).has_flea_b) {
        ++it;
    }
    //now it has a flea
    (*it).has_flea_b = false; //flea hops off 
    //std::cout << "flea orientation: " << fin.direction << std::endl;

    if ((*it).state * fin.direction == -1) {
        if ((*it).state == -1) fin.direction *= -1;
        (*it).state *= -1; //update state
        --it; 
        (*it).has_flea_b = true;
    } else { 
        if ((*it).state == -1) fin.direction *= -1;
        (*it).state *= -1; //update state
        ++it; 
        (*it).has_flea_b = true;
    }
}

Polygon<Vertex>::Iterator find_flea_a(Polygon<Vertex> &in){
    auto it = in.begin();
    while (!(*it).has_flea_a) {
        ++it;
    }
    return it;
}

Polygon<Vertex>::Iterator find_flea_b(Polygon<Vertex> &in){
    auto it = in.begin();
    while (!(*it).has_flea_b) {
        ++it;
    }
    return it;
}
