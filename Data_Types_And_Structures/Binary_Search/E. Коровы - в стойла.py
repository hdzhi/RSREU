def good(boxes, k, r):
    cows_count = 1
    last_box = boxes[0]
    for box in boxes[1:]:
        if box - last_box >= r:
            cows_count += 1
            last_box = box
    return cows_count >= k


n, k = map(int, input().split())
a = list(map(int, input().split()))
l = 0
r = a[-1] - a[0] + 1
while r - l > 1:
    m = (l + r) // 2
    if good(a, k, m):
        l = m
    else:
        r = m
print(l)
