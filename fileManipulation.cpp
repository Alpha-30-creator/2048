#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;

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

bool sortscores(const string& a, const string& b) {
    int score_a = stoi(a.substr(a.find_last_of(" ") + 1));
    int score_b = stoi(b.substr(b.find_last_of(" ") + 1));
    return score_a > score_b;
}

vector<string> get_leaderboard(){
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
    //if file has scores, read scores of top 10 or less depending on how many exist, and return
    while (getline(fin, line)) {
        scores.push_back(line);
        i+=1;
        if(i>10){
            break;
        }
    }

    fin.close();

    return scores;
}


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
        if (user==username){
            user_record_exists=true;
            int oldscore=stof(linedata.substr(username.length()+1)); //get old score from linedata
            if(score>oldscore){
                beat_high_score=true;
            }
            break;
        }
    }
    //insert the new score at the appropriate position
    if(user_record_exists){
        if(beat_high_score){
            leaderboard[i]=username+" "+to_string(score);
        }else{
            //if already exists and doesnt beat high score, end function call without any modification
            return false;
        }
    }
    else{
        leaderboard.push_back(username+" "+to_string(score));
    }

    //sort the leaderboard vector array in terms of score
    sort(leaderboard.begin(), leaderboard.end(), sortscores);
    
    //update the leaderboard file with updated scores
    ofstream fout;
    fout.open("leaderboard.txt");
    if (fout.fail()) {
        cout<<"error in opening the file";
    }else{
    for (int i=0;i<leaderboard.size();i++){
            fout<<leaderboard[i]<<endl;
        }
    }
    fout.close();
    
    return beat_high_score;
}
