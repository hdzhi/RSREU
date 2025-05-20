#include <iostream>
#include <string>
#include <cmath>
#include <cstring>
#include <stdexcept>
#include <memory>

template <typename T, typename CharacteristicType>
class SinglyLinkedList // Объявление шаблонного класса односвязного списка
{
private:
    // Внутренняя структура узла списка
    struct Node
    {
        T data;                                            // Данные, хранящиеся в узле (тип T - шаблонный параметр)
        Node *next;                                        // Указатель на следующий узел в списке
        Node(const T &data) : data(data), next(nullptr) {} // Конструктор узла: инициализирует данные и указатель на следующий узел
    };

    Node *head;                           // Указатель на первый узел списка (голова списка)
    size_t length;                        // Текущая длина списка (количество элементов)
    CharacteristicType maxCharacteristic; // Максимально допустимая характеристика для добавляемых элементов

    // Функция для вычисления характеристики элемента (используется для проверки ограничений)
    CharacteristicType calculateCharacteristic(const T &elem) const
    {

        if constexpr (std::is_same_v<T, int> || std::is_same_v<T, float>)
        {
            return std::abs(elem);
        }
        else if constexpr (std::is_same_v<T, struct Vec2>)
        {
            return std::sqrt(elem.x * elem.x + elem.y * elem.y);
        }
        else
        {
            throw std::runtime_error("Unsupported type for characteristic calculation");
        }
    }

public:
    // Конструктор по умолчанию
    SinglyLinkedList(CharacteristicType maxCharacteristic)
        : head(nullptr), length(0), maxCharacteristic(maxCharacteristic) {}

    // Конструктор копирования
    SinglyLinkedList(const SinglyLinkedList &other)
        : head(nullptr), length(0), maxCharacteristic(other.maxCharacteristic)
    {
        Node *currentOther = other.head; // Указатель для перебора узлов в другом списке
        while (currentOther != nullptr)
        {
            insert(currentOther->data, length); // Вставляем данные из другого списка в конец текущего
            currentOther = currentOther->next;  // Переходим к следующему узлу в другом списке
        }
    }

    // Деструктор
    ~SinglyLinkedList()
    {
        clear(); // Вызываем функцию для очистки списка и освобождения памяти
    }

    // Оператор присваивания
    SinglyLinkedList &operator=(const SinglyLinkedList &other)
    {
        if (this != &other) // Проверка на самоприсваивание (чтобы не удалить данные, которые нужно скопировать)
        {
            clear();                                     // Очищаем текущий список перед присваиванием
            maxCharacteristic = other.maxCharacteristic; // копируем значение характеристики

            Node *currentOther = other.head; // Указатель для перебора узлов в другом списке
            while (currentOther != nullptr)
            {
                insert(currentOther->data, length); // Вставляем данные из другого списка в конец текущего
                currentOther = currentOther->next;  // Переходим к следующему узлу в другом списке
            }
        }
        return *this; // Возвращаем ссылку на текущий объект (для цепочечных присваиваний)
    }

    // Очистка списка (удаление всех элементов)
    void clear()
    {
        while (head != nullptr)
        {
            Node *temp = head; // Сохраняем указатель на текущую голову
            head = head->next; // Перемещаем голову на следующий узел
            delete temp;       // Удаляем сохраненный узел (освобождаем память)
        }
        length = 0; // Обнуляем длину списка
    }

    // Получение длины списка
    size_t getLength() const { return length; }

    // Проверка наличия элемента в списке
    bool isExist(const T &elem) const
    {
        Node *current = head; // Указатель для перебора узлов
        while (current != nullptr)
        {
            if (current->data == elem) // Сравниваем данные текущего узла с искомым элементом
            {
                return true; // Если элемент найден, возвращаем true
            }
            current = current->next; // Переходим к следующему узлу
        }
        return false; // Если элемент не найден, возвращаем false
    }

