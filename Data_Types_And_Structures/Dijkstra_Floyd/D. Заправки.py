import heapq


def solve():
    n = int(input())  # количество вершин
    costs = list(map(int, input().split()))  # веса в графе
    m = int(input())  # количество ребер в графе

    edges = []  # список для хранения ребер
    # граф создается в виде списка смежности (храним в виде словаря)
    graph = {i: [] for i in range(n)}
    # вводим узлы
    for _ in range(m):
        u, v = map(int, input().split())
        edges.append((u - 1, v - 1))

    # Добавляем рёбра в граф для обеих вершин, так как граф неориентированный
    for u, v in edges:
        graph[u].append(v)
        graph[v].append(u)
    # расстояния до всех вершин
    dist = {i: float('inf') for i in range(n)}
    dist[0] = 0 # расстояние до стартовой вершины - 0

    pq = [(0, 0)] #  Приоритетная очередь для хранения пар (стоимость, узел)
    visited = set()  # отслеживаем посещенные вершины
    # Пока очередь не пуста
    while pq:
        # Извлекаем узел с наименьшей стоимостью
        cost, node = heapq.heappop(pq)
        # Если текущая стоимость больше известного расстояния, пропускаем
        if cost > dist[node]:
            continue
        # Если достигли конечной вершины (n-1)
        if node == n - 1:
            # Выводим общую стоимость
            print(cost)
            return
        # Добавляем текущую вершину в множество посещённых
        visited.add(node)
        # Обходим всех соседей текущей вершины
        for neighbor in graph[node]:
            # Если сосед не посещён
            if neighbor not in visited:
                # Рассчитываем новую стоимость
                new_cost = cost + costs[node]
                # Если новая стоимость меньше текущего известного расстояния
                if new_cost < dist[neighbor]:
                    # Обновляем расстояние
                    dist[neighbor] = new_cost
                    # Добавляем нового соседа в очередь
                    heapq.heappush(pq, (new_cost, neighbor))
    # Если не удалось достичь конечной вершины, выводим -1
    print(-1)


solve()
