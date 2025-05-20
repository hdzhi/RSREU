class Queue:
    def __init__(self):
        self.items = []

    def is_empty(self):
        return self.items == []

    def push(self, item):
        self.items.append(item)
        return "ok"

    def front(self):
        if self.is_empty():
            return "error"
        return self.items[0]

    def pop(self):
        if self.is_empty():
            return "error"
        return self.items.pop(0)

    def size(self):
        return len(self.items)

    def clear(self):
        self.items = []
        return "ok"

    def exit(self):
        return "bye"


q = Queue()

while True:
    command = input().split()
    if command[0] == "push":
        print(q.push(command[1]))
    elif command[0] == "front":
        print(q.front())
    elif command[0] == "pop":
        print(q.pop())
    elif command[0] == "size":
        print(q.size())
    elif command[0] == "clear":
        print(q.clear())
    elif command[0] == "exit":
        print(q.exit())
        break