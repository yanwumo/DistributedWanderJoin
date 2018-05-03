//
// Created by Ben on 2018/4/29.
//

#ifndef DISTRIBUTEDWANDERJOIN_INDEX_H
#define DISTRIBUTEDWANDERJOIN_INDEX_H

#include <unordered_map>
#include <vector>
#include <random>
#include <chrono>

template<class K, class V>
class BaseIndex {
private:
    std::mt19937 randomNumberGenerator;

protected:
    size_t size;

public:
    BaseIndex() {
        auto seed = std::chrono::system_clock::now().time_since_epoch().count();
        randomNumberGenerator.seed(static_cast<unsigned int>(seed));
    }

    size_t getRandomNumberOfSize(const size_t &size) {
        std::uniform_int_distribution<size_t> distribution(0, size - 1);
        return distribution(randomNumberGenerator);
    }

    virtual void insert(const K &key, V &value) = 0;

    virtual V *sampleFromEntriesWhoseKeyEqualTo(const K &key) = 0;
};



template<class K, class V>
class PrimaryKey : public BaseIndex<K, V> {
private:
    std::unordered_map<K, V *> map;

public:
    void reserve(const size_t &size);

    void insert(const K &key, V &value) override;

    V *sampleFromEntriesWhoseKeyEqualTo(const K &key) override;
};

template<class K, class V>
void PrimaryKey<K, V>::reserve(const size_t &size){
    map.reserve(size);
}

template<class K, class V>
void PrimaryKey<K, V>::insert(const K &key, V &value) {
    map.insert(std::make_pair(key, &value));
}

template<class K, class V>
V *PrimaryKey<K, V>::sampleFromEntriesWhoseKeyEqualTo(const K &key) {
    const auto iter = map.find(key);
    if (iter != map.end()) {
        // Found
        return iter->second;
    } else {
        // Not found
        return nullptr;
    }
}



template<class K, class V>
class SecondaryIndex : public BaseIndex<K, V> {
private:
    std::unordered_map<K, size_t> map;
    std::vector<std::vector<V *>> entries;

public:
    void reserve(const size_t &size);

    void insert(const K &key, V &value) override;

    V *sampleFromEntriesWhoseKeyEqualTo(const K &key) override;

    template<class K>
    size_t getNumberOfEntriesWhoseKeyEqualTo(const K &key);
};

template<class K, class V>
void SecondaryIndex<K, V>::reserve(const size_t &size) {
    map.reserve(size);
}

template<class K, class V>
void SecondaryIndex<K, V>::insert(const K &key, V &value) {
    const auto iter = map.find(key);
    if (iter != map.end()) {
        // Found
        entries[iter->second].push_back(&value);
    } else {
        // Not found
        entries.push_back(std::vector<V *>{&value});
        map.insert(std::make_pair(key, entries.size() - 1));
    }
}

template<class K, class V>
size_t SecondaryIndex<K, V>::getNumberOfEntriesWhoseKeyEqualTo(const K &key) {
    const auto iter = map.find(key);
    if (iter != map.end()) {
        // Found
        const std::vector<V *> &result = entries[iter->second];
        return result.size();
    } else {
        // Not found
        return 0;
    }
}

template<class K, class V>
V *SecondaryIndex<K, V>::sampleFromEntriesWhoseKeyEqualTo(const K &key) {
    const auto iter = map.find(key);
    if (iter != map.end()) {
        // Found
        const std::vector<V *> &result = entries[iter->second];
        // Sample one from them
        return result[BaseIndex<K, V>::getRandomNumberOfSize(result.size())];
    } else {
        // Not found
        return nullptr;
    }
}


#endif //DISTRIBUTEDWANDERJOIN_INDEX_H
