#include <iostream>
#include <random>
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <vector>

#define clear() system("clear");
using namespace std;

string getMask(const char* str);
string updateMask(char guess, const char* str, const char* masked, int *tries, int *count);
string setDifficulty(int *tries);

int main(){
  clear();
  int tries = 8;
  int count = 0;
  string dif = setDifficulty(&tries);
  vector<char> guesses;
  vector<string> list;

  
  //grab the line from the word list
  ifstream words(dif);
  string temp;
  while(getline(words, temp)){
    list.push_back(temp);
  }
  words.close();

//random number to choose line in file
  srand((unsigned) time(0));
  int line = rand()% list.size() + 1;

  string str = list[line];

  string masked = getMask(str.c_str());

  while(tries>0 && count < str.length()){
    clear();
      cout << "Welcome to Hangman\n" << endl;
      
      cout << "Tries: " << tries << "\n" << endl;
      
      cout << masked << endl;
      
      
      if(guesses.size()){
          cout << "\nUsed characters: ";
          for(int i = 0; i < guesses.size(); i++){
              cout << guesses[i] << ' ';
          }
          cout << "\n" <<  endl;
      }
      string guess;
      cin >> guess;
      cin.ignore();
      if(guess.length() == 1){
          bool dup = false;
          for(int i = 0; i < guesses.size(); i++){
              if(guesses[i] == char(tolower(guess[0]))){
                  dup = true;
              }
          }
          if(!dup){
          guesses.push_back(char(tolower(guess[0])));
          masked = updateMask(guess[0], str.c_str(), masked.c_str(), &tries, &count);

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
  string again;
  cin >> again; cin.ignore();
  if(tolower(again[0]) == 'y'){
    main();
  }
  else{
    return 0;
  }
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

//masking the word
string getMask(const char* str){
    string masked = string(str);
    masked += masked;
    for(int i = 0; i < masked.length(); i++){
        if(i%2){
            masked[i] = ' ';
        }
        else{
            masked[i] = '_';
        }
    }
    
    return masked;
}

// update the console and masked word if letter is correct
string updateMask(char guess, const char* str, const char* masked, int *tries, int *count){
    string mask = string(masked);
    bool correct = false;
 for(int i = 0; i < string(str).length(); i++){
     if(str[i]==char(tolower(guess))){
         mask[i*2] = char(tolower(guess));
         correct = true;
         *count += 1;
     }
 }
 if(!correct){
     *tries = *tries-1;
 }
 return mask;
}


//eventually i'll replace the one word with puzzles from wheeloffortuneanswer.com
