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

    for(auto i : coords) {
        cout << i.first << ", " << i.second << endl;
    }
    cout << endl;

    auto i = directions[0];
    cout << i.first << ", " << i.second << endl << endl;
    for(auto& coord : coords) {
        cout << "at " << coord.first << ", " << coord.second << endl;
        if(i.second != 0) {
            int diffY = i.second - coord.second;
            cout << "y diff " << diffY << endl;
            if(diffY < 0) {
                cout << coord.first << ", " << coord.second << " -> " << coord.first << ", " << i.second+diffY << endl;
                coord.second = i.second + diffY;
            }
        }
        else if(i.first != 0) {
            int diffX = i.first - coord.first;
            cout << "x diff " << diffX << endl;
            if(diffX < 0) {
                cout << coord.first << ", " << coord.second << " -> " << i.first+diffX << ", " << coord.second << endl;
                coord.first = i.first + diffX;
            }
        }
    }
    sort(coords.begin(), coords.end());
    coords.erase(unique(coords.begin(), coords.end()), coords.end());
    
    for(auto i : coords) {
        cout << i.first << ", " << i.second << endl;
    }
    cout << endl;

    cout << "size: " << coords.size() << endl;

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