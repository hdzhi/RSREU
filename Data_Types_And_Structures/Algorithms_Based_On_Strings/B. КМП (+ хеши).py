PRIME, MOD = 31, 10**9 + 7

def prime_power(n):
    # Функция для вычисления степеней числа PRIME до n
    pow = [1] * (n + 1)  # Массив для хранения степеней
    for i in range(1, n + 1):
        pow[i] = (pow[i - 1] * PRIME) % MOD  # Вычисляем каждую степень как (предыдущая степень * PRIME) % MOD
    return pow

def hash_func(s):
    hashes = [0] * (len(s) + 1)  # Массив для хранения хешей префиксов
    for i in range(len(s)):
        # Вычисляем хеш текущего префикса
        hashes[i + 1] = (hashes[i] * PRIME + (ord(s[i]) - ord("a") + 1)) % MOD
    return hashes  # Возвращаем массив хешей

def get_hash(p, hashes, l, r):
    # Функция для вычисления хеша строки с l по r
    result = (hashes[r + 1] - hashes[l] * p[r - l + 1]) % MOD  # Вычисляем хеш по формуле
    return result  # Возвращаем хеш

text = input()
s = input()

hashes = hash_func(text)
p = prime_power(len(text))

pattern = hash_func(s)[-1]

# Список для хранения позиций, где найден паттерн
positions = []
# Проходим по всем подстрокам длины len(s) в тексте
for i in range(len(text) - len(s) + 1):
    # Если хеш текущей подстроки равен хешу паттерна, добавляем позицию в список
    if get_hash(p, hashes, i, i + len(s) - 1) == pattern:
        positions.append(i)

# Выводим все позиции, где найден паттерн в тексте
print(" ".join(map(str, positions)))
