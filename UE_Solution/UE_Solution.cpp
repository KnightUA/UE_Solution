#include <iostream>
#include <vector>
#include <array>

struct FPlayer
{
    std::string Name;
    int TeamID;
    float Health;
    float Damage;
};

struct FTeam
{
    int ID;
    std::string Name;
    std::vector<FPlayer> Players;
};

enum ECommand
{
    EC_AddPlayerToTeam,
    EC_RemovePlayerFromTeam,
    EC_SimulateFight
};

enum EGameResult
{
    EGR_Unknown,
    EGR_TeamWins,
    EGR_Draw
};

void DisplayAvailableCommands();
bool IsValidCommand(int input);
ECommand RequestCommandFromCommandLine();
void HandleCommand(ECommand command, std::array<FTeam, 2>* teams);
void ExecuteAddPlayerToTeamCommand(std::array<FTeam, 2>* teams);
void ExecuteRemovePlayerFromTeamCommand(std::array<FTeam, 2>* teams);
void ExecuteSimulateFightCommand(std::array<FTeam, 2>* teams);

int main(int argc, char* argv[])
{
    EGameResult GameResult = EGR_Unknown;

    std::array<FTeam, 2> Teams;

    for (int i = 0; i < Teams.size(); i++)
    {
        Teams[i].ID = i;
        std::cout << "Enter name of team " << i << ": " << std::endl;

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


    while (GameResult == EGR_Unknown)
    {
        ECommand Command = RequestCommandFromCommandLine();
        HandleCommand(Command, &Teams);
        GameResult = EGR_Draw;
    }

    return 0;
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
            std::cout << "Wrong command! Please, check list of commands below.";
        }
    }

    return static_cast<ECommand>(input);
}

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


void HandleCommand(ECommand command, std::array<FTeam, 2>* teams)
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

void ExecuteAddPlayerToTeamCommand(std::array<FTeam, 2>* teams)
{
    std::cout << "================= Add player to team =================" << std::endl;
    
    std::cout << "List of available teams:" << std::endl;
    for (FTeam team : *teams)
    {
        std::cout << "Team #" << team.ID << " - " << team.Name << std::endl;
    }
}

void ExecuteRemovePlayerFromTeamCommand(std::array<FTeam, 2>* teams)
{
}

void ExecuteSimulateFightCommand(std::array<FTeam, 2>* teams)
{
}
