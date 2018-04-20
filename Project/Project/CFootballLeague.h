#pragma once

#include "CFootballTeam.h"
#include "CFootballTable.h"

/**
 * League object will be used for management of a collection of teams.
 * 
 * @author Mark Hester (k00233238).
 * @date 09/04/2018.
 */
class CFootballLeague
{
	private: 
		/**
		 * Define the maximum allowed teams in the league.
		 * This will be used for logic and memory allocation on array.
		 */
		int m_MaxLeagueSize = 25;

		/**
		 * Track the number of teams stored in the team array.
		 */
		int m_LeagueSize = 0;

		/**
		 * Array memory allocation for maximum data storage of teams in the league.
		 */
		CFootballTeam m_League[25];

	public:

		/**
		* Get the total count of teams in the league.
		*
		* @return integer the count of teams in the league.
		*/
		int GetTeamSize(void);

		/**
		 * Get the maximum count of teams the league can hold.
		 * 
		 * @return integer the max. count of teams the league can hold.
		 */
		int GetMaxLeagueSize(void);

		/**
		 * Remove all teams from the league table, start of season?
		 * 
		 * @return void
		 */
		void LeagueClear(void);

		/**
		* Check if a team exists using teamname.
		*
		* @param teamname for name of team
		*
		* @return boolean of the team existance in the league
		*/
		bool TeamExists(const string teamname);

		/**
		* Record a match results for a single team.
		*
		* @param teamname for name of team
		* @param goalsFor the goals team has scored.
		* @param goalsAgainst the goals conceeded by the team
		*
		* @return void
		*/
		void RecordScore(string teamname, int goalsFor, int goalsAgainst);

		/**
		* Deduct points from total team points.
		*
		* @param teamname for name of team.
		* @param points that should be deducted from team.
		*
		* @return void
		*/		
		void RemovePoints(string teamname, int points);

		/**
		* Get the most conceeded goals in the league by a single team.
		*
		* @return the most conceeded goals in the league by a single team.
		*/
		int MostGoalsConceeded(void);

		/**
		* Return an array from the league of the teams with the least amount of goals conceeded.
		*
		* @param defenderTeams[] pass-by-reference for array of teams to be listed.
		* @param foundTeams the array size to be captured and sent back.
		*
		* @return void
		*/		
		void GetTeamsWithBestDefence(CFootballTeam defenderTeams[], unsigned int& foundTeams);

		/**
		* Return an array from the league with the teams facing relegation using the relegation size.
		*
		* @param relegationTeams pass-by-reference for array of teams to be listed.
		* @param relegationSize the array size to be captured and sent back.
		*
		* @return void
		*/		
		void GetTeamsFacingRelegation(CFootballTeam relegationTeams[], const int relegationSize);

		/*
		* An accessor that allows retrieval of an element from the array.
		*
		* @param position of the array as an integer.
		*
		* @return the retrieved team from the league.
		*/
		CFootballTeam& GetTeam(const int position);

		/*
		* An accessor that allows retrieval of an element where teamname is equal to element teamname.
		*
		* @param teamname the name of the team to retrieve.
		*
		* @return the retrieved team from the league.
		*
		* @exception will be thrown if team can not be retrieved.
		*/
		CFootballTeam& GetTeam(const string teamname);

		/**
		 * Return the integer position where the team sits on the array.
		 */
		int GetArrayPosition(CFootballTeam& team);

		/*
		* An accessor that allows the setting of an element in the league array.
		*
		* @param position of the array as an integer.
		* @param team object that should be stored in the position.
		*
		* @return void
		*/
		void SetTeam(const int position, CFootballTeam& team);

		/**
		* Expand the league to accomadate a new team. <https://en.wikipedia.org/wiki/Expansion_team>
		*
		* @param team the object that will be added to the league.
		*
		* @return boolean of condition of league addition.
		*/
		bool Expand(CFootballTeam team);

		/**
		* Accessor that allows a team to be removed from the league array.
		*
		* @param teamname the name of the team to be removed.
		*
		* @return void
		*/
		void RemoveTeam(string teamname);

		/**
		* Update the team positions in the league, based on the conditional requirements of the model.
		* This will assign each team a league position and use bubble sort to sort and order.
		*
		* @return void
		*/
		void SyncLeagueTable(void);

		/**
		 * The data inside the league will be saved to league.dat allowing persistant data.
		 * 
		 * @return boolean condition of the writing to league.dat
		 */
		bool SaveLeagueData(string fileLocation);

		/**
		 * The data inside the league.dat file will be loaded into the league class.
		 * 
		 * @return boolean condition of the loading of league.dat
		 */
		bool LoadLeagueData(string fileLocation);
};

