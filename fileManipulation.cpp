#include "fileManipulation.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

/*
    (save_game) := Function to save game
    Inputs: (i) 2D vector of current board, (ii) int containing score, (iii) string containing username (all are passed by value)
    Outputs: does not return anything
    Purpose: (i) saves the current game to loadgame.txt file
    Logic:
    first checks if the user already has a saved game
    if it does, overwrites the existing saved game with the new board passed into the function
    if does not have already saved game, appends it to the end of file
    saves all the information as <username><space><size><space><score><board values seperated by space>
*/
void save_game(vector<vector<int>> board, int score, string username) {
    ifstream fin;
    //vector to store saved games of all users from loadgame.txt
    vector<string> saved_games;
    //counter variable to see which line already has save game in loadgame.txt of same user 
    int i = 0;
    //boolean variable to check if user already has a saved game
    bool user_found = false;
    //convert username to lowercase
    transform(username.begin(), username.end(), username.begin(), ::tolower);
    fin.open("loadgame.txt");
    //if file opens successfully, read all data
    if(!fin.fail()){
        string line;
        //read until end of file
        while(getline(fin, line)){
            saved_games.push_back(line);
        }  
    } else {
        //if file does not open, write current game to file and exit
        fin.close();
        ofstream fout;
        fout.open("loadgame.txt");
        //covert username to lowercase
        string saved_game = username + " " + to_string(board.size()) + " " + to_string(score) + " ";
        //loop through all board values
        for(int j = 0; j < board.size(); j++){
            for(int k = 0;k < board.size(); k++){
                saved_game = saved_game + to_string(board[j][k])+" ";    
            }
        }
        fout << saved_game << endl;
        fout.close();
        return;
    }
        //check is the user already has a saved game by looping through all 
        for(i ; i < saved_games.size(); i++){
            if (saved_games[i].substr(0, username.length()) == username){
                user_found = true;
                break;
            }
        } 

    //if condition to check if user already has a saved game
    if (user_found == true) {
        saved_games[i] = username + " " + to_string(board.size()) + " " + to_string(score) + " ";
        //modify the saved game by overwriting the existing saved game with the new saved game
        for(int j = 0; j < board.size(); j++){
            for(int k = 0; k < board.size(); k++){
                saved_games[i] = saved_games[i] + to_string(board[j][k])+" ";    
            }
        }
    } 
    else {
        //if user does not have a saved game yet, add new save game to the end of vector
        saved_games.push_back(username+" "+to_string(board.size())+" "+to_string(score)+" ");
        //add board values to the end of the new save game
        for(int j = 0; j < board.size(); j++){
            for(int k = 0; k < board[j].size(); k++){
                saved_games.back()=saved_games.back()+to_string(board[j][k])+" ";    
            }
        }
    }
    
    ofstream fout;
    // Creating or overwriting loadgame.txt file, as the modified data is in vector 
    fout.open("loadgame.txt");
    
    //if fail in opening file, output error and exit
    if (fout.fail()) {
         cout << "Error in opening the file"<<endl;
         exit(1);
    } 
    else {
        //write the modified information in the specified format if file opens
        for(int j = 0; j < saved_games.size(); j++){
            fout<<saved_games[j]<<endl;
        }
        fout.close();
        
        cout<<"Game saved successfully!"<<endl;
    }
}

