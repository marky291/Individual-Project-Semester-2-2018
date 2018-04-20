#include "stdafx.h"
#include "CFootballLeague.h"

/**
 * Get the total count of teams in the league.
 * 
 * @return integer the count of teams in the league.
 */
int CFootballLeague::GetTeamSize(void)
{
	return m_LeagueSize;
}

/**
* Get the maximum count of teams the league can hold.
*
* @return integer the max. count of teams the league can hold.
*/
int CFootballLeague::GetMaxLeagueSize(void)
{
	return m_MaxLeagueSize;
}

/**
* Remove all teams from the league table, clear.
*
* @return void
*/
void CFootballLeague::LeagueClear()
{
	for (int i = 0; i < GetMaxLeagueSize(); i++)
	{
		// remove team by using a blank.
		CFootballTeam removeTeam;

		SetTeam(i, removeTeam);
	}

	// reset the size count
	m_LeagueSize = 0;

	// save changes.
	SyncLeagueTable();
}

/**
 * Check if a team exists using teamname.
 * 
 * @param teamname for name of team
 * 
 * @return boolean of the team existance in the league
 */
bool CFootballLeague::TeamExists(const string teamname)
{
	for (int i = 0; i < m_LeagueSize; i++)
	{
		if (m_League[i].GetName() == teamname)
		{
			return true;
		}
	}

	return false;
}

/**
 * Record a match results for a single team.
 * 
 * @param teamname for name of team
 * @param goalsFor the goals team has scored.
 * @param goalsAgainst the goals conceeded by the team
 * 
 * @return void
 */
void CFootballLeague::RecordScore(string teamname, int goalsFor, int goalsAgainst)
{
	GetTeam(teamname).UpdateOnResult(goalsFor, goalsAgainst);

	SyncLeagueTable();
}

/**
 * Deduct points from total team points.
 * 
 * @param teamname for name of team.
 * @param points that should be deducted from team.
 * 
 * @return void
 */
void CFootballLeague::RemovePoints(string teamname, int points)
{
	GetTeam(teamname).DeductPoints(points);

	SyncLeagueTable();
}

/*
 * An accessor that allows the setting of an element in the league array.
 * 
 * @param position of the array as an integer.
 * @param team object that should be stored in the position.
 * 
 * @return void
 */
void CFootballLeague::SetTeam(const int position, CFootballTeam& team)
{
	m_League[position] = team;
}

/*
* An accessor that allows retrieval of an element from the array.
*
* @param position of the array as an integer.
* 
* @return the retrieved team from the league.
*/
CFootballTeam& CFootballLeague::GetTeam(const int position)
{
	try
	{
		return m_League[position];
	}
	catch (...)
	{
		throw std::exception("Unable to retrieve non-existant array position.");
	}
}

/*
 * An accessor that allows retrieval of an element where teamname is equal to element teamname.
 * 
 * @param teamname the name of the team to retrieve.
 * 
 * @return the retrieved team from the league.
 * 
 * @exception will be thrown if team can not be retrieved.
 */
CFootballTeam& CFootballLeague::GetTeam(const string teamname)
{
	for (int i = 0; i < m_LeagueSize; i++)
	{
		if (m_League[i].GetName() == teamname)
		{
			return GetTeam(i);
		}
	}

	throw std::exception("Unable to locate and retrieve team from league.");
}

/**
 * Get the most conceeded goals in the league by a single team.
 * 
 * @return the most conceeded goals in the league by a single team.
 */
int CFootballLeague::MostGoalsConceeded(void)
{
	int lowest_goals_against = m_League[0].GetGoalsAgainst();

	for (int i = 0; i < m_LeagueSize; i++)
	{
		if (lowest_goals_against > m_League[i].GetGoalsAgainst())
		{
			lowest_goals_against = m_League[i].GetGoalsAgainst();
		}
	}

	return lowest_goals_against;
}

/**
 * Return an array from the league of the teams with the least amount of goals conceeded.
 * 
 * @param defenderTeams[] pass-by-reference for array of teams to be listed.
 * @param foundTeams the array size to be captured and sent back.
 * 
 * @return void
 */
void CFootballLeague::GetTeamsWithBestDefence(CFootballTeam defenderTeams[], unsigned int& foundTeams)
{
	int lowest_goals = MostGoalsConceeded();

	for (int i = 0; i < m_LeagueSize; i++)
	{
		if (lowest_goals == m_League[i].GetGoalsAgainst())
		{
			defenderTeams[foundTeams++] = m_League[i];
		}
	}
}

/**
 * Return an array from the league with the teams facing relegation using the relegation size.
 * 
 * @param relegationTeams pass-by-reference for array of teams to be listed.
 * @param relegationSize the array size to be captured and sent back.
 * 
 * @return void
 */
