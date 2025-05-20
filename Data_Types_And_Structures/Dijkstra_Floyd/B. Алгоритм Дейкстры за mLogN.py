import sys
import heapq

# Константа для обозначения недостижимой вершины
INF = 2009000999


# Функция Dijkstra для нахождения кратчайших расстояний
def dijkstra(start, n, graph):
    # Инициализация массива расстояний до всех вершин
    distances = [INF] * n
    distances[start] = 0

    # Приоритетная очередь и добавление в нее стартового узла
    pq = []
    heapq.heappush(pq, (0, start))

    while pq:
        # берем узел с наименьшим расстоянием
        current_distance, current_vertex = heapq.heappop(pq)

        # Если текущее расстояние больше уже известного, то пропускаем
        if current_distance > distances[current_vertex]:
            continue

        # Перебираем соседей текущей вершины
        for neighbor, weight in graph[current_vertex]:
            distance = current_distance + weight  # Рассчитываем новое расстояние

            # Если новое расстояние меньше известного, обновляем и добавляем в кучу
            if distance < distances[neighbor]:
                distances[neighbor] = distance
                heapq.heappush(pq, (distance, neighbor))

    return distances


def main():
    input_data = sys.stdin.read
    data = input_data().splitlines()
    idx = 0

    # Читаем количество запусков алгоритма
    NUM = int(data[idx])
    idx += 1
    results = []

    # Проходим по каждому блоку данных
    for _ in range(NUM):
        # Читаем количества вершин (N) и рёбер (M)
        N, M = map(int, data[idx].split())
        idx += 1

        # Инициализация графа
        graph = [[] for _ in range(N)]

        # Читаем рёбра
        for _ in range(M):
            x, y, val = map(int, data[idx].split())
            graph[x].append((y, val))  # Добавляем рёбра в граф
            graph[y].append((x, val))  # Так как граф неориентированный
            idx += 1

        # Читаем стартовую вершину
        start_vertex = int(data[idx])
        idx += 1

        # Получаем расстояния от стартовой вершины до всех остальных
        distances = dijkstra(start_vertex, N, graph)

        # Создаем строку с результатами
        results.append(' '.join(str(d) if d != INF else str(INF) for d in distances))

    # Выводим результаты
    print('\n'.join(results))


# Точка входа в программу
if __name__ == "__main__":
    main()