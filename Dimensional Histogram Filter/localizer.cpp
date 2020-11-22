#include "helpers.cpp"
#include <stdlib.h>
#include "debugging_helpers.cpp"

using namespace std;

vector< vector <float> > initialize_beliefs(vector< vector <char> > grid) {
	vector< vector <float> > newGrid;
	vector<float> newRow;
	int i, j, height, width, area;
	float total, prob_per_cell;

	height = grid.size();
	width = grid[0].size();
	area = height * width;

	prob_per_cell = 1.0 / ( (float) area) ;

	// beliefs are 0.0
	for (i=0; i<grid.size(); i++) {
		newRow.clear();
		for (j=0; j<grid[0].size(); j++) {
			newRow.push_back(prob_per_cell);
		}
		newGrid.push_back(newRow);
	}
	return newGrid;
}

vector< vector <float> > sense(char color, 
	vector< vector <char> > grid, 
	vector< vector <float> > beliefs, 
	float p_hit,
	float p_miss) 
{
	vector< vector <float> > newGrid;
	vector<float> row, newRow;

	float prior, p;

	char cell;

	int i, j, height, width;
	height = grid.size();
	width = grid.size();

	for (i=0; i<grid.size(); i++) {
		newRow.clear();
		for (j=0; j<grid[0].size(); j++) {
			prior = beliefs[i][j];
			cell = grid[i][j];
			if (cell == color) {
				p = prior * p_hit;
			}
			else {
				p = prior * p_miss;
			}
			newRow.push_back(p);
		}
		newGrid.push_back(newRow);
	}
	return normalize(newGrid);
}

vector< vector <float> > move(int dy, int dx, 
	vector < vector <float> > beliefs,
	float blurring) 
{
	int height, width;
	height = beliefs.size();
	width = beliefs[0].size();

	float belief;
	vector < vector <float> > newGrid;
	newGrid = zeros(height, width);

	vector <float> row, newRow;

	int i, j, new_i, new_j;
	for (i=0; i<height; i++) {
		for (j=0; j<width; j++) {
			new_i = (i + dy + height) % height;
			new_j = (j + dx + width)  % width;
			belief = beliefs[i][j];

			newGrid[new_i][new_j] = belief;
		}
	}
	return blur(newGrid, blurring);
}

	

// int main() {
// 	vector < vector <float> > grid;
// 	vector < vector <float> > newGrid;


// 	vector < vector <char> >  map;
// 	vector <char> mapRow;
// 	char color;

// 	vector<float> row ;
// 	float p;
// 	int i;
// 	int j;
// 	for (i = 0; i < 4; i++)
// 	{
// 		row.clear();
// 		for (j=0; j< 4; j++)
// 		{
// 			p = (float) j;
// 			row.push_back(p);	
// 			cout << p << ' ';
// 		}
// 		cout << '\n';
// 		grid.push_back(row);
// 	}
// 	cout << "\n###\n";
// 	newGrid = normalize(grid);
// 	cout << "\nafter call to normalize\n";

// 	show_grid(newGrid);
// 	int randInt;

// 	newGrid = blur(grid, 0.5);
// 	cout << "\nafter call to blur\n";
// 	for (i = 0; i < newGrid.size(); i++)
// 	{
// 		row = newGrid[i];
// 		mapRow.clear();
// 		for (j=0; j< row.size(); j++)
// 		{
// 			randInt = rand() % 2;
// 			if (randInt == 0 ) {
// 				color = 'r';
// 			} 
// 			else {
// 				color = 'g';
// 			}
// 			mapRow.push_back(color);
// 		}
// 		map.push_back(mapRow);
// 	}

// 	show_grid(map);

// 	newGrid = initialize_beliefs(map);
// 	cout << "\nafter call to initialize_beliefs\n";
// 	show_grid(newGrid);

// 	newGrid[1][1] = 1.0;
// 	cout << "\n\n\nbefore call to move\n";
// 	show_grid(newGrid);
// 	newGrid = move(0, 1, newGrid, 0.0);
// 	cout << "\nafter call to move\n";
// 	show_grid(newGrid);



// 	return 0;
// }
