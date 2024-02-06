#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
using namespace std;


//Use Simple Rating System (SRS) = (point differential - Opponents point differential)
//Thsi determines what team would win the nba championship based on trhe SRS rating

const float oppRatingCeltics[] = { 1.8, 1.9, -9.0, 1.8, -0.7, 5.6, 10.3, -0.7, -1.1, 1.8, 10.3, -1.1, -6.3, -11.1, 5.7, 2.5, -0.6, -2.5, 1.8, 1.8, 0.1, 0.1, 2.5, 2.5, 0.4, -0.1, 4.3, -0.8, -10.7, -1.1, -11.7 };
const float oppRatingLakers[] = { 1.8, 1.9, -9.0, 1.8, -0.7, 5.6, 10.3, -0.7, -1.1, 1.8, 10.3, -1.1, -6.3, -11.1, 5.7, 2.5, -0.6, -2.5, 1.8, 1.8, 0.1, 0.1, 2.5, 2.5, 0.4, -0.1, 4.3, -0.8, -10.7, -1.1, -11.7 };
const float oppRatingSixers[] = { 1.8, 1.9, -9.0, 1.8, -0.7, 5.6, 10.3, -0.7, -1.1, 1.8, 10.3, -1.1, -6.3, -11.1, 5.7, 2.5, -0.6, -2.5, 1.8, 1.8, 0.1, 0.1, 2.5, 2.5, 0.4, -0.1, 4.3, -0.8, -10.7, -1.1, -11.7 };
const float oppRatingWarriors[] = { 1.8, 1.9, -9.0, 1.8, -0.7, 5.6, 10.3, -0.7, -1.1, 1.8, 10.3, -1.1, -6.3, -11.1, 5.7, 2.5, -0.6, -2.5, 1.8, 1.8, 0.1, 0.1, 2.5, 2.5, 0.4, -0.1, 4.3, -0.8, -10.7, -1.1, -11.7 };


class NBA_team {
private:
	float pointDiff;
	float oppPointDiff;
	float srsRating;
	string team_Name;

public:
	//default constructor
	NBA_team() : pointDiff(0), oppPointDiff(0), team_Name("") {}

	NBA_team(string name, float pointDifferential, float oppPointDifferntial)
	{
		team_Name = name;
		pointDiff = pointDifferential;
		oppPointDiff = oppPointDifferntial;

	}
	//setters
	void setteamName(string name)
	{
		team_Name = name;
	}
	void setSRSRating(float SRS)
	{
		srsRating = SRS;
	}
	void setpointDiff(float pointDifferential)
	{
		pointDiff = pointDifferential;
	}
	void setoppPointDiff(float oppPointDifferntial)
	{
		oppPointDiff = oppPointDifferntial;
	}

	//getters
	string getTeam_Name() const
	{
		return team_Name;
	}
	float getSRSRating() const
	{
		return srsRating;
	}
	float getpointDiff() const
	{
		return pointDiff;
	}
	float getoppPointDiff() const
	{
		return oppPointDiff;
	}
};

class Game {
public:
	NBA_team team1;
	NBA_team team2;

	Game(NBA_team t1, NBA_team t2) : team1(t1), team2(t2) {}

	NBA_team simulateGame() {
		// Simulate the game logic here
		// You can use various factors like team strength, player performance, etc.
		return (team1.getSRSRating() > team2.getSRSRating()) ? team1 : team2;
	}
};


float calculatetotalOppPoints(const float param[], int size);
float calculateSRS(float pointDiff, float oppPointDiff);

// Comparator function for sorting teams based on SRS rating
bool compareTeamsBySRS(const NBA_team& a, const NBA_team& b) {
	return a.getSRSRating() > b.getSRSRating();
}

// Function to simulate a one-game elimination tournament
NBA_team simulateOneGameElimination(vector<NBA_team>& teams) {
	while (teams.size() > 1) {
		vector<NBA_team> winners;
		for (size_t i = 0; i < teams.size(); i += 2) {
			NBA_team team1 = teams[i];
			NBA_team team2 = teams[i + 1];

			// Simulate the game
			Game game(team1, team2);
			NBA_team winner = game.simulateGame();
			winners.push_back(winner);
		}
		teams = winners;
	}

	return teams.front();
}

int main()
{
	
	float srsRating;
	float totalOppPointsCeltics = calculatetotalOppPoints(oppRatingCeltics, sizeof(oppRatingCeltics) / sizeof(float));
	float totalOppPointsLakers = calculatetotalOppPoints(oppRatingLakers, sizeof(oppRatingLakers) / sizeof(float));
	float totalOppPointsSixers = calculatetotalOppPoints(oppRatingSixers, sizeof(oppRatingSixers) / sizeof(float));
	float totalOppPointsWarriros = calculatetotalOppPoints(oppRatingWarriors, sizeof(oppRatingWarriors) / sizeof(float));

	const string teamNames[] = { "Boston Celtics", "LA Lakers", "Phil Sixers", "GS Warriors" };
	const float teamNetRating[] = { 10.4, -1.5, 9.0, 0.5 };
	const float totalOppPoints[] = { totalOppPointsCeltics, totalOppPointsLakers, totalOppPointsSixers, totalOppPointsWarriros };
	NBA_team teams[4];

	for (int i = 0; i < 4; ++i) {		//sets each team with their respective team name, net rating, and opponent net rating
		teams[i] = NBA_team(teamNames[i], teamNetRating[i], totalOppPoints[i]);
	}
	
	for (int i = 0; i < 4; i++) {		//calculates each teams SRS rating 
		srsRating = calculateSRS(teams[i].getpointDiff(), teams[i].getoppPointDiff());
		// Attach the calculated SRS rating back to the respective team
		teams[i].setSRSRating(srsRating);
	}
	// Sort teams based on SRS rating
	sort(teams, teams + 4, compareTeamsBySRS);

	// Print sorted teams
	cout << "\nTeams sorted by SRS rating:\n";
	for (const NBA_team& team : teams) {
		cout << "Team: " << team.getTeam_Name() << ", SRS Rating: " << team.getSRSRating() << "\n";
	}

	// Simulate one-game elimination tournament based on SRS
	vector<NBA_team> teamsVector(teams, teams + 4);
	NBA_team winner = simulateOneGameElimination(teamsVector);

	// Print the winner
	cout << "\nOne-Game Elimination Winner:\n";
	cout << "Team: " << winner.getTeam_Name() << ", SRS Rating: " << winner.getSRSRating() << "\n";

	return 0;
	
}

float calculatetotalOppPoints(const float param[], int size)
{
	float totalOppPoints = 0;
	for (int i = 0; i < size; i++)
	{
		totalOppPoints = param[i] + totalOppPoints;
	}
	float oppPointDiff = totalOppPoints / size;
	return oppPointDiff;
}
float calculateSRS(float pointDiff, float oppPointDiff)
{
	float teamSRS = 0;
	teamSRS = pointDiff + oppPointDiff;
	return teamSRS;
}

