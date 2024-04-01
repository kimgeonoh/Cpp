#include <vector>
#include <queue>

using namespace ::std;

const int MAX_N = 20;
const int MAX_HASH = 9999;

int n;
int initMap[MAX_N + 2][MAX_N + 2];
int modifiedMap[MAX_N + 2][MAX_N + 2];

struct Candidate
{
    int r;
    int c;
    bool isHorizontal; // 수직인가 수평인가
    bool isReverse; // 180, 270도 돌렸을 때 반대수열인가
};
vector<Candidate> candidate[MAX_HASH + 1];

void init(int N, int mMap[20][20])
{
    n = N;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            modifiedMap[i + 1][j + 1] = initMap[i + 1][j + 1] = mMap[i][j];
    for (int i = 0; i <= MAX_HASH; i++)
        candidate[i].clear();

    for (int length = 2; length <= 5; length++) // 구조물의 길이에 따라 
    {
        // 수평 방향으로 구조물 놓기
        for (int i = 1; i <= n; i++)
        {
            // (i,j) 를 시작으로 오른쪽으로 구조물을 놓을 때
            for (int j = 1; j + length - 1 <= n; j++)
            {
                // 왼쪽에서 오른쪽으로 구조물을 놓았을 때
                int hash = 0;
                for (int k = 0; k + 1 < length; k++)
                    hash = hash * 10 + (initMap[i][j + k + 1] - initMap[i][j + k] + 5); // 오른쪽 - 왼쪽 + 5
                candidate[hash].push_back({ i, j, true, false });
                // 오른쪽에서 왼쪽으로 (180도 회전해서) 구조물을 놓았을 때
                int reverseHash = 0;
                for (int k = length - 1; k - 1 >= 0; k--)
                    reverseHash = reverseHash * 10 + (initMap[i][j + k - 1] - initMap[i][j + k] + 5); // 왼쪽 - 오른쪽 + 5
                if (reverseHash != hash) // 180도, 270도 돌렸을때 대칭인 경우 예외처리
                    candidate[reverseHash].push_back({ i, j, true, true });
            }
        }
        // 수직 방향으로 구조물 놓기
        for (int i = 1; i + length - 1 <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                int hash = 0;
                for (int k = 0; k + 1 < length; k++)
                    hash = hash * 10 + (initMap[i + k + 1][j] - initMap[i + k][j] + 5);
                candidate[hash].push_back({ i, j, false, false });

                int reverseHash = 0;
                for (int k = length - 1; k - 1 >= 0; k--)
                    reverseHash = reverseHash * 10 + (initMap[i + k - 1][j] - initMap[i + k][j] + 5);
                if (reverseHash != hash)
                    candidate[reverseHash].push_back({ i, j, false, true });
            }
        }
    }
}

int numberOfCandidate(int M, int mStructure[5])
{
    if (M == 1)
        return n * n;

    int hash = 0;
    for (int i = 0; i + 1 < M; i++)
        hash = hash * 10 + (mStructure[i] - mStructure[i + 1] + 5);
    return candidate[hash].size(); // 전처리(hash)로 이미 값이 저장되어 있다.
}

bool check[MAX_N + 2][MAX_N + 2];
int dx[4] = { 1, 0, -1, 0 };
int dy[4] = { 0, 1, 0, -1 };

// 잠기지 않는 넓이 계산
// 그래프 탐색
int unsubmergedArea(int mMap[MAX_N + 2][MAX_N + 2], int mSeaLevel)
{
    queue<pair<int, int>> q;
    for (int i = 0; i <= n + 1; i++)
    {
        for (int j = 0; j <= n + 1; j++)
        {
            if (i == 0 || i == n + 1 || j == 0 || j == n + 1)
            {
                q.push({ i, j });
                check[i][j] = true;
            }
            else
                check[i][j] = false;
        }
    }
    while (!q.empty())
    {
        pair<int, int> front = q.front();
        for (int i = 0; i < 4; i++)
        {
            pair<int, int> rear = { front.first + dx[i], front.second + dy[i] };
            if (rear.first >= 1 && rear.first <= n && rear.second >= 1 && rear.second <= n)
            {
                if (!check[rear.first][rear.second] && mMap[rear.first][rear.second] < mSeaLevel)
                {
                    q.push(rear);
                    check[rear.first][rear.second] = true;
                }
            }
        }
        q.pop();
    }
    int ret = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (!check[i][j])
                ret++;
    return ret;
}

int maxArea(int M, int mStructure[5], int mSeaLevel)
{
    int ret = -1;
    if (M == 1) // 모든 구역에 한번씩 놓아본다
    {
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                modifiedMap[i][j] = initMap[i][j] + mStructure[0];
                ret = max(ret, unsubmergedArea(modifiedMap, mSeaLevel));
                modifiedMap[i][j] = initMap[i][j];
            }
        }
        return ret;
    }

    int hash = 0;
    for (int i = 0; i + 1 < M; i++)
        hash = hash * 10 + (mStructure[i] - mStructure[i + 1] + 5);

    for (auto wall : candidate[hash]) // 완탐
    {
        if (wall.isHorizontal)
        {
            int height = mStructure[0] + (wall.isReverse ? initMap[wall.r][wall.c + M - 1] : initMap[wall.r][wall.c]);
            for (int i = 0; i < M; i++)
                modifiedMap[wall.r][wall.c + i] = height;
            ret = max(ret, unsubmergedArea(modifiedMap, mSeaLevel));
            for (int i = 0; i < M; i++)
                modifiedMap[wall.r][wall.c + i] = initMap[wall.r][wall.c + i];
        }
        else
        {
            int height = mStructure[0] + (wall.isReverse ? initMap[wall.r + M - 1][wall.c] : initMap[wall.r][wall.c]);
            for (int i = 0; i < M; i++)
                modifiedMap[wall.r + i][wall.c] = height;
            ret = max(ret, unsubmergedArea(modifiedMap, mSeaLevel));
            for (int i = 0; i < M; i++)
                modifiedMap[wall.r + i][wall.c] = initMap[wall.r + i][wall.c];
        }
    }
    return ret;
}
