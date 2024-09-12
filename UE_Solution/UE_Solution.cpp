#include <iostream>
#include <vector>
#include <array>
#include <string>

struct FPlayer
{
    std::string Name;
    int TeamID;
    float Health;
    float Damage;

    void Attack(FPlayer& opponent)
    {
        if (opponent.TeamID == TeamID)
        {
            std::cout << "Player can't attack other player from same team!" << std::endl;;
            return;
        }
        std::cout << Name << " attacks " << opponent.Name << " with " << Damage << " damage!" << std::endl;
        opponent.Health -= Damage;
        if (opponent.Health <= 0)
        {
            std::cout << opponent.Name << " dies!" << std::endl;;
        }
    }
};

struct FTeam
{
    int ID;
    std::string Name;
    std::vector<FPlayer> Players;

    bool HasLivingPlayers()
    {
        return !Players.empty();
    }

    void RemoveAllDeadPlayers()
    {
        for (auto it = Players.begin(); it != Players.end();)
        {
            if (it->Health <= 0)
            {
                it = Players.erase(it);
            }
            else
            {
                ++it;
            }
        }
    }
};

enum ECommand
{
    EC_AddPlayerToTeam,
    EC_RemovePlayerFromTeam,
    EC_SimulateFight
};

void DisplayAvailableCommands()
{
    std::cout << "================= Commands =================" << std::endl;
    std::cout << "0. Add player to team." << std::endl;
    std::cout << "1. Remove player from team." << std::endl;
    std::cout << "2. Simulate Fight." << std::endl;
    std::cout << "============================================" << std::endl;
}

bool IsValidCommand(int input)
{
    ECommand bMaybeValidCommand = static_cast<ECommand>(input);
    switch (bMaybeValidCommand)
    {
    case EC_AddPlayerToTeam:
    case EC_RemovePlayerFromTeam:
    case EC_SimulateFight:
        return true;
    }

    return false;
}

ECommand RequestCommandFromCommandLine()
{
    int input = -1;
    bool bIsValidCommand = false;

    while (!bIsValidCommand)
    {
        DisplayAvailableCommands();

        std::cout << "Enter command: ";
        std::cin >> input;

        bIsValidCommand = IsValidCommand(input);
        if (!bIsValidCommand)
        {
            std::cout << "Wrong command! Please, check list of commands below." << std::endl;
        }
    }

    return static_cast<ECommand>(input);
}

void ExecuteAddPlayerToTeamCommand(std::array<FTeam, 2>& teams)
{
    std::cout << "================= Add player to team =================" << std::endl;

    std::cout << "List of available teams:" << std::endl;
    for (FTeam& team : teams)
    {
        std::cout << "Team #" << team.ID << " - " << team.Name << std::endl;
    }

    int selectedTeamId = -1;

    while (selectedTeamId < 0)
    {
        std::string selectedTeamInput;
        std::cout << "Enter team name or ID: ";
        std::cin >> selectedTeamInput;

        for (FTeam& team : teams)
        {
            int inputIndex = -1;

            try
            {
                inputIndex = std::stoi(selectedTeamInput);
            }
            catch (std::invalid_argument)
            {
                inputIndex = -1;
            }

            if (selectedTeamInput == team.Name || inputIndex == team.ID)
            {
                selectedTeamId = team.ID;
            }
        }

        if (selectedTeamId < 0)
        {
            std::cout << "Please enter correct team name or id using info from list above." << std::endl;
        }
    }

    std::string playerName;

    FTeam& team = teams[selectedTeamId];
    bool bIsPlayerNameAvailableForCurrentTeam = false;

    while (!bIsPlayerNameAvailableForCurrentTeam)
    {
        bIsPlayerNameAvailableForCurrentTeam = true;

        std::cout << "Enter player name: ";
        std::cin >> playerName;

        for (auto it = team.Players.begin(); it != team.Players.end(); it++)
        {
            if (playerName == it->Name)
            {
                bIsPlayerNameAvailableForCurrentTeam = false;
            }
        }

        if (!bIsPlayerNameAvailableForCurrentTeam)
        {
            std::cout << "Player name already used in current team #" << team.ID << " - " << team.Name <<
                ". Please use different name." << std::endl;
        }
    }

    float health, damage;

    std::cout << "Enter " << playerName << "'s health: ";
    std::cin >> health;
    std::cout << "Enter " << playerName << "'s damage: ";
    std::cin >> damage;

    FPlayer newPlayer;

    newPlayer.TeamID = team.ID;
    newPlayer.Name = playerName;
    newPlayer.Health = health;
    newPlayer.Damage = damage;

    team.Players.push_back(newPlayer);

    std::cout << "Player " << newPlayer.Name << " has been successfully added to selected Team #" << team.ID << " - " <<
        team.Name << std::endl;
}

