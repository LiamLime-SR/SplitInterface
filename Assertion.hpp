#pragma once

// assertion method for user input
namespace Assert {

    // assert that string is not empty
    static const std::string &assertHas(const std::string &next, const std::string &message) {

        if (next.empty()) throw std::invalid_argument("empty " + message);
        return next;
    }

    // assert that stream has at least a threshold of elements left
    static std::istream &assertHas(std::istream &stream, int count, const std::string &message) {

        auto pos = stream.tellg();

        for (int i = 0; i < count; i++) {
            std::string next;
            stream >> next;
            assertHas(next, message);
        }

        stream.seekg(pos);
        return stream;
    }

    // assert that stream has elements left
    static std::istream &assertHas(std::istream &stream, const std::string &message) {

        return assertHas(stream, 1, message);
    }

    // assert that integer is above 0
    static int assertPositive(int num, const std::string &message) {

        if (num <= 0) throw std::invalid_argument("nonpositive " + message);
        return num;
    }

    // assert that integer is valid argument for range up to max
    static int assertRange(int num, int max, const std::string &message) {

        if (num < 0 || num >= max) throw std::invalid_argument("outranged " + message);
        return num;
    }

    // assert that integers are equal
    static int assertEqual(int num1, int num2, const std::string &message) {

        if (num1 != num2) throw std::invalid_argument("unequal " + message);
        return num1;
    }

    // assert that file successfully opened
    static bool assertIsOpen(bool isOpen, const std::string &message) {

        if (!isOpen) throw std::invalid_argument("inaccessible " + message + " file");
        return isOpen;
    }

    // assert that key exists in hash map
    template<class K, class V>
    static const K &assertExist(const K &key, const std::map<K, V> &map, const std::string &message) {

        if (!map.count(key)) throw std::invalid_argument("undefined " + message);
        return key;
    }

    // assert that key does not yet exist in hash map
    template<class K, class V>
    static const K &assertNonexist(const K &key, const std::map<K, V> &map, const std::string &message) {

        if (map.count(key)) throw std::invalid_argument("predefined " + message);
        return key;
    }
}
