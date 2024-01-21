#include "asstes.h"

class File
{
public:
	vector<vector<char>> loadBoardFromFile(const string& filename, int& m, int& n);
	int saveSolution(const string& outname, vector<string> path);
	void readAndUpdatePathFromFile(const string& filePath, vector<vector<char>> board);
	int saveAllSolution(const string& outname, vector<vector<string>> paths);
};