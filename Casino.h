#ifndef CASINO_H
#define CASINO_H
#include <iostream>
#include <memory>
#include <vector>
#include <string.h>
#include "Bet.h"
#include "Player.h"
#include "Round.h"

class Player;

using namespace std;
class Casino
{
private:
    //  players in the casino
    vector<std::shared_ptr<Player>> m_players;

    //  recored of rounds
    vector<std::shared_ptr<Round>> m_rounds;

    //  current round number
    int m_round_number;

public:
    Casino() : m_players(), m_rounds(), m_round_number(0){};
    void startRound();
    void addPlayer(std::string name, int money);
    void removePlayer(std::string name);
    void printGameStatus();
    void printRoundInfo(int round);
    void printOpenningAnouncment() const;
    void printChoiseOptions() const;
    void printGoodByeMSG() const;
    int handleChoise();
    void handleAddPlayer();
    void handleRemovePlayer();
    void handlePrintRoundResults();
};

#endif