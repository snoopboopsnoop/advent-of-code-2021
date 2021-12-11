#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>

using namespace std;

//https://en.wikipedia.org/wiki/Brainfuck
//https://youtu.be/aAlR3cezPJg?list=PLE18841CABEA24090&t=1336

vector<string> readInput();
//i don't give a fuck what it returns it doesnt even matter
char algorithm(string line, int& pos, vector<char> open, vector<char> closed, string& closingChars);

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

    //vector of score counts for each clump
    vector<long long> scores;

    //each clump
    for(string line : input) {
        //current position passed by reference
        int pos = 0;
        //score of current clump
        long long score = 0;
        //chars to be added to incomplete clump
        string closingChars;

        /* this while loop is here wholly as a bandaid to this one fucking mess of a bug
           where if the clump consists of 2+ groups (aka the first character closes before eol)
           there is a space at the end of closingChars which idfk why, so this fixes it */
        while(pos < line.size()) {
            char out = algorithm(line, pos, open, closed, closingChars);
            //ignore line if it's corrupt
            if(out != '/') {
                break;
            }
            pos++;
        }
        //math for calculating scores
        if(closingChars.size() != 0) {
            for(char i : closingChars) {
                score *= 5;
                switch(i) {
                    case ')':
                        score += 1;
                        break;  
                    case ']':
                        score += 2;
                        break;  
                    case '}':
                        score += 3;
                        break;  
                    case '>':
                        score += 4;
                        break;  
                    default:
                        break;            
                }
            }
            scores.push_back(score);
        }
    }
    sort(scores.begin(), scores.end());

    //answer
    cout << scores[scores.size()/2] << endl;;

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

//okay maybe one return is important
//return ' ' in recurse means eol
//return '/' means closed
char algorithm(string line, int& pos, vector<char> open, vector<char> closed, string& closingChars) {
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
        //if the character opens a new group
        else if(find(open.begin(), open.end(), next) != open.end()) {
            //recurse
            char out = algorithm(line, pos, open, closed, closingChars);
            //if closed, keep going with current group
            if(out == '/') {
                continue;
            }
            //if eol, add the current char's respective close
            else if(out == ' ') {
                closingChars.append(1, currClose);
                return ' ';
            }
            //return corrupt which doesn't actually matter just too lazy to change this shit
            else return out;
        }
        //if corrupt
        else if(find(closed.begin(), closed.end(), next) != closed.end()) {
            if(next != currClose) {
                return next;
            }
        }
    }
    //add the first char at eol to closingChars
    closingChars.append(1, currClose);
    return ' ';
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