#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>

using namespace std;

//https://www.youtube.com/watch?v=zp4BMR88260

vector<string> readInput();

//debug functions
template <typename T>
void printVector(vector<T> vector);

template <typename T>
void printWrapper(vector<vector<T>> vector);

int main() {
    //write input to vector
    vector<string> input = readInput();
    int count = 0;

    //take the output section of each line
    for(string i : input) {
        string curr;
        string output = i.substr(i.find("|")+2);

        //separate each output code into individual strings
        while(output.size() != 0) {
            if(output.find(" ") == string::npos) {
                curr = output.substr(0);
                output.erase(output.begin(), output.end());
            }
            else {
                curr = output.substr(0, output.find(" "));
                output.erase(0, output.find(" ")+1);
            }

            //unique sizes for 7 seg displays
            if(curr.size() == 2 || curr.size() == 3 || curr.size() == 4 || curr.size() == 7) {
                count++;
            }
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