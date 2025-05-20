from collections import deque


def solve():
    n = int(input())
    x1, y1 = map(int, input().split())
    x2, y2 = map(int, input().split())

    q = deque([(x1, y1, 0, [])])
    visited = set()
    moves = [(2, 1), (1, 2), (-1, 2), (-2, 1), (-2, -1), (-1, -2), (1, -2), (2, -1)]

    while q:
        x, y, dist, path = q.popleft()
        if (x, y) == (x2, y2):
            print(dist)
            for px, py in path + [(x, y)]:
                print(px, py)
            return

        if (x, y) in visited:
            continue
        visited.add((x, y))

        for dx, dy in moves:
            nx, ny = x + dx, y + dy
            if 1 <= x <= n and 1 <= y <= n:
                q.append((nx, ny, dist + 1, path + [(x, y)]))

    print(-1)


solve()
