#include "cell.h"
#include <vector>

Cell::Cell (std::vector<int> position){
    _age = 0;
    _position = position;
    _isLiving_current = false;
}

void Cell::setNeighbors(int neighbors){
    _neighbors = neighbors;
}

bool Cell::getLivingStatus(){
    return _isLiving_current;
}

int Cell::getAge(){
    return _age;
}

void Cell::resetAge(){
    _age = 0;
}

std::vector<int> Cell::getPosition(){
    return _position;
}

void Cell::setLiving(bool isLiving){
    _isLiving_current = isLiving;
}

void Cell::determineNextState(){
    if (_isLiving_current){                 // cell is alive
        if (_neighbors < 2){
            _isLiving_next = false;          // dead, underpopulation
        } else if (_neighbors < 4){
            _isLiving_next = true;           // alive, good population
            _age ++;
        }else {
            _isLiving_next = false;          // dead, overpopulation
        }
    } else {                        // cell is dead
        if (_neighbors == 3){
            _isLiving_next = true;           // alive, reproduction
            _age = 0;
        }
    }
}

void Cell::update(){
    _isLiving_current = _isLiving_next;
}
