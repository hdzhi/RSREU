n = int(input())
a = [0]
b = [0]
c = [0]
for i in range(1, n + 1):
    ai, bi, ci = map(int, input().split())
    a.append(ai)
    b.append(bi)
    c.append(ci)

t = [0] * (n + 1)
t[0] = 0
t[1] = a[1]
if n > 1:
    t[2] = min(a[1] + a[2], b[1])

for i in range(3, n + 1):
    t[i] = min(t[i - 1] + a[i], t[i - 2] + b[i - 1], t[i - 3] + c[i - 2])
print(t[-1])
