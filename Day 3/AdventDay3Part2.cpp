#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

vector<string> readInput();

vector<string> remove(vector<string> vector, int pos, char num);

template <typename T>
void printVector(vector<T> vector);

template <typename T>
void printWrapper(vector<vector<T>> vector);

int main() {
    //write input to vector
    vector<string> input = readInput();
    vector<string> temp = input;

    //oxygen gen rating, too lazy to rename
    int gamma = 0;
    //co2 rating, too lazy to rename
    int epsilon = 0;
    int zeroes = 0;
    int ones = 0;

    //find the oxygen generator rating
    for(int i = 0; i < temp[0].size(); i++) {
        zeroes = 0;
        ones = 0;
        for(int j = 0; j < temp.size(); j++) {
            if(temp[j][i] == '0') {
                zeroes++;
            } 
            else ones++;
        }
        if(zeroes > ones) {
            temp = remove(temp, i, '0');
        }
        else temp = remove(temp, i, '1');

        if(temp.size() == 1) {
            break;
        }
    }
    gamma = stoi(temp[0], nullptr, 2);

    //reset
    temp = input;
    for(int i = 0; i < temp[0].size(); i++) {
        zeroes = 0;
        ones = 0;
        for(int j = 0; j < temp.size(); j++) {
            if(temp[j][i] == '0') {
                zeroes++;
            } 
            else ones++;
        }
        if(zeroes > ones) {
            temp = remove(temp, i, '1');
        }
        else temp = remove(temp, i, '0');

        if(temp.size() == 1) {
            break;
        }
    }
    epsilon = stoi(temp[0], nullptr, 2);

    //answer
    cout << gamma*epsilon << endl;

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

vector<string> remove(vector<string> vector, int pos, char num) {
    for(int i = 0; i < vector.size(); i++) {
        //cout << vector[i][pos] << endl;
        if(vector[i][pos] != num) {
            vector.erase(vector.begin() + i);
            i--;
        }
    }
    return vector;
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