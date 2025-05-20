class Deque:
    def __init__(self):
        self.items = []

    def is_empty(self):
        return self.items == []

    def push_front(self, item):
        self.items = [item] + self.items
        return "ok"

    def push_back(self, item):
        self.items.append(item)
        return "ok"

    def pop_front(self):
        if self.is_empty():
            return "error"
        return self.items.pop(0)

    def pop_back(self):
        if self.is_empty():
            return "error"
        return self.items.pop()

    def front(self):
        if self.is_empty():
            return "error"
        return self.items[0]

    def back(self):
        if self.is_empty():
            return "error"
        return self.items[-1]

    def size(self):
        return len(self.items)

    def clear(self):
        self.items = []
        return "ok"

    def exit(self):
        return "bye"

d = Deque()

while True:
    command = input().split()
    if command[0] == "push_front":
        print(d.push_front(command[1]))
    elif command[0] == "push_back":
        print(d.push_back(command[1]))
    elif command[0] == "pop_front":
        print(d.pop_front())
    elif command[0] == "pop_back":
        print(d.pop_back())
    elif command[0] == "front":
        print(d.front())
    elif command[0] == "back":
        print(d.back())
    elif command[0] == "size":
        print(d.size())
    elif command[0] == "clear":
        print(d.clear())
    elif command[0] == "exit":
        print(d.exit())
        break