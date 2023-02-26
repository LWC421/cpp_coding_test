#include <iostream>
#include <vector>

using namespace std;

struct coord {
	int y;
	int x;
	coord() {};
	coord(int y, int x) : y(y), x(x) {};
};

int length;					//맵의 크기
vector<vector<bool>> used;	//사용중 표시 맵
vector<coord> cores;		//코어들 좌표 저장

int currentCount;			//현재 전선수
int currentCore;			//현재 연결된 코어 수
int minCount;				//최소 전선수
int maxCore;				//연결 된 최대 코어 수

//우, 하, 좌, 상
int dy[] = { 0, 1, 0, -1 };
int dx[] = { 1, 0, -1, 0 };

//일직선으로 가기 -> 현재 보고 있는 코어, 방향
bool dfs(coord current, int dir) {
	if (dir == -1) return false;	//가만히 있을 경우
	int y, x;
	y = current.y;
	x = current.x;

	bool isValid = true;

	while (y > 1 && y < length &&
		x > 1 && x < length) {
		//맵 안에 있는 동안
		y += dy[dir];
		x += dx[dir];

		if (used[y][x]) {
			//사용중인게 있으면
			isValid = false;	//실행하지 않는다
			//cout << y << " " << x << "\n";

			break;
		}
	}

	if (!isValid) {
		//실행하지 않는다고 반환
		return false;
	}

	y = current.y;
	x = current.x;

	while (y > 1 && y < length &&
		x > 1 && x < length) {
		//맵 안에 있는 동안
		y += dy[dir];
		x += dx[dir];

		used[y][x] = true;	//사용중으로 표시
		currentCount++;
	}

	currentCore++;
	return true;	//실행하였다고 표시
}

//사용하고 있던 애들 지우기
void rollback(coord current, int dir) {
	if (dir == -1) return;	//가만히 있을 경우
	int y, x;
	y = current.y;
	x = current.x;

	while (y > 1 && y < length &&
		x > 1 && x < length) {
		//맵 안에 있는 동안
		y += dy[dir];
		x += dx[dir];
		used[y][x] = false;	//사용중 아니라고 표기
		currentCount--;
	}

	currentCore--;
}

void go(int index) {
	if (index == cores.size()) {
		//모든 코어를 봤으면
		if (maxCore < currentCore) {
			maxCore = currentCore;
			minCount = currentCount;
		}
		else if (maxCore == currentCore) {
			minCount = min(minCount, currentCount);
		}
		return;
	}

	coord current = cores[index];
	bool executed;	//dfs가 실행이 되었는지
	for (int i = 0; i < 4; i++) {
		executed = dfs(current, i);
		
		if (executed) {	//dfs가 실행이 되었으면 롤백한다
			go(index + 1);	//다음 코어로 가기
			rollback(current, i);
		}
	}
	go(index + 1);
}

int main(void) {
	ios::sync_with_stdio(false);
	cout.tie(nullptr);

	int T;
	cin >> T;

	//테스트 케이스 시작
	for (int test_case = 1; test_case <= T; test_case++) {
		currentCount = 0;
		currentCore = 0;
		maxCore = 0;
		minCount = 12 * 12 + 1;

		cin >> length;	//맵 크기 받기

		used.clear();	//맵 초기화
		cores.clear();	//코어 초기화
		
		//일단 false로  [length+2][length+2]로 초기화
		for (int i = 0; i <= length + 1; i++) {
			used.push_back(vector<bool>(length + 2, false));
		}

		//벽치기
		for (int y = 0; y <= length + 1; y++) {
			used[y][0]		  = true;	//맵 끝은 사용중으로 표시
			used[y][length+1] = true;	//맵 끝은 사용중으로 표시
		}
		for (int x = 0; x <= length + 1; x++) {
			used[0][x]			= true;	//맵 끝은 사용중으로 표시
			used[length + 1][x] = true;	//맵 끝은 사용중으로 표시
		}

		int number;
		for (int y = 1; y <= length; y++) {
			for (int x = 1; x <= length; x++) {
				cin >> number;
				if (number == 1) {
					//코어이면
					if ( !(y == 1 || y == length ||
						x == 1 || x == length) ) {
						//맵 끝에 있지 않을때만
						cores.push_back(coord(y, x));
					}
					used[y][x] = true;	//사용중으로 표시하기
				}
			}
		}

		go(0);

		cout << "#" << test_case << " " << minCount << "\n";
	}

	return 0;
}