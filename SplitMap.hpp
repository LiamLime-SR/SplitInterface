#pragma once
#include <map>
#include "Time.hpp"

// key wrapper for hash map
template<class K>
class HasMapKey : public StreamIO<HasMapKey<K>> {

private:

    // value of key
    K key;

public:

    // constructor

    explicit HasMapKey() : key(K()) {}

    explicit HasMapKey(K key) : key(std::move(key)) {}

    // getter

    const K &getKey() const { return key; };

    // stream operator

    friend std::ostream &operator<<(std::ostream &stream, const HasMapKey &a) { return stream << a.key; }

    // file io

    const std::ostream &exportFull(std::ostream &stream, bool newObject) const override {

        if (newObject) key.exportFull(stream, true);
        return stream;
    }

    static HasMapKey *importFull(std::istream &stream, HasMapKey *result, bool newObject) {

        if (newObject) {
            K k;
            K::importFull(stream, &k, true);
            *result = HasMapKey(k);
        }

        return result;
    }
};

// hash map wrapper for file io
template<class K, class V>
class MapInstance : public StreamIO<MapInstance<K, V>> {

public:

    // value of map
    std::map<K, V> map;

public:

    // map operation

    const V &getValue(const K &key) const { return map.find(key)->second; }

    const V &addValue(const V &value) { return map.insert({value.getKey(), value}).first->second; }

    V delValue(const K &key) {

        V value = getValue(key);
        map.erase(key);
        return value;
    }

    // getter

    const std::map<K, V> &getMap() const { return map; };

    // transfer all to this map

    void transfer(const MapInstance<K, V> &a) {

        for (const auto &it: a.map) addValue(it.second);
    }

    // stream operator

    friend std::ostream &operator<<(std::ostream &stream, const MapInstance &a) {

        for (const auto &it: a.map) stream << it.second << std::endl;
        return stream;
    }

    friend std::istream &operator>>(std::istream &stream, const MapInstance &a) {

        for (const auto &it: a.map) stream >> it.second;
        return stream;
    }

    // file io

    const std::ostream &exportFull(std::ostream &stream, bool newObject) const override {

        if (newObject) {
            stream << map.size() << " ";
            for (const auto &it: map) it.second.exportFull(stream, true);
        }

        return stream;
    }

    static MapInstance *importFull(std::istream &stream, MapInstance *result, bool newObject) {

        if (newObject) {

            int size;
            stream >> size;
            *result = MapInstance();

            for (int i = 0; i < size; i++) {
                V v;
                V::importFull(stream, &v, true);
                result->addValue(v);
            }
        }

        return result;
    }
};

// name wrapper for hash key
class HasName : public HasMapKey<Name> {

public:

    // constructor

    explicit HasName() : HasMapKey(Name()) {}

    explicit HasName(const std::string& name) : HasMapKey(Name(name)) {}

    // file io

    static HasName *importFull(std::istream &stream, HasName *result, bool newObject) {

        HasMapKey::importFull(stream, result, newObject);
        return result;
    }
};

// moment wrapper for hash key
class HasMoment : public HasMapKey<Moment> {

public:

    // constructor

    explicit HasMoment() : HasMapKey(Moment()) {}

    explicit HasMoment(const Moment &moment) : HasMapKey(moment) {}

    // file io

    static HasMoment *importFull(std::istream &stream, HasMoment *result, bool newObject) {

        HasMapKey::importFull(stream, result, newObject);
        return result;
    }
};

// hash map wrapper for name
template<class V>
class NamedMap : public MapInstance<Name, V> {

public:

    // file io

    static NamedMap *importFull(std::istream &stream, NamedMap *result, bool newObject) {

        MapInstance<Name, V>::importFull(stream, result, newObject);
        return result;
    }
};

// hash map wrapper for moment
template<class V>
class MomentMap : public MapInstance<Moment, V> {

public:

    // file io

    static MomentMap *importFull(std::istream &stream, MomentMap *result, bool newObject) {

        MapInstance<Moment, V>::importFull(stream, result, newObject);
        return result;
    }
};
