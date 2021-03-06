/**
 * Football League Software Code.
 *
 * @author Mark Hester (k00233238)
 * @version 1.0 (20/04/2018)
*/

#include "stdafx.h"
#include "CFootballTeam.h"
#include "CFootballLeague.h"
#include "CDisplay.h"
#include "CFootballTable.h"
#include "CAuthentication.h"

using namespace std;

CFootballLeague League; // League management.
CAuthentication Auth; // Login gate.

// Required functions.
void DoLoadFromFile(void);
void DoDisplayLeague();
void DoEnterMatchResult(void);
void DoDeductPoints(void);
void DoBestDefence(void);
void DoRelegationZone(void);
void DoAddTeamToList(void);

// Additional functions.
void DoInitilizeNewTable(void);
void DoDisplayLoginPanel(void);
void DoRemoveTeamFromList(void);
void GenerateTeamTable(CFootballTeam[], int teamsize, string tablename);

/**
 * Constants for default file location.
 */
const string LOCATION_LEAGUE_DATA = "league.dat";
const string LOCATION_USERS_DATA = "users.dat";

/**
 * Allows logic gates for user permissions.
 */
bool MenuGuard(CUser::user_type user_type);
void MenuDisplay(CUser::user_type user_type, const string message);

/**
 * Entry point of application.
 * Display and allow the user to select a menu option, which provides
 * further dialogue instructions, logic will live inside the league 
 * object. 
 * 
 * @return integer application executution code
 */
int main()
{
	// Store the user input.
	int menuSelection;

	CDisplay::Linebreak('=');
	CDisplay::Message("=> League data read/write file: " + LOCATION_LEAGUE_DATA, CDisplay::COLOR_CYAN);
	CDisplay::Message("=> Users data read/write file: " + LOCATION_USERS_DATA, CDisplay::COLOR_CYAN);
	CDisplay::Linebreak('=');

	// Display Login panel for usage.
	DoDisplayLoginPanel();

	// Create the data for the league.
	DoLoadFromFile();

	do
	{
		/**
		 * VIEW.
		 */
		CDisplay::Heading("League Menu.");
		MenuDisplay(CUser::USERTYPE_MANAGER,   "1. Initialize A New League Table");
		MenuDisplay(CUser::USERTYPE_ASSISTANT, "2. Display League Table");
		MenuDisplay(CUser::USERTYPE_ASSISTANT, "3. Enter a Match Result");
		MenuDisplay(CUser::USERTYPE_ASSISTANT, "4. Deduct Points");
		MenuDisplay(CUser::USERTYPE_ASSISTANT, "5. Best Defence");
		MenuDisplay(CUser::USERTYPE_ASSISTANT, "6. Relegation Zone");
		MenuDisplay(CUser::USERTYPE_MANAGER,   "7. Add Team to List");
		MenuDisplay(CUser::USERTYPE_MANAGER,   "8. Remove Team from List");
		MenuDisplay(CUser::USERTYPE_ASSISTANT, "0. Quit");
		CDisplay::Linebreak('-');

		CDisplay::Input("Input menu selection : ", menuSelection);

		/**
		 * LOGIC
		 */
		switch (menuSelection)
		{
			case 1: if (MenuGuard(CUser::USERTYPE_MANAGER))   DoInitilizeNewTable();  else  CDisplay::Failure("Invalid Permission."); break;
			case 2: if (MenuGuard(CUser::USERTYPE_ASSISTANT)) DoDisplayLeague();	  else  CDisplay::Failure("Invalid Permission."); break;
			case 3: if (MenuGuard(CUser::USERTYPE_ASSISTANT)) DoEnterMatchResult();	  else  CDisplay::Failure("Invalid Permission."); break;
			case 4: if (MenuGuard(CUser::USERTYPE_ASSISTANT)) DoDeductPoints();	      else  CDisplay::Failure("Invalid Permission."); break;
			case 5: if (MenuGuard(CUser::USERTYPE_ASSISTANT)) DoBestDefence();	      else  CDisplay::Failure("Invalid Permission."); break;
			case 6: if (MenuGuard(CUser::USERTYPE_ASSISTANT)) DoRelegationZone();	  else  CDisplay::Failure("Invalid Permission."); break;
			case 7: if (MenuGuard(CUser::USERTYPE_MANAGER))   DoAddTeamToList();	  else  CDisplay::Failure("Invalid Permission."); break;
			case 8: if (MenuGuard(CUser::USERTYPE_MANAGER))   DoRemoveTeamFromList(); else  CDisplay::Failure("Invalid Permission."); break;
			case 0: continue;
			
			default: CDisplay::Failure("Please enter a valid menu choice.");
		}
		
	} while (menuSelection != 0);

    return EXIT_SUCCESS;
}

