def ba_bah(N):
    safe = [0] * (N + 1)

    # Базовые случаи
    safe[0] = 1
    safe[1] = 3

    for i in range(2, N + 1):
        safe[i] = 2 * safe[i - 1] + 2 * safe[i - 2]

    return safe[N]


N = int(input())
print(ba_bah(N))
