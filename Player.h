#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include "Bet.h"

using namespace std;
class Player
{
private:
    //  player's name
    std::string m_name;

    //  player's money
    int m_money;

    //  player's last bet
    Bet m_current_bet;

    //  player's number of rounds won
    int m_rounds_won;

public:
    Player(std::string name, int money) : m_name(name), m_money(money), m_current_bet(), m_rounds_won()
    {
        m_money = m_money < 0 ? 0 : m_money;
    }
    ~Player() = default;
    std::string getName() const;
    int getMoney() const;
    void printPlayerStatus() const;
    void setCurrentBet(Bet player_bet);
    void applyBet(int result);
};

#endif