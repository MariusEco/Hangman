#include "../headers/HangmanGameWithScores.h"
#include "../headers/RandWord.h"
#include "../headers/UI.h"

HangmanGameWithScores::HangmanGameWithScores(const Highscore &highscore, const Player &player, int incorrectGuesses,
                                             const std::string &guessedLetters, int maxTries
) : AbstractHangman(player, incorrectGuesses,
                guessedLetters, maxTries),
    highscore(highscore) {}

Highscore* HangmanGameWithScores::getHighscore() const{
    return const_cast<Highscore*>(&highscore);
}

void HangmanGameWithScores::game() {
    UI::beginGame();
    UI::readPlayerName(player);
    bool play = true;
    while (play) {
        player.setScore(0);
        while (true) {
            guessedLetters = "";
            incorrectGuesses = 0;
            /// \brief The word that we have to guess
            std::string secret = RandWord::getRandomWord();
            /// \brief A simple terminal display of the word we have to guess
            std::string word_to_guess;
            UI::createDisplayedWord(secret, word_to_guess);
            /// \brief Condition for the game to continue
            while (incorrectGuesses < MAX_TRIES && word_to_guess != secret) {

                UI::displayWord(word_to_guess);

                char letter;
                std::cout << "Guess a letter: ";
                /// \brief Restriction for only 1 character input
                while (!(std::cin >> letter) || std::cin.peek() != '\n') {
                    std::cout << "Invalid input. Please enter a single letter: ";
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
                if (!AbstractHangman::not_letter(letter)) {
                    UI::displayMessage("Oops! That is not a valid letter. Try another one!");
                    incorrectGuesses++;
                    UI::displayTries(MAX_TRIES - incorrectGuesses);
                    continue;
                }
                if (guessedLetters.find(letter) != std::string::npos) {
                    UI::displayMessage("Oops! You already tried to guess that letter. Try another one!");
                    incorrectGuesses++;
                    UI::displayTries(MAX_TRIES - incorrectGuesses);
                    continue;
                }

                guessedLetters += letter;
                bool search = AbstractHangman::addLetters(secret, letter, word_to_guess);
                if (!search) {
                    incorrectGuesses++;
                    UI::displayMessage("Unfortunately the letter " + std::string(1, letter) +
                                       " is not found in the word. Try another one!");
                    UI::displayTries(MAX_TRIES - incorrectGuesses);
                }

            }
            if (word_to_guess == secret) {
                UI::displayEnd(true, secret, player);
                player.incrementScore();
                std::cout << "Current score: " << player.getScore() << "\n";
                highscore.displayHighscore();
            } else {
                UI::displayEnd(false, secret, player);
                std::cout << "Final score: " << player.getScore() << "\n";
                highscore.displayHighscore();
                break;
            }
        }
        int score = player.getScore();
        highscore.updateHighscore(player, score);
        std::string answer;
        std::cout << "Do you want to play again? (Y/N): ";
        std::cin >> answer;
        if (answer == "y" || answer == "Y") {
            play = true;
        } else play = false;
    }
}