d = []
s2 = []

n = int(input())

s1 = list(map(int, input().split()))
while len(s1) != 0:
    d.append(s1.pop(0))
    while True:
        if len(d) != 0:
            if len(s2) > 0:
                if s2[-1]+1 == d[-1]:
                    s2.append(d.pop())
                else:
                    break
            else:
                if d[-1] == 1:
                    s2.append(d.pop())
                else:
                    break
        else:
            break

if len(s2) != n:
    print('NO')
else:
    print('YES')