import heapq


def dkstra(graph, start, end):
    # словарь расстояний, в котором все узлы имеют бесконечное расстояние
    dist = {node: float('inf') for node in graph}
    dist[start] = 0

    # приоритетная очередь и добавление в нее стартового узла
    pq = [(0, start)]
    heapq.heapify(pq)

    # Пока в нашей очереди есть элементы:
    while pq:
        # берем узел с наименьшим расстоянием
        cur_dist, cur_vertex = heapq.heappop(pq)

        # если достигнут конечный узел, возвращаем его расстояние
        if cur_vertex == end:
            return dist[end]

        # проверка на необходимость релаксации
        if dist[cur_vertex] < cur_dist:
            continue

        # проходимся по всем соседям текущего узла
        for neighbor, weight in graph[cur_vertex].items():
            d = cur_dist + weight  # новое расстояние до соседа
            # если найденное расстояние меньше известного - добавляем в очередь
            if d < dist[neighbor]:
                dist[neighbor] = d
                heapq.heappush(pq, (d, neighbor))
    # -1, если путь не был найден
    return -1


N, S, F = map(int, input().split())
graph = {i: {} for i in range(1, N + 1)}
for i in range(1, N + 1):
    weights = list(map(int, input().split()))
    for j, w in enumerate(weights):
        if w != -1:
            graph[i][j + 1] = w

print(dkstra(graph, S, F))
