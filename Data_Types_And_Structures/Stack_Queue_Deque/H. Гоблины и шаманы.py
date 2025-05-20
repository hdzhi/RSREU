import sys
from collections import deque

n = int(sys.stdin.readline())
queue_left = deque()
queue_right = deque()

while n > 0:
    s = sys.stdin.readline().split()
    if s[0] == "+":
        queue_right.append(s[1])
        if len(queue_left) < len(queue_right):
            queue_left.append(queue_right.popleft())
    elif s[0] == "*":
        queue_left.append(s[1])
        if len(queue_left) - len(queue_right) > 1:
            queue_right.appendleft(queue_left.pop())
    else:
        print(queue_left.popleft())
        if len(queue_left) < len(queue_right):
            queue_left.append(queue_right.popleft())
    n -= 1
