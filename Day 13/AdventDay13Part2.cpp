#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>

using namespace std;

//https://en.wikipedia.org/wiki/Brainfuck

vector<string> readInput();

//debug functions
template <typename T>
void printVector(vector<T> vector);

template <typename T>
void printWrapper(vector<vector<T>> vector);

int main() {
    //write input to vector
    vector<string> input = readInput();
    vector<pair<int, int>> coords;
    vector<pair<int, int>> directions;
    vector<vector<char>> display;

    for(int i = 0; i < 1; i++) {
        display.push_back(vector<char>(1, '.'));
    }

    for(string line : input) {
        if(line == "") continue;
        else if(isdigit(line[0])) {
            coords.push_back(pair<int, int>(stoi(line.substr(0, line.find(","))), stoi(line.substr(line.find(",")+1))));
        }   
        else {
            if(line.find("x") != string::npos) {
                directions.push_back(pair<int, int>(stoi(line.substr(line.find("=")+1)), 0));
            }
            else if(line.find("y") != string::npos) {
                directions.push_back(pair<int, int>(0, stoi(line.substr(line.find("=")+1))));
            }
        }
    }

    for(auto i : directions) {
        for(auto& coord : coords) {
            if(i.second != 0) {
                int diffY = i.second - coord.second;
                if(diffY < 0) {
                    coord.second = i.second + diffY;
                }
            }
            else if(i.first != 0) {
                int diffX = i.first - coord.first;
                if(diffX < 0) {
                    coord.first = i.first + diffX;
                }
            }
        }
        sort(coords.begin(), coords.end());
        coords.erase(unique(coords.begin(), coords.end()), coords.end());
        
    }

    // for(auto i : coords) {
    //     cout << i.first << ", " << i.second << endl;
    // }
    // cout << endl;

    for(auto i : coords) {
        if(i.first+1 > display[0].size()) {
            for(vector<char>& line : display) {
                line.resize(i.first+1, '.');
            }
        }
        if(i.second+1 > display.size()) {
            vector<char> temp(display[0].size(), '.');
            display.resize(i.second+1, temp);
        }
        display[i.second][i.first] = char(254);
    }

    printWrapper(display);

    

    return 0;
}

vector<string> readInput() {
    string line;
    vector<string> inputVector;
    ifstream input("input.txt");

    //put each line of input file into vector
    if(input.is_open()) {
        while(getline(input, line)) {
            inputVector.push_back(line);
        }
    }
    return inputVector;
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