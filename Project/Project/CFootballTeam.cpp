#include "stdafx.h"
#include "CFootballTeam.h"
#include "CFootballTable.h"

CFootballTeam::CFootballTeam() :
	m_Name(""),
	m_GamesPlayed(0),
	m_GoalsFor(0),
	m_GoalsAgainst(0),
	m_Points(0)
{
}

CFootballTeam::CFootballTeam(string name) : 
	m_Name(name),
	m_GamesPlayed(0),
	m_GoalsFor(0),
	m_GoalsAgainst(0),
	m_Points(0)
{
}

CFootballTeam::CFootballTeam(string name, int gamesPlayed, int goalsFor, int goalsAgainst, int points) : 
	m_Name(name), 
	m_GamesPlayed(gamesPlayed),
	m_GoalsFor(goalsFor),
	m_GoalsAgainst(goalsAgainst),
	m_Points(points)
{
}

string CFootballTeam::GetName(void)
{
	return m_Name;
}

int CFootballTeam::GetGamesPlayed(void)
{
	return m_GamesPlayed;
}

int CFootballTeam::GetGoalsFor(void)
{
	return m_GoalsFor;
}

int CFootballTeam::GetGoalsAgainst(void)
{
	return m_GoalsAgainst;
}

int CFootballTeam::GetPoints(void)
{
	return m_Points;
}

bool CFootballTeam::HasName(const string searchName)
{
	return m_Name == searchName;
}

/*
 * The difference between the number of goals scored for and against a team 
 * in a series of matches, sometimes used in deciding the team's position 
 * in a table
 */
int CFootballTeam::GetGoalDifference()
{
	return m_GoalsFor - m_GoalsAgainst;
}

// A method to update a team’s data based on a match result.
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

// A method to deduct points from a team for disciplinary reasons.
void CFootballTeam::DeductPoints(int num)
{
	m_Points = m_Points - num;
}

/*
 * A method to compare two teams as their positions may need to be swapped when sorting
 * the league table based on the following; *
 * i) Greatest number of points * ii) Greatest Goal difference if team points are equal
 * iii) Fewest Games played if both team points and Goal difference are equal.
 */
bool CFootballTeam::IsLessThan(CFootballTeam& team)
{
	return GetPoints() < team.GetPoints() || GetGoalDifference() < team.GetGoalDifference() || GetGamesPlayed() < team.GetGamesPlayed();
}

