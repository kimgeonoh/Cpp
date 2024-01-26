#include <iostream>
#include <queue>

using namespace std;

// 1 ~ p 명 산타
// 1,1 ~ n,n 격자
// M번 게임, 루돌프-> 1~p 산타
// 거리 (r1-r2)^2+(c1-c2)^2

// 1.루돌프는 산타로 1칸돌진 (탈락x인 산타)
// 우선순위: 거리 짧 > r 큰 > c 큰 순으로 우선순위

// 2. 1~p 산타 (기절x, 탈락x) 루돌프에게 가까워지는 방향으로 1칸돌진
// 단, 다른 산타가 있는 칸, 격자밖x.
// 단, 움직일 수 있는 칸이 있더라도 가까워질 수 없다면 움직이지 않는다

// 루->산) 산타+c점 루돌프 방향으로 산타가 c칸 밀린다
// 산->루) 산타+d점 산타 반대방향으로 산타가 d칸 밀린다
// 단, 밀릴때 충돌x
// 밀렸을때 격자밖이라면 탈락, 밀려난 칸에 다른 산타가 있을 경우 상호작용
// 상호작용 시 다른 산타는 1칸 같은 방향으로 밀려나게 된다. 이를 반복한다
// 산+루 => 산타 기절, 기절 효과는 현재 k 시 k+1 기절 k+2 정상으로 변경
// 기절 시 산타는 움직일 수 없다, 루 -> 기절한 산타 불가능

// M번 턴 루 -> 산 move
// 만약 P명 모두 탈락 시 게임 종료
// 매 턴 이후 탈락하지 않은 산타에게 1점 추가
// 끝낫을 경우 산타가 얻은 최종 점수는?

int N, M, P, C, D;
int ru_x, ru_y; // 루돌프의 위치

int ru_dx[8] = {0,-1,0,1,1,-1,-1,1};
int ru_dy[8] = {1,0,-1,0,1,-1,1,-1};
int san_dx[4] = {-1,0,1,0}; // 가까워지는 방향이 여러개일때 상우하좌 우선순위
int san_dy[4] = {0,1,0,-1};

struct Turn_ru{
	int dist;
	int x;
	int y;
	int p;
	bool operator<(const Turn_ru& other) const {
		if (dist != other.dist) return dist > other.dist;
		if (x != other.x) return x < other.x;
		if (y != other.y) return y < other.y;
		return 0;
	}
};

int calculation(int r1,int c1, int r2, int c2) {
	return (r1 - r2)*(r1 - r2) + (c1 - c2)*(c1 - c2);
}

struct Santa{
	int x;
	int y;
	int stun; // 0 x k o
	int die; // 0 x 1 o
	int score;
}santa[31]; // idx: 1 ~ p 번

priority_queue<Turn_ru> turn_ru;

void mutual_interaction(int target_p, int dir, int dist) { 
	// 파라미터 위치를 변경해서 서로의 위치를 바꿀 수 있도록하여
	// 루->산, 산->루 던 상관없도록 한다
	// 밀리는 방향을 파라미터로 처리한다
	// 두 경우 모두 산타가 기절처리

	// parameter(움직이는 산타, 밀리는 방향 정반, 밀리는 정도)
	santa[target_p].x +=  

}

void simulation(int k) {
	// 1. 루돌프 -> 산타에게 1칸 돌진
	// 거리,santa r,c 순서
	// 우선순위로 pq 뽑기
	// 탈락x 인 산타
	for (int i = 1; i <= P; i++) {
		if (santa[i].die == 1) continue;

		int dist = calculation(santa[i].x, santa[i].y, ru_x, ru_y);
		int x = santa[i].x;
		int y = santa[i].y;
		turn_ru.push({ dist,x,y,i });
	}
	
	// 돌진해야할 대상 선택
	// 가장 가까워지는 방향, 대상 선택
	int closet_dist = 1e9;
	int target_dir;          // 전진 방향
	int target = turn_ru.top().p; // 전진 대상
	for (int i = 0; i < 8; i++) {
		int nx = ru_x + ru_dx[i];
		int ny = ru_y + ru_dy[i];
		if (nx < 1 || N < nx || ny < 1 || N < ny) continue; // 격자밖으로 이동하지 않는다

		int temp_dist = calculation(nx, ny, santa[target].x, santa[target].y);
		if (temp_dist < closet_dist) {
			closet_dist = temp_dist;
			target_dir = i;
		}
	}

	// 이동한다
	ru_x = ru_x + ru_dx[target_dir];
	ru_y = ru_y + ru_dy[target_dir];
	// 상호작용이 일어난다면
	for (int i = 1; i <= P; i++) {
		if (ru_x == santa[i].x && ru_y == santa[i].y) {
			santa[i].score += C;
			mutual_interaction(i,target_dir,C);
		}
	}

	// 2. 산타 -> 루로 이동한다
	// 제일 가까워지는 방향을 정해야 한다
	// 이동한다
	// 상호작용이 일어난다면
	// 아니라면 위치처리만 하고 끝
}

int main() {
	cin >> N >> M >> P >> C >> D;
	cin >> ru_x >> ru_y;
	for (int i = 0; i < P; i++) {
		int tp, tx, ty; cin >> tp >> tx >> ty;
		// inital
		santa[tp].x = tx;
		santa[tp].y = ty;
		santa[tp].stun = 0;
		santa[tp].die = 0;
		santa[tp].score = 0;
	}
	// simulation
	for (int i = 1; i <= M; i++) {
		//initial
		turn_ru = priority_queue<Turn_ru>();
		simulation(i);
		// 모든 산타가 탈락한다면 그 즉시 게임이 종료된다
		// 탈락하지 않은 산타들 점수 추가
	}
	// 각 산타가 얻은 최종 점수
	for (int i = 1; i <= P; i++) {
		cout << santa[i].score << ' ';
	}
}
