#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

vector<int> readInput();

template <typename T>
void printVector(vector<T> vector);

template <typename T>
void printWrapper(vector<vector<T>> vector);

int main() {
    //write input to vector
    vector<int> input = readInput();
    int count = 0;
    int last = 0;

    //first window
    for(int i = 0; i < 3; i++) {
        last += input[i];
    }

    //increase count if input window increases
    for(int i = 1; i+2 < input.size(); i++) {
        int window = 0;

        //create window
        for(int j = 0; j < 3; j++) {    
            window += input[i+j];
        }
        if(window > last) {
            count++;
        }
        last = window;
    }

    cout << count;

    return 0;
}

vector<int> readInput() {
    string line;
    vector<int> inputVector;
    ifstream input("input.txt");

    //put each line of input file into vector
    if(input.is_open()) {
        while(getline(input, line)) {
            inputVector.push_back(stoi(line));
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