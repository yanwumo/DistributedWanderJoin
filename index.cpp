//
// Created by Ben on 2018/4/29.
//

#include "index.h"
/*
template<class K, class V>
void SecondaryIndex<K, V>::insert(const K &key, const V &value) {
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
*/