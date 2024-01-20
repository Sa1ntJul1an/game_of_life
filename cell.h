#ifndef CELL_HEADER
#define CELL_HEADER

#include <vector>

class Cell{
    public:
        Cell(std::vector<int>);

        void setNeighbors(int);

        bool getLivingStatus();

        int getAge();
        
        void resetAge();

        std::vector<int> getPosition();

        void setLiving(bool);

        void update();

    private:
        int _age;
        int _neighbors;
        bool _isLiving;
        std::vector<int> _position;
};

#endif /* !CELL_HEADER */