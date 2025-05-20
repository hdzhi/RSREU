
n = int(input()) # Размер матрицы
matrix = []
# Считываем строки матрицы
for _ in range(n):
    r = list(map(int, input().split()))
    matrix.append(r)

is_simple = True

for i in range(n):
    # Проверяем, равен ли элемент на главной диагонали нулю
    if matrix[i][i] != 0:
        is_simple = False
        break  # Выходим из цикла из-за несоответствия условию
    for j in range(n):
        if matrix[i][j] != matrix[j][i]:
            is_simple = False
            break
    if not is_simple:
        break

if is_simple:
    print("YES")
else:
    print("NO")
