#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>

using namespace std;

//https://en.wikipedia.org/wiki/Brainfuck

string readInput();
int trajectory(pair<int, int> velocity, pair<pair<int, int>, pair<int, int>> goal);

//debug functions
template <typename T>
void printVector(vector<T> vector);

template <typename T>
void printWrapper(vector<vector<T>> vector);

int main() {
    //write input to vector
    string input = readInput();
    pair<pair<int, int>, pair<int, int>> goal;
    pair<int, int> goalX (stoi(input.substr(input.find("=")+1, input.find("."))), stoi(input.substr(input.find(".")+2, input.find(","))));
    input.erase(0, input.find("y")+2);
    pair<int, int> goalY (stoi(input.substr(0, input.find("."))), stoi(input.substr(input.find(".")+2)));

    goal = pair<pair<int, int>, pair<int, int>> (goalX, goalY);

    int count = 0;
    int max = -1;
    for(int y = goal.second.first; y < abs(goal.second.first); y++) {
        for(int x = 1; x <= goal.first.second; x++) {
            int tempMax = trajectory(pair<int, int> (x, y), goal);
            if(tempMax >= 0) {
                cout << "trajectory with velocity " << x << ", " << y << " max at " << tempMax << endl;
                count++;
            }
            if(tempMax > max) {
                max = tempMax;
            }
        }
    }

    //cout << "trajectory test: " << trajectory(pair<int, int> (23, -10), goal) << endl;

    cout << "trajectory max: " << max << endl;
    cout << "count: " << count << endl;

    return 0;
}

int trajectory(pair<int, int> velocity, pair<pair<int, int>, pair<int, int>> goal) {
    int minX = goal.first.first;
    int maxX = goal.first.second;
    int minY = goal.second.first;
    int maxY = goal.second.second;

    //cout << "x goal: " << minX << " to " << maxX << endl;
    //cout << "y goal: " << minY << " to " << maxY << endl;

    int dx = velocity.first;
    int dy = velocity.second;

    int currX = 0;
    int currY = 0;

    int apex = 0;

    while(currX <= maxX && currY >= minY) {
        if(dy == 0) apex = currY;

        currX += dx;
        currY += dy;

        if(currX <= maxX && currX >= minX && currY <= maxY && currY >= minY) {
            return apex;
        }

        --dy;

        if(dx > 0) --dx;
        else if(dx < 0) ++dx;
    }
    return -1;
}

string readInput() {
    string line;
    ifstream input("input.txt");

    //first line of input file
    if(input.is_open()) {
        getline(input, line);
        return line;
    }
    //if closed return empty string
    return line;
}

template <typename T>
void printVector(vector<T> vector) {
    for(int i = 0; i < vector.size(); i++) {
        cout << vector[i] << ", ";
    }
    cout << endl;
}

template <typename T>
void printWrapper(vector<vector<T>> vector) {
    for(int i = 0; i < vector.size(); i++) {
        printVector(vector.at(i));
    }
}