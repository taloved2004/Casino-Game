#include "Casino.h"
#include <string.h>

bool isValidGuess(std::string cmd_line)
{
    //  check if a number between 1 to 10
    if (int(cmd_line.size()) == 1 && isdigit(cmd_line[0]))
        return (cmd_line[0] != '0');
    else if (int(cmd_line.size()) == 2 && cmd_line == "10")
        return true;
    else
        return false;
}

int getNumberPicked()
{
    bool valid_number = false;
    int number_picked;

    std::string cmd_line;

    std::cout << "Guess any betting number between 1 & 10 :" << std::endl;
    while (!valid_number)
    {
        cmd_line = "";

        //  get input
        while (cmd_line == "")
        {
            std::cout << "Guess>";
            std::getline(std::cin, cmd_line);
        }

        // check validation
        if (cmd_line == "-1")
            return -1;
        else if (isValidGuess(cmd_line))
        {
            number_picked = stoi(cmd_line);
            valid_number = true;
        }
        else
            std::cout << "ERROR : Number should be between 1 to 10, please try again!"
                      << std::endl;
    }

    return number_picked;
}

bool isValidAmount(std::string cmd_line)
{
    if (cmd_line == "")
        return false;
    //  check if every character is a digit
    for (int i = 0; i < int(cmd_line.size()); i++)
    {
        if (!isdigit(cmd_line[0]))
            return false;
    }
    return true;
}

bool isThereActivePlayers(vector<std::shared_ptr<Player>> m_players)
{
    //  check if there atleast one player who has money
    for (auto player : m_players)
        if (player->getMoney() > 0)
            return true;
    return false;
}

int getAmountOfBet(int max_bet)
{

    bool valid_money = false;
    int bet_amount = 0;

    std::string cmd_line;

    std::cout << "Please enter amount to bet :" << std::endl;
    while (!valid_money)
    {
        cmd_line = "";
        //  get input
        while (cmd_line == "")
        {
            std::cout << "Amount>";
            std::getline(std::cin, cmd_line);
        }

        //  check validation
        if (isValidAmount(cmd_line))
            bet_amount = stoi(cmd_line);
        else
            bet_amount = -1;

        //  check if possible bet
        if (bet_amount >= 1 && bet_amount <= max_bet)
            valid_money = true;
        else
            std::cout << "ERROR : Invalid amount, please try again!\n";
    }
    return bet_amount;
}

void Casino::startRound()
{
    //  check if there are players
    if (m_players.empty())
    {
        std::cout << "\nThere are no players in the game.\n"
                  << std::endl;
        return;
    }

    //  check if there are players with money to bet on
    if (!isThereActivePlayers(m_players))
    {
        std::cout << "\nThere are no Active players in the game.\n"
                  << std::endl;
        return;
    }

    //  increase round counter
    m_round_number++;

    //  print openning messege
    std::cout << "=========== Casino Game - Round " << m_round_number << " ===========" << std::endl;

    std::cout << "Please place your bets!" << std::endl;
    std::cout << "***Note: if you don't want to participate this round enter -1 as guess" << std::endl;

    //  create new round
    std::shared_ptr<Round> cur_round(new Round(m_round_number));

    //  get bets for players
    for (std::shared_ptr<Player> player : m_players)
    {
        std::cout << "Hey, " << player->getName() << std::endl;

        //  check if player can play
        if (player->getMoney() <= 0)
        {
            std::cout << "Looks like you ran out of money, such a shame!" << std::endl;
            continue;
        }

        //  get player guess
        int number_picked = getNumberPicked();
        int bet_amount = 0;

        //  get player's bet amount
        if (number_picked != -1)
            bet_amount = getAmountOfBet(player->getMoney());

        //  update player's current bet
        Bet player_bet(bet_amount, this->m_round_number, number_picked);
        player->setCurrentBet(player_bet);

        //  add bet to round
        if (number_picked != -1)
            cur_round->addBet(player->getName(), player_bet);
    }

    //  get a random number between 1 - 10
    int random_number = (rand() % 10) + 1;

    //  print results
    std::cout << "---------- Round " << m_round_number << " Result ----------" << std::endl;

    std::cout << "\nThe number is ... " << random_number << " !" << std::endl;
    std::cout << "Congrats to the winners!\n " << std::endl;

    //  apply round result on players
    for (std::shared_ptr<Player> player : m_players)
    {

        player->applyBet(random_number);
    }

    // upadte the results vector
    cur_round->setRoundResult(random_number);
    m_rounds.push_back(cur_round);
}

