#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>

using namespace std;

vector<string> readInput();

//debug functions
template <typename T>
void printVector(vector<T> vector);

template <typename T>
void printWrapper(vector<vector<T>> vector);

int main() {
    //write input to vector
    vector<string> input = readInput();
    //2d array of input
    vector<vector<int>> map;
    int count = 0;

    //input -> map
    for(string i : input) {
        vector<int> temp;
        while(i.size() != 0) {
            temp.push_back(stoi(i.substr(0,1)));
            i.erase(i.begin());
        }
        map.push_back(temp);
    }

    //find each low point
    for(int i = 0; i < map.size(); i++) {
        for(int j = 0; j < map[0].size(); j++) {
            int curr = map[i][j];
            //north
            if(i-1 > -1) {
                if(map[i-1][j] <= curr) {
                    continue;
                }
            }
            //south
            if(i+1 < map.size()) {
                if(map[i+1][j] <= curr) {
                    continue;
                }
            }
            //west
            if(j-1 > -1) {
                if(map[i][j-1] <= curr) {
                    continue;
                }
            }
            //east
            if(j+1 < map[0].size()) {
                if(map[i][j+1] <= curr) {
                    continue;
                }
            }
            count += curr+1;
        }
    }

    //answer
    cout << count << endl;

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