    // Вставка элемента в список на заданную позицию
    bool insert(const T &elem, size_t n)
    {
        if (calculateCharacteristic(elem) > maxCharacteristic) // Проверяем, не превышает ли характеристика элемента максимум
        {
            throw std::runtime_error("Element exceeds maximum characteristic"); // Если превышает, выбрасываем исключение
        }

        if (n > length) // Проверяем, не выходит ли позиция за границы списка
        {
            throw std::out_of_range("Invalid position for insertion"); // Если выходит, выбрасываем исключение
        }

        Node *newNode = new Node(elem); // Создаем новый узел с данными

        if (n == 0) // Если вставка в начало списка
        {
            newNode->next = head; // Указываем новому узлу на текущую голову
            head = newNode;       // Делаем новый узел новой головой
        }
        else
        {
            Node *current = head;              // Указатель для поиска позиции вставки
            for (size_t i = 0; i < n - 1; ++i) // Ищем узел, перед которым нужно вставить новый узел
            {
                current = current->next; // Переходим к следующему узлу
            }
            newNode->next = current->next; // Указываем новому узлу на узел, следующий за текущим
            current->next = newNode;       // Указываем текущему узлу на новый узел
        }
        length++; // Увеличиваем длину списка
        return true;
    }

    // Удаление элемента из списка на заданной позиции
    bool remove(const T &elem, size_t n)
    {
        if (n >= length) // Проверяем, не выходит ли позиция за границы списка
        {
            throw std::out_of_range("Invalid position for removal"); // Если выходит, выбрасываем исключение
        }

        if (n == 0) // Если удаление первого элемента
        {
            Node *temp = head; // Сохраняем указатель на текущую голову
            head = head->next; // Перемещаем голову на следующий узел
            delete temp;       // Удаляем сохраненный узел (освобождаем память)
        }
        else
        {
            Node *current = head;              // Указатель для поиска позиции удаления
            for (size_t i = 0; i < n - 1; ++i) // Ищем узел, перед которым нужно удалить следующий узел
            {
                current = current->next; // Переходим к следующему узлу
            }
            Node *temp = current->next; // Сохраняем указатель на удаляемый узел
            current->next = temp->next; // Указываем текущему узлу на узел, следующий за удаляемым
            delete temp;                // Удаляем сохраненный узел (освобождаем память)
        }
        length--; // Уменьшаем длину списка
        return true;
    }

    // Добавление элемента в начало списка
    void push_front(const T &elem)
    {
        if (calculateCharacteristic(elem) > maxCharacteristic) // Проверяем характеристику
        {
            throw std::runtime_error("Element exceeds maximum characteristic");
        }

        Node *newNode = new Node(elem); // Создаем новый узел
        newNode->next = head;           // Указываем новому узлу на текущую голову
        head = newNode;                 // Делаем новый узел новой головой
        length++;                       // Увеличиваем длину списка
    }

    // Удаление всех вхождений элемента из списка
    void remove_all(const T &elem)
    {
        Node *current = head; // Указатель для перебора узлов
        Node *prev = nullptr; // Указатель на предыдущий узел

        while (current != nullptr)
        {
            if (current->data == elem) // Если нашли элемент, который нужно удалить
            {
                if (prev == nullptr) // Если удаляем первый элемент
                {
                    head = current->next; // Перемещаем голову на следующий узел
                    delete current;       // Удаляем текущий узел
                    current = head;       // Перемещаем указатель current на новую голову
                }
                else
                {
                    prev->next = current->next; // Указываем предыдущему узлу на узел, следующий за текущим
                    delete current;             // Удаляем текущий узел
                    current = prev->next;       // Перемещаем указатель current на следующий за предыдущим
                }
                length--; // Уменьшаем длину списка
            }
            else
            {
                prev = current;          // Запоминаем текущий узел как предыдущий
                current = current->next; // Переходим к следующему узлу
            }
        }
    }

