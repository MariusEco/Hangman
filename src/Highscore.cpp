#include "../headers/Highscore.h"

void Highscore::updateHighscore(const Player &player1, int score) {
    if (score > highscore) {
        highscore = score;
        std::cout << "Congratulations, " << player1.getName() << "! You have a new highscore: " << highscore << "\n";
    }
}

void Highscore::displayHighscore() const {
    std::cout << "Highscore : " << highscore << "\n";
}

Highscore::Highscore(const Player &player, int highscore) : player(player), highscore(highscore) {}

std::ostream &operator<<(std::ostream &os, const Highscore &highscore) {
    os << "player: " << highscore.player << " highscore: " << highscore.highscore;
    return os;
}