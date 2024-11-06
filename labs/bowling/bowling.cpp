#include <iostream>
#include <string>
#include <vector>

using namespace std;

const size_t NUMBER_OF_FRAMES = 10;
const size_t ROLLS_PER_FRAME = 2;
const size_t TOTAL_ROLLS = NUMBER_OF_FRAMES * 2 + 1; // 21
const int NUMBER_OF_PINS = 10;

void printPlayerRolls(const vector<int> &playerRolls) {
    for (size_t i = 0; i < playerRolls.size(); ++i) {
        cerr << playerRolls[i] << " ";
    }
    cerr << endl;
}

vector<int> inputPlayerRolls() {
    vector<int> playerRolls(TOTAL_ROLLS, 0);
    int rollInput;

    for (size_t frame = 0; frame < NUMBER_OF_FRAMES; ++frame) {
        for (size_t roll = 0; roll < ROLLS_PER_FRAME; ++roll) {
            cout << "Enter score for frame " << frame + 1 << ", roll " << roll + 1 << ": ";
            cin >> rollInput;
            if (rollInput > NUMBER_OF_PINS) {
                cout << "Roll must be less than " << NUMBER_OF_PINS << endl;
                roll--;
                continue;
            }
            const int roll_idx = (frame * 2) + roll;
            playerRolls[roll_idx] = rollInput;
            if (rollInput == NUMBER_OF_PINS) {
                break;
            }
        }
    }

    if (playerRolls[18] == NUMBER_OF_PINS) {
        cout << "Enter score for frame 10, roll 2: ";
        cin >> rollInput;
        playerRolls[19] = rollInput;
    }

    if (playerRolls[18] + playerRolls[19] == NUMBER_OF_PINS) {
        cout << "Enter score for frame 10, roll 3: ";
        cin >> rollInput;
        playerRolls[20] = rollInput;
        
    }

    if (playerRolls[19] == NUMBER_OF_PINS) {
        cout << "Enter score for frame 10, roll 3: ";
        cin >> rollInput;
        playerRolls[20] = rollInput;
    }

    return playerRolls;
}

int calculatePlayerScore(const vector<int> &playerRolls) {
    int playerScore = 0;

    for (size_t frameNumber = 0; frameNumber < NUMBER_OF_FRAMES - 1;
         ++frameNumber) {

        const size_t currentFrame = frameNumber * 2;
        const size_t nextFrame = currentFrame + 2;
        const size_t nextNextFrame = nextFrame + 2;

        const int roll1 = playerRolls[currentFrame];
        const int roll2 = playerRolls[currentFrame + 1];

        const bool isStrike = roll1 == NUMBER_OF_PINS;
        const bool isSpare = roll1 + roll2 == NUMBER_OF_PINS;

        playerScore += roll1 + roll2;
        if (isStrike) {
            if (frameNumber == 8) {
                playerScore += playerRolls[nextFrame] + playerRolls[nextFrame + 1];
                continue;
            }
            if (playerRolls[nextFrame] == NUMBER_OF_PINS) {
                playerScore += playerRolls[nextFrame] + playerRolls[nextNextFrame];
                continue;
            }

            playerScore += playerRolls[nextFrame] + playerRolls[nextFrame + 1];
            continue;
        }
        if (isSpare) {
            playerScore += playerRolls[nextFrame];
        }
    }

    playerScore += playerRolls[18];
    playerScore += playerRolls[19];
    playerScore += playerRolls[20];

    return playerScore;
}

void printGameSummary(const vector<string> &playerNames,
                      const vector<int> &playerScores) {

    if (playerNames.empty()) {
        cout << "No players were entered." << endl;
        return;
    }

    cout << endl;

    for (size_t i = 0; i < playerNames.size(); ++i) {
        cout << playerNames[i] << " scored " << playerScores[i] << "." << endl;
    }
    

    string worstPlayerName = playerNames[0];
    int worstPlayerScore = playerScores[0];

    string bestPlayerName = playerNames[0];
    int bestPlayerScore = playerScores[0];

    for (size_t i = 1; i < playerNames.size(); ++i) {
        if (playerScores[i] > bestPlayerScore) {
            bestPlayerScore = playerScores[i];
            bestPlayerName = playerNames[i];
        }
        if (playerScores[i] < worstPlayerScore) {
            worstPlayerScore = playerScores[i];
            worstPlayerName = playerNames[i];
        }
    }

    cout << worstPlayerName << " did the worst by scoring " << worstPlayerScore << "." << endl;
    cout << bestPlayerName << " won the game by scoring " << bestPlayerScore << "." << endl;
}

int main() {
    vector<string> playerNames;
    vector<int> playerScores;
    
    while (true) {
        string inputString;

        cout << "Enter player's name (done for no more players): ";
    
        cin >> inputString;
        
        if (inputString == "done") {
            break;
        }
        
        playerNames.push_back(inputString);

        const vector<int> playerRolls = inputPlayerRolls();

        const int playerScore = calculatePlayerScore(playerRolls);
        playerScores.push_back(playerScore);

        if (!cin) {
            throw runtime_error("Invalid input");
        }
    }

    if (playerNames.size() == 0) {
        cout << "No players were entered." << endl;;
        return 0;
    }

    printGameSummary(playerNames, playerScores);
    
    return 0;
}
