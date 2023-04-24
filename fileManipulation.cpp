#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

//Function to load a saved game
vector<vector<int>> loadGame(string username) {
    //create a 2D vector of int
    vector<vector<int>> board;
    //open file loadgame.txt
    ifstream fin;
    fin.open("loadgame.txt");
    //if file does not open
    if (fin.fail()) {
        cout << "User does not have any saved games." << endl;
        exit(1);
    }
    //if file opens
    else {
        string user;
        int size;
        //read file line by line
        string line;
        while (getline(fin, line)) {
            //extract data from line
            istringstream word(line);
            word >> user;
            if (user == username) {
                //extract size of board
                word >> size;
                //extract board from file and store in 2D vector
                for(int i= 0; i < size; i++) {
                    int num;
                    vector<int> row;
                    for(int j = 0; j < size; j++){
                        word >> num;
                        row.push_back(num);
                    }
                    board.push_back(row);
                }
            }
        }
    }
    //close file
    fin.close();
    //if board empty, exit program. else return board
    if (board.empty()) {
        cout << "User does not have any saved games." << endl;
        exit(1);
    }
    else {
        return board;
    }
}