    // Удаление первого элемента из списка
    void pop_front()
    {
        if (head == nullptr) // Проверяем, не пуст ли список
        {
            throw std::runtime_error("List is empty"); // Если пуст, выбрасываем исключение
        }

        Node *temp = head; // Сохраняем указатель на текущую голову
        head = head->next; // Перемещаем голову на следующий узел
        delete temp;       // Удаляем сохраненный узел
        length--;          // Уменьшаем длину списка
    }

    // Оператор доступа к элементу по индексу (с возможностью изменения)
    T &operator[](size_t n)
    {
        if (n >= length) // Проверяем, не выходит ли индекс за границы списка
        {
            throw std::out_of_range("Index out of range"); // Если выходит, выбрасываем исключение
        }

        Node *current = head;          // Указатель для поиска нужного узла
        for (size_t i = 0; i < n; ++i) // Перебираем узлы до нужного индекса
        {
            current = current->next; // Переходим к следующему узлу
        }
        return current->data; // Возвращаем ссылку на данные найденного узла
    }

    // Константная версия оператора доступа к элементу по индексу (без возможности изменения)
    const T &operator[](size_t n) const
    {
        if (n >= length) // Проверяем, не выходит ли индекс за границы списка
        {
            throw std::out_of_range("Index out of range"); // Если выходит, выбрасываем исключение
        }

        Node *current = head;          // Указатель для поиска нужного узла
        for (size_t i = 0; i < n; ++i) // Перебираем узлы до нужного индекса
        {
            current = current->next; // Переходим к следующему узлу
        }
        return current->data; // Возвращаем константную ссылку на данные найденного узла
    }

    // Дружественный оператор вывода в поток
    friend std::ostream &operator<<(std::ostream &os, const SinglyLinkedList &list)
    {
        os << "List (Length: " << list.length << "): "; // Выводим длину списка
        Node *current = list.head;                      // Указатель для перебора узлов
        while (current != nullptr)
        {
            os << current->data << " "; // Выводим данные текущего узла
            current = current->next;    // Переходим к следующему узлу
        }
        os << std::endl; // Выводим символ новой строки
        return os;       // Возвращаем ссылку на поток (для цепочечных вызовов)
    }
};

// Специализация шаблона класса SinglyLinkedList для типа данных char*
template <typename CharacteristicType>
class SinglyLinkedList<char *, CharacteristicType>
{
private:
    // Внутренняя структура узла списка для char*
    struct Node
    {
        char *data;                                     // Указатель на строку (char*)
        Node *next;                                     // Указатель на следующий узел
        Node(char *data) : data(data), next(nullptr) {} // Конструктор узла
        ~Node() { delete[] data; }                      // Деструктор узла: освобождает память, выделенную под строку
    };

    Node *head;                           // Указатель на первый узел списка
    size_t length;                        // Длина списка
    CharacteristicType maxCharacteristic; // Максимальная характеристика для строк

    // Вычисление характеристики строки (длина)
    CharacteristicType calculateCharacteristic(const char *elem) const
    {
        if (elem == nullptr) // Проверяем, не является ли указатель нулевым
        {
            throw std::invalid_argument("Null pointer passed to calculateCharacteristic"); // Если является, выбрасываем исключение
        }
        return std::strlen(elem); // Возвращаем длину строки
    }

    // Функция для копирования строки
    char *copyString(const char *str) const
    {
        if (str == nullptr) // Проверяем, не является ли указатель нулевым
        {
            throw std::invalid_argument("Cannot copy null string"); // Если является, выбрасываем исключение
        }
        char *newStr = new char[std::strlen(str) + 1]; // Выделяем память для новой строки
        std::strcpy(newStr, str);                      // Копируем строку
        return newStr;                                 // Возвращаем указатель на новую строку
    }

public:
    // Конструктор
    SinglyLinkedList(CharacteristicType maxCharacteristic)
        : head(nullptr), length(0), maxCharacteristic(maxCharacteristic) {}

