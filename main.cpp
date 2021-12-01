#include <iostream>
#include <random>
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <vector>

#define clear() system("clear");
using namespace std;

string getMask(string str);
string updateMask(char guess, const char* str, string masked, int *tries, int *count);
string setDifficulty(int *tries);
vector<string> getList(const char* dif);
int randNum(int max);

int main(){
  clear();
  int tries = 8;
  int count = 0;
  string input;
  string dif = setDifficulty(&tries);
  vector<char> guesses;
  vector<string> list; //use this to load the list of words


    //grab the line from the word list
    list = getList(dif.c_str());

    //random number to choose line in file
    int line = randNum(list.size()); //avg .0023638 time

  string str = list[line];

  string masked = getMask(str);

  while(tries>0 && count < str.length()){
    clear();

      cout << "Welcome to Hangman\n\n";

      cout << "Tries: " << tries << "\n\n";

      cout << masked << endl;


      if(guesses.size()){
          cout << "\nUsed characters: ";
          for(int i = 0; i < guesses.size(); i++){
              cout << guesses[i] << ' ';
          }
          cout << "\n" <<  endl;
      }
      cin >> input;
      cin.ignore();
      if(input.length() == 1){
          bool dup = false;
          for(int i = 0; i < guesses.size(); i++){
              if(guesses[i] == char(tolower(input[0]))){
                  dup = true;
              }
          }
          if(!dup){
          guesses.push_back(char(tolower(input[0])));
         masked = updateMask(char(tolower(input[0])), str.c_str(), masked, &tries, &count); //masked.c_str()

          //sort the vector of guesses
          int temp;
          for(int i = 0; i < guesses.size(); i++){
            for(int j = 0; j < guesses.size(); j++){
              if(int(guesses[j]) > int(guesses[i])){
                temp = int(guesses[i]);
                guesses[i] = guesses[j];
                guesses[j] = char(temp);
              }
            }
          }
          }
      }

    }
    clear();
  if(count == str.length()){
      cout << "Congrats the answer was " << str << endl;
  }
  if(tries == 0){
      cout << "The word was " << str << ". Better luck next time!" << endl;
  }

  cout << "\nPlay Again? [y]es or [n]o" << endl;
  cin >> input; cin.ignore();
  if(tolower(input[0]) == 'y'){
    main();
  }
  else{
    return 0;
  }
}

//load the word file
vector<string> getList(const char* dif){
    vector<string> list;
    ifstream words(dif);
    string temp;
    while(getline(words, temp)){
        list.push_back(temp);
    }
    words.close();
    return list;
}

//generate random number to get word from file == line in list
int randNum(int max){
    srand((unsigned) time(0));
    int line = rand()% max + 1;

    return line;
}

//setting difficulty
string setDifficulty(int *tries){
  while(true){
    cout << "Please select a difficulty level [e]asy, [n]ormal [h]ard" << endl;
    string dif;
    cin >> dif; cin.ignore();

    switch(tolower(dif[0])){
    case 101:
      return "easy.txt";
    case 110:
      *tries -= 1;
      return "normal.txt";
    case 104:
      *tries -= 2;
      return "hard.txt";
    default:
      continue;
  }  }
}

string getMask(string str){
    str += str;
    int len = str.length();
    for(int i = 0; i < len; i++){
        if(i%2){
            str[i] = ' ';
        }
        else{
            str[i] = '_';
        }
    }

    return str;
}
// update the console and masked word if letter is correct
string updateMask(char guess, const char* str, string masked, int *tries, int *count){
    bool correct = false;
    int len = string(str).length();
     for(int i = 0; i < len; i++){
         if(str[i] == guess){
             masked[i*2] = guess;
             correct = true;
             *count += 1;
         }
 }
 if(!correct){
     *tries = *tries-1;
 }
 return masked;
}

//eventually i'll replace the one word with puzzles from wheeloffortuneanswer.com
