
n, m = map(int, input().split())
weights = list(map(int, input().split()))

dp = [0] * (m + 1)

for w in weights:
    for capacity in range(m, w - 1, -1):
        dp[capacity] = max(dp[capacity], dp[capacity - w] + w)


print(dp[m])

