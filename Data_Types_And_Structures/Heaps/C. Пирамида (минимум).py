class MinHeap:
    def __init__(self):
        self.heap = []

    def perc_up(self, i):
        while i > 0:
            parent = (i - 1) // 2
            if self.heap[i] < self.heap[parent]:
                self.heap[i], self.heap[parent] = self.heap[parent], self.heap[i]
                i = parent
            else:
                break

    def perc_down(self, i, size):
        while 2 * i + 1 < size:
            child = 2 * i + 1
            if child + 1 < size and self.heap[child + 1] < self.heap[child]:
                child += 1
            if self.heap[i] > self.heap[child]:
                self.heap[i], self.heap[child] = self.heap[child], self.heap[i]
                i = child
            else:
                break

    def insert(self, k):
        self.heap.append(k)
        self.perc_up(len(self.heap) - 1)

    def extract(self):
        if not self.heap:
            return -1
        min_value = self.heap[0]
        self.heap[0] = self.heap[-1]
        self.heap.pop()
        if self.heap:
            self.perc_down(0, len(self.heap))
        return min_value

    def clear(self):
        self.heap.clear()


def main():
    min_heap = MinHeap()

    while True:
        command = input().strip()
        if command == "CLEAR":
            min_heap.clear()
        elif command.startswith("ADD"):
            n = int(command[4:])
            min_heap.insert(n)
        elif command == "EXTRACT":
            result = min_heap.extract()
            if result == -1:
                print("CANNOT")
            else:
                print(result)
        else:
            break


if __name__ == "__main__":
    main()

"""
#include <iostream>
#include <vector>
#include <string>

using namespace std;

void perc_up(vector<int>& heap, int i){
    while (i > 0){
        int parent = (i - 1) / 2;
        if (heap[i] < heap[parent]) {
            swap(heap[i], heap[parent]);
            i = parent;
        } else {
            break;
        }
    }
}

void perc_down(vector<int>& heap, int i, int size){
    while (2 * i + 1 < size){
        int child = 2 * i + 1;
        if (child + 1 < size && heap[child + 1] < heap[child]){
            child++;
        }
        if (heap[i] > heap[child]) {
            swap(heap[i], heap[child]);
            i = child;
        } else {
            break;
        }
    }
}

void insert(vector<int>& heap, int k){
    heap.push_back(k);
    perc_up(heap, heap.size() - 1);
}

int extract(vector<int>& heap){
    if (heap.empty()){
        return -1;
    }
    int min_value = heap[0];
    heap[0] = heap.back();
    heap.pop_back();
    if(!heap.empty()){
        perc_down(heap, 0, heap.size());
    }
    return min_value;
}

void clear(vector<int>& heap){
    heap.clear();
}

int main() {
    vector<int> heap;
    string command;

    while (true) {
        getline(cin, command);
        if (command == "CLEAR") {
            clear(heap);
        } else if (command.rfind("ADD", 0) == 0) {
            int n = stoi(command.substr(4));
            insert(heap, n);
        } else if (command == "EXTRACT") {
            int result = extract(heap);
            if (result == -1) {
                cout << "CANNOT" << endl;
            } else {
                cout << result << endl;
            }
        } else {
            break;
        }
    }

    return 0;
}
"""
