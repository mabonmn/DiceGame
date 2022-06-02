// author @Mabon Manoj Ninan M13883690
// https://github.com/mabonmn


#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <stdlib.h>
#include <string>

// The maximum number of players is predefined as max 10
#define MAX_PLAYERS 10


using namespace std;


// Define the Class dice which creates a dice based on the total number of sides
// The class also contains a roll() function that generates a random number based on the 
// total number of sides in the dice. 
// Private 
//                   1. numSides -> Number of sides of the dice.
// Public:
//                   Class constructor based on the number of sides
//
//
//

class Dice {
private:
    int numSides;
public:
    Dice(int numSides) {
        this->numSides = numSides;
        srand((unsigned)time(0));
    }

    int roll() {
        
        int a = rand() % numSides + 1;
        return a;
    }
};




// Class Player which creates and class that store the player name and score
// Private Variables:
//                  1. name -> Player Name
//                  2. score -> Player Name
// Public 
//                  1.Class constructor load name and score
//                  2.getters for score
//                  3.addToScore -> Update Score
//
//
//


class Player {
private:
    string name;
    int score;
public:// Getter : Player Name
    Player(string Name, int Score) {   //Constructor
        this->name = Name;
        this->score = Score;

    }
    // Getter : Name
    string getName() {
        return name;

    }
    // Getter : Score
    int getScore() {
        return score;
    }

    void addToScore(int val) {
        score = score + val;;
        

    }
};

// Class DiceGame which defines the basic charecteristics of a dice game
// such as a function for the inout of new player information, etc. It 
// creates objects of the class Players and Dice .
// Private Variables:
//                  1.getNameAndScore-> Define Delimter to store name and score in the file
// Protected Variables:
//                  1.players -> Array of pointers to point to the Player objects
//                  2.Dice ->Pointers to point to the Dice object
//                  3.numPlayers, numDice-> TEMP Integer values
// Public 
//                  1.virtual void play()-> Virutal Function to be implement in the particalur game clases
//                  2.initPlayers()-> Initilize the players of the class
//                  3.displayScores()-> Display scores of each player
//                  4.writeScoresToFile()-> Write Scores in the file 
//                  5.findHighestScore()-> Display highest score in the file
//
//
//

class DiceGame {
private:
    void getNameAndScore(string line, char delimiter, string& name1, int& score1) {//script for getting the name and score from user
        int delimiterIdx = -1;
        for (int i = 0; line[i] != '\0'; i++) {
            if (line[i] == delimiter) {
                delimiterIdx = i;
            }
        }
        name1 = line.substr(0, delimiterIdx);
        score1 = atoi(line.substr(delimiterIdx + 1, delimiterIdx + 2).c_str());
    }
   
protected:
    Player* players[MAX_PLAYERS];
    Dice* dice;
    int numPlayers, numDice;

public:
    //Pure virtual function
    virtual void play() {};

    void initPlayers() {
        string Name;
        int score=0;
        int i = 0;
        while (i < numPlayers) {
            cout << "Player's Name? " << endl;
            cin >> Name;
            cout<<"Enter Score"<< endl;
            cin>> score;
            players[i] = new Player(Name, score);
            i = i + 1;
        }
    }

    void displayScores() {//to display score
        cout<<"\nDisplay Scores:\n";
        for (int i = 0; i < numPlayers; i++)
        {
            cout << players[i]->getName() << ":"<< players[i]->getScore() << endl; 
        }
    }

    void writeScoresToFile(char* fileName) {
        ofstream textFile(fileName, ios::app); 
        if (textFile.is_open())
        {
            for (int i = 0; i < numPlayers; i++)
            {
                textFile << players[i]->getName() << ":" << players[i]->getScore() << endl; 
            }
            textFile.close(); 
        }
        else
        {
            cout << "Unable to open the text file!"; 
        }
    }

