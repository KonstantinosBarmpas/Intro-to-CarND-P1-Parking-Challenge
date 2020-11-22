void show_grid(vector < vector <float> > grid) {
	int i, j;
	float p;
	vector<float> row;
	for (i = 0; i < grid.size(); i++)
	{
		row = grid[i];
		for (j=0; j< row.size(); j++)
		{
			p = row[j];	
			cout << p << ' ';
		}
		cout << endl;
	}
}

void show_grid(vector < vector <char> > map) {
	int i, j;
	char p;
	vector<char> row;
	for (i = 0; i < map.size(); i++)
	{
		row = map[i];
		for (j=0; j< row.size(); j++)
		{
			p = row[j];	
			cout << p << ' ';
		}
		cout << endl;
	}
}

vector < vector <float> > zeros(int height, int width) {
	int i, j;
	vector < vector <float> > newGrid;
	vector <float> newRow;

	for (i=0; i<height; i++) {
		newRow.clear();
		for (j=0; j<width; j++) {
			newRow.push_back(0.0);
		}
		newGrid.push_back(newRow);
	}
	return newGrid;
}