    // Конструктор копирования
    SinglyLinkedList(const SinglyLinkedList &other)
        : head(nullptr), length(0), maxCharacteristic(other.maxCharacteristic)
    {
        Node *currentOther = other.head; // Указатель для перебора узлов в другом списке
        while (currentOther != nullptr)
        {
            insert(copyString(currentOther->data), length); // Копируем строку и вставляем ее в текущий список
            currentOther = currentOther->next;              // Переходим к следующему узлу
        }
    }

    // Деструктор
    ~SinglyLinkedList()
    {
        clear(); // Очищаем список
    }

    // Оператор присваивания
    SinglyLinkedList &operator=(const SinglyLinkedList &other)
    {
        if (this != &other) // Проверка на самоприсваивание
        {
            clear();                                     // Очищаем текущий список
            maxCharacteristic = other.maxCharacteristic; // копируем значение характеристики

            Node *currentOther = other.head; // Указатель для перебора узлов в другом списке
            while (currentOther != nullptr)
            {
                insert(copyString(currentOther->data), length); // Копируем строку и вставляем ее в текущий список
                currentOther = currentOther->next;              // Переходим к следующему узлу
            }
        }
        return *this; // Возвращаем ссылку на текущий объект
    }

    // Очистка списка
    void clear()
    {
        while (head != nullptr)
        {
            Node *temp = head; // Сохраняем указатель на текущую голову
            head = head->next; // Перемещаем голову на следующий узел
            delete temp;       // Удаляем узел
        }
        length = 0; // Обнуляем длину
    }

    // Получение длины списка
    size_t getLength() const { return length; }

    // Проверка наличия строки в списке
    bool isExist(const char *elem) const
    {
        if (elem == nullptr) // Проверяем указатель
        {
            throw std::invalid_argument("Cannot search for null string"); // Если нуль, выбрасываем исключение
        }

        Node *current = head; // Перебираем узлы
        while (current != nullptr)
        {
            if (std::strcmp(current->data, elem) == 0) // Сравниваем строки
            {
                return true; // Найдено
            }
            current = current->next; // Далее
        }
        return false; // Не найдено
    }

    // Вставка строки в список
    bool insert(char *elem, size_t n)
    {
        if (elem == nullptr)
        {
            throw std::invalid_argument("Cannot insert null string");
        }

        if (calculateCharacteristic(elem) > maxCharacteristic)
        {
            delete[] elem;
            throw std::runtime_error("Element exceeds maximum characteristic");
        }

        if (n > length) // Проверка индекса
        {
            delete[] elem;
            throw std::out_of_range("Invalid position for insertion");
        }

        Node *newNode = new Node(elem); // Создаем новый узел

        if (n == 0) // Вставка в начало
        {
            newNode->next = head; // Новый узел указывает на текущую голову
            head = newNode;       // Новый узел становится головой
        }
        else
        {
            Node *current = head; // Перебираем до позиции вставки
            for (size_t i = 0; i < n - 1; ++i)
            {
                current = current->next; // Двигаемся по списку
            }
            newNode->next = current->next; // Новый узел указывает на узел, на который указывал текущий
            current->next = newNode;       // Текущий узел указывает на новый
        }
        length++; // Обновляем длину
        return true;
    }

    // Удаление строки из списка
    bool remove(const char *elem, size_t n)
    {
        if (elem == nullptr) // Проверяем указатель
        {
            throw std::invalid_argument("Cannot remove null string"); // Если нуль, выбрасываем исключение
        }

        if (n >= length) // Проверка индекса
        {
            throw std::out_of_range("Invalid position for removal"); // Выбрасываем исключение
        }

        if (n == 0) // Удаление первого элемента
        {
            Node *temp = head; // Запоминаем голову
            head = head->next; // Новая голова
            delete temp;       // Удаляем узел (вызовется ~Node(), который удалит char*)
        }
        else
        {
            Node *current = head; // Перебираем до позиции удаления
            for (size_t i = 0; i < n - 1; ++i)
            {
                current = current->next; // Двигаемся по списку
            }
            Node *temp = current->next; // Запоминаем удаляемый узел
            current->next = temp->next; // Обновляем указатель
            delete temp;                // Удаляем узел (вызовется ~Node(), который удалит char*)
        }
        length--; // Обновляем длину
        return true;
    }

