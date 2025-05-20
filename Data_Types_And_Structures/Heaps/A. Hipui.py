class Heap:
    def __init__(self):
        self.heap = [0]
        self.size = 0

    # тут мы вставляем число в кучу
    def insert(self, k):
        self.heap.append(k)
        self.size += 1
        self._heapify_up(self.size)

    # после вставки пермещаем число наверх по куче, если необходимо
    def _heapify_up(self, i):
        while i // 2 > 0:
            if self.heap[i] > self.heap[i // 2]:
                self.heap[i], self.heap[i // 2] = self.heap[i // 2], self.heap[i]
            i //= 2

    # находим и удаляем число из кучи
    def extract(self):
        max_value = self.heap[1]
        self.heap[1] = self.heap[self.size]
        self.heap.pop()
        self.size -= 1
        self._heapify_down(1)
        return max_value

    # перемещаем число вниз по куче, если необходимо
    def _heapify_down(self, i):
        while (i * 2) <= self.size:
            mc = self._max_child(i)
            if self.heap[i] < self.heap[mc]:
                self.heap[i], self.heap[mc] = self.heap[mc], self.heap[i]
            i = mc

    def _max_child(self, i):
        if (i * 2) + 1 > self.size:
            return i * 2
        else:
            if self.heap[i * 2] > self.heap[(i * 2) + 1]:
                return i * 2
            else:
                return (i * 2) + 1


if __name__ == "__main__":
    n = int(input())
    heap = Heap()
    for _ in range(n):
        command = input().split()
        if command[0] == "0":
            heap.insert(int(command[1]))
        elif command[0] == "1":
            print(heap.extract())