void Casino::printRoundInfo(int round)
{
    m_rounds[round - 1]->printRoundInfo();
}

void Casino::addPlayer(std::string name, int money = 100)
{
    if (money < 0)
        money = 0;

    //  check if player exists
    for (auto player : m_players)
    {
        if (player->getName() == name)
        {
            std::cout << "\n"
                      << name << " is taken! Try again later\n"
                      << std::endl;
            return;
        }
    }

    //  create and add player
    std::shared_ptr<Player> new_player(new Player(name, money));
    this->m_players.push_back(new_player);
}

void Casino::removePlayer(std::string name)
{
    // check if player exists
    for (int i = 0; i < int(m_players.size()); i++)
    {
        if (m_players[i]->getName() == name)
        {
            m_players.erase(m_players.begin() + i);
            std::cout << "Player Removed." << std::endl;
            return;
        }
    }

    //  print error messege if player do not exists
    std::cout << "ERROR : Player " << name << " doesn't found"
              << std::endl;
}

void printOpenningStatus(int m_round_number)
{
    std::cout << "=========== Casino Game - Status ===========" << std::endl;
    std::cout << "Rounds Played: " << m_round_number << std::endl;
    std::cout << "------- Players Balance -------" << std::endl;
}

void printPlayersInfo(std::vector<std::shared_ptr<Player>> &players)
{
    if (players.empty())
        std::cout << "\nThere are no players in the game\n"
                  << std::endl;
    else
    {
        //  print info for every player
        for (std::shared_ptr<Player> player : players)
            player->printPlayerStatus();
    }
}

void Casino::printGameStatus()
{
    printOpenningStatus(this->m_round_number);
    printPlayersInfo(m_players);
    std::cout << "============================================" << std::endl;
}

void rules()
{
    cout << "======CASINO NUMBER GUESSING RULES!======\n";
    cout << "1. Choose a number between 1 to 10\n";
    cout << "2. Winner gets 10 times of the money bet\n";
    cout << "3. Wrong bet, and you lose the amount you bet\n\n";
}

void Casino::printOpenningAnouncment() const
{
    std::cout << "=========== Casino Game ===========" << std::endl;
    std::cout << "Welcome to my Casino!\n\n";
    rules();
}

void Casino::printChoiseOptions() const
{

    std::cout << "---------- Options ----------" << std::endl;
    std::cout << "Pick Your Choise:" << std::endl;
    std::cout << "(1) - Start New Round." << std::endl;
    std::cout << "(2) - Add New Player." << std::endl;
    std::cout << "(3) - Remove Player." << std::endl;
    std::cout << "(4) - Print Game's Status" << std::endl;
    std::cout << "(5) - Print Specific Round's Info" << std::endl;
    std::cout << "(6) - Exit Game" << std::endl;
}

bool validOption(std::string cmd_line)
{
    return (cmd_line == "1" || cmd_line == "2" || cmd_line == "3" || cmd_line == "4" || cmd_line == "5" || cmd_line == "6");
}

int Casino::handleChoise()
{
    //  get input
    std::string cmd_line;
    bool is_valid = false;
    while (!is_valid)
    {
        is_valid = true;
        cmd_line = "";

        while (cmd_line == "")
        {
            std::cout << "option>";
            std::getline(std::cin, cmd_line);
        }
        int choise;

        //  check validation
        if (!validOption(cmd_line))
            choise = -1;
        else
            choise = stoi(cmd_line);

        // handle choise
        switch (choise)
        {
        case 1:
            startRound();
            break;
        case 2:
            handleAddPlayer();
            break;
        case 3:
            handleRemovePlayer();
            break;
        case 4:
            this->printGameStatus();
            break;
        case 5:
            handlePrintRoundResults();
            break;
        case 6:
            this->printGoodByeMSG();
            return 0;
            break;
        default:
            std::cout << "ERROR : Invalid choise!"
                      << std::endl;
            is_valid = false;
            break;
        }
    }
    return 1;
}

