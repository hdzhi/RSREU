def heap(n, size, index):
    large = index
    left = 2 * index + 1
    right = 2 * index + 2

    if left < size and n[left] > n[large]:
        large = left

    if right < size and n[right] > n[large]:
        large = right

    if large != index:
        n[index], n[large] = n[large], n[index]
        heap(n, size, large)


def heap_sort(n):
    a = len(n)
    for i in range(a, -1, -1):
        heap(n, a, i)

    for i in range(a - 1, 0, -1):
        n[i], n[0] = n[0], n[i]
        heap(n, i, 0)


k = int(input())
l = list(map(int, input().split()))
heap_sort(l)
print(*l)