void ExecuteRemovePlayerFromTeamCommand(std::array<FTeam, 2>& teams)
{
    std::cout << "================= Remove player from team =================" << std::endl;

    std::cout << "List of available teams:" << std::endl;
    for (FTeam& team : teams)
    {
        std::cout << "Team #" << team.ID << " - " << team.Name << std::endl;
    }

    int selectedTeamId = -1;

    while (selectedTeamId < 0)
    {
        std::string selectedTeamInput;

        std::cout << "Enter team name or ID: ";
        std::cin >> selectedTeamInput;

        for (FTeam& team : teams)
        {
            int inputIndex = -1;

            try
            {
                inputIndex = std::stoi(selectedTeamInput);
            }
            catch (std::invalid_argument)
            {
                inputIndex = -1;
            }

            if (selectedTeamInput == team.Name || inputIndex == team.ID)
            {
                selectedTeamId = team.ID;
            }
        }

        if (selectedTeamId < 0)
        {
            std::cout << "Please enter correct team name or id using info from list above." << std::endl;
        }
    }

    std::string playerName;

    FTeam& team = teams[selectedTeamId];
    if (team.Players.empty())
    {
        std::cout << "Team #" << team.ID << " - " << team.Name <<
            " hasn't any players. Return back to the commands menu." << std::endl;;
        return;
    }

    bool bHasPlayerRemovedFromCurrentTeam = false;

    while (!bHasPlayerRemovedFromCurrentTeam)
    {
        std::cout << "Enter player name: ";
        std::cin >> playerName;

        for (auto it = team.Players.begin(); it != team.Players.end(); it++)
        {
            if (playerName == it->Name)
            {
                team.Players.erase(it);
                bHasPlayerRemovedFromCurrentTeam = true;
                break;
            }
        }

        if (bHasPlayerRemovedFromCurrentTeam)
        {
            std::cout << "Sorry, but team player is not exist in current team." << std::endl;
        }
    }

    std::cout << "Player " << playerName << " has been successfully removed from selected Team #" << team.ID << " - " <<
        team.Name << std::endl;
}

bool HasAllTeamsLivingPlayers(std::array<FTeam, 2>& teams)
{
    bool bHasAllTeamsLivingPlayers = true;
    for (auto& team : teams)
    {
        bHasAllTeamsLivingPlayers = bHasAllTeamsLivingPlayers && team.HasLivingPlayers();
    }

    return bHasAllTeamsLivingPlayers;
}

void ExecuteSimulateFightCommand(std::array<FTeam, 2>& teams)
{
    std::cout << "================= Simulate Fight =============" << std::endl;

    if (!HasAllTeamsLivingPlayers(teams))
    {
        std::cout <<
            "Some teams doesn't have any players. Simulation is impossible!. Return back to the command selection." <<
            std::endl;
        return;
    }

    int roundNumber = 1;

    while (HasAllTeamsLivingPlayers(teams))
    {
        int otherRandomTeamIndex;
        int randomTeamIndex = rand() % teams.size();

        // need to select random other team which is not the same as the first one
        do
        {
            otherRandomTeamIndex = std::rand() % teams.size();
        }
        while (randomTeamIndex == otherRandomTeamIndex);

        FTeam& team = teams[randomTeamIndex];
        FTeam& otherTeam = teams[otherRandomTeamIndex];

        int playerIndex = std::rand() % team.Players.size();
        int otherPlayerIndex = std::rand() % otherTeam.Players.size();

        team.Players[playerIndex].Attack(otherTeam.Players[otherPlayerIndex]);
        if (otherTeam.Players[otherPlayerIndex].Health <= 0)
        {
            otherTeam.RemoveAllDeadPlayers();
        }

        if (!otherTeam.HasLivingPlayers()) break;

        otherTeam.Players[otherPlayerIndex].Attack(team.Players[randomTeamIndex]);
        if (team.Players[randomTeamIndex].Health <= 0)
        {
            team.RemoveAllDeadPlayers();
        }

        std::cout << "***** Round " << roundNumber++ << " results" << "****" << std::endl;
        for (const auto& team : teams)
        {
            std::cout << team.Name << " has " << team.Players.size() << " players" << std::endl;
        }
        std::cout << "****************************************" << std::endl;
    }

    std::cout << "================= Fight is Over =============" << std::endl;

    FTeam& teamWithMaxPlayersAlive = teams.at(0);

    for (const auto& team : teams)
    {
        if (team.Players.size() > teamWithMaxPlayersAlive.Players.size())
        {
            teamWithMaxPlayersAlive = team;
        }
    }

    std::cout << teamWithMaxPlayersAlive.Name << " team with " << teamWithMaxPlayersAlive.Players.size() <<
        " player(s) alive has been WON this battle." << std::endl;
    std::cout << "============================================" << std::endl;
}


void ProcessCommand(const ECommand& command, std::array<FTeam, 2>& teams)
{
    switch (command)
    {
    case EC_AddPlayerToTeam:
        ExecuteAddPlayerToTeamCommand(teams);
        break;
    case EC_RemovePlayerFromTeam:
        ExecuteRemovePlayerFromTeamCommand(teams);
        break;
    case EC_SimulateFight:
        ExecuteSimulateFightCommand(teams);
        break;
    default:
        std::cout << "Command not found. Command code is " << command << std::endl;
        break;
    }
}

int main(int argc, char* argv[])
{
    bool isGamePlaying = true;

    std::array<FTeam, 2> Teams;

    for (int i = 0; i < Teams.size(); i++)
    {
        Teams[i].ID = i;
        std::cout << "Enter name of team " << i << ": ";

        std::string TeamName;
        bool IsAvailableTeamName = false;

        while (!IsAvailableTeamName)
        {
            std::cin >> TeamName;
            IsAvailableTeamName = true;

            for (int j = 0; j < i; j++)
            {
                if (Teams[j].Name == TeamName)
                {
                    IsAvailableTeamName = false;
                    break;
                }
            }

            if (!IsAvailableTeamName)
            {
                std::cout << "Please enter team name which is not used previously:" << std::endl;
            }
        }

        Teams[i].Name = TeamName;
    }


    while (isGamePlaying)
    {
        ECommand Command = RequestCommandFromCommandLine();
        ProcessCommand(Command, Teams);

        if (Command == EC_SimulateFight)
        {
            isGamePlaying = false;
        }
    }

    return 0;
}
