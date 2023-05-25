#ifndef ROUND_H
#define ROUND_H
#include <iostream>
#include <map>
#include <memory>
#include "Bet.h"
#include "Player.h"

using namespace std;
class Round
{
private:
    // round's number
    int m_round_number;

    //  round's result
    int m_round_result;

    //  record of players bets
    std::map<std::string, Bet> m_players_bets;

public:
    Round(int round_number) : m_round_number(round_number), m_round_result(), m_players_bets(){};
    void addBet(std::string name, Bet bet);
    void removeBet(std::string player_name);
    void printRoundInfo() const;
    int getRoundNumber() const;
    int getRoundResult() const;
    void setRoundResult(int round_result);
};

#endif