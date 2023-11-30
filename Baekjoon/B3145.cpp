#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>

using namespace std;

#define V vector
#define UM unordered_map
#define US unordered_set

struct Coord { int y, x; };

struct Name {
	int y, x;
	string name;

	bool operator==(const Name &o) const{
		return this->y == o.y && this->x == o.x;
	}
};

struct NameHash {
	size_t operator() (const Name &n) const{
		return n.y * 51 + n.x;
	}
};

const int dy[] = { -1, -1, -1, 0, 0, 1, 1, 1 };
const int dx[] = { -1, 0, 1, -1, 1, -1, 0, 1 };

V<V<int>> edgess;
V<int> from;
V<int> to;
V<bool> visited;

bool isUpper(const char a) {
	return a >= 'A' && a <= 'Z';
}

bool dfs(int f) {
	visited[f] = true;
	for (int t : edgess[f]) {
		if (to[t] == -1 || (!visited[to[t]]) && dfs(to[t])) {
			from[f] = t;
			to[t] = f;
			return true;
		}
	}
	return false;
}


int main(void) {
	//freopen("input.txt", "r", stdin);

	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int yLength, xLength;
	cin >> yLength >> xLength;

	V<V<char>> inputs(yLength + 2, V<char>(xLength + 2, '.'));
	for (int y = 1; y <= yLength; y++) {
		for (int x = 1; x <= xLength; x++) {
			cin >> inputs[y][x];
		}
	}
	//input finished

	int numVillage = 0;
	V<US<Name, NameHash>> set;
	V<Coord> villages;
	for (int y = 1; y <= yLength; y++) {
		for (int x = 1; x <= xLength; x++) {
			if (inputs[y][x] == 'x') {
				//if target is village
				numVillage++;
				villages.push_back({ y, x });
				US<Name, NameHash> localSet;
				for (int d = 0; d < 8; d++) {
					//find near names
					int nY, nX;
					nY = y + dy[d];
					nX = x + dx[d];
					if (isUpper(inputs[nY][nX])) {
						// if upper case
						while (isUpper(inputs[nY][nX])) nX--;

						nX++;
						int firstX = nX;
						string str = "";
						while (isUpper(inputs[nY][nX])) {
							str += inputs[nY][nX++];
						}
						localSet.insert({ nY, firstX, str });
					}
				}
				set.push_back(localSet);
			}
		}
	}

	// process name to index
	int count = 0;
	UM<Name, int, NameHash> nameToIndex;
	V<string> indexToName;

	edgess.resize(numVillage);
	from.resize(numVillage, -1);
	to.resize(numVillage, -1);
	visited.resize(numVillage, false);

	for (auto targetSet = set.begin(); targetSet != set.end(); targetSet++) {
		for (auto t = targetSet->begin(); t != targetSet->end(); t++) {
			if (nameToIndex.find(*t) == nameToIndex.end()) {
				nameToIndex.insert({ *t, count++ });
				indexToName.push_back(t->name);
			}
		}
	}

	int index = 0;
	for (auto targetSet = set.begin(); targetSet != set.end(); targetSet++) {
		for (auto t = targetSet->begin(); t != targetSet->end(); t++) {
			edgess[index].push_back(nameToIndex.find(*t)->second);
		}
		index++;
	}

	for (int i = 0; i < numVillage; i++){
		if (from[i] == -1) {
			//if target is not matched
			fill(visited.begin(), visited.end(), false);
			dfs(i);
		}
	}

	for (int i = 0; i < numVillage; i++) {
		Coord v = villages[i];
		string name = indexToName[from[i]];
		printf("%d %d %s\n", v.y, v.x, name.c_str());
	}

	return 0;
}