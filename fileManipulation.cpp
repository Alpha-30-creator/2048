#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;

//function to save a game in the file "leaderboard.txt"
//takes the game board, score and username as paramters
//saves all the information as <username(in lower space)><space><size><space><score><board values seperated by space>

void save_game(vector<vector<int>> board, int score, string username) {
    ofstream fout;
    //opening loadgame file in append mode
    fout.open("loadgame.txt", ios::app);
    
    //if fail in opening file, output error and exit
    if (fout.fail()) {
         cout << "Error in opening the file"<<endl;
         exit(1);
    }
    else {
        //write the information in the specified format if file opens
        
        //first write user information
        fout<<username<<" "<<board.size()<<" "<<score<<endl;
        
        //then write board state
        for(int i=0;i<board.size();i++){
            for(int j=0; j<board.size();j++){
                fout<<board[i][j]<<" ";
        }
        }

        fout.close();
        cout<<"Game saved successfully!"<<endl;
    }
}

//Function to load a saved game
vector<vector<int>> loadGame(string username) {
    //create a 2D vector of int to store board
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

//function for sorting the leaderboard file in terms of score
bool sortscores(const string& a, const string& b) {
    //finding scores in line and converting it to string
    int score_a = stoi(a.substr(a.find_last_of(" ") + 1));
    int score_b = stoi(b.substr(b.find_last_of(" ") + 1));
    //returning true or false depending on if previous value is greater
    return score_a > score_b;
}

//function for extracting leaderboard from leaderboard file
vector<string> get_leaderboard(){
    //opening the leaderboard file
    ifstream fin;
    vector<string> scores;
    fin.open("leaderboard.txt");

    //check if file exists
    if (fin.fail()) {
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
        i+=1;
        if(i>10){  //if file has scores, read scores of top 10 or less depending on how many exist, and return
            break;
        }
    }

    fin.close();

    return scores;
}

//function for adding new scores in the leaderboard file and sorting it in terms of score
//takes score and username as a parameter, saves it in the format <username><space><score>
//sorts it using the sort function of STL
bool update_leaderboard(int score, string username) {
    //read the current leaderboard from the file
    vector<string> leaderboard = get_leaderboard();
    bool beat_high_score=false;
    bool user_record_exists=false;
    //if no scores return false
    if(leaderboard[0]=="No scores yet."){
        return false;
    }
    int i=0;
    //find the position to insert the new score
    for (i; i < leaderboard.size(); i++) {
        string linedata=leaderboard[i];
        string user="";
        int j=0;
        //get the username on one line of the file
        while(linedata[j]!=' '){
            user.insert(j,1,linedata[j]);
            i+=1;
        }
        //check if username already exists in file
        if (user==username){
             //if it does, turn flag true and extract previous score   
            user_record_exists=true;            
            int oldscore=stof(linedata.substr(username.length()+1)); //get old score of same user from file
            if(score>oldscore){ 
                //if newscore greater than previous score, make a flag true
                beat_high_score=true; 
            }
            break;
        }
    }
    //insert the new score at the appropriate position
    if(user_record_exists){
        //if user record exists and new score is greater, update the oldscore
        if(beat_high_score){
            leaderboard[i]=username+" "+to_string(score);
        }else{
            //if user record exists and doesnt beat high score, end function call without any modification (because file is already sorted)
            return false;
        }
    }
    else{
        //if user record doesn exist, make new entry
        leaderboard.push_back(username+" "+to_string(score));
    }

    //sort the leaderboard vector array in terms of score
    sort(leaderboard.begin(), leaderboard.end(), sortscores);
    
    //update the leaderboard file with updated scores
    ofstream fout;
    //overwriting file here as all data is already in vector leaderboard
    fout.open("leaderboard.txt");
    //if file does not open, return false
    if (fout.fail()) {
        return false;
    }else{
        //if file opens save all info on every line
    for (int i=0;i<leaderboard.size();i++){
            fout<<leaderboard[i]<<endl;
        }
    }
    fout.close();
    
    return beat_high_score;
}
