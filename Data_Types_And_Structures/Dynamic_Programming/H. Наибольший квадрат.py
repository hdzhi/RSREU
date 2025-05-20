def largest_square(matrix, n, m):
    dp = [[0] * m for _ in range(n)]
    max_size = 0
    max_x = 0
    max_y = 0

    for i in range(n):
        for j in range(m):
            if matrix[i][j] == 1:
                if i == 0 or j == 0:
                    dp[i][j] = 1
                else:
                    dp[i][j] = min(dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]) + 1

                if dp[i][j] > max_size:
                    max_size = dp[i][j]
                    max_x = i
                    max_y = j

    return max_size, max_x - max_size + 2, max_y - max_size + 2


def main():
    n, m = map(int, input().split())

    matrix = [list(map(int, input().split())) for _ in range(n)]

    size, x, y = largest_square(matrix, n, m)

    print(size)
    print(x, y)


if __name__ == "__main__":
    main()
