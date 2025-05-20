def dfs(start, visited, matrix):
    visited[start] = True
    for v in range(len(matrix)):
        if matrix[start][v] == 1 and not visited[v]:
            dfs(v, visited, matrix)


n, s = map(int, input().split())
matrix = []

for _ in range(n):
    matrix.append(list(map(int, input().split())))

s -= 1
visited = [False] * n
count = 0

dfs(s, visited, matrix)

for v in visited:
    if v:
        count += 1

print(count)
