// Project.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "CFootballTeam.h"
#include "CFootballTable.h"
#include "CFootballLeague.h"

using namespace std;

CFootballTable Table;
CFootballLeague League;

void DoInitialize(void);
void DoDisplayLeague();
void DoEnterMatchResult(void);
void DoDeductPoints(void);
void DoBestDefence(void);
void DoRelegationZone(void);
void DoAddTeamToList(void);

// Generation for all teams.
void GenerateLeagueTable();

// Generate for relegation teams & best defence.
void GenerateTeamTable(CFootballTeam [], int teamsize, string tablename);

int main()
{
	int menuSelection;
	bool cls = true;

	do
	{
		std::cout << "\t\t\t" << "League Menu." << endl;
		std::cout << "\t\t\t" << "--------------------------" << endl;
		std::cout << "\t\t\t" << "1. Initialize League Table" << endl;
		std::cout << "\t\t\t" << "2. Display League Table" << endl;
		std::cout << "\t\t\t" << "3. Enter a Match Result" << endl;
		std::cout << "\t\t\t" << "4. Deduct Points" << endl;
		std::cout << "\t\t\t" << "5. Best Defence" << endl;
		std::cout << "\t\t\t" << "6. Relegation Zone" << endl;
		std::cout << "\t\t\t" << "7. Add Team to List" << endl;
		std::cout << "\t\t\t" << "0. Quit" << endl;

		cin >> menuSelection;

		switch (menuSelection)
		{
			case 1: 
				DoInitialize(); 
				cls = true;
				break;

			case 2: 
				DoDisplayLeague();
				cls = false;
				break;

			case 3: 
				DoEnterMatchResult(); 
				cls = true;
				break;

			case 4: DoDeductPoints(); 
				cls = true;
				break;

			case 5: DoBestDefence(); 
				cls = false;
				break;

			case 6: 
				DoRelegationZone(); 
				cls = false;
				break;

			case 7: DoAddTeamToList(); 
				cls = false;
				break;

			case 0:
				// quit option.
				break;
			
			default: 
				cout << "\t\t\t" << "Please enter a valid menu choice." << endl;
		}

		/*
		 * We dont want to clear tables from being shown.
		 */
		if (cls == true)
		{
			system("cls");
		}
		
	} while (menuSelection != 0);

    return 0;
}

//callback for option 0
//Scan the collection ....
//allow user to enter a team name
//instantiate an object
//copy the object into the collection
void DoInitialize(void)
{
	string teamname;

	cout << "\t\t\t" << "Enter [Teamname] for league addition." << endl;

	cout << "\t\t\t => "; cin >> teamname;

	CFootballTeam team(teamname);

	League.Expand(team);
}

/*
 * Display the league will all the teams.
 */
void DoDisplayLeague()
{
	GenerateLeagueTable();
}

/*
 * should allow the user to enter a match result in the form:
 * hometeam homescore awayteam awayscore
 */
void DoEnterMatchResult()
{
	int homescore, awayscore;

	string hometeam, awayteam;

	cout << "\t\t\t" << "Enter [Hometeam] [Homescore] [AwayTeam] [AwayScore]." << endl;

	cout << "\t\t\t => "; cin >> hometeam >> homescore >> awayteam >> awayscore;

	// If home team not found, ask again.
	while (League.RecordScore(hometeam, homescore, awayscore) == false)
	{
		cout << "\t\t\t" << "Hometeam was not found, try again. [Hometeam] [Homescore]" << endl;

		cout << "\t\t\t => "; cin >> hometeam >> homescore;
	}

	// If away team not found, ask again.
	while (League.RecordScore(awayteam, awayscore, homescore) == false)
	{
		cout << "\t\t\t" << "Awayteam was not found, try again. [AwayTeam] [AwayScore]" << endl;

		cout << "\t\t\t => "; cin >> awayteam >> awayscore;
	}
}

void DoDeductPoints()
{
	int points;

	string teamname;

	cout << "\t\t\t" << "Enter [Teamname] and [Teampoints] to deduct." << endl;
	cout << "\t\t\t => "; cin >> teamname >> points;

	while (League.RemovePoints(teamname, points) == false)
	{
		cout << "\t\t\t" << "Team not found, try again. [teamname] [points]" << endl;

		cout << "\t\t\t => "; cin >> teamname >> points;
	}
}

/*
 * DoBestDefence (callback for option 4) should firstly search the collection league to
 * ascertain the lowest number of goals against. The collection should then be re-searched and
 * the name(s) of the team(s) with the lowest goals against should be displayed.
 */
void DoBestDefence()
{
	// storage for best defender teams.
	CFootballTeam best_defenders[25];

	// Populate this with the league class.
	unsigned int count_teams_found = 0;

	// Get the teams in the league with best defence.
	League.GetTeamsWithBestDefence(best_defenders, count_teams_found);

	// Teams with the lowest goals should be displayed.
	GenerateTeamTable(best_defenders, count_teams_found, "Leagues Best Defenders");
}

/*
 * This should display the names and points of the last three teams in the league.
 */
void DoRelegationZone()
{
	// A maximum of three teams should be stored.
	const unsigned int relegation_size = 3;

	// Storage for relegation teams.
	CFootballTeam relegation_teams[relegation_size];

	// Get the last teams in the league.
	League.GetTeamsFacingRelegation(relegation_teams, relegation_size);

	// Display the teams in console table.
	GenerateTeamTable(relegation_teams, relegation_size, "Leagues Relegated Teams");
}

/*
 * Allows the user to add a new team to the existing list of teams.
 */
void DoAddTeamToList()
{
}

/*
 * Generate a table of all the teams in the league.
 */
void GenerateLeagueTable()
{
	Table.Header("All Teams");

	for (int i = 0; i < League.GetTeamSize(); i++)
	{
		Table.TeamStanding(League.GetTeam(i));
	}

	Table.Footer(League.GetTeamSize());
}

/*
 * Generate a table of teams based on the array of teams and the array size.
 * Allows the usage of showing All, Best Defenders and Relegation zoned teams.
 */
void GenerateTeamTable(CFootballTeam teams[], int teamsize, string tablename)
{
	Table.Header(tablename);

	for (int i = 0; i < teamsize; i++)
	{
		Table.TeamStanding(teams[i]);
	}

	Table.Footer(teamsize);
}