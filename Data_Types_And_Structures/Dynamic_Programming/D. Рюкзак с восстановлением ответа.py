def backpack(v, c, w, n):
    dp = [[0] * (w + 1) for _ in range(n + 1)]

    for i in range(1, n + 1):
        for current_w in range(w + 1):
            if current_w < v[i-1]:
                dp[i][current_w] = dp[i - 1][current_w]
            else:
                dp[i][current_w] = max(dp[i - 1][current_w], dp[i - 1][current_w - v[i-1]] + c[i-1])

    res = []
    i, w1 = n, w
    while i > 0 and w1 > 0:
        if dp[i][w1] > dp[i - 1][w1]:
            res.append(i)
            w1 -= v[i-1]
        i -= 1
    return res[::-1]


n, capacity = map(int, input().split())
weight = list(map(int, input().split()))
cost = list(map(int, input().split()))


print(*backpack(weight, cost, capacity, n), sep='\n')