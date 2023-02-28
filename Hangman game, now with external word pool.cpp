#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>

using namespace std;

const int MAX_WRONG = 6; // maximum number of incorrect guesses

int main()
{
    srand(static_cast<unsigned int>(time(0)));

    // Read in words from file
    vector<string> words;
    ifstream file("keyword.txt");
    if (file.is_open()) {
        string word;
        while (file >> word) {
            words.push_back(word);
        }
        file.close();
    } else {
        cerr << "Failed to open keyword file!" << endl;
        return 1;
    }

    // Select a random word from the list
    string target = words[rand() % words.size()];

    // Initialize the game state
    string state(target.size(), '_');
    int numWrong = 0;
    string guesses;

    // Game loop
    while (numWrong < MAX_WRONG && state != target) {
        // Print the current state of the game
        cout << "Word: " << state << endl;
        cout << "Guesses: " << guesses << endl;
        cout << "Number of wrong guesses left: " << MAX_WRONG - numWrong << endl;

        // Ask the player for a guess
        char guess;
        cout << "Enter a letter: ";
        cin >> guess;

        // Check if the guess is valid
        guess = tolower(guess);
        if (!isalpha(guess)) {
            cout << "Invalid guess! Please enter a letter." << endl;
            continue;
        } else if (guesses.find(guess) != string::npos) {
            cout << "You already guessed that letter!" << endl;
            continue;
        }

        // Record the guess
        guesses += guess;

        // Check if the guess is correct
        bool correct = false;
        for (int i = 0; i < target.size(); i++) {
            if (target[i] == guess) {
                state[i] = guess;
                correct = true;
            }
        }
        if (!correct) {
            numWrong++;
            cout << "Wrong guess!" << endl;
        } else {
            cout << "Correct guess!" << endl;
        }
    }

    // Print the final state of the game
    cout << "Word: " << target << endl;
    if (numWrong == MAX_WRONG) {
        cout << "You lose! The word was " << target << "." << endl;
    } else {
        cout << "You win! Congratulations!" << endl;
    }

    return 0;
}
