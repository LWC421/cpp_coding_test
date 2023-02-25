#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

typedef long long ll;

#define MAX_SIZE 100001	//노드의 최대 개수

vector<int> childs[MAX_SIZE];	//자식 정보 저장
int parents[MAX_SIZE][20];		//조상 정보 저장
int depths[MAX_SIZE];			//자신의 depth정보 저장
bool visited[MAX_SIZE];			//방문 체크용

void init() {
	for (int i = 0; i < MAX_SIZE; i++) {
		childs[i].clear();
	}
	memset(parents, 0, sizeof(parents));
	memset(depths, 0, sizeof(depths));
	memset(visited, false, sizeof(visited));
}

int LCA(int n1, int n2) {
	if (depths[n1] > depths[n2]) {
		swap(n1, n2); //n1의 depth가 더 높으면 -> n2와 n1을 바꾼다 -> n2의 depth가 더 깊다
	}
	if (parents[n2][0] == n1) {
		return 1;	//이미 부모 노드이면
	}

	int count = 0;
	for (int i = 19; i >= 0; i--) {
		if (depths[n2] - depths[n1] >= (1 << i)) {
			n2 = parents[n2][i];
			count += (1 << i);
		}
	}
	if (parents[n1][0] != parents[n2][0]) {
		for (int i = 19; i >= 0; i--) {
			if (parents[n1][i] != parents[n2][i]) {
				count += 2 * (1 << i);	//조상노드 *2만큼 해주기
				n1 = parents[n1][i];
				n2 = parents[n2][i];
			}
		}
	}

	return count + 2;
}

ll bfs() {
	queue<int> q;
	q.push(1);			//루트부터 가기
	visited[1] = true;	//루트는 방문했다 표시

	int current;		//현재 보고있는 노드
	int next;			//다음 넣을 노드
	int prev = 1;		//이전 노드

	ll result = 0;		//몇개나 봤는지

	while (!q.empty()) {
		current = q.front();
		q.pop();

		for(int i = 0; i < childs[current].size(); i++){
			next = childs[current][i];
			if (visited[next]) {
				continue;	//이미 방문했으면
			}

			visited[next] = true;	//방문할 예정으로 
			q.push(next);
			int tmp = LCA(prev, next);

			result += tmp;
			prev = next;
		}
	}
	return result;
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int T;
	cin >> T;

	int number;
	for (int test_case = 1; test_case <= T; test_case++) {
		init();	//기존에 썻던거 초기화

		int numVertex;
		cin >> numVertex;

		for (int i = 2; i <= numVertex; i++) {
			//0번 인덱스 사용X, 1번은 루트노드
			cin >> number;
			childs[number].push_back(i);	//자식노드 넣기
			parents[i][0] = number;
			depths[i] = depths[number] + 1;	//부모 노드의 depth +1이라는 뜻이다
		}

		for (int h = 1; h < 20; h++) {
			//2^depth만큼 돌면서
			for (int x = 1; x <= numVertex; x++) {
				parents[x][h] = parents[parents[x][h - 1]][h - 1];	//나의 2^h조상은 -> 나의 2^(h-1)조상의 2^(h-1)조상이다
			}
		}

		cout << "#" << test_case << " " << bfs() << "\n";
	}

	return 0;
}