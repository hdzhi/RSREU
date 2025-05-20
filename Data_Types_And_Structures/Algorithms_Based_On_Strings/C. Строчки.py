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

def check(t, s):
    if s == t:
        print(0)
        exit()

    if len(t) != len(s):
        print(-1)
        exit()

    dbl = t + t  # Создаем строку, состоящую из t, повторенной дважды

    # Вычисляем префикс-функцию для нового комбинированного текста
    p = prefix_function(s + '#' + dbl)

    # Проходим по всем индексам, начиная с длины s + 1, до конца dbl
    for i in range(len(s) + 1, len(dbl) + len(s) + 1):
        # Если нашли длину совпадения, выводим результат
        if p[i] == len(s):
            print(len(s) - (i - 2 * len(s)))
            exit()

    print(-1)

t = input()
s = input()

check(t, s)