void DoInitilizeNewTable(void)
{
	string teamname;
	string agreement;

	CDisplay::Heading("Creating a new league table.");

	CDisplay::Status("WARNING!", "This will destroy all existing league data.", CDisplay::COLOR_CYAN);

	while(true)
	{
		CDisplay::Input("Are you sure you wish to continue? [Yes, No] ", agreement);
		if (agreement == "No" || agreement == "no" || agreement == "n") return;
		if (agreement == "Yes" || agreement == "yes" || agreement == "y") break;
	}

	League.LeagueClear(); // reset/clear the league.

	for (int i = 0; i < League.GetMaxLeagueSize(); i++)
	{
		CDisplay::Input("Add team to league [type stop to finish]: ", teamname);

		if (teamname == "stop" || teamname == "Stop") break;

		League.Expand(CFootballTeam(teamname));

		CDisplay::Message(teamname + " was added to the league.");
	}

	CDisplay::Success("New table has been initilized.");
}

/**
 * Console dialogue for reading from the persistant storage of the league table.
 * 
 * @return void
 */
void DoLoadFromFile(void)
{

	CDisplay::Linebreak('-');

	if (League.LoadLeagueData(LOCATION_LEAGUE_DATA) == true)
	{
		CDisplay::Message("League loading completed.", CDisplay::COLOR_GREEN);
	}
	else
	{
		CDisplay::Message("An error occured while loading the league.", CDisplay::COLOR_RED);
	}
}

/**
 * Console Dialogue choosen by user for displaying and generating a table with all the
 * teams that exist within the league object.
 * 
 * @return void
 */
void DoDisplayLeague()
{
	CFootballTable::Heading("All Teams");

	if (League.GetTeamSize() == 0)
	{
		CDisplay::Message("No team data to be shown.");
	}
	else
	{
		for (int i = 0; i < League.GetTeamSize(); i++) {
			CFootballTable::TeamStanding(League.GetTeam(i));
		}
	}

	CFootballTable::Footer(League.GetTeamSize());
}

/**
 * Console Dialogue choosen by user for entering a match record into the league object.
 * 
 * @return void
 */
void DoEnterMatchResult()
{
	int homescore, awayscore;
	string hometeam, awayteam;

	CDisplay::Heading("League match results recording.");
	CDisplay::Input("Enter Home teamname : ", hometeam);
	CDisplay::Input("Enter Home team score : ", homescore);
	CDisplay::Input("Enter Away teamname : ", awayteam);
	CDisplay::Input("Enter Away team score : ", awayscore);

	if (League.TeamExists(hometeam) && League.TeamExists(awayteam)) 
	{
		League.RecordScore(hometeam, homescore, awayscore);
		League.RecordScore(awayteam, awayscore, homescore);
		CDisplay::Success("League scores have been updated.");
		return;
	}

	CDisplay::Failure("One of the team names entered did not exist.");

}

/**
 * Console dialogue choosen by user for removing points from a team existing in the league object.
 * 
 * @return void
 */
