#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include <map>

using namespace std;

//https://www.youtube.com/watch?v=zp4BMR88260
//https://docs.google.com/spreadsheets/d/1t3fW47BBSCB8QKFvBUgOdKo1P8lgkWM2PyxMqYhRvxk/edit?usp=sharing

vector<string> readInput();
//deduce the mapping between wires and segment and put them into letters map
//numbers represent a code's relation to each digit; abcdef -> 8, for example
void solve(vector<string>& encrypted, map<char, char>& letters, map<string, int>& numbers);

//debug functions
template <typename T>
void printVector(vector<T> vector);

template <typename T>
void printWrapper(vector<vector<T>> vector);

int main() {
    //write input to vector
    vector<string> input = readInput();
    int count = 0;

    for(string i : input) {
        //encrypted input codes
        vector<string> encrypted;
        //encrypted output codes
        vector<string> outputCodes;
        //maps signal wire (input char) to segments (respective segment in display)
        map<char, char> letters;
        //maps alphabetized string to its representative digit
        map<string, int> numbers;
        string outputVal;

        //initialize input/output
        string input = i.substr(0, i.find("|"));
        string output = i.substr(i.find("|")+2);
        
        while(input.size() != 0) {
            string curr = input.substr(0, input.find(" "));
            //alphabetize each code for easy comparison
            sort(curr.begin(), curr.end());
            input.erase(0, input.find(" ")+1);

            encrypted.push_back(curr);
        }

        while(output.size() != 0) {
            if(output.find(" ") == string::npos) {
                string curr = output.substr(0);
                //alphabetize each code for easy comparison
                sort(curr.begin(), curr.end());
                output.erase(output.begin(), output.end());

                outputCodes.push_back(curr);
            }
            else {
                string curr = output.substr(0, output.find(" "));
                //alphabetize each code for easy comparison
                sort(curr.begin(), curr.end());
                output.erase(0, output.find(" ") + 1);

                outputCodes.push_back(curr);
            }
        }

        //sort by length for absolutely no reason (i don't think this actually helps with anything)
        sort(encrypted.begin(), encrypted.end(), []
            (const string& first, const string& second) {
                return first.size() < second.size();
            });
        
        //algorithm
        solve(encrypted, letters, numbers);

        //append the 4 output digits together using numbers map to decode
        for(string code : outputCodes) {
            outputVal.append(to_string(numbers.at(code)));
        }
        //sum all output values
        count += stoi(outputVal);
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

//probably wildly inefficient but this problem gave me brain rot
void solve(vector<string>& encrypted, map<char, char>& letters, map<string, int>& numbers) {
    //kind of misnamed; this keeps track of how many times the character APPEARS in the codes
    map<char, int> missing;
    //initialize missing characters map
    missing.insert(pair<char, int>('a', 0));
    missing.insert(pair<char, int>('b', 0));
    missing.insert(pair<char, int>('c', 0));
    missing.insert(pair<char, int>('d', 0));
    missing.insert(pair<char, int>('e', 0));
    missing.insert(pair<char, int>('f', 0));
    missing.insert(pair<char, int>('g', 0));

    //find the number of times a character appears in the codes
    for(string i : encrypted) {
        for(char j : i) {
            missing.at(j)++;
        }
        //initialize unique digits 1, 4, 7, 8 because why not
        switch(i.length()) {
            case 2:
                numbers.insert(pair<string, int>(i, 1));
                break;
            case 3:
                numbers.insert(pair<string, int>(i, 7));
                break;
            case 4:
                numbers.insert(pair<string, int>(i, 4));
                break;
            case 7:
                numbers.insert(pair<string, int>(i, 8));
        }
    }

    //character missing from only 1 number is f
    for(auto i : missing) {
        if(i.second == 9) {
            letters.insert(pair<char, char>('f', i.first));
            break;
        }
    }

    //2
    for(string i : encrypted) {
        //the code missing f character is 2
        if(i.find(letters.at('f')) == string::npos) {
            //in the one that doesn't have f, the other missing is b
            for(auto elem : missing) {
                //using missing to find the missing strings since it has keys to all letters a-g
                //if the character is missing and not the 'f' character previously deduced
                if(i.find(elem.first) == string::npos && elem.first != letters.at('f')) {
                    //found b
                    letters.insert(pair<char, char>('b', elem.first));
                    numbers.insert(pair<string, int>(i, 2));
                    //won't ever use code again since its digit has been found and mapped in numbers
                    encrypted.erase(find(encrypted.begin(), encrypted.end(), i));
                    break;
                }
            }
            break;
        }
    }

    //3
    for(string i : encrypted) {
        //other code missing b character is 3
        if(i.find(letters.at('b')) == string::npos && i.size() == 5) {
            //the 5 letter one that doesn't have b is e
            for(auto elem : missing) {
                //if the character is missing and not the 'b' character previously deduced
                if(i.find(elem.first) == string::npos && elem.first != letters.at('b')) {
                    //found e
                    letters.insert(pair<char, char>('e', elem.first));
                    numbers.insert(pair<string, int>(i, 3));

                    encrypted.erase(find(encrypted.begin(), encrypted.end(), i));
                    break;
                }
            }
            break;
        }
    }

    //5
    for(string i : encrypted) {
        //other one missing e
        if(i.find(letters.at('e')) == string::npos && i.size() == 5) {
            //the other 5 letter char in i is supposed to be c 
            for(auto elem : missing) {
                if(i.find(elem.first) == string::npos && elem.first != letters.at('e')) {
                    letters.insert(pair<char, char>('c', elem.first));
                    //it's 5
                    numbers.insert(pair<string, int>(i, 5));
                    encrypted.erase(find(encrypted.begin(), encrypted.end(), i));
                    break;
                }
            }
            break;
        }
    }

    //7
    for(string i : encrypted) {
        //unknown letter in 3 letter code is a
        if(i.size() == 3) {
            for(char j : i) {
                bool found = false;
                for(auto elem : letters) {
                    if(elem.second == j) {
                        found = true;
                    }
                }
                if(found == false) {
                    letters.insert(pair<char, char>('a', j));
                }
            }
        }
    }

    //4
    for(string i : encrypted) {
        //unknown letter in 4 letter code is d
        if(i.size() == 4) {
            for(char j : i) {
                bool found = false;
                for(auto elem : letters) {
                    if(elem.second == j) {
                        found = true;
                    }
                }
                if(found == false) {
                    letters.insert(pair<char, char>('d', j));
                }
            }
        }
    }

    //c
    for(auto elem : missing) {
        bool found = false;
        for(auto i : letters) {
            if(elem.first == i.second) {
                found = true;
            }
        }
        if(found == false) {
            letters.insert(pair<char, char>('g', elem.first));
        }
    }

    //0, 6, 9
    for(string code : encrypted) {
        if(code.size() == 6) {
            if(code.find(letters.at('d')) == string::npos) {
                numbers.insert(pair<string, int>(code, 0));
            }
            else if(code.find(letters.at('c')) == string::npos) {
                numbers.insert(pair<string, int>(code, 6));
            }
            else if(code.find(letters.at('e')) == string::npos) {
                numbers.insert(pair<string, int>(code, 9));
            }
        }
    }
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