/*
    (load_game) := Function to load game
    Inputs: (i) int containing score, (ii) string containing username (all are passed by value)
    Outputs: returns a 2D vector of int containing the loaded game board
    Purpose: load a saved game from loadgame.txt file
    Logic:
    first checks if the user already has a saved game
    if it does, extracts the board from the file and returns it
    if does not have already saved game, returns an empty board
*/
vector<vector<int>> load_game(string username, int &score) {
    //create a 2D vector of int to store board
    vector<vector<int>> board;
    //open file loadgame.txt
    ifstream fin;
    //convert username to lowercase
    transform(username.begin(), username.end(), username.begin(), ::tolower);
    fin.open("loadgame.txt");
    //if file does not open
    if (fin.fail()) {
        cout << "User does not have any saved games." << endl;
        return board;
    }
    //if file opens
    else {
        string user;
        int size;
        //read file line by line
        string line;
        while (getline(fin, line)) {
            //set user to empty string
            user = "";
            //extract username from line
            int index = 0, spaces = 0;
            while(isdigit(line[index]) == false) {
                user += line[index];
                if (line[index] == ' ') {
                    spaces++;
                }
                index++;
            }
            //remove space at the end of username
            user.pop_back();
            stringstream word(line);
            string dummy;
            //so that word starts from the size of board
            for (int i = 0; i < spaces; i++) {
                word >> dummy;
            }
            //if username matches, extract board
            if (user == username) {
                //extract size of board
                word >> size;
                word >> score;
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
        return board;
    }
    else {
        return board;
    }
}

/*
    (leaderboard) := Function to display leaderboard
    Inputs: none
    Outputs: none
    Purpose: to display the leaderboard
    Logic:
    first gets the leaderboard from the file
    then sorts the leaderboard in descending order
    then displays the leaderboard
*/
bool sort_scores(const string& a, const string& b) {
    //finding scores in line and converting it to string
    int score_a = stoi(a.substr(a.find_last_of(" ") + 1));
    int score_b = stoi(b.substr(b.find_last_of(" ") + 1));
    //returning true or false depending on if previous value is greater
    return score_a > score_b;
}

/*
    (leaderboard) := Function to display leaderboard
    Inputs: none
    Outputs: none
    Purpose: to display the leaderboard
    Logic:
        first gets the leaderboard from the file
        then sorts the leaderboard in descending order
        then displays the leaderboard
*/
vector<string> get_leaderboard(){
    //opening the leaderboard file
    ifstream fin;
    vector<string> scores;
    fin.open("leaderboard.txt");

    //check if file exists
    if (fin.fail()) {
        //close file so we can open in write mode
        fin.close();
        //if does not exist, create the file
        ofstream fout;
        fout.open("leaderboard.txt");
        //indicate there are no scores yet added
        scores.push_back("No scores yet.");
        return scores;
    }
    
    string line;
    int i=0;
    //read each line from file
    while (getline(fin, line)) {
        scores.push_back(line);
        i++;
    }

    fin.close();

    return scores;
}

/*
    (leaderboard) := Function to display leaderboard
    Inputs: none
    Outputs: none
    Purpose: to display the leaderboard
    Logic:
    first gets the leaderboard from the file
    then sorts the leaderboard in descending order
    then displays the leaderboard
*/
bool update_leaderboard(int score, string username) {
    //read the current leaderboard from the file
    vector<string> leaderboard = get_leaderboard();
    bool beat_high_score = false;
    bool user_record_exists = false;
    int i = 0;
    //convert username to lowercase
    transform(username.begin(), username.end(), username.begin(), ::tolower);
    //if no scores add current score to the leaderboard
    if(leaderboard[0] == "No scores yet.") {
        leaderboard[0] = username + " " + to_string(score);
    }
    else {
        //loop used to check if user has beaten his previous high score
        for (i; i < leaderboard.size(); i++) {
        string line = leaderboard[i];
        string user = "";
        int j = 0;
            //get the username on one line of the file
            user = line.substr(0, username.length());
            //check if username already exists in file
            if (user == username){
                //check if user has achieved a new high score            
                int oldscore = stof(line.substr(username.length() + 1)); //get old score of same user from file
                if (score > oldscore){ 
                    //if newscore greater than previous score, make a flag true
                    beat_high_score = true; 
                }
                break;
            }
        }
        //insert the new score in the leaderboard vector array
        leaderboard.push_back(username + " " + to_string(score));
    }

    //sort the leaderboard vector array in terms of score
    sort(leaderboard.begin(), leaderboard.end(), sort_scores);
    //pop elements from leaderboard so that it only has 10 elements
    while (leaderboard.size() > 10) {
        leaderboard.pop_back();
    }
    //update the leaderboard file with updated scores
    ofstream fout;
    //overwriting file here as all data is already in vector leaderboard
    fout.open("leaderboard.txt");
    //if file does not open, return false
    if (fout.fail()) {
        return false;
    }
    else {
        //if file opens save all info on every line
        for (int i=0; i < leaderboard.size(); i++) {
            fout << leaderboard[i] << endl;
        }
    }
    fout.close();
    return beat_high_score;
}