    // Добавление строки в начало списка
    void push_front(char *elem)
    {
        if (elem == nullptr)
        {
            throw std::invalid_argument("Cannot push null string");
        }

        if (calculateCharacteristic(elem) > maxCharacteristic)
        {
            delete[] elem;
            throw std::runtime_error("Element exceeds maximum characteristic");
        }

        Node *newNode = new Node(elem);
        newNode->next = head;
        head = newNode;
        length++;
    }

    // Удаление всех вхождений строки из списка
    void remove_all(const char *elem)
    {
        if (elem == nullptr)
        {
            throw std::invalid_argument("Cannot remove null string");
        }

        Node *current = head;
        Node *prev = nullptr;

        while (current != nullptr)
        {
            if (std::strcmp(current->data, elem) == 0)
            {
                if (prev == nullptr)
                {
                    head = current->next;
                    delete current;
                    current = head;
                }
                else
                {
                    prev->next = current->next;
                    delete current;
                    current = prev->next;
                }
                length--;
            }
            else
            {
                prev = current;
                current = current->next;
            }
        }
    }

    // Удаление первого элемента из списка
    void pop_front()
    {
        if (head == nullptr)
        {
            throw std::runtime_error("List is empty");
        }

        Node *temp = head;
        head = head->next;
        delete temp;
        length--;
    }

    // Оператор доступа к строке по индексу
    char *operator[](size_t n)
    {
        if (n >= length)
        {
            throw std::out_of_range("Index out of range");
        }

        Node *current = head;
        for (size_t i = 0; i < n; ++i)
        {
            current = current->next;
        }
        return current->data;
    }

    // Константный оператор доступа к строке по индексу
    const char *operator[](size_t n) const
    {
        if (n >= length)
        {
            throw std::out_of_range("Index out of range");
        }

        Node *current = head;
        for (size_t i = 0; i < n; ++i)
        {
            current = current->next;
        }
        return current->data;
    }

    // Дружественный оператор вывода в поток
    friend std::ostream &operator<<(std::ostream &os, const SinglyLinkedList &list)
    {
        os << "List (Length: " << list.length << "): ";
        Node *current = list.head;
        while (current != nullptr)
        {
            os << current->data << " ";
            current = current->next;
        }
        os << std::endl;
        return os;
    }
};

// Структура для представления 2D вектора
struct Vec2
{
    float x; // Компонента x вектора
    float y; // Компонента y вектора

    // Перегрузка оператора == для сравнения векторов
    bool operator==(const Vec2 &other) const
    {
        return (x == other.x) && (y == other.y); // Векторы равны, если равны их компоненты
    }
};

// Перегрузка оператора вывода в поток для Vec2
std::ostream &operator<<(std::ostream &os, const Vec2 &vec)
{
    os << "(" << vec.x << ", " << vec.y << ")";
    return os;
}

