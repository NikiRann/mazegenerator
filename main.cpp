#include <iostream>
#include <fstream>
#include <stdio.h>
#include <cstring>
#include <time.h>  
#include <stack>
#include <vector>



struct Point
{
    int y;
    int x;
};


bool ended = false;


void constructMaze(std :: string _maze[], int &_sizeY, int &_sizeX) {
    for (int i = 0; i < _sizeY; i ++) {
        std :: string init;
        if (i == 0 || i == (_sizeY - 1)) {
            std :: string _pusher (_sizeX / 2 + 1, '-');
            init = _pusher;
        } else {
            std :: string _pusher (_sizeX / 2 + 1, '#');
            
            _pusher[0] = '|';
            _pusher[_sizeX / 2] = '|';
            if (i % 2 != 0) 
                for (int j = 1; j < _sizeX / 2; j += 2) 
                    _pusher[j] = ' ';
            
            init = _pusher;
        }

        _maze[i] = init;
    }

}

void printMaze(std :: string _maze[], int &_sizeY, int &_sizeX, Point _start, Point _finish) {
    std :: ofstream result ("maze.txt");
    if (result.is_open())
    {
        for (int i = 0; i < _sizeY; i ++) {
            for (int j = 0; j <= _sizeX / 2; j ++) {
                if (j != 0 && j != _sizeX / 2) {
                    if (j == _start.x && i == _start.y)
                        result << 'S' << ' ';
                    else if (j == _finish.x && i == _finish.y)
                        result << ' ' << 'E';
                    else
                        result << _maze[i][j] << _maze[i][j];
                } else { 
                    result << _maze[i][j];
                }
            }
            result << std :: endl;
        }
        result.close();
    }
    else std :: cout << "Unable to open file";

}



bool stepDown(std :: string maze[], Point p, int stepSize, int _sizeY, int _sizeX, std :: vector <std :: vector <bool>> visited) { 
    if (p.y >= _sizeY - stepSize - 1)
        return false;
    if (visited[(p.y + stepSize) / 2][p.x / 2])
        return false;

    for (int y = p.y; y < p.y + stepSize; y ++) {
        maze[y][p.x] = ' ';
    }
    return true;
}

bool stepUp(std :: string maze[], Point p, int stepSize, int _sizeY, int _sizeX, std :: vector <std :: vector <bool>> visited){ 
    if (p.y <= stepSize)
        return false;
    if (visited[(p.y - stepSize) / 2][p.x / 2])
        return false;
    for (int y = p.y; y > p.y - stepSize; y --) {
        maze[y][p.x] = ' ';
    }
    return true;
}

bool stepRight(std :: string maze[], Point p, int stepSize, int _sizeY, int _sizeX, std :: vector <std :: vector <bool>> visited){ 
    if (p.x >= _sizeX - stepSize)
        return false;
    if (visited[p.y / 2][(p.x + stepSize) / 2])
        return false;
    for (int x = p.x; x < p.x + stepSize; x ++) {
        maze[p.y][x] = ' ';
    }
    return true;
}

bool stepLeft(std :: string maze[], Point p, int stepSize, int _sizeY, int _sizeX, std :: vector <std :: vector <bool>> visited){ 
    if (p.x <= stepSize)
        return false;
    if (visited[p.y / 2][(p.x - stepSize) / 2])
        return false;
    for (int x = p.x; x > p.x - stepSize; x --) {
        maze[p.y][x] = ' ';        
    }
    return true;
}


int generateDirection(bool *possibleDirs) {
    std :: vector <int> dirs;
    int possible = 0;
    if (possibleDirs[0]) {
        dirs.push_back(1);
        possible++;
    }
    if (possibleDirs[1]) {
        dirs.push_back(2);
        possible++;
    }
    if (possibleDirs[2]) {
        dirs.push_back(3);
        possible++;
    }
    if (possibleDirs[3]) {
        dirs.push_back(4);
        possible++;
    }
    return ((possible == 0) ? 0 : dirs[rand() % possible]);
}

// 1 - up
// 2 - right
// 3 - down
// 4 - left

void generatePathRecursive(std::string maze[], Point start, int _sizeY, int _sizeX, std :: stack <Point> &path, std :: vector <std :: vector <bool>> visited) {


    visited[start.y / 2][start.x / 2] = true;
    bool validDirection = false;
    
    bool possibleDirections[4] = {1, 1, 1, 1};
    bool *dirPointer = possibleDirections;
    
    while (!validDirection && !ended) {

        int direction = generateDirection(dirPointer);
        
        if (direction == 1) {
            if (stepUp(maze, start, 2, _sizeY, _sizeX, visited)) {
                validDirection = true;
                path.push(Point{start.y - 2, start.x});
                generatePathRecursive(maze, path.top(), _sizeY, _sizeX, path, visited);
            } else {
                possibleDirections[0] = 0;
            }
        }
        if (direction == 2) {
            if (stepRight(maze, start, 2, _sizeY, _sizeX, visited)) {
                validDirection = true;
                path.push(Point{start.y, start.x + 2});
                generatePathRecursive(maze, path.top(), _sizeY, _sizeX, path, visited);
            } else {
                possibleDirections[1] = 0;
            }
        }
        if (direction == 3) {
            if (stepDown(maze, start, 2, _sizeY, _sizeX, visited)) {
                validDirection = true;
                path.push(Point{start.y + 2, start.x});
                generatePathRecursive(maze, path.top(), _sizeY, _sizeX, path, visited);
            }  else {
                possibleDirections[2] = 0;
            }
        }
        if (direction == 4) {
            if (stepLeft(maze, start, 2, _sizeY, _sizeX, visited)) {
                validDirection = true;
                path.push(Point{start.y, start.x - 2});
                generatePathRecursive(maze, path.top(), _sizeY, _sizeX, path, visited);
            }  else {
                possibleDirections[3] = 0;
            }
        }
        if ((!possibleDirections[0] && !possibleDirections[1] && !possibleDirections[2] && !possibleDirections[3]) || direction == 0){
            path.pop();
            
            if (path.empty() || (start.y == 1 && start.x == 1)) {
               ended = true;
               return;
            } else {
                generatePathRecursive(maze, path.top(), _sizeY, _sizeX, path, visited);
            }
        }
    }

}

std :: string formatLastRow(std :: string maze[], int _sizeX, int _sizeY) {
    std :: string result (_sizeX / 2 + 1, '#');
    result[0] = '|';
    result[_sizeX / 2] = '|';
    for (int i = 1; i < (_sizeX / 2 - 4); i += 2) {
        if (maze[_sizeY - 3][i] == ' ')
            if (rand() % 2)
               result[i] = ' ';
    }
    return result;
}

int main() {
    
    int sizeY = 20;
    int sizeX = 80;
    
    std :: string maze[sizeY]; 
    
    const Point start = {1, 1};
    const Point finish = {18, 39}; 
    srand(time(NULL));

    constructMaze(maze, sizeY, sizeX);
    
    std :: stack <Point> path;

    std :: vector <std :: vector <bool>> visited;
    for (int i = 0; i < sizeY / 2 - 1; i ++) {
        std :: vector <bool> pusher (sizeX / 4, false);
        visited.push_back(pusher);
    }

    path.push(start);
    
    generatePathRecursive(maze, start, sizeY, sizeX / 2, path, visited);
    
    maze[sizeY - 2] = formatLastRow(maze, sizeX, sizeY);
    
    printMaze(maze, sizeY, sizeX, start, finish);

    
    return 0;
}