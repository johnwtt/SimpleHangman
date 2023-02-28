#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

void printHangman(int wrongGuesses) {
    cout << "   +-----+\n";
    cout << "   |     |\n";
    cout << "   |     ";
    if (wrongGuesses >= 1) cout << "O";
    cout << endl;
    cout << "   |    ";
    if (wrongGuesses >= 3) cout << "/";
    if (wrongGuesses >= 2) cout << "|";
    if (wrongGuesses >= 4) cout << "\\";
    cout << endl;
    cout << "   |     ";
    if (wrongGuesses >= 5) cout << "/";
    cout << " ";
    if (wrongGuesses >= 6) cout << "\\";
    cout << endl;
    cout << "   |\n";
    cout << "  ===\n\n";
}

int main() {
    // Read in the keywords from a file
    ifstream inFile;
    inFile.open("keyword.txt");
    if (!inFile) {
        cerr << "Unable to open file keyword.txt";
        exit(1);
    }

    vector<string> keywords;
    string word;
    while (inFile >> word) {
        keywords.push_back(word);
    }
    inFile.close();

    // Set up the game
    srand(time(nullptr));
    string keyword = keywords[rand() % keywords.size()];
    string hiddenKeyword(keyword.size(), '-');
    int wrongGuesses = 0;
    vector<char> guessedLetters;

    // Play the game
    cout << "Welcome to Hangman!" << endl;
    while (wrongGuesses < 6 && hiddenKeyword != keyword) {
        // Print the current state of the game
        cout << "Guess the word: " << hiddenKeyword << endl;
        cout << "Guessed letters: ";
        for (char c : guessedLetters) {
            cout << c << " ";
        }
        cout << endl;
        printHangman(wrongGuesses);

        // Get the user's guess
        cout << "Guess a letter: ";
        char guess;
        cin >> guess;

        // Check if the letter has already been guessed
        bool alreadyGuessed = false;
        for (char c : guessedLetters) {
            if (c == guess) {
                alreadyGuessed = true;
                break;
            }
        }
        if (alreadyGuessed) {
            cout << "You already guessed that letter." << endl;
            continue;
        }

        // Add the letter to the list of guessed letters
        guessedLetters.push_back(guess);

        // Check if the guess is correct
        bool correctGuess = false;
        for (int i = 0; i < keyword.size(); i++) {
            if (keyword[i] == guess) {
                hiddenKeyword[i] = guess;
                correctGuess = true;
            }
        }
        if (correctGuess) {
            cout << "Correct!" << endl;
        } else {
            cout << "Incorrect." << endl;
            wrongGuesses++;
        }
    }

    // Print the final state of the game
    if (wrongGuesses == 6) {
        cout << "You lose! The word was " << keyword << "." << endl;
        printHangman(wrongGuesses);
    } else {
        cout << "Congratulations, you win! The word was " << keyword << "." << endl;
    }

    return 0;
}
