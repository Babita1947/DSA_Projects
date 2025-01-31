#include<iostream>
#include<string>
#include<vector>
#include<ctime> //The ctime function is declared in the <ctime> header file. 
#include<cstdlib>
#include<fstream> // for file handling 

using namespace std;

vector<string> loadWords(){
    vector<string> words;
    string line;
    ifstream fin("wordlist.txt");// to read the wordlist.txt file
    while(getline(fin, line)){ // fin pick one line of string one by one if ends the string then it return false
        if(line.length() > 0){
            words.push_back(line);
        }
    }
    return words;
}

string choose_word(){
    vector<string> word_list = loadWords();
    srand(time(0));
    int random_index = rand() % word_list.size();
    return word_list[random_index];    
}
bool display_word(string word,const vector<char> &guessed_letters){
    bool winStatus = true;
    for(char c:word){
        if(find(guessed_letters.begin(),guessed_letters.end(), c) != guessed_letters.end()){
            cout<<c<<" ";
        }
        else{
            cout<<"_ ";
            winStatus = false;
        }
    }
    cout<<endl;
    return winStatus;
}

int main(){
    string word_to_guess = choose_word();
    vector<char> guessed_letters; 
    bool winStatus = false;
    int lives = 6;

    cout<<"Welcome to Hangman!"<<endl;

    while(lives > 0){
        cout<<"Lives Remaining: "<<lives<<endl;
        winStatus = display_word(word_to_guess,guessed_letters);

        if(winStatus){
            cout<<"Congratulations! You guessed the word: "<<word_to_guess<<endl;
            break;
        }
        char guess;
        cout<<"Guess a letter: ";
        cin>>guess;
        guessed_letters.push_back(guess);

        if(word_to_guess.find(guess) != string::npos){
            cout<<" Correct Guess! "<<endl;
        }
        else{
            cout<<"Incorrect Guess!"<<endl;
            lives--;
        }
    }
    if(lives == 0){
        cout<<"You lost!, The word was: "<<word_to_guess<<endl;
    }
    return 0;
}