// Главная функция программы
int main()
{
    try
    {
        // Test with int
        std::cout << "Testing with int:" << std::endl;
        SinglyLinkedList<int, int> intList(100); // Создаем список целых чисел с максимальной характеристикой 100
        intList.push_front(10);                  // Добавляем элемент 10 в начало списка
        intList.insert(20, 1);                   // Вставляем элемент 20 на позицию 1
        intList.insert(5, 0);                    // Вставляем элемент 5 на позицию 0
        std::cout << intList;                    // Выводим список в консоль

        intList.remove_all(10); // Удаляем все вхождения элемента 10
        std::cout << intList;   // Выводим список

        intList.pop_front();  // Удаляем первый элемент
        std::cout << intList; // Выводим список

        std::cout << "Element at index 0: " << intList[0] << std::endl; // Выводим элемент по индексу

        SinglyLinkedList<int, int> intList2 = intList; // Создаем копию списка
        std::cout << "Copied list: " << intList2;      // Выводим копию

        intList2 = intList;                         // Присваиваем списку значение другого списка
        std::cout << "Assigned list: " << intList2; // Выводим список

        // Test with float
        std::cout << "\nTesting with float:" << std::endl;
        SinglyLinkedList<float, float> floatList(50.0f); // Создаем список вещественных чисел
        floatList.push_front(10.5f);
        floatList.insert(20.2f, 1);
        floatList.insert(5.1f, 0);
        std::cout << floatList;

        floatList.remove_all(10.5f);
        std::cout << floatList;

        floatList.pop_front();
        std::cout << floatList;

        std::cout << "Element at index 0: " << floatList[0] << std::endl;

        SinglyLinkedList<float, float> floatList2 = floatList;
        std::cout << "Copied list: " << floatList2;

        floatList2 = floatList;
        std::cout << "Assigned list: " << floatList2;

        // Test with char*
        std::cout << "\nTesting with char*:" << std::endl;
        SinglyLinkedList<char *, int> charList(20); // Создаем список строк (C-style)

        char *str1 = new char[6];   // Выделяем память под строку
        std::strcpy(str1, "hello"); // Копируем строку
        char *str2 = new char[6];
        std::strcpy(str2, "world");
        char *str3 = new char[4];
        std::strcpy(str3, "C++");

        try
        {
            charList.push_front(str1); // Добавляем строку в список
            charList.insert(str2, 1);  // Вставляем строку в список
            charList.insert(str3, 0);  // Вставляем строку в список
        }
        catch (const std::exception &e)
        {
            std::cerr << "Error during char* insertion: " << e.what() << std::endl;
        }

        std::cout << charList; // Выводим список

        charList.remove_all("hello"); // Удаляем все вхождения строки "hello"
        std::cout << charList;        // Выводим список

        charList.pop_front();  // Удаляем первый элемент
        std::cout << charList; // Выводим список

        std::cout << "Element at index 0: " << charList[0] << std::endl; // Выводим элемент по индексу

        SinglyLinkedList<char *, int> charList2 = charList; // Создаем копию списка
        std::cout << "Copied list: " << charList2;          // Выводим копию

        charList2 = charList;                        // Присваиваем списку значение другого списка
        std::cout << "Assigned list: " << charList2; // Выводим список

        // Test with Vec2
        std::cout << "\nTesting with Vec2:" << std::endl;
        SinglyLinkedList<Vec2, float> vecList(10.0f); // Создаем список векторов
        Vec2 v1 = {3.0f, 4.0f};                       // Создаем векторы
        Vec2 v2 = {1.0f, 1.0f};
        Vec2 v3 = {6.0f, 8.0f};

        vecList.push_front(v1); // Добавляем вектор в список
        vecList.insert(v2, 1);  // Вставляем вектор в список
        vecList.insert(v3, 0);  // Вставляем вектор в список
        std::cout << vecList;   // Выводим список

        vecList.remove_all(v1); // Удаляем все вхождения вектора v1
        std::cout << vecList;   // Выводим список

        vecList.pop_front();  // Удаляем первый элемент
        std::cout << vecList; // Выводим список

        std::cout << "Element at index 0: " << vecList[0] << std::endl; // Выводим элемент по индексу

        SinglyLinkedList<Vec2, float> vecList2 = vecList; // Создаем копию списка
        std::cout << "Copied list: " << vecList2;         // Выводим копию

        vecList2 = vecList;                         // Присваиваем списку значение другого списка
        std::cout << "Assigned list: " << vecList2; // Выводим список
        delete[] str1;
        delete[] str2;
        delete[] str3;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl; // Ловим и выводим сообщения об исключениях
        return 1;

        return 0;
    }
}