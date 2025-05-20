def max_cost_way():
    N, M = map(int, input().split())
    grid = []
    for _ in range(N):
        grid.append(list(map(int, input().split())))

    dp = [[0] * M for _ in range(N)]
    dp[0][0] = grid[0][0]

    paths = [[""] * M for _ in range(N)]
    paths[0][0] = ""

    for i in range(N):
        for j in range(M):
            if i == 0 and j == 0:
                continue

            up = dp[i - 1][j] if i > 0 else float('-inf')
            left = dp[i][j - 1] if j > 0 else float('-inf')

            if up > left:
                dp[i][j] = up + grid[i][j]
                paths[i][j] = paths[i - 1][j] + "D"
            else:
                dp[i][j] = left + grid[i][j]
                paths[i][j] = paths[i][j - 1] + "R"

    print(dp[N - 1][M - 1])
    print(paths[N - 1][M - 1])


max_cost_way()