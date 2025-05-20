deque = []
n, k = map(int, input().split())
numbers = list(map(int, input().split()))

for i in range(k):
    deque.append(numbers[i])
    while len(deque) > 1 and deque[-1] < deque[-2]:
        deque.pop(-2)

i = 0
print(deque[0])

for i in range(k, len(numbers)):
    if deque[0] == numbers[i - k] or len(deque) > k:
        deque.pop(0)
    deque.append(numbers[i])
    while len(deque) > 1 and deque[-1] < deque[-2]:
        deque.pop(-2)
    print(deque[0])