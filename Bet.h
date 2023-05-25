#ifndef BET_H
#define BET_H
#include <iostream>

using namespace std;
class Bet
{
private:
    int m_bet_amount;
    int m_round_number;
    int m_number_picked;

public:
    Bet() = default;
    Bet(int bet_amount, int round_number, int number_picked) : m_bet_amount(bet_amount), m_round_number(round_number), m_number_picked(number_picked)
    {
    }
    ~Bet() = default;

    int getNumberPicked() const;
    int getAmount() const;
};

#endif