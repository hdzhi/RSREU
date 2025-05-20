N = int(input())
# Считываем матрицу смежности графа
graph = [list(map(int, input().split())) for _ in range(N)]

# Инициализация матрицы расстояний
dist = [[graph[i][j] for j in range(N)] for i in range(N)]

# Алгоритм Флойда-Уоршелла
for k in range(N):
    for i in range(N):
        for j in range(N):
            if dist[i][k] != float('inf') and dist[k][j] != float('inf'):
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j])

# Проверка на наличие отрицательных циклов
for k in range(N):
    if dist[k][k] < 0:  # Если расстояние до самой себя отрицательное, то есть отрицательный цикл
        print(-1)
        exit()

# Поиск минимального расстояния между всеми парами различных вершин
min_distance = float('inf')
for i in range(N):
    for j in range(N):
        if i != j:  # Исключаем пары (i, i)
            min_distance = min(min_distance, dist[i][j])

# Если минимальные расстояния остались бесконечными, выводим -1
if min_distance == float('inf'):
    print(-1)
else:
    print(min_distance)
