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
    void insert(const K &key, const V &value);

};


#endif //DISTRIBUTEDWANDERJOIN_INDEX_H
