#pragma once

#include "CFootballTeam.h"
#include "CFootballTable.h"

class CFootballLeague
{
	private: 
		// Adapt the application so that it could be used for leagues of various sizes.
		// This supplements the required allowance of various team sizes based on user input.
		// DEFAULT = 10. MAXIMUM IS ALLOCATED ON ARRAY MEMORY (25).
		// int max_league_size = 10;

		// Counter for the current size of the football team array.
		int m_TeamSize = 0;

		// Adapt the application so that it could be used for leagues of various sizes up to a maximum of 25 teams.
		// !! Allocate a total of 25 slots for the entire league as this is the maximum allowed value.
		CFootballTeam m_Team[25];

	public:
		// Get the used array team size.
		int GetTeamSize();

		// Check the teamname exists in the league.
		bool TeamExists(string name);

		// Record scoring for a team. (applies logic).
		bool RecordScore(string teamname, int goalsFor, int goalsAgainst);

		// Remove points from a team. (applies logic).
		bool RemovePoints(string teamname, int points);

		// Return the lowest conceeded goals by a team on the league.
		int LowestGoalsConceeded(void);

		// Get all the teams with the lowest conceeded goals on the league.
		// Store on the input array based on the array size.
		void GetTeamsWithBestDefence(CFootballTeam defenderTeams[], unsigned int& foundTeams);

		// Get Last three teams in the league.
		// Store on the input array based on the relegation size.
		void GetTeamsFacingRelegation(CFootballTeam relegationTeams[], const int relegationSize);

		// Return the team with the name.
		CFootballTeam& GetTeam(string teamname);

		// Return the team from an array position.
		CFootballTeam& GetTeam(int array_position);

		// Return the team from an array position.
		void SetTeam(int position, CFootballTeam& team);

		// Add a new team to the league
		// This will increment the league size and add a new value.
		// @note: new teams joining a league <https://en.wikipedia.org/wiki/Expansion_team>
		bool Expand(CFootballTeam team);

		// Remove a team from the league based on their array position number.
		// Usefull for menu with text-based table display with number input.
		void RemovePositionedTeam(const unsigned int position);

		// Team sorting method based on points.
		// Could be abstracted better, but this will do for the project.
		void UpdateTeamPositions(void);

		// Place a single team into the league, using the sorting
		// algorithem, this is a more direct approach to a single
		// object.
		// void SortTeamIntoLeague(CFootballTeam& team);

		// Update the teams position in the league.
		// also referred to as a team position.
		// void UpdateTeamLeaguePositions(void);
};

