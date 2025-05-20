class Stack:
    def __init__(self):
        self.items = []

    def push(self, item):
        self.items.append(item)
        return "ok"

    def pop(self):
        if self.is_empty():
            return "error"
        return self.items.pop()

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

    def is_empty(self):
        return len(self.items) == 0


s = Stack()

while True:
    command = input().split()
    if command[0] == "push":
        print(s.push(command[1]))
    elif command[0] == "pop":
        print(s.pop())
    elif command[0] == "back":
        print(s.back())
    elif command[0] == "size":
        print(s.size())
    elif command[0] == "clear":
        print(s.clear())
    elif command[0] == "exit":
        print(s.exit())
        break