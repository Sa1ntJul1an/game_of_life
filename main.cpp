#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <vector>
#include <random>
#include <cmath>

#include "cell.h"

// mingw32-make.exe

using namespace sf;
using namespace std;

// width in height, in grid cells
const int WIDTH = 100;
const int HEIGHT = 100;

// size of cell, pixels
const int CELL_SIZE = 10;

int main(){

    vector<float> mousePosition;

    vector<vector<Cell>> cells;

    for (int row = 0; row < WIDTH; row ++){
        vector<Cell> column;
        for (int col = 0; col < HEIGHT; col ++){
            Cell cell({row, col});
            column.push_back(cell);
        }
        cells.push_back(column);
    }

    bool gameRunning = false;

    int generation = 0;
    int population;

    // RENDER WINDOW
    // =======================================================================
    RenderWindow renderWindow(VideoMode(WIDTH * CELL_SIZE, HEIGHT * CELL_SIZE), "Game of Life");
    renderWindow.setFramerateLimit(10);
    // =======================================================================

    Font font;
    FileInputStream fontIn;
    fontIn.open("slkscr.ttf");
    font.loadFromStream(fontIn);

    Text generationText;
    generationText.setFillColor(Color::Red);
    generationText.setPosition(10, 10);
    generationText.setFont(font);
    generationText.setCharacterSize(30);

    Text populationText;
    populationText.setFillColor(Color::Red);
    populationText.setPosition(10, 40);
    populationText.setFont(font);
    populationText.setCharacterSize(30);

    RectangleShape cellRect(Vector2f(CELL_SIZE, CELL_SIZE));

    while(renderWindow.isOpen()){

        population = 0;

        mousePosition = {float(Mouse::getPosition(renderWindow).x), float(Mouse::getPosition(renderWindow).y)};

        if (Mouse::isButtonPressed(Mouse::Left)){       // alive cells
            int row = mousePosition[0] / CELL_SIZE;
            int col = mousePosition[1] / CELL_SIZE;

            if (row < WIDTH && row > 0 && col < HEIGHT && col > 0) {
                cells[row][col].setLiving(true);
            }

        } else if (Mouse::isButtonPressed(Mouse::Right))       // kill cells
        {
            int row = mousePosition[0] / CELL_SIZE;
            int col = mousePosition[1] / CELL_SIZE;

            if (row < WIDTH && row > 0 && col < HEIGHT && col > 0) {
                cells[row][col].setLiving(false);
            }
        }

        if (gameRunning){
            generation ++;

            for (int row = 0; row < WIDTH; row ++){
                for (int col = 0; col < HEIGHT; col ++){
                    int living_neighbors = 0;

                    for (int row_offset = -1; row_offset < 2; row_offset ++){
                        for (int col_offset = -1; col_offset < 2; col_offset++){
                            if (row_offset == 0 && col_offset == 0){
                                continue;
                            }else if (row + row_offset < 0 || row + row_offset >= WIDTH || col + col_offset < 0 || col + col_offset >= HEIGHT){
                                continue;
                            }
                            
                            if (cells[row + row_offset][col + col_offset].getLivingStatus()){
                                living_neighbors ++;
                            }
                        }

                        if (living_neighbors >= 4 ){
                                    break;
                        }
                    }

                    cells[row][col].setNeighbors(living_neighbors);
                    cells[row][col].update();

                }
            }
        }


        // KEYBOARD EVENTS =========================================
        if (Keyboard::isKeyPressed(Keyboard::Space)){   // space to pause / unpause
            gameRunning = !gameRunning;
        }
        if (Keyboard::isKeyPressed(Keyboard::R)){       // R to reset
            for (int row = 0; row < WIDTH; row++){
                for (int col = 0; col < HEIGHT; col++){
                    cells[row][col].setLiving(false);
                    cells[row][col].resetAge();
                }
            }
            generation = 0;
            population = 0;
            gameRunning = false;
        }
        // =========================================================


        // CLOSE WINDOWS IF X PRESSED
        // ==========================================================
        Event renderWindowEvent;

        while(renderWindow.pollEvent(renderWindowEvent)){
            
            if(renderWindowEvent.type == Event::Closed){
                renderWindow.close();
            }
        }
        // ==========================================================


        // DRAW CELLS
        // ==========================================================
        renderWindow.clear();

        for (int row = 0; row < WIDTH; row ++){
            for (int col = 0; col < WIDTH; col ++){
                if (cells[row][col].getLivingStatus()){
                    population ++;
                    vector<int> cellPosition = cells[row][col].getPosition();
                    cellRect.setPosition(Vector2f(double(cellPosition[0] * CELL_SIZE), double(cellPosition[1] * CELL_SIZE)));
                    
                    int redIntensity = cells[row][col].getAge() * 5;
                    if (redIntensity > 255) {
                        redIntensity = 255;
                    }

                    Color color(redIntensity, 60, 60);
                    cellRect.setFillColor(color);

                    renderWindow.draw(cellRect);
                }
            }
        }
        // ==========================================================

        populationText.setString("Population: " + to_string(population));
        generationText.setString("Generation: " + to_string(generation));

        renderWindow.draw(generationText);
        renderWindow.draw(populationText);

        renderWindow.display();

    }

    return 0;
}
