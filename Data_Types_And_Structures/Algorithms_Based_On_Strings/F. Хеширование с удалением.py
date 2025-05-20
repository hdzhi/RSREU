class StringSet:
    def init(self):
        # Инициализируем множество для хранения строк
        self.data = set()

    def add(self, string):
        # Добавляем строку в множество
        self.data.add(string)

    def remove(self, string):
        # Удаляем строку из множества, если она существует
        self.data.discard(string)

    def contains(self, string):
        # Проверяем, содержится ли строка в множестве
        return string in self.data


# Создаем экземпляр класса StringSet
string_set = StringSet()

while True:
    text = input()

    if text == "#":
        break

    op, word = text.split()

    # Если операция равна "+", добавляем строку в множество
    if op == "+":
        string_set.add(word)

    # Если операция равна "-", удаляем строку из множества
    elif op == "-":
        string_set.remove(word)

    # Если операция равна "?", проверяем наличие строки в множестве и выводим результат
    elif op == "?":
        print("YES" if string_set.contains(word) else "NO")
