from math import sqrt


def search(c):
    left = 0
    right = c
    while left <= right:
        middle = (right + left) / 2
        if c == middle ** 4 + middle:
            return f'{sqrt(middle):.6f}'
        elif middle ** 2 + sqrt(middle) < c:
            left = middle + 0.000001
        else:
            right = middle - 0.000001
    return (left + right) / 2


c = float(input())
print(search(c))

