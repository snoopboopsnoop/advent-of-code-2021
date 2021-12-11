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
    int pos = 0;
    int depth = 0;

    //for each instruction
    for(int i = 0; i < input.size(); i++) {
        vector<string> temp;
        string curr = input[i];
        int space = curr.find(" ");
        
        //direction
        temp.push_back(curr.substr(0, space));
        //strength
        temp.push_back(curr.substr(space+1));

        //add depending on direction
        if(temp[0] == "forward") {
            pos += stoi(temp[1]);
        }
        else if(temp[0] == "up") {
            depth -= stoi(temp[1]);
        }
        else if(temp[0] == "down") {
            depth += stoi(temp[1]);
        }
    }

    //answer
    cout << pos*depth << "\n";

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