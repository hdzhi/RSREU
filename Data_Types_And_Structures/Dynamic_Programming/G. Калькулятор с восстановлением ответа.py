n = int(input())
dp = [0] * (n + 1)
for i in range(2, (n + 1)):
    if i % 6 == 0:
        dp[i] = min(dp[i // 3], dp[i // 2], dp[i - 1]) + 1
    elif i % 3 == 0:
        dp[i] = min(dp[i // 3], dp[i - 1]) + 1
    elif i % 2 == 0:
        dp[i] = min(dp[i // 2], dp[i - 1]) + 1
    else:
        dp[i] = dp[i - 1] + 1

i = n
s = ' '
while i != 1:
    if dp[i - 1] + 1 == dp[i]:
        s = '1' + s
        i -= 1
    elif i % 2 == 0 and dp[i // 2] + 1 == dp[i]:
        s = '2' + s
        i //= 2
    else:
        s = '3' + s
        i //= 3
print(s)
