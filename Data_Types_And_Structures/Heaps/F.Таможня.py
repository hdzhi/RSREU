import heapq


def devices_needed(n, data):
    data.sort(key=lambda x: x[0])
    devices_heap = []
    for arrival_time, processing_time in data:
        if devices_heap and devices_heap[0] <= arrival_time:
            heapq.heappush(devices_heap, arrival_time + processing_time)
        # иначе, нужен новый аппарат
        else:
            heapq.heappush(devices_heap, arrival_time + processing_time)
    return len(devices_heap)


n = int(input())
data = []
for el in range(n):
    arr_time, process_time = map(int, input().split())
    data.append((arr_time, process_time))

print(devices_needed(n, data))
