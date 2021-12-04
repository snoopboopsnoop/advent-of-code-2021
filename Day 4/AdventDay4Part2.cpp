#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

vector<string> readInput();
vector<vector<string>> makeBoard(vector<string> board);
void checkNum(string num, vector<vector<string>> &board);
bool isWinner(vector<vector<string>> board);
int getSum(vector<vector<string>> board);

template <typename T>
void printVector(vector<T> vector);

template <typename T>
void printWrapper(vector<vector<T>> vector);

template <typename T>
void print3d(vector<vector<T>> vector);

int main() {
    //write input to vector
    vector<string> input = readInput();
    //bingo numbers
    vector<string> bingoNums;
    string line = input[0];
    input.erase(input.begin(), input.begin()+2);

    while(line.size() != 0) {
        int comma = line.find(",");
        if(comma == string::npos) {
            bingoNums.push_back(line.substr(0));
            line.erase(line.begin(), line.end());
        }
        else {
            bingoNums.push_back(line.substr(0, comma));

            line.erase(line.begin(), line.begin()+comma+1);
        }
    }

    vector<vector<vector<string>>> boards;

    //initialize boards
    while(input.size() != 0) {
        vector<vector<string>> tempBoard;
        string currLine;

        //each group of 5 lines (1 board)
        for(int j = 0; j < 5; j++) {
            vector<string> temp;
            currLine = input[j];

            //put each group of numbers into temp vector
            while(currLine.size() != 0) {
                //string -> stoi -> to_string gets rid of space characters
                temp.push_back(to_string(stoi(currLine.substr(0, 2))));

                if(currLine.size() == 2) {
                    currLine.erase(currLine.begin(), currLine.end());
                }
                else currLine.erase(currLine.begin(), currLine.begin()+3);
            }
            //push the lines into the temp board 2d vector
            tempBoard.push_back(temp);
        }
        //push the board into the 3d boards vector
        boards.push_back(tempBoard);

        if(input.size() == 5) {
            input.erase(input.begin(), input.end());
        }
        else input.erase(input.begin(), input.begin()+6);
    }
    
    int winners = 0;
    int boardCount = boards.size();

    cout << boardCount << endl;

    //check each board for each bingo number
    for(string i : bingoNums) {
        bool winner = false;
        cout << "number: " << i << endl;
        for(vector<vector<string>> &board : boards) {
            checkNum(i, board);
            if(isWinner(board)) {
                winners++;
                if(winners == boardCount) {
                    cout << "winner: " << endl;
                    printWrapper(board);

                    winner = true;

                    cout << "i: " << i << endl;
                    cout << "sum: " << getSum(board) << endl;
                    cout << stoi(i)*getSum(board) << endl;

                    break;
                }
                // cout << "winners: " << winners << endl;
                
                for(vector<string> &line : board) {
                    fill(line.begin(), line.end(), NULL);
                }

            }
        }
        if(winner == true) {
            break;
        }
        // cout << "boards:" << endl;
        // print3d(boards);
    }

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

void checkNum(string num, vector<vector<string>> &board) {
    for(int i = 0; i < board.size(); i++) {
        for(int j = 0; j < board[0].size(); j++) {
            // cout << "checking: ";
            // printVector(board[i]);
            if(board[i][j] == num) {
                board[i][j] = 'X';
            }
        }
    }
}

bool isWinner(vector<vector<string>> board) {
    bool found = false;
    //horizontals
    for(int i = 0; i < board.size(); i++) {
        for(int j = 0; j < board[0].size(); j++) {
            if(board[i][j] != "X") {
                found = false;
                break;
            }
            else found = true;
        }
        if(found == true) {
            return true;
        }
    }
    //verticals
    for(int i = 0; i < board[0].size(); i++) {
        for(int j = 0; j < board.size(); j++) {
            if(board[j][i] != "X") {
                found = false;
                break;
            }
            else found = true;
        }
        if(found == true) {
            return true;
        }
    }
    return false;
}

int getSum(vector<vector<string>> board) {
    int sum = 0;
    for(int i = 0; i < board.size(); i++) {
        for(int j = 0; j < board[0].size(); j++) {
            if(board[i][j] != "X") {
                sum += stoi(board[i][j]);
            }
        }
    }
    return sum;
}

template <typename T>
void printVector(vector<T> vector) {
    for(int i = 0; i < vector.size(); i++) {
        cout << vector[i] << ", ";
    }
    cout << "\n";
}

template <typename T>
void printWrapper(vector<vector<T>> vector) {
    for(int i = 0; i < vector.size(); i++) {
        printVector(vector.at(i));
    }
}

template <typename T>
void print3d(vector<vector<T>> vector) {
    for(int i = 0; i < vector.size(); i++) {
        for(int j = 0; j < vector[0].size(); j++) {
            printVector(vector[i][j]);
        }
        cout << endl;
    }
}