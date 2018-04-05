#include "stdafx.h"
#include "CFootballLeague.h"

/*
 * Get the count of all the teams stored as of current in the league.
 */
int CFootballLeague::GetTeamSize()
{
	return m_TeamSize;
}

bool CFootballLeague::TeamExists(string name)
{
	for (int i = 0; i < m_TeamSize; i++)
	{
		if (m_Team[i].GetName() == name)
		{
			return true;
		}
	}

	return false;
}

bool CFootballLeague::RecordScore(string teamname, int goalsFor, int goalsAgainst)
{
	if (TeamExists(teamname))
	{
		GetTeam(teamname).UpdateOnResult(goalsFor, goalsAgainst);

		// Assign new league positions and sorting.
		UpdateTeamPositions();

		return true;
	}

	return false;
}

bool CFootballLeague::RemovePoints(string teamname, int points)
{
	if (TeamExists(teamname))
	{
		GetTeam(teamname).DeductPoints(points);

		return true;
;	}

	return false;
}

/*
 * Return a team from teh league team array. (override for integer values)
 */
CFootballTeam& CFootballLeague::GetTeam(int array_position)
{
	return m_Team[array_position];
}

void CFootballLeague::SetTeam(int position, CFootballTeam& team)
{
	m_Team[position] = team;
}

/*
 * Return a team from the league team array. (override for stirng values)
 */
CFootballTeam& CFootballLeague::GetTeam(string teamname)
{
	for (int i = 0; i < m_TeamSize; i++)
	{
		if (m_Team[i].GetName() == teamname)
		{
			return GetTeam(i);
		}
	}

	throw std::exception("Trying to retrieve a team that does not exist!");
}


int CFootballLeague::LowestGoalsConceeded(void)
{
	unsigned int lowest_goals_against = m_Team[0].GetGoalsAgainst();

	for (int i = 0; i < m_TeamSize; i++)
	{
		if (lowest_goals_against > m_Team[i].GetGoalsAgainst())
		{
			lowest_goals_against = m_Team[i].GetGoalsAgainst();
		}
	}

	return lowest_goals_against;
}

void CFootballLeague::GetTeamsWithBestDefence(CFootballTeam defenderTeams[], unsigned int& foundTeams)
{
	int lowest_goals = LowestGoalsConceeded();

	for (int i = 0; i < m_TeamSize; i++)
	{
		if (lowest_goals == m_Team[i].GetGoalsAgainst())
		{
			defenderTeams[foundTeams++] = m_Team[i];
		}
	}
}

/*
 * Get the leagues that face relegations.
 * Store into the array that is passed by reference.
 */
void CFootballLeague::GetTeamsFacingRelegation(CFootballTeam relegationTeams[], const int relegationSize)
{
	const int starting_position = m_TeamSize - relegationSize;

	for (int i = 0; i < relegationSize; i++)
	{
		relegationTeams[i] = m_Team[starting_position + i];
	}
}

/*
 * Add a new team to the league.
 * New teams joining a league <https://en.wikipedia.org/wiki/Expansion_team>
 */
bool CFootballLeague::Expand(CFootballTeam team)
{
	// Assign the team and update the size.
	SetTeam(m_TeamSize++, team);

	// Assign league position and sorting.
	UpdateTeamPositions();

	return true;
}

void CFootballLeague::RemovePositionedTeam(const unsigned int position)
{
	// get the starting position on the array.
	const int array_position = m_TeamSize - position;

	// Move array positions above to fill the removed data position.
	for(int i = 0; i < m_TeamSize; i++)
	{
		m_Team[array_position + i] = m_Team[array_position + i + 1];
	}

	// Tell the league used teams has changed.
	m_TeamSize--;
}

void CFootballLeague::UpdateTeamPositions()
{
	// Will false if a sort occurs.
	bool sorted = true;
	bool teams_adjusted = false;

	// Only run when sets of two exist.
	do
	{
		sorted = true;

		for (int i = 0; (i + 1) < GetTeamSize(); i++)
		{
			if (GetTeam(i).IsLessThan(GetTeam(i + 1)))
			{
				CFootballTeam storage = GetTeam(i);

				SetTeam(i, GetTeam(i + 1));

				SetTeam(i + 1, storage);

				// assign new positions.
				teams_adjusted = true;

				// we need to run for loop again.
				sorted = false;
			}
		}
	} while (!sorted);

	// if teams were adjusted reassign positions.
	if (teams_adjusted)
	{
		for (int i = 0; i < GetTeamSize(); i++)
		{
			// league positions start at 1 not 0.
			GetTeam(i).SetLeaguePosition(i + 1);
		}
	}
}