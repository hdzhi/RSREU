n, start, end = map(int, input().split())
start -= 1
end -= 1

# Граф в виде матрицы смежности
graph = []
for _ in range(n):
    graph.append(list(map(int, input().split())))

visited = [False] * n
dist = [float('inf')] * n  # массив дистанций (изначально все - INF)
dist[start] = 0  # стартовый узел = 0
prev = [-1] * n  # массив для предыдущих узлов

for _ in range(n):
    # минимальное расстояние (для начала, принимаем за INF)
    min_dist = float('inf')
    min_index = -1  # индекс узла с минимальным расстоянием
    # поиск узла с минимальным расстоянием из непосещенных
    for i in range(n):
        if not visited[i] and dist[i] < min_dist:
            min_dist = dist[i]
            min_index = i
    # если не нашли - выходим из цикла
    if min_index == -1:
        break
    # отмечаем узел как посещенный
    visited[min_index] = True
    # обновляем расстояние до "соседей" от текущего узла
    for i in range(n):
        if graph[min_index][i] >= 0:  # проверка на наличие узла
            # считаем новое расстояние
            new_dist = dist[min_index] + graph[min_index][i]
            # Если найденное расстояние меньше, обновляем его и предшествующий узел
            if new_dist < dist[i]:
                dist[i] = new_dist
                prev[i] = min_index
# проверка на достижение конечного узла, если нет, то -1
if dist[end] == float('inf'):
    print(-1)

else:
    # восстановление кратчайшего пути
    curr = end  # восстановление начинаем с конечного узла
    ans = [curr + 1]  # массив для хранения пути
    # пока есть предыдущий узел
    while prev[curr] + 1 > 0:
        curr = prev[curr]
        ans.append(curr + 1)
    print(*ans[::-1])
