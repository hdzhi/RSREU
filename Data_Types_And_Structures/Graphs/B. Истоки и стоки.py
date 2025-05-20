n = int(input())
matrix = []

for _ in range(n):
    matrix.append(list(map(int, input().split())))

sources = []
sinks = []

for i in range(n):
    source_node = True
    sink_node = True

    for j in range(n):
        if matrix[j][i] == 1:
            source_node = False
            break

    for j in range(n):
        if matrix[i][j] == 1:
            sink_node = False
            break

    if source_node:
        sources.append(i + 1)
    if sink_node:
        sinks.append(i + 1)

print(len(sources))
for source in sorted(sources):
    print(source)

print(len(sinks))
for sink in sorted(sinks):
    print(sink)
