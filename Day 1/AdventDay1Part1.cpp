#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

vector<int> readInput();
void printVector(vector<int> vector);

int main() {
    //write input to vector
    vector<int> input = readInput();
    int count = 0;

    int last = input[0];

    //increase count if input increases
    for(int i = 1; i < input.size(); i++) {
        if(input[i] > last) {
            count++;
        }
        last = input[i];
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

void printVector(vector<int> vector) {
    for(int i = 0; i < vector.size(); i++) {
        cout << vector.at(i) << "\n";
    }
}