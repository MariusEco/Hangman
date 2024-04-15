#include <fstream>
#include "../headers/RandWord.h"
#include "../headers/Exceptions.h"

std::string RandWord::getRandomWord() {
    try {
        std::vector<std::string> fileNames = {"animals.txt", "clothes.txt", "fruits.txt", "home_objects.txt",
                                              "jobs.txt", "sports.txt", "transport.txt"};

        std::random_device rd;
        std::mt19937 rng(rd());
        std::uniform_int_distribution<int> fileDistribution(0, static_cast<int>(fileNames.size()) - 1);
        std::string chosenFileName = fileNames[fileDistribution(rng)];

        std::ifstream file(chosenFileName);
        if (!file.is_open()) {
            throw FileOpenException("Failed to open words file!");
        }

        std::vector<std::string> words;
        std::string word;
        while (file >> word) {
            bool validWord = true;
            for (char c: word) {
                if (!std::isalpha(c) && c != '\'' && c != '-') {
                    validWord = false;
                    break;
                }
            }
            if (validWord)
                words.push_back(word);
            else throw InvalidWordsException("Invalid word found in file!");
        }

        if (words.empty()) {
            throw EmptyFileException("No words found in the file!");
        }

        std::uniform_int_distribution<int> wordDistribution(0, static_cast<int>(words.size()) - 1);
        int index = wordDistribution(rng);

        return words[index];
    } catch (const std::exception &ex) {
        throw;
    }
}
