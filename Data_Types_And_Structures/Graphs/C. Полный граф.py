n, m = map(int, input().split())
edges = set()
for _ in range(m):
    u, v = map(int, input().split())
    edges.add((min(u, v), max(u, v)))

# Вычисляем общее число ребер в полном графе с n вершинами
total_edges = n * (n - 1) // 2
# Проверяем, равно ли количество уникальных ребер количеству ребер в полном графе
if len(edges) == total_edges:
    print("YES")
else:
    print("NO")
