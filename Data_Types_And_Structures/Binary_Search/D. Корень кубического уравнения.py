def Root_Of_Cubic_Equasion(a, b, c, d):
    left = -10 ** 10
    right = 10 ** 10
    e = 1e-7

    while right - left > e:
        middle = (left + right) / 2
        if a * middle ** 3 + b * middle ** 2 + c * middle + d == 0:
            return middle
        elif (a * middle ** 3 + b * middle ** 2 + c * middle + d) * \
                (a * left ** 3 + b * left ** 2 + c * left + d) < 0:
            right = middle
        else:
            left = middle

    return round(((left + right) / 2), 6)


a, b, c, d = map(int, input().split())
root = Root_Of_Cubic_Equasion(a, b, c, d)
print(f'{root:.6f}')