void DoDeductPoints()
{
	string teamname;
	int points;

	CDisplay::Heading("Team disciplinary point deduction.");
	CDisplay::Input("Enter teamname : ", teamname);
	CDisplay::Input("Enter deduction points : ", points);

	if (League.TeamExists(teamname)) 
	{
		League.RemovePoints(teamname, points);
		CDisplay::Success("Point(s) have been deducted from " + teamname);
		return;
	}

	CDisplay::Failure("Team with name " + teamname + " does not exist.");
}

/**
 * Console display of a generated table using a pass-by-reference array and team count.
 * 
 * Display and show the team(s) with the most conceeded goals in the league.
 * 
 * @return void
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

/**
 * Console display of a generated table using a pass-by-reference array and team count.
 * 
 * Display and show the last three teams in the league.
 * 
 * @return void
 */
void DoRelegationZone()
{
	// A maximum of three teams should be stored.
	const unsigned int relegation_size = 3;

	// Storage for relegation teams.
	CFootballTeam relegation_teams[3];

	// Get the last teams in the league.
	League.GetTeamsFacingRelegation(relegation_teams, relegation_size);

	// Display the teams in console table.
	GenerateTeamTable(relegation_teams, relegation_size, "Leagues Relegated Teams");
}

/**
 * Allows the user to add a new team to the existing list of teams.
 * 
 * @return void
 */
void DoAddTeamToList()
{
	string teamname;
	int games_played, goals_for, goals_against, points;

	CDisplay::Heading("Add pre-existing team details to league.");
	CDisplay::Input("Enter teamname : ", teamname);
	CDisplay::Input("Enter team games played : ", games_played);
	CDisplay::Input("Enter team goals for : ", goals_for);
	CDisplay::Input("Enter team goals against : ", goals_against);
	CDisplay::Input("Enter team points : ", points);

	if (League.TeamExists(teamname))
	{
		CDisplay::Failure("A team already exists with the name " + teamname);
		return;
	}

	League.Expand(CFootballTeam(teamname, games_played, goals_for, games_played, points));

	CDisplay::Success(teamname + " has been added to the current league.");
}

/**
 * @return void
 */
void DoRemoveTeamFromList()
{
	string teamname;

	CDisplay::Heading("Remove an existing team from the league");
	CDisplay::Input("Enter teamname : ", teamname);

	if (League.TeamExists(teamname))
	{
		League.RemoveTeam(teamname);

		CDisplay::Success("Team " + teamname + " has been removed from the league.");

		return;
	}

	CDisplay::Failure("Cannot remove non-existant team from the league.");
}

/**
 * Generate a table of teams based on the array of teams and the array size.
 * Allows the usage of showing Best Defenders and Relegation zoned teams.
 * 
 * @return void
 */
void GenerateTeamTable(CFootballTeam teams[], int teamsize, string tablename)
{
	CFootballTable::Heading(tablename);

	if (teamsize == 0)
	{
		CDisplay::Message("No team data to be shown.");
	}
	else
	{
		for (int i = 0; i < teamsize; i++)
		{
			CFootballTable::TeamStanding(teams[i]);
		}
	}

	CFootballTable::Footer(teamsize);
}

/**
 * MenuGuard Logic for access to the function.
 * 
 * @param user_type the type required for access.
 * 
 * @return boolean of the condition.
 */
bool MenuGuard(CUser::user_type user_type)
{
	return Auth.CurrentUser().HasPermission(user_type);
}

void MenuDisplay(CUser::user_type user_type, const string message)
{
	if (MenuGuard(user_type))
	{
		CDisplay::Message(message);

		return;
	}

	CDisplay::Message(message, CDisplay::COLOR_RED);
}


void DoDisplayLoginPanel()
{
	string username, password;

	while(true)
	{
		CDisplay::Heading("Login Panel");
		CDisplay::Input("Enter your username: ", username);
		CDisplay::Input("Enter your password: ", password);

		if (Auth.AttemptLogin(username, password))
		{
			CDisplay::Success("Welcome to the Football League Software " + Auth.CurrentUser().GetUsername() + "!");

			return;
		}

		CDisplay::Failure("Incorrect password [" + to_string(Auth.GetLoginAttemptCount()) + " attempts made]");
	}
}
