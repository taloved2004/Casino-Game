#include "Player.h"

std::string Player::getName() const
{
    return this->m_name;
}

int Player::getMoney() const
{
    return this->m_money;
}

void Player::printPlayerStatus() const
{
    std::cout << "Name: " << m_name << std::endl;
    std::cout << "Current Ballance: " << m_money << std::endl;
    std::cout << "Rounds Won: " << m_rounds_won << "\n"
              << std::endl;
}

void Player::setCurrentBet(Bet player_bet)
{
    this->m_current_bet = player_bet;
}

void Player::applyBet(int result)
{
    if (m_current_bet.getNumberPicked() == result)
    {
        //  victory
        m_rounds_won++;
        m_money += m_current_bet.getAmount() * 9;
    }
    else // lose
    {
        m_money -= m_current_bet.getAmount();
        if (m_money <= 0)
        {
            m_money = 0;
            Bet b(0, 0, 0);
            m_current_bet = b;
        }
    }
}