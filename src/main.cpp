#include <iostream>
#include <fstream>
#include <string>
#include <numeric>
#include <unordered_map>

const uint8_t NUMBER_OF_ELVES = 3;

void advent_of_code_22_1()
{
    std::fstream file;
    file.open("../inputs/task_01.txt", std::ios::in);

    if (!file.is_open()) {
        std::cerr << "COULD NOT OPEN INPUT FILE" << std::endl;
        return;
    }

    std::string line;
    uint64_t mostCalories = 0;
    uint64_t topNCalories[NUMBER_OF_ELVES] = {};
    while (std::getline(file, line)) {
        if (line.empty()) {
            continue;
        }
        uint64_t calories = stoi(line);
        while (std::getline(file, line)) {
            if (line.empty()) {
                break;
            }
            calories += stoi(line);
        }
        for (int i = 0; i < NUMBER_OF_ELVES; i++) {
            if (calories > topNCalories[i]) {
                // move elves down by one rank
                for (int j = NUMBER_OF_ELVES - 2; j >= i; j--) {
                    topNCalories[j+1] = topNCalories[j];
                }
                topNCalories[i] = calories;
                break;
            }
        }
        mostCalories = std::max(mostCalories, calories);
    }
    std::cout << "Advent of code 1: Most calories: " << mostCalories << std::endl;
    uint64_t sum = 0;
    std::cout << "Top N elves: " << topNCalories[0] << " " << topNCalories[1] << " " << topNCalories[2] << " sum: " << std::accumulate(topNCalories, topNCalories + NUMBER_OF_ELVES, sum) << std::endl;
}

void advent_of_code_22_2()
{
    std::fstream file;
    file.open("../inputs/task_02.txt", std::ios::in);

    if (!file.is_open()) {
        std::cerr << "COULD NOT OPEN INPUT FILE" << std::endl;
        return;
    }

    std::unordered_map<std::string, std::unordered_map<std::string, uint8_t>> rockPaperScissorScores(
    {
        {
            "A", // rock
            {
                {"X", (3 + 1)}, // rock, draw + 1
                {"Y", (6 + 2)}, // paper, win + 2
                {"Z", (0 + 3)}  // scissor, loose + 3
            }
        },
        {
            "B", // paper
            {
                {"X", (0 + 1)}, // rock, loose + 1
                {"Y", (3 + 2)}, // paper, draw + 2
                {"Z", (6 + 3)}  // scissor, win + 3
            }
        },
        {
            "C", // scissor
            {
                {"X", (6 + 1)}, // rock, win + 1
                {"Y", (0 + 2)}, // paper, loose + 2
                {"Z", (3 + 3)}  // scissor, draw + 3
            }
        }
    });

    std::unordered_map<std::string, std::unordered_map<std::string, uint8_t>> rockPaperScissorScoresSecond(
    {
        {
            "A", // rock
            {
                {"X", (0 + 3)}, // scissor, loose + 3
                {"Y", (3 + 1)}, // rock, draw + 1
                {"Z", (6 + 2)}  // paper, win + 2
            }
        },
        {
            "B", // paper
            {
                {"X", (0 + 1)}, // rock, loose + 1
                {"Y", (3 + 2)}, // paper, draw + 2
                {"Z", (6 + 3)}  // scissor, win + 3
            }
        },
        {
            "C", // scissor
            {
                {"X", (0 + 2)}, // paper, loose + 2
                {"Y", (3 + 3)}, // scissor, draw + 3
                {"Z", (6 + 1)}  // rock, win + 1
            }
        }
    });

    std::string line;
    uint64_t score = 0;
    uint64_t scoreSecond = 0;
    while (std::getline(file, line)) {
        std::string opponentChoice = std::string(1, line.at(0));
        std::string ourChoice = std::string(1, line.at(2));
        score += rockPaperScissorScores[opponentChoice][ourChoice];
        scoreSecond += rockPaperScissorScoresSecond[opponentChoice][ourChoice];
    }
    std::cout << "Advent of code 2: total scores: " << score << "|" << scoreSecond << std::endl;
}

int main(int argc, char* argv[])
{
    advent_of_code_22_1();
    advent_of_code_22_2();
    return 0;
}
