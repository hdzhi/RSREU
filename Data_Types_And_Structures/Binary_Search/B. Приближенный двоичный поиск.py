def approx_bin_search(arr, x):
    left = 0
    right = len(arr) - 1
    while right - left > 1:
        middle = (left + right) // 2
        if arr[middle] < x:
            left = middle
        else:
            right = middle
    if x - arr[left] <= arr[right] - x:
        return arr[left]
    else:
        return arr[right]


N, K = map(int, input().split())
N_elem = list(map(int, input().split()))
K_elem = list(map(int, input().split()))

for i in range(K):
    print(approx_bin_search(N_elem, K_elem[i]))