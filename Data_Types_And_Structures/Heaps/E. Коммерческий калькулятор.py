import heapq

n = int(input())
a = list(map(int, input().split()))
heapq.heapify(a)
res = 0
min1 = heapq.heappop(a)

for i in range(n-1):
    min2 = heapq.heappop(a)
    s = min1 + min2
    res += s / 20
    min1 = heapq.heappushpop(a, s)
print("%.2f" % res)
