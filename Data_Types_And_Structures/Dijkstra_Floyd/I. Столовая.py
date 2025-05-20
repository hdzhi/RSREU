import heapq


def solve():
    # Считываем количество зданий (n) и количество дорог (m)
    n, m = map(int, input().split())
    edges = []  # Список для хранения рёбер графа

    # Считываем рёбра графа
    for _ in range(m):
        u, v, w = map(int, input().split())  # Считываем ребро (u, v) с весом w
        edges.append((u - 1, v - 1, w))  # Сохраняем ребро (переводим в 0-индексацию)
        edges.append((v - 1, u - 1, w))  # Для неориентированного графа добавляем обратное ребро

    # Создаем граф в виде словаря смежности
    graph = {i: [] for i in range(n)}  # Инициализируем граф как пустой словарь
    for u, v, w in edges:
        graph[u].append((v, w))  # Добавляем связь u -> v с весом w

    best_building = -1  # Переменная для хранения "лучшего" здания
    min_max_dist = float('inf')  # Минимальное из максимальных расстояний

    # Перебираем каждое здание как стартовую точку
    for start_node in range(n):
        distances = dijkstra(graph, start_node)  # Получаем расстояния от стартовой точки
        max_dist = max(distances)  # Находим максимальное расстояние до остальных зданий

        # Сравниваем, является ли текущее максимальное расстояние минимальным из найденных
        if max_dist < min_max_dist:
            min_max_dist = max_dist  # Обновляем минимальное максимальное расстояние
            best_building = start_node + 1  # Обновляем лучшее здание (с учетом 1-индексации)
        elif max_dist == min_max_dist and (best_building == -1 or start_node + 1 < best_building):
            best_building = start_node + 1  # Если веса равны, выбираем с меньшим индексом

    print(best_building)  # Печатаем индекс лучшего здания


def dijkstra(graph, start):
    n = len(graph)  # Получаем количество зданий
    dist = [float('inf')] * n  # Инициализируем расстояния до зданий как бесконечность
    dist[start] = 0  # Расстояние до стартовой точки равно 0
    pq = [(0, start)]  # Начинаем с добавления стартовой точки в очередь с приоритетом

    # Пока есть элементы в очереди
    while pq:
        d, u = heapq.heappop(pq)  # Извлекаем элемент с наименьшим расстоянием
        if d > dist[u]:  # Если текущий элемент имеет большее значение, пропускаем его
            continue
        # Перебираем все соседние вершины u
        for v, weight in graph.get(u, []):
            # Если найдено лучшее расстояние до вершины v
            if dist[u] + weight < dist[v]:
                dist[v] = dist[u] + weight  # Обновляем расстояние до v
                heapq.heappush(pq, (dist[v], v))  # Добавляем v в очередь с новым расстоянием
    return dist  # Возвращаем список расстояний от стартовой точки


solve()  # Вызываем функцию решения
