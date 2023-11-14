#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int yLength, xLength;
vector<vector<int>> map;
vector<vector<int>>visited;

const int dy[] = { 1, 0, -1, 0 };
const int dx[] = { 0, -1, 0, 1 };

const int EMPTY = 0;
const int WALL = 1;

struct Data{
	int y, x, count;
};
queue<Data> q;


int main(void) {
	//freopen("input.txt", "r", stdin);

	cin >> yLength >> xLength;
	
	for (int y = 0; y < yLength; y++) {
		map.push_back(vector<int>(xLength, 0));
		visited.push_back(vector<int>(xLength, 100));
		for(int x = 0; x < xLength; x++){
			char value;
			cin >> value;
			map[y][x] = value - '0';
		}
	}


	q.push({ 0, 0, 0 });

	Data curr;
	int nY, nX, nCount;

	int turn = 0;
	while ( !q.empty() ) {
		turn++;
		int size = q.size();
		for (int s = 0; s < size; s++) {
			curr = q.front();
			if (curr.y == yLength - 1 && curr.x == xLength - 1) {
				std::cout << turn;
				return 0;
			}
			q.pop();
		
			for (int d = 0; d < 4; d++) {
				nY = curr.y + dy[d];
				nX = curr.x + dx[d];
				if (nY >= yLength || nY < 0) continue;
				if (nX >= xLength || nX < 0) continue;

				if (curr.count >= visited[nY][nX]) continue;
			
				nCount = curr.count + map[nY][nX];
				if (nCount > 1) continue;
				if (visited[nY][nX] <= nCount) continue;

				visited[nY][nX] = nCount;
				q.push({ nY, nX, nCount });
			}
		}
	}

	std::cout << -1;
	return 0;
}