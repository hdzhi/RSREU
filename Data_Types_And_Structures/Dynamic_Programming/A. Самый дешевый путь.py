def cheapest_way(costs):
    n = len(costs)
    if n <= 0:
      return 0
    if n == 1:
      return costs[0]

    dp = [0] * n
    dp[0] = costs[0]
    dp[1] = min(costs[0] + costs[1], costs[1])

    for i in range(2, n):
      dp[i] = costs[i] + min(dp[i - 1], dp[i - 2])
    return dp[n - 1]

N = int(input())

costs = list(map(int, input().split()))

result = cheapest_way(costs)
print(result)
