def calculate_next_failure_time(n, fish_counts):
    aquariums = []

    # Считываем начальные значения рыб и добавляем их в список
    for i in range(n):
        f = fish_counts[i]
        aquariums.append((max(1000 - f, 1), i, f + 1))  # (время до следующей рыбы, индекс аквариума, количество рыб)

    time = 0
    pos = 0

    while True:
        # Сортируем список аквариумов по времени до следующей рыбки
        aquariums.sort()
        next_time, ind, f = aquariums[0]  # Получаем ближайшее событие из списка

        # Проверяем, может ли Игорь записать следующую рыбку
        if time + abs(ind - pos) > next_time:
            return next_time  # Возвращаем время, когда Игорь не успел записать

        # Обновляем время и позицию
        time = next_time
        pos = ind

        # Обновляем количество рыбок и время до следующей
        aquariums[0] = (time + max(1000 - f, 1), ind, f + 1)  # Обновляем значения для текущего аквариума


# Основная часть программы
n = int(input())
fish_counts = [int(input()) for _ in range(n)]

# Вызываем функцию и выводим результат
next_failure_time = calculate_next_failure_time(n, fish_counts)
print(next_failure_time)