void CFootballLeague::GetTeamsFacingRelegation(CFootballTeam relegationTeams[], const int relegationSize)
{
	const int starting_position = m_LeagueSize - relegationSize;

	for (int i = 0; i < relegationSize; i++)
	{
		relegationTeams[i] = m_League[starting_position + i];
	}
}

/**
 * Expand the league to accomadate a new team. <https://en.wikipedia.org/wiki/Expansion_team>
 * 
 * @param team the object that will be added to the league.
 * 
 * @return boolean of condition of league addition.
 */
bool CFootballLeague::Expand(CFootballTeam team)
{
	if (m_LeagueSize >= m_MaxLeagueSize)
	{
		return false;
	}

	// Assign the team and update the size.
	SetTeam(m_LeagueSize++, team);

	// Assign league position and sorting.
	SyncLeagueTable();

	return true;
}

/**
 * Accessor that allows a team to be removed from the league array.
 * 
 * @param teamname the name of the team to be removed.
 * 
 * @return void
 */
void CFootballLeague::RemoveTeam(string teamname)
{
	int position = 0;

	try
	{
		// Find the teams position in the array that must be removed.
		for (int i = 0; i < m_LeagueSize; i++)
		{
			if (m_League[i].HasName(teamname))
			{
				position = i;

				break;
			}
		}
		// Move array positions above to fill the removed data position.
		for (int i = 0; i < m_LeagueSize; i++)
		{
			m_League[position + i] = m_League[position + i + 1];
		}

		// Tell the league used teams has changed.
		m_LeagueSize--;
	}
	catch (...)
	{
		std::exception("Issue has occured trying to remove team from the league.");
	}

	SyncLeagueTable();
}

/*
 * Update the team positions in the league, based on the conditional requirements of the model.
 * This will assign each team a league position and use bubble sort to sort and order.
 * 
 * @return void
 */
void CFootballLeague::SyncLeagueTable()
{
	// Will false if a sort occurs.
	bool sorted;

	// Only run when sets of two exist.
	do
	{
		sorted = true;

		// We only need to run the sort if more than one team
		// exists.
		for (int i = 0; (i + 1) < GetTeamSize(); i++)
		{
			if (GetTeam(i).IsLessThan(GetTeam(i + 1)))
			{
				CFootballTeam storage = GetTeam(i);

				SetTeam(i, GetTeam(i + 1));

				SetTeam(i + 1, storage);

				sorted = false;
			}
		}
	} while (!sorted);

	for (int i = 0; i < GetTeamSize(); i++)
	{
		// league positions start at 1 not 0.
		GetTeam(i).SetLeaguePosition(i + 1);
	}

	SaveLeagueData("league.dat");
}

/**
* The data inside the league will be saved to league.dat allowing persistant data.
*
* @return boolean condition of the writing to league.dat
*/
bool CFootballLeague::SaveLeagueData(string fileLocation)
{
	ofstream file(fileLocation);

	try
	{
		for (int i = 0; i < m_LeagueSize; i++)
		{
			file << GetTeam(i).GetName() << ", " 
				 << GetTeam(i).GetGamesPlayed() << ", " 
				 << GetTeam(i).GetGoalsFor() << ", " 
				 << GetTeam(i).GetGoalsAgainst() << ", " 
				 << GetTeam(i).GetPoints() 
				 << endl;
		}
	} 
	catch (...)
	{
		return false;
	}

	return true;
}

/**
* The data inside the league.dat file will be loaded into the league class.
*
* @return boolean condition of the loading of league.dat
*/
bool CFootballLeague::LoadLeagueData(string fileLocation)
{
	string row;

	vector<string> columns; // reinvent the wheel == false;

	ifstream file(fileLocation);

	// If file was not read.
	if (file.fail())
	{
		return false;
	}

	while(getline(file, row))
	{
		// Clear vector elements.
		columns.clear();

		// Track the character count we are working with.
		int substr_previous_position = 0;
		int substr_current_position = 0;

		// Store each column data to the vector
		while ((substr_current_position = row.find(',', substr_previous_position)) != string::npos)
		{
			columns.push_back(row.substr(substr_previous_position, substr_current_position - substr_previous_position));

			substr_previous_position = substr_current_position + 2;
		}

		// Store last delimeter to the vector.
		columns.push_back(row.substr(substr_previous_position));

		// Verify only five columns existed for object construction.
		if (columns.size() > 5)
		{
			CDisplay::Failure("Row with too many values exists [max: 5]");
		}

		// Construct the object with the vector data we pulled.
		Expand(CFootballTeam(columns[0], stoi(columns[1]), stoi(columns[2]), stoi(columns[3]), stoi(columns[4])));
	}

	return true;
}
