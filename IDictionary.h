#ifndef IDICTIONARY_H
#define IDICTIONARY_H

#include "HashTable.h"

template<typename KeyType, typename ValueType, typename Hash = std::hash<KeyType>>
class IDictionary {
private:
    HashMap<KeyType, ValueType, Hash> hashMap;

public:
    IDictionary() = default;

    void Add(const KeyType& key, const ValueType& value) {
        hashMap.Add(key, value);
    }

    void Remove(const KeyType& key) {
        hashMap.Remove(key);
    }

    ValueType Get(const KeyType& key) const {
        return hashMap.Get(key);
    }

    bool Contains(const KeyType& key) const {
        return hashMap.ContainsKey(key);
    }

    int Size() const {
        return hashMap.GetCount();
    }

    KeyType GetKeyAtIndex(int index) const {
        int currentIndex = 0;
        for (const auto &entry : hashMap.GetBuckets()) { // Предполагается, что `GetBuckets` возвращает вектор всех корзин
            auto current = entry;
            while (current != nullptr) {
                if (currentIndex == index) {
                    return current->key;
                }
                currentIndex++;
                current = current->next;
            }
        }
        throw std::out_of_range("Index out of range");
    }

};

#endif //IDICTIONARY_H
