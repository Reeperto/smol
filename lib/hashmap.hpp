#include <iostream>
#include <ostream>
#include <stdexcept>

namespace smol
{

template <typename Key> std::size_t get_hash(const Key &item, int size)
{
    static_assert(
        sizeof(Key) != sizeof(Key),
        "There is no hash function defined for the given key type.");
    return 0;
}

template <> inline std::size_t get_hash<int>(const int &item, int size)
{
    int x = item;
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = (x >> 16) ^ x;
    return (x % size + size) % size;
}

template <typename K, typename V> struct HashMap
{

  private:
    struct HashItem
    {
        K key;
        V value;
        bool filled;

        V &operator=(const V &other)
        {
            value = other;
            filled = true;
        }
    };

    HashItem *table;
    int size, capacity;

  public:
    HashMap() : table{new HashItem[32]{}}, size{0}, capacity{2} {}

    void put(const K &key, const V &value)
    {
        if (size == capacity)
        {
            rehash();
        };

        std::size_t hash = get_hash<K>(key, capacity);
        table[quadric_probe(table, hash, capacity)] =
            HashItem{key, value, true};

        ++size;
    }

    V &get(const K &key)
    {
        int position = find(key);

        if (position != -1)
        {
            return table[position].value;
        } else
        {
            throw std::out_of_range{"Key not found in HashMap"};
        }
    }

    HashItem &operator[](const K &key)
    {
        int position = find(key);

        if (position != -1)
        {
            return table[position];
        } else
        {
            throw std::out_of_range{"Key not found in HashMap"};
        }
    }

    void remove(const K &key)
    {
        int position = find(key);

        if (position != -1)
        {
            table[position].filled = false;
        }
    }

    void rehash()
    {
        int old_capacity = capacity;
        int new_capacity = capacity * 2;

        HashItem *new_table = new HashItem[new_capacity]{};

        for (int i = 0; i < old_capacity; ++i)
        {
            if (table[i].filled)
            {
                int new_position = quadric_probe(
                    new_table, get_hash(table[i].key, new_capacity),
                    new_capacity);

                new_table[new_position] = table[i];
            }
        }

        delete[] table;

        table = new_table;
        capacity = new_capacity;
    }

    void print(std::ostream &out) const
    {
        for (int i = 0; i < capacity; ++i)
        {
            if (table[i].filled)
            {
                out << table[i].key << ": " << table[i].value << std::endl;
            }
        }
    }

    ~HashMap() { delete[] table; }

  private:
    int find(const K &key) // TODO: This could be better probably.
                           // Potentially also combined with quadric_probe
    {
        std::size_t position = get_hash<K>(key, capacity);

        if (table[position].key == key)
        {
            return position;
        }

        std::size_t starting_position = position;
        int counter = 2;
        int current_factor = 1;

        while (table[position].filled && table[position].key != key &&
               starting_position != position)
        {
            position = (position + current_factor) % capacity;
            current_factor += counter;
            ++counter;
        }

        return starting_position == position ? -1 : position;
    }

    static int quadric_probe(HashItem *table, std::size_t hash,
                             int capacity)
    {
        int counter = 2;
        int current_factor = 1;
        int new_position = hash;

        while (table[new_position].filled)
        {
            new_position = (hash + current_factor) % capacity;
            current_factor += counter;
            ++counter;
        }

        return new_position;
    }
};

} // namespace smol
