#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

const int MAX_WRONG = 8; // maximum number of incorrect guesses allowed

int main() {
    srand(static_cast<unsigned int>(time(0)));

    vector<string> words; // collection of possible words
    ifstream file("keyword.txt");
    if (file.is_open()) {
        string word;
        while (getline(file, word)) {
            words.push_back(word);
        }
        file.close();
    } else {
        cerr << "Failed to open keyword file!" << endl;
        return 1;
    }

    char playAgain = 'y';
    while (playAgain == 'y') {
        string word = words[rand() % words.size()]; // word to guess
        int wrong = 0; // number of incorrect guesses
        string soFar(word.length(), '-'); // word guessed so far
        string used; // letters already guessed

        cout << "\nWelcome to Hangman. Good luck!\n";

        // game loop
        while ((wrong < MAX_WRONG) && (soFar != word)) {
            cout << "\n\nYou have " << (MAX_WRONG - wrong) << " incorrect guesses left.\n";
            cout << "\nYou've used the following letters:\n" << used << endl;
            cout << "\nSo far, the word is:\n" << soFar << endl;

            char guess;
            cout << "\n\nEnter your guess: ";
            cin >> guess;
            guess = tolower(guess); // convert to lowercase

            while (used.find(guess) != string::npos) {
                cout << "\nYou've already guessed " << guess << endl;
                cout << "Enter your guess: ";
                cin >> guess;
                guess = tolower(guess);
            }

            used += guess;

            if (word.find(guess) != string::npos) {
                cout << "\nThat's right! " << guess << " is in the word.\n";

                // update soFar to include newly guessed letter
                for (int i = 0; i < word.length(); ++i) {
                    if (word[i] == guess) {
                        soFar[i] = guess;
                    }
                }
            } else {
                cout << "\nSorry, " << guess << " isn't in the word.\n";
                ++wrong;
            }
        }

        // game over
        if (wrong == MAX_WRONG) {
            cout << "\nYou've been hanged!";
        } else {
            cout << "\nYou guessed it!";
        }

        cout << "\nThe word was " << word << "\n\n";
        cout << "Do you want to play again? (y/n): ";
        cin >> playAgain;
    }

    return 0;
}