    void findHighestScore(char* fileName) {
        string line, name, maxName;
        int score, maxScore = 0;
        ifstream textFile(fileName);

        if (textFile.is_open())
        {
            while (getline(textFile, line))
            {
                score = 0;
                getNameAndScore(line, ':', name, score);
                if (score > maxScore) {
                    maxScore = score;
                    maxName = name;
                }
            }
            textFile.close();
            cout << "Player with the highest score:\n" << maxName << "\t" << maxScore;
        }
        else {
            cout << "Unable to read from ip file";
        }
    }
};


// Class Knockout -> Inherits from the DiceGame Class 
// We difine the virtual function play() here for the game
//

class KnockOut : public DiceGame {
private:
    int Knock_Out_Score=0;
    int remainingPlayers=0;
    int sr=0;
public:
    
    KnockOut(int numSides, int numPlayers, int numDice) {
        dice=new Dice(numSides);
        this->numDice = numDice;
        this->numPlayers = numPlayers;
        for(int i=0;i<numDice;i++){
            Knock_Out_Score+=dice->roll();
        }
    }
    
    void play()
    {
        int Roll_Sum, Remaining_Players;
        
        Player *Original_Players[10];
        for (int i = 0; i < numPlayers; i++)
        {
            Original_Players[i]=new Player(players[i]->getName() , 0); 
            
        }

        Remaining_Players = numPlayers;
        while (Remaining_Players > 1)
        {
           
            for (int i = 0; i < numPlayers; i++)
            {
                Roll_Sum = 0;
                for (int j = 0; j < numDice; j++)
                {
                    Roll_Sum += dice->roll();
                }

                if (Roll_Sum == Knock_Out_Score)
                {   
                    cout<<"\n"<<Original_Players[i]->getName()<<" is knocked out \n";
                    Remaining_Players--; 
                    Original_Players[i]->addToScore(-1);
                    break;
                }
                
            }
        }
      
        for (int i = 0; i < numPlayers; i++)
        {   
            if (Original_Players[i]->getScore() >=0) 
            {   cout<<"\nGAME WINNER: \n";
                
                players[i]->addToScore(10); 
                cout<<players[i]->getName()<<':'<< players[i]->getScore()<<endl;
                break;
            }
        }

    }
};


// Class BostonDiceGame -> Inherits from the DiceGame Class 
// We difine the virtual function play() here for the game
//


class BostonDiceGame : public DiceGame
{
private:
    int maxroll=0,temp_store;
public:
    BostonDiceGame(int numSides, int numPlayers, int numDice) 
    {
        dice=new Dice(numSides);
        this->numPlayers = numPlayers;
        this->numDice = numDice; 
    }
    void play()
    {   int scoret=0,j=0;
        for(int i=0;i<numPlayers;i++){
            scoret=0;
            for(j=0;j<numDice;j++){
                maxroll=-1;
                for(int k=j;k<numDice;k++){
                    temp_store=dice->roll();
                    if(maxroll<temp_store){
                        maxroll=temp_store;
                    }
                }
                scoret+=maxroll;
            }
            players[i]->addToScore(scoret);
        }
    }
};

// Main Funtion


int main()
{   DiceGame* obj;
    int game, numPlayers, numDice, numSides;
    cout << "ENTER WHICH GAME YOU WOULD LIKE TO PLAY: \n1. Knock Out \n2. Boston Dice Game \n";
    cin >> game;
    cout << "Enter the number of dice \n";
    cin >> numDice;
    cout << "Enter the number of sides on the dice\n";
    cin >> numSides;
    cout << "Enter the number of Players:\n";
    cin >> numPlayers;
    if (game == 1) {
        KnockOut obj2(numSides, numPlayers, numDice);
        obj = &obj2;
        
    }
    else {
        BostonDiceGame obj2(numSides, numPlayers, numDice);
        obj = &obj2;
    }
    
    obj->initPlayers();
    obj->play();
    obj->displayScores();
    obj->writeScoresToFile("scorecard.txt");
    obj->findHighestScore("scorecard.txt");
    return 1;
}

/*	  Cerificate:
//....This Code was Developed By Mabon Manoj Ninan
......University of Cincinnati
......Machine Learning Reseacher: Lab Of Computer Vision- MNourzi
......Cource: Data Structures
......Instructor: Nitin Nitin
......05/31/2022
*/