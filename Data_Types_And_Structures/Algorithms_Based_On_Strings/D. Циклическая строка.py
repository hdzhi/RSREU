
def prefix_function(s):
    prefix = [0] * len(s)  # Массив для хранения значений префикс-функции
    for i in range(1, len(s)):
        j = prefix[i - 1]  # Начинаем с значения префикс-функции для предыдущего символа
        # Проверяем, совпадают ли символы s[j] и s[i]
        while j > 0 and s[j] != s[i]:
            j = prefix[j - 1]  # Уменьшаем j до последнего подходящего префикса
        if s[j] == s[i]:
            j += 1  # Если символы совпали, увеличиваем значение j
        prefix[i] = j  # Записываем найденное значение в массив
    return prefix

t = input()
n = len(t)
pref = prefix_function(t)
length = n - pref[-1]

print(length)
