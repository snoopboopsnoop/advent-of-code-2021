#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>

using namespace std;

//https://en.wikipedia.org/wiki/Brainfuck

vector<string> readInput();
//return corrupted char, or '/' if chunk is incomplete
char algorithm(string line, int& pos, vector<char> open, vector<char> closed);

//debug functions
template <typename T>
void printVector(vector<T> vector);

template <typename T>
void printWrapper(vector<vector<T>> vector);

int main() {
    //write input to vector
    vector<string> input = readInput();
    //opening characters
    vector<char> open{'(', '[', '{', '<'};
    //closing characters
    vector<char> closed{')', ']', '}', '>'};
    int count = 0;

    //check each chunk
    for(string line : input) {
        int pos = 0;
        char out = algorithm(line, pos, open, closed);
        //add all points of illegal characters
        switch(out) {
            case ')':
                count += 3;
                break;
            case ']':
                count += 57;
                break;
            case '}':
                count += 1197;
                break;
            case '>':
                count += 25137;
                break;
            default:
                break;   
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

//return '/': while recursing, means that a set has been closed. when returned in main, means clump is incomplete
//else: corrupted char
char algorithm(string line, int& pos, vector<char> open, vector<char> closed) {
    //current character
    char curr = line[pos];
    //respective closing character
    char currClose = closed[find(open.begin(), open.end(), curr)-open.begin()];
    while(pos < line.size()) {
        pos++;
        //next character
        char next = line[pos];
        //if the next character closes the previous one
        if(next == currClose) {
            return '/';
        }
        //if the next character opens a new group
        else if(find(open.begin(), open.end(), next) != open.end()) {
            //recurse; return if corrupted char was found
            char out = algorithm(line, pos, open, closed);
            if(out == '/') {
                continue;
            }
            else return out;
        }
        //if the next character is corrupted
        else if(find(closed.begin(), closed.end(), next) != closed.end()) {
            if(next != currClose) {
                return next;
            }
        }
    }
    return '/';
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