std::string getNewPlayerName(const vector<std::shared_ptr<Player>> &m_players)
{
    std::string name;
    bool is_valid = false;

    std::cout << "Enter new player's name (-1 to abort action): " << std::endl;

    while (!is_valid)
    {
        name = "";
        //  get input
        while (name == "")
        {
            std::cout << "Name>";
            std::getline(std::cin, name);
        }
        //  check if user asked to cancel
        is_valid = true;
        if (name == "-1")
            return name;

        //  check if player is already exists
        for (auto player : m_players)
        {
            if (player->getName() == name)
            {
                is_valid = false;
                std::cout << "ERROR : This name already exists - try again!\n";
                break;
            }
        }
    }
    return name;
}

bool isNonNegativeNumber(std::string cmd_line)
{
    if (cmd_line == "")
        return false;
    //  check if a string is a non negative number
    for (int i = 0; i < int(cmd_line.size()); i++)
    {
        if (!isdigit(cmd_line[i]))
            return false;
    }
    return true;
}

int getNewPlayerMoneyAmount()
{
    int money = 0;
    bool is_valid = false;
    std::string cmd_line = "";

    std::cout << "Enter new player's ballance (-1 to abort action): " << std::endl;

    while (!is_valid)
    {
        cmd_line = "";
        //  get input
        while (cmd_line == "")
        {
            std::cout << "Ballance>";
            std::getline(std::cin, cmd_line);
        }

        // user asked to cancel
        if (cmd_line == "-1")
            return -1;
        else if (isNonNegativeNumber(cmd_line))
        {
            money = stoi(cmd_line);
            is_valid = true;
        }
        else
        {
            std::cout << "ERROR : Ballance must be a non-negative number!"
                      << std::endl;
            is_valid = false;
        }
    }
    return money;
}

void Casino::handleAddPlayer()
{
    //  get new player's name
    std::string player_name(getNewPlayerName(this->m_players));

    //  check if user asked to cancel
    if (player_name == "-1")
        return;

    //  get new player's money
    int money_amount = getNewPlayerMoneyAmount();
    if (money_amount == -1)
        return;

    //  add player
    this->addPlayer(player_name, money_amount);
}

void Casino::handleRemovePlayer()
{
    //  check if there are players in the system
    if (m_players.empty())
        std::cout << " \nThere are no players in the game.\n"
                  << std::endl;
    else
    {
        std::cout << "Enter player to remove:" << std::endl;

        //  get player to remove
        std::string player_name = "";
        while (player_name == "")
        {
            std::cout << "Name>";
            std::getline(std::cin, player_name);
        }
        //  remove player
        this->removePlayer(player_name);
    }
}

void Casino::handlePrintRoundResults()
{
    if (m_round_number == 0)
    {
        std::cout << "No round was played yet." << std::endl;
        return;
    }

    int round_requested;
    bool is_valid = false;
    std::string cmd_line;

    std::cout << "Pick a a round from the " << m_round_number << " rounds played:\n";
    while (!is_valid)
    {
        cmd_line = "";
        while (cmd_line == "")
        {
            std::cout << "round>";
            //  get input from user
            std::getline(std::cin, cmd_line);
        }
        //  check if valid number
        if (isNonNegativeNumber(cmd_line))
        {

            round_requested = stoi(cmd_line);

            //  check if round number exists
            if (round_requested >= 1 && round_requested <= m_round_number)
            {

                //  print requsted round info
                this->printRoundInfo(round_requested);
                is_valid = true;
            }
        }

        //  check if process ended right
        if (!is_valid)
            std::cout << "Error : Round doesn't exists in system, try again!\n";
    }
}

void Casino::printGoodByeMSG() const
{
    std::cout << "Thanks for playing - see you soon!" << std::endl;
    std::cout << "=========== Casino Game - Out ===========" << std::endl;
}
