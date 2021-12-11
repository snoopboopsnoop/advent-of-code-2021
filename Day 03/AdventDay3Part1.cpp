#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

vector<string> readInput();

template <typename T>
void printVector(vector<T> vector);

template <typename T>
void printWrapper(vector<vector<T>> vector);

int main() {
    //write input to vector
    vector<string> input = readInput();
 
    string gamma = "";
    int zeroes = 0;
    int ones = 0;

    //find common bit
    for(int i = 0; i < input[0].size(); i++) {
        zeroes = 0;
        ones = 0;
        for(int j = 0; j < input.size(); j++) {
            if(input[j][i] == '0') {
                zeroes++;
            } 
            else ones++;
        }
        if(zeroes > ones) {
            gamma.push_back('0');
        }
        else gamma.push_back('1');
    }

    //epsilon is the inverse of gamma
    string epsilon = gamma;

    for(int i = 0; i < epsilon.size(); i++) {
        if(epsilon[i] == '0') {
            epsilon[i] = '1';
        }
        else epsilon[i] = '0';
    }

    //multiply both binary
    cout << stoi(gamma, nullptr, 2)*stoi(epsilon, nullptr, 2) << endl;

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
        cout << vector[i] << " ";
    }
    cout << endl;
}

template <typename T>
void printWrapper(vector<vector<T>> vector) {
    for(int i = 0; i < vector.size(); i++) {
        printVector(vector.at(i));
    }
}