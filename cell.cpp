#include "cell.h"
#include <vector>

Cell::Cell (std::vector<int> position){
    _age = 0;
    _position = position;
    _isLiving = false;
}

void Cell::setNeighbors(int neighbors){
    _neighbors = neighbors;
}

bool Cell::getLivingStatus(){
    return _isLiving;
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
    _isLiving = isLiving;
}

void Cell::update(){
    if (_isLiving){                 // cell is alive
        if (_neighbors < 2){
            _isLiving = false;          // dead, underpopulation
        } else if (_neighbors < 4){
            _isLiving = true;           // alive, good population
            _age ++;
        }else {
            _isLiving = false;          // dead, overpopulation
        }
    } else {                        // cell is dead
        if (_neighbors == 3){
            _isLiving = true;           // alive, reproduction
            _age = 0;
        }
    }
}
