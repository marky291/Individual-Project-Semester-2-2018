#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Project/CFootballTeam.cpp"
#include "../Project/CFootballLeague.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{		
	TEST_CLASS(UnitTest1)
	{
		public:
		
			TEST_METHOD(LeagueWillExpandWithNewTeams)
			{
				CFootballLeague league;

				CFootballTeam team("Poison Spanners");

				league.Expand(team);

				Assert::AreEqual(1, league.GetTeamSize());
			}

			TEST_METHOD(LeagueWillRemovePositionedTeams)
			{
				CFootballLeague league;

				CFootballTeam team_one("Awesome Widows");
				CFootballTeam team_two("Blue Tigers");
				CFootballTeam team_three("Dream Monkeys");

				league.Expand(team_one); // position 1 in human form.
				league.Expand(team_two); // position 2 in human form.
				league.Expand(team_three); // position 3 in human form.

				league.RemovePositionedTeam(2);

				Assert::AreEqual(2, league.GetTeamSize());
			}
			

			// TEST_METHOD(LeagueExpansionHasRestrictions)
			// {
			// 	CFootballLeague league;
			// 
			// 	league.SetMaximumTeamSize(1);
			// 
			// 	CFootballTeam team_one("Red Hurricanes");
			// 	CFootballTeam team_two("New York Stingers");
			// 
			// 	bool team_one_creation = league.Expand(team_one);
			// 	bool team_two_creation = league.Expand(team_two);
			// 	
			// 	// Maximum is one, this should pass.
			// 	Assert::IsTrue(team_one_creation);
			// 
			// 	// Maximum is one, this should fail.
			// 	Assert::IsFalse(team_two_creation);
			// }

			// TEST_METHOD(LeaueShouldAssignPosition)
			// {
			// 	CFootballLeague league;
			// 
			// 	CFootballTeam team_one("Scorpions", 39, 71, 34, 85); // League position #1
			// 	CFootballTeam team_two("Crunchers", 39, 62, 33, 80); // League position #2
			// 	CFootballTeam team_three("Blind", 40, 68, 41, 72); // League position #3
			// 
			// 	league.Expand(team_one);
			// 	league.Expand(team_two);
			// 	league.Expand(team_three);
			// 
			// 	Assert::AreEqual(1, team_one.GetLeaguePosition());
			// 	Assert::AreEqual(2, team_two.GetLeaguePosition());
			// 	Assert::AreEqual(3, team_three.GetLeaguePosition());
			// }

			// TEST_METHOD(LeagueShouldSortPositions)
			// {
			// 	CFootballLeague league;
			// 
			// 	CFootballTeam team_one("Scorpions", 39, 71, 34, 85); // League position #1
			// 	CFootballTeam team_two("Crunchers", 39, 62, 33, 80); // League position #2
			// 
			// 	league.Expand(team_two);
			// 	league.Expand(team_one);
			// 
			// 	Assert::AreEqual(1, team_one.GetLeaguePosition());
			// 	Assert::AreEqual(2, team_two.GetLeaguePosition());
			// }

			/*
			* i) Greatest number of points			* ii) Greatest Goal difference if team points are equal
			* iii) Fewest Games played if both team points and Goal difference are equal
			*/
			TEST_METHOD(TeamComparisonBasedOnConditions)
			{
				// Set up of fake statistics for testing.
				CFootballTeam team_one("Awesome Scorpions", 39, 71, 34, 85); // League position #1
				CFootballTeam team_two("Eccentric Crunchers", 39, 62, 33, 80); // League position #2
				CFootballTeam team_three("Color Blind", 40, 68, 41, 72); // League position #3

				// Copies of team one for testing condition, two, three & non-conditional.
				CFootballTeam team_one_less_goal_difference("American Monkeys", 38, 34, 34, 85); // Copy of League position #1
				CFootballTeam team_one_less_games_test("American Monkeys", 38, 71, 34, 85); // Copy of League position #1
				CFootballTeam team_one_copy("New York Mafia", 38, 71, 34, 85); // Copy of League position #1

				// Team with less points is considered to be less than the compared team. (condition one).
				Assert::IsTrue(team_two.IsLessThan(team_one));
				Assert::IsTrue(team_three.IsLessThan(team_two));

				// Team with the least the worst goal difference is considered to be less than compared team. (condition two).
				Assert::IsTrue(team_one_less_goal_difference.IsLessThan(team_one));

				// Team with fewest games is considered to be less than the compared team. (condition three).
				Assert::IsTrue(team_one_less_games_test.IsLessThan(team_one));

				// If both have exact same stats in three conditions, then will return false.
				Assert::IsFalse(team_one.IsLessThan(team_one_copy));
			}

			TEST_METHOD(TeamPointsShouldBeDeductable)
			{
				CFootballTeam team("New York Sonics", 0, 0, 0, 15);

				// test points deduct normally.
				team.DeductPoints(10);

				Assert::AreEqual(5, team.GetPoints());

				// test negative points are equal to 0.
				team.DeductPoints(7);

				Assert::AreEqual(-2, team.GetPoints());
			}

			TEST_METHOD(TeamShouldUpdateStatsOnResults)
			{
				CFootballTeam team("Awesome Flyers", 0, 0, 0, 0);

				team.UpdateOnResult(3, 1);

				Assert::AreEqual(1, team.GetGamesPlayed());
				Assert::AreEqual(2, team.GetGoalDifference());
				Assert::AreEqual(3, team.GetPoints());
				Assert::AreEqual(3, team.GetGoalsFor());
				Assert::AreEqual(1, team.GetGoalsAgainst());
			}

			TEST_METHOD(LeagueCanSearchForTeamExist)
			{
				CFootballLeague league;

				CFootballTeam team_one("Rocky Lightning");
				CFootballTeam team_two("Protagonists");
				CFootballTeam team_three("American Heroes");

				league.Expand(team_one);
				league.Expand(team_two);
				league.Expand(team_three);

				Assert::IsTrue(league.TeamExists("Rocky Lightning"));
				Assert::IsTrue(league.TeamExists("American Heroes"));
			}

			TEST_METHOD(LeagueShouldReturnTeamsFacingRelegation)
			{
				CFootballLeague league;
				CFootballTeam relegation_teams[3];

				CFootballTeam team_one("Rocky Lightning", 39, 29, 57, 36);
				CFootballTeam team_two("Protagonists", 39, 39, 58, 34);
				CFootballTeam team_three("American Heroes", 40, 43, 72, 31);
				CFootballTeam team_four("Red Kings", 40, 29, 71, 31);

				league.Expand(team_one);
				league.Expand(team_two);
				league.Expand(team_three);
				league.Expand(team_four);

				league.GetTeamsFacingRelegation(relegation_teams, 3);
			
				Assert::AreEqual(34, relegation_teams[0].GetPoints()); // team two.
				Assert::AreEqual(31, relegation_teams[1].GetPoints()); // team three.
				Assert::AreEqual(31, relegation_teams[2].GetPoints()); // team four.
			}

			TEST_METHOD(LeagueShouldReturnLowestGoalsConceededByTeam)
			{
				CFootballLeague league;

				CFootballTeam team_one("Awesome Gangstaz", 39, 29, 39, 36);
				CFootballTeam team_two("Eccentric Blockers", 39, 39, 52, 34);

				league.Expand(team_one);
				league.Expand(team_two);

				Assert::AreEqual(39, league.LowestGoalsConceeded());
			}

			TEST_METHOD(LeagueShouldReturnTeamsWithMostConceededGoals)
			{
				CFootballLeague league;

				unsigned int foundteams = 0;
				CFootballTeam teams_lowest_conceeded_goals[25];

				CFootballTeam team_one("American Bombers", 39, 29, 43, 36);
				CFootballTeam team_two("New York Robots", 39, 43, 19, 57);

				league.Expand(team_one);
				league.Expand(team_two);

				league.GetTeamsWithBestDefence(teams_lowest_conceeded_goals, foundteams);

				Assert::AreEqual(19, teams_lowest_conceeded_goals[0].GetGoalsAgainst());
			}

			TEST_METHOD(LeagueCanRecordTeamEvent)
			{
				CFootballLeague league;

				CFootballTeam team_one("American Bombers");
				CFootballTeam team_two("New York Robots");

				league.Expand(team_one); // array pos 0
				league.Expand(team_two); // array pos 1

				league.RecordScore("American Bombers", 3, 1);
				league.RecordScore("New York Robots", 1, 3);

				Assert::AreEqual(3, league.GetTeam(0).GetGoalsFor());
				Assert::AreEqual(1, league.GetTeam(0).GetGoalsAgainst());
			}

	};
}