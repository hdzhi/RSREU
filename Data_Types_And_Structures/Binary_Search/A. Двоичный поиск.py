def binary_search(arr, x):
    left = 0
    right = len(arr) - 1

    while left <= right:
        middle = (left + right) // 2
        if arr[middle] == x:
            return 'YES'
        elif arr[middle] < x:
            left = middle + 1
        else:
            right = middle - 1
    return 'NO'


N, K = map(int, input().split())
N_elem = list(map(int, input().split()))
K_elem = list(map(int, input().split()))

for i in range(K):
    print(binary_search(N_elem, K_elem[i]))