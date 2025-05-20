import heapq
import sys

heap = []


def clear_heap():
    global heap
    heap = []


def add_to_heap(value):
    heapq.heappush(heap, -value)


def extract_max():
    if heap:
        return -heapq.heappop(heap)
    else:
        return "CANNOT"


for line in sys.stdin:
    command = line.strip().split()
    if command[0] == "CLEAR":
        clear_heap()
    elif command[0] == "ADD":
        add_to_heap(int(command[1]))
    elif command[0] == "EXTRACT":
        result = extract_max()
        if result == "CANNOT":
            print(result)
        else:
            print(result)