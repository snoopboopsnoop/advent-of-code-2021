#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>

using namespace std;

//https://www.youtube.com/watch?v=wUAJWzVotZg

vector<string> readInput();

//day by day
int step(vector<vector<int>>& octopi);
//increment adjacents using good ol' recursion
int increment(int i, int j, vector<vector<int>>& octopi);

//debug functions
template <typename T>
void printVector(vector<T> vector);

template <typename T>
void printWrapper(vector<vector<T>> vector);

int main() {
    //write input to vector
    vector<string> input = readInput();
    //2d array of octopus power levels
    vector<vector<int>> octopi;
    int flashes = 0;

    //initialize octopi array
    for(string line : input) {
        vector<int> temp;
        for(char i : line) {
            temp.push_back(i-'0');
        }
        octopi.push_back(temp);
    }

    //100 steps
    for(int i = 0; i < 100; i++) {
        flashes += step(octopi);
    }

    //answer
    cout << flashes << endl;

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

int step(vector<vector<int>>& octopi) {
    int flashes = 0;
    for(auto& line : octopi) {
        for(int& i : line) {
            i++;
        }
    }
    for(int i = 0; i < octopi.size(); i++) {
        for(int j = 0; j < octopi[0].size(); j++) {
            //already flashed
            if(octopi[i][j] == 0) {
                continue;
            }
            else if(octopi[i][j] > 9) {
                flashes++;
                flashes += increment(i, j, octopi);
            }
        }
    }
    return flashes;
}

int increment(int i, int j, vector<vector<int>>& octopi) {
    int flashes = 0;
    if(octopi[i][j] > 9) {
        octopi[i][j] = 0;
        //surrounding octopi
        for(int k = i-1; k < i+2; k++) {
            for(int l = j-1; l < j+2; l++) {
                //out_of_bounds
                if(k < 0 || k >= octopi.size() || l < 0 || l >= octopi[0].size()) {
                    continue;
                }
                //already flashed
                else if(octopi[k][l] == 0) {
                    continue;
                }
                //increment the surrounding octopi then check if they will flash
                octopi[k][l]++;
                if(octopi[k][l] > 9) {
                    flashes++;
                    flashes += increment(k, l, octopi);
                }
            }
        }
    }
    return flashes;
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
    cout << endl;
}