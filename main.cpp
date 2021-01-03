#include <iostream>
#include <fstream>
#include <stdio.h>
#include <cstring>



struct Point
{
    int x;
    int y;
};
void constructMaze(char *_maze[], int &_sizeY, int &_sizeX) {
    for (int i = 0; i < _sizeY; i ++) {
        _maze[i] = new char[_sizeX];
    }
    for (int i = 0; i < _sizeY; i ++) {
        if (i == 0 || i == _sizeY - 1)
            memset(_maze[i], '-', _sizeX);
        else {
            memset(_maze[i], '#', _sizeX);
            _maze[i][0] = '|';
            _maze[i][_sizeX - 1] = '|';
        }
        _maze[i][_sizeX] = '\0';

    }
}
void printMaze(char *_maze[], int &_sizeY, int &_sizeX) {
    for (int i = 0; i < _sizeY; i ++) {
        std :: cout << _maze[i] << '\n';
    }
}

int main() {
    
    int sizeY = 5;
    int sizeX = 10;
    
    char *maze[sizeY]; 
    
    Point start, finish;
    
    constructMaze(maze, sizeY, sizeX);
    printMaze(maze, sizeY, sizeX);
    //std :: cin >> start.y >> start.x >> finish.y >> finish.x;
    
  
    return 0;
}