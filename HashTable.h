#ifndef TRAINING_SFML_IDICTIONARY_H
#define TRAINING_SFML_IDICTIONARY_H
#include <iostream>
#include <vector>
#include <stdexcept>

// Пример простой хеш-функции для типа int
struct IntHash {
    size_t operator()(const int key) const {
        // Просто используем значение ключа как хеш
        return static_cast<size_t>(key);
    }
};

// Шаблон хеш-таблицы
template <typename TKey, typename TValue, typename Hash = std::hash<TKey>>
class HashMap {
private:
    struct Entry {
        TKey key;
        TValue value;
        Entry* next;  // Для цепочек коллизий
    };

    static constexpr size_t INITIAL_CAPACITY = 10;
    static const double LOAD_FACTOR_THRESHOLD;

    std::vector<Entry*> table;
    size_t count;
    Hash hashFunction;

    size_t getBucketIndex(const TKey& key) const {
        // Вычисляем индекс корзины с использованием хеш-функции
        return hashFunction(key) % table.size();
    }

    void resizeTable() {
        // Увеличиваем размер таблицы при превышении порога
        if (static_cast<double>(count) / table.size() > LOAD_FACTOR_THRESHOLD) {
            std::vector<Entry*> newTable(table.size() * 2, nullptr);

            // Перехешируем все элементы в новую таблицу
            for (const auto& bucket : table) {
                Entry* current = bucket;
                while (current != nullptr) {
                    Entry* next = current->next;

                    size_t newIndex = hashFunction(current->key) % newTable.size();
                    current->next = newTable[newIndex];
                    newTable[newIndex] = current;

                    current = next;
                }
            }

            table = std::move(newTable);
        }
    }

public:
    HashMap() : table(INITIAL_CAPACITY, nullptr), count(0) {}

    int GetCount() const {
        return static_cast<int>(count);
    }

    void Add(const TKey& key, const TValue& value) {
        size_t index = getBucketIndex(key);

        // Проверяем, есть ли уже элемент с таким ключом
        Entry* current = table[index];
        while (current != nullptr) {
            if (current->key == key) {
                throw std::invalid_argument("Key already exists in the dictionary");
            }
            current = current->next;
        }

        // Создаем новую запись
        Entry* newEntry = new Entry{key, value, table[index]};
        table[index] = newEntry;

        count++;
        resizeTable();
    }

    TValue Get(const TKey& key) const {
        size_t index = getBucketIndex(key);

        // Ищем элемент с заданным ключом
        Entry* current = table[index];
        while (current != nullptr) {
            if (current->key == key) {
                return current->value;
            }
            current = current->next;
        }

        throw std::out_of_range("Key not found in the dictionary");
    }

    bool ContainsKey(const TKey& key) const {
        size_t index = getBucketIndex(key);

        // Проверяем, есть ли элемент с заданным ключом
        Entry* current = table[index];
        while (current != nullptr) {
            if (current->key == key) {
                return true;
            }
            current = current->next;
        }

        return false;
    }

    void Remove(const TKey& key) {
        size_t index = getBucketIndex(key);

        // Удаляем элемент с заданным ключом, если он существует
        Entry* current = table[index];
        Entry* prev = nullptr;

        while (current != nullptr) {
            if (current->key == key) {
                if (prev == nullptr) {
                    table[index] = current->next;
                } else {
                    prev->next = current->next;
                }

                delete current;
                count--;
                return;
            }

            prev = current;
            current = current->next;
        }

        throw std::out_of_range("Key not found in the dictionary");
    }

    std::vector<Entry*> GetBuckets() const {
        return table;
    }
};

// Инициализация статической константы LOAD_FACTOR_THRESHOLD
template <typename TKey, typename TValue, typename Hash>
const double HashMap<TKey, TValue, Hash>::LOAD_FACTOR_THRESHOLD = 0.75;


#endif //TRAINING_SFML_IDICTIONARY_H
