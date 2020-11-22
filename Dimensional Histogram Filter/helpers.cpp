#include <vector>
#include <iostream>
#include <string>
#include <cmath> 

#include <fstream> 

using namespace std;
using std::vector;

vector< vector<float> > normalize(vector< vector <float> > grid) {
	cout << "normalize called\n";
	float total = 0.0;
	int i;
	int j;
	vector<float> row;
	vector<float> newRow;
	float oldProb;
	for (i = 0; i < grid.size(); i++)
	{
		row = grid[i];
		// cout << "row size: " << row.size(); 
		for (j=0; j< row.size(); j++)
		{
			oldProb = row[j];
			total += oldProb;
		}
	}

	vector< vector<float> > newGrid;

	for (i = 0; i < grid.size(); i++) {
		vector<float> row = grid[i];
		newRow.clear();
		for (j=0; j< row.size(); j++) {
			float oldProb = row[j];
			float newProb = oldProb / total;
			newRow.push_back(newProb);
		}
		newGrid.push_back(newRow);
	}

	return newGrid;
}

vector < vector <float> > blur(vector < vector < float> > grid, float blurring) {

	vector < vector <float> > window;
	vector < vector <float> > newGrid;
	// vector < vector <float> > newGrid = vector(height, vector(width, 0.0) );
	vector <float> row;
	vector <float> newRow;

	int height;
	int width;
	float center, corner, adjacent;

	

	height = grid.size();
	width = grid[0].size();

	center = 1.0 - blurring;
	corner = blurring / 12.0;
	adjacent = blurring / 6.0;

	int i, j;
	float val;

	for (i=0; i<3; i++) {
		row.clear();
		for (j=0; j<3; j++) {
			switch (i) {
				case 0: 
				switch (j) {
					case 0: 
					val = corner;
					break;

					case 1: 
					val = adjacent;
					break;

					case 2: 
					val = corner;
					break;
				}
				break; 

				case 1:
				switch (j) {
					case 0: 
					val = adjacent;
					break;

					case 1: 
					val = center;
					break;
					
					case 2: 
					val = adjacent;
					break;
				}
				break;

				case 2:
				switch(j) {
					case 0: 
					val = corner;
					break;

					case 1: 
					val = adjacent;
					break;
					
					case 2: 
					val = corner;
					break;
				}
				break;
			}
			row.push_back(val);
		}
		window.push_back(row);
	}


	vector <int> DX;
	vector <int> DY;

	DX.push_back(-1); DX.push_back(0); DX.push_back(1);
	DY.push_back(-1); DY.push_back(0); DY.push_back(1);

	int dx;
	int dy;
	int ii;
	int jj;
	int new_i;
	int new_j;
	float multiplier;
	float newVal;

	// initialize new grid to zeros
	for (i=0; i<height; i++) {
		newRow.clear();
		for (j=0; j<width; j++) {
			newRow.push_back(0.0);
		}
		newGrid.push_back(newRow);
	}


	for (i=0; i< height; i++ ) {
		for (j=0; j<width; j++ ) {
			val = grid[i][j];
			newVal = val;
			for (ii=0; ii<3; ii++) {
				dy = DY[ii];
				for (jj=0; jj<3; jj++) {
					dx = DX[jj];
					new_i = (i + dy + height) % height;
					new_j = (j + dx + width) % width;
					multiplier = window[ii][jj];
					newGrid[new_i][new_j] += newVal * multiplier;
				}
			}
		}
	}

	return normalize(newGrid);
}

bool close_enough(vector < vector <float> > g1, vector < vector <float> > g2) {
	int i, j;
	float v1, v2;
	for (i=0; i<g1.size(); i++) {
		for (j=0; j<g1[0].size(); j++) {
			v1 = g1[i][j];
			v2 = g2[i][j];
			if (abs(v2-v1) > 0.0001 ) {
				return false;
			}
		}
	}
	return true;
}

bool close_enough(float v1, float v2) { 
	if (abs(v2-v1) > 0.0001 ) {
		return false;
	} 
	return true;
}

/**
    Helper function for reading in map data

    @param s - a string representing one line of map data.

    @return - A row of chars, each of which represents the
    color of a cell in a grid world.
*/
vector <char> read_line(string s) {
	vector <char> row;

	size_t pos = 0;
	string token;
	string delimiter = " ";
	char cell;

	while ((pos = s.find(delimiter)) != std::string::npos) {
		token = s.substr(0, pos);
		s.erase(0, pos + delimiter.length());

		cell = token.at(0);
		row.push_back(cell);
	}

	return row;
}

/**
    Helper function for reading in map data

    @param file_name - The filename where the map is stored.

    @return - A grid of chars representing a map.
*/
vector < vector <char> > read_map(string file_name) {
	ifstream infile(file_name);
	vector < vector <char> > map;
	if (infile.is_open()) {

		char color;
		vector <char> row;
		
		string line;

		while (std::getline(infile, line)) {
			row = read_line(line);
			map.push_back(row);
		}
	}
	return map;
}

// int main() {
// 	vector < vector <float> > grid;
// 	vector < vector <float> > newGrid;
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
// 	cout << "after call to normalize\n";
// 	for (i = 0; i < newGrid.size(); i++)
// 	{
// 		row = newGrid[i];
// 		for (j=0; j< row.size(); j++)
// 		{
// 			p = row[j];	
// 			cout << p << ' ';
// 		}
// 		cout << '\n';
// 	}


// 	newGrid = blur(grid, 0.5);
// 	cout << "after call to blur\n";
// 	for (i = 0; i < newGrid.size(); i++)
// 	{
// 		row = newGrid[i];
// 		for (j=0; j< row.size(); j++)
// 		{
// 			p = row[j];	
// 			cout << p << ' ';
// 		}
// 		cout << '\n';
// 	}


// 	return 0;
// }