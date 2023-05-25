#include "Round.h"

void Round::addBet(std::string name, Bet bet)
{
    m_players_bets[name] = bet;
}

void Round::removeBet(std::string player_name)
{
    m_players_bets.erase(player_name);
}

void Round::printRoundInfo() const
{
    int sum = 0;
    std::cout << "=========== Round " << m_round_number << " Results ===========\n"
              << std::endl;

    for (auto const &player : m_players_bets)
    {
        std::string status;
        if (player.second.getNumberPicked() == m_round_result)
            status = "Won!";
        else
            status = "Lost...";

        std::cout << "Name: " << player.first << "\nNumber picked: " << player.second.getNumberPicked() << "\nAmount: " << player.second.getAmount() << "\nresult: " << status << "\n"
                  << std::endl;

        sum += player.second.getAmount();
    }
    std::cout << "Round result was: " << m_round_result << std::endl;
    std::cout << "Total money bet on:" << sum << std::endl;
    std::cout << "\n=========== Round " << m_round_number << " End ===========" << std::endl;
}

int Round::getRoundNumber() const
{
    return m_round_number;
}

int Round::getRoundResult() const
{
    return m_round_result;
}

void Round::setRoundResult(int round_result)
{
    this->m_round_result = round_result;
}