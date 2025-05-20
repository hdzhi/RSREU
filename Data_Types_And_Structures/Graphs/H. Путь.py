from collections import deque

# Задаем бесконечность для начальной инициализации расстояний
INF = float('inf')
n = int(input())

# Инициализируем граф в виде словаря, в котором каждой вершине сопоставлено множество соседей
graph = {i: set() for i in range(n)}
for i in range(n):
    ls = input().split()
    for j, val in enumerate(ls):
        # Если существует ребро между вершинами i и j
        if val == '1':
            # Добавляем j как соседей для вершины i
            graph[i].add(j)

# Считываем начальную (s) и конечную (t) вершины
s, t = map(int, input().split())
s -= 1
t -= 1

# Инициализируем массив расстояний до всех вершин
dist = [INF] * n
# Расстояние до стартовой вершины равно 0
dist[s] = 0
q = deque([s])  # Создаем очередь для BFS и добавляем начальную вершину
prev = [-1] * n  # Массив для хранения предыдущей вершины на пути
prev[s] = s # Для стартовой вершины предыдущей вершиной является она сама

while q:
    node = q.popleft() # Извлекаем текущую вершину из очереди
    for neigh in graph[node]:
        if dist[neigh] == INF: # Если сосед еще не посещен
            dist[neigh] = dist[node] + 1  # Обновляем дистанцию до соседа
            prev[neigh] = node  # Сохраняем предшественника
            q.append(neigh)  # Добавляем соседа в очередь для дальнейшего обхода

if dist[t] == INF:
    print(-1)
elif dist[t] == 0:
    print(dist[t])
else:
    path = []
    curr = t
    # Пока не дойдем до стартовой вершины
    while curr != s:
        path.append(curr)  # Добавляем текущую вершину в путь
        curr = prev[curr]  # Переходим к предыдущей вершине
    path.append(s)
    path.reverse()  # Разворачиваем путь от s до t
    print(dist[t])  # Выводим длину кратчайшего пути
    print(*[x + 1 for x in path])
