#include "asstes.h"
class Board
{
private:
	// Struktura reprezentuj¹ca wspó³rzêdne pola na planszy
	struct Point {
		int x, y;

		Point(int x, int y) : x(x), y(y) {}
	};
public:
	bool isValid(int x, int y, int m, int n);
	vector<string> findPath(vector<vector<char>>& board);
};

