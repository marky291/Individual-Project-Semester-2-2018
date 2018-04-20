#include "stdafx.h"
#include "CFootballTeam.h"
#include "CFootballTable.h"

/**
 * Default constructor.
 */
CFootballTeam::CFootballTeam() :
	m_Name(""),
	m_GamesPlayed(0),
	m_GoalsFor(0),
	m_GoalsAgainst(0),
	m_Points(0),
	m_LeaguePosition(0)
{
}

/**
 * Football Team Constructor
 * 
 * @param name of the team.
 */
CFootballTeam::CFootballTeam(string name) : 
	m_Name(name),
	m_GamesPlayed(0),
	m_GoalsFor(0),
	m_GoalsAgainst(0),
	m_Points(0),
	m_LeaguePosition(0)
{
}

/**
 * Constructor
 * 
 * @param name of the team.
 * @param gamesPlayed the count of games played by the team.
 * @param goalsFor the count of goals scored by the team.
 * @param goalsAgainst the count of goals conceeded by the tema.
 * @param points the count of league points the team has earned.
 */
CFootballTeam::CFootballTeam(string name, int gamesPlayed, int goalsFor, int goalsAgainst, int points) : 
	m_Name(name), 
	m_GamesPlayed(gamesPlayed),
	m_GoalsFor(goalsFor),
	m_GoalsAgainst(goalsAgainst),
	m_Points(points),
	m_LeaguePosition(0)
{
}

/**
 * Accessor get name of object.
 */
string CFootballTeam::GetName(void)
{
	return m_Name;
}

/**
 * Accessor get games played of object
 */
int CFootballTeam::GetGamesPlayed(void)
{
	return m_GamesPlayed;
}

/**
 * Accessor get goals for of object.
 */
int CFootballTeam::GetGoalsFor(void)
{
	return m_GoalsFor;
}

/**
 * Accessor get goals against of object.
 */
int CFootballTeam::GetGoalsAgainst(void)
{
	return m_GoalsAgainst;
}

/**
 * Accessor get points of object.
 */
int CFootballTeam::GetPoints(void)
{
	return m_Points;
}

/**
 * Accessor get League position of object.
 */
int CFootballTeam::GetLeaguePosition()
{
	return m_LeaguePosition;
}

/**
 * Accessor set the league position.
 * 
 * @param position the position order of the team in the league.
 */
void CFootballTeam::SetLeaguePosition(int position)
{
	m_LeaguePosition = position;
}

/**
 * Check if the parameter name matches the object name.
 * 
 * @param searchName of the comparison against object name.
 * 
 * @return boolean value of condition.
 */
bool CFootballTeam::HasName(const string searchName)
{
	return m_Name == searchName;
}

/**
 * The difference in goals for and goals against.
 * 
 * @return integer of the objects goal difference.
 */
int CFootballTeam::GetGoalDifference(void)
{
	return m_GoalsFor - m_GoalsAgainst;
}

/**
* Remove team points from the object.
*
* @param num integer of points to be deducted from the teams points.
*
* @return void
*/
void CFootballTeam::DeductPoints(int num)
{
	m_Points = m_Points - num;
}

/**
 * Update a teams statistics on the league table, this will increment the gamesPlayed and points.
 * 
 * @param goalsFor the goals the team has scored.
 * @param goalsAgainst the goals that the team has conceeded.
 * 
 * @return void
 */
void CFootballTeam::UpdateOnResult(int goalsFor, int goalsAgainst)
{
	m_GamesPlayed = m_GamesPlayed + 1;

	m_GoalsFor += goalsFor;

	m_GoalsAgainst += goalsAgainst;

	if (goalsFor == goalsAgainst)
	{
		m_Points += 1;
	}
	else if (goalsFor > goalsAgainst)
	{
		m_Points += 3;
	}
}

/*
 * A Comparison method for comparing a team against another team.
 *
 * i) Greatest number of points
 * ii) Greatest Goal difference if team points are equal
 * iii) Fewest Games played if both team points and Goal difference are equal.
 * 
 * @param team the object that the object should be compared against.
 * 
 * @return boolean of the conditional statement comparison.
 */
bool CFootballTeam::IsLessThan(CFootballTeam& team)
{
	if (GetPoints() == team.GetPoints())
	{
		if (GetGoalDifference() == team.GetGoalDifference())
		{
			return GetGamesPlayed() < team.GetGamesPlayed();
		}

		return GetGoalDifference() < team.GetGoalDifference();
	}

	return GetPoints() < team.GetPoints();
}

