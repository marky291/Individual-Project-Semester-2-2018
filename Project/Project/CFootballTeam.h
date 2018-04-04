#pragma once

using namespace std;

class CFootballTeam
{
	private:
		// Attributes
		string m_Name;
		int m_GamesPlayed;
		int m_GoalsFor;
		int m_GoalsAgainst;
		int m_Points;

	public:
		// Constructors
		CFootballTeam(void);
		CFootballTeam(string name);
		CFootballTeam(string name, int gamesPlayed, int goalsFor, int goalsAgainst, int points);

		// Accessors
		string GetName(void);
		int GetGamesPlayed(void);
		int GetGoalsFor(void);
		int GetGoalsAgainst(void);
		int GetPoints(void);
		bool HasName(string searchName);

		// Implementors
		int GetGoalDifference();
		void DeductPoints(int num);
		void UpdateOnResult(int goalsFor, int goalsAgainst);
		bool IsLessThan(CFootballTeam& team);
};

