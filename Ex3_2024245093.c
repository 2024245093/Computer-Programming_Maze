#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
int maze[8][8];
int visited[8][8];     //방문 배열
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};
int x = 0, y = 0;   // 로봇의 위치
int move_robot(char *commands) {
    int steps = 0;
    for (int i = 0; commands[i] != '\0'; i++) {
        int nx = x, ny = y;
        int direction = -1;
        // 명령에 따른 방향 결정
        if (commands[i] == 'U') direction = 0;
        if (commands[i] == 'D') direction = 1;
        if (commands[i] == 'L') direction = 2;
        if (commands[i] == 'R') direction = 3;
        if (commands[i] == 'S') {    //벽 부순다면
            i++; // 다음 문자를 확인
            if (commands[i] == 'U') direction = 0;
            if (commands[i] == 'D') direction = 1;
            if (commands[i] == 'L') direction = 2;
            if (commands[i] == 'R') direction = 3;
            // 벽을 뚫기
            nx += dx[direction];
            ny += dy[direction];
        }
        nx += dx[direction];   //각각 이동
        ny += dy[direction];
        if (nx>=0 && nx<8 && ny>=0 && ny<8 && maze[nx][ny]!=1) {    // 이동 가능한지 확인
            x = nx;
            y = ny;
            visited[x][y] = 3; //이동 경로 표시용
            steps++;
            if (maze[x][y]==2) return steps; //도착
        }
    }
    return -1; // 탈출 X
}
int main() {
    char commands[21];
    for (int i=0; i<8; i++)   //입력 미로
        for (int j=0; j<8; j++)
            scanf("%d", &maze[i][j]);
    scanf("%s", commands);
    visited[0][0] = 3;
    int result = move_robot(commands);
    if (result != -1) {
        printf("%d\n", result);
        for (int i=0; i<8; i++) {
            for (int j=0; j<8;j++) {
                if (visited[i][j]) {    //방문한 경우, visited
                    printf("%d ", visited[i][j]);
                } else {   //아니면 maze
                    printf("%d ", maze[i][j]);
                }
            }
            printf("\n");
        }
    } else {
        printf("-1\n");
    }
    return 0;
}