//
// Created by Ben on 2018/4/29.
//

#ifndef DISTRIBUTEDWANDERJOIN_INDEX_H
#define DISTRIBUTEDWANDERJOIN_INDEX_H

#include <unordered_map>
#include <vector>

template <class K, class V>
class SecondaryIndex {
private:
    std::unordered_map<K, size_t> map;
    std::vector<std::vector<V *>> entries;

public:
    void insert(const K &key, V &value);

};

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


#endif //DISTRIBUTEDWANDERJOIN_INDEX_H
