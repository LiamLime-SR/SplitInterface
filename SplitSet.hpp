#pragma once
#include "Time.hpp"

// pointer to array
template<class E>
class PointerSet : public StreamIO<PointerSet<E>> {

private:

    // indefinitely sized array
    int size;
    E *set;

public:

    // constructor

    explicit PointerSet() : size(0) {}

    explicit PointerSet(int size) : size(size), set(new E[size]) {}

    // getter

    int getSize() const { return size; }

    E *getSet() const { return set; }

    // copy elements to this array

    void copy(const PointerSet &a) const { std::copy(a.set, a.set + size, set); }

    // stream operator

    friend std::ostream &operator<<(std::ostream &stream, const PointerSet &a) {

        for (int i = 0; i < a.size; i++) stream << a.set[i] << " ";
        return stream;
    }

    friend std::istream &operator>>(std::istream &stream, const PointerSet &a) {

        for (int i = 0; i < a.size; i++) stream >> a.set[i];
        return stream;
    }

    // file io

    const std::ostream &exportFull(std::ostream &stream, bool newObject) const override {

        if (newObject) stream << size << " ";
        for (int i = 0; i < size; i++) set[i].exportFull(stream, true);
        return stream;
    }

    static PointerSet *importFull(std::istream &stream, PointerSet *result, bool newObject) {

        if (newObject) {
            int size;
            stream >> size;
            *result = PointerSet(size);
        }

        for (int i = 0; i < result->size; i++) {
            E &e = result->set[i];
            E::importFull(stream, &e, true);
        }

        return result;
    }
};

// pointer to array of period
class IntervalSet : public PointerSet<Period> {

public:

    // constructor

    explicit IntervalSet() : PointerSet(0) {}

    explicit IntervalSet(int size) : PointerSet(size) {}

    // summation

    Period sum(int start, int end) const {

        return std::accumulate(getSet() + start, getSet() + end, Period(0));
    }

    Period sum() const { return sum(0, getSize()); }

    Period sumAsPrefix(int start, int end) const { return getSet()[end] - getSet()[start]; }

    Period sumAsPrefix() const { return sumAsPrefix(0, getSize() - 1); }

    Period asPrefix(int index) const { return sumAsPrefix(index, index + 1); }

    IntervalSet prefixSum() const {

        IntervalSet result(getSize() + 1);
        for (int i = 0; i < getSize(); i++) result.getSet()[i + 1] = result.getSet()[i] + getSet()[i];
        return result;
    }

    // arithmetic operator

    IntervalSet operator+(const IntervalSet &a) const {

        IntervalSet result(getSize());
        for (int i = 0; i < getSize(); i++) result.getSet()[i] = getSet()[i] + a.getSet()[i];
        return result;
    }

    IntervalSet operator-(const IntervalSet &a) const {

        IntervalSet result(getSize());
        for (int i = 0; i < getSize(); i++) result.getSet()[i] = getSet()[i] - a.getSet()[i];
        return result;
    }

    IntervalSet operator*(double a) const {

        IntervalSet result(getSize());
        for (int i = 0; i < getSize(); i++) result.getSet()[i] = getSet()[i] * a;
        return result;
    }

    IntervalSet operator/(double a) const {

        IntervalSet result(getSize());
        for (int i = 0; i < getSize(); i++) result.getSet()[i] = getSet()[i] / a;
        return result;
    }

    const IntervalSet &operator+=(const IntervalSet &a) const {

        for (int i = 0; i < getSize(); i++) getSet()[i] += a.getSet()[i];
        return *this;
    }

    const IntervalSet &operator-=(const IntervalSet &a) const {

        for (int i = 0; i < getSize(); i++) getSet()[i] -= a.getSet()[i];
        return *this;
    }

    const IntervalSet &operator*=(double a) const {

        for (int i = 0; i < getSize(); i++) getSet()[i] *= a;
        return *this;
    }

    const IntervalSet &operator/=(double a) const {

        for (int i = 0; i < getSize(); i++) getSet()[i] /= a;
        return *this;
    }

    // file io

    static IntervalSet *importFull(std::istream &stream, IntervalSet *result, bool newObject) {

        PointerSet::importFull(stream, result, newObject);
        return result;
    }
};

// pointer to array of name
class NameSet : public PointerSet<Name> {

public:

    // formatting
    static const char defaultName;
    static const char addOperator;
    static const char subtractOperator;
    static const char multiplyOperator;
    static const char divideOperator;

    // constructor

    explicit NameSet() : PointerSet(0) {}

    explicit NameSet(int size) : PointerSet(size) {

        std::fill(getSet(), getSet() + getSize(), Name(std::string(1, defaultName)));
    }

    // arithmetic operator

    NameSet operator+(const NameSet &a) const {

        NameSet result(getSize());
        for (int i = 0; i < getSize(); i++)
            result.getSet()[i] = Name(getSet()[i] + addOperator + a.getSet()[i]);
        return result;
    }

    NameSet operator-(const NameSet &a) const {

        NameSet result(getSize());
        for (int i = 0; i < getSize(); i++)
            result.getSet()[i] = Name(getSet()[i] + subtractOperator + a.getSet()[i]);
        return result;
    }

    NameSet operator*(double a) const {

        NameSet result(getSize());
        for (int i = 0; i < getSize(); i++)
            result.getSet()[i] = Name(getSet()[i] + multiplyOperator + std::to_string(a));
        return result;
    }

    NameSet operator/(double a) const {

        NameSet result(getSize());
        for (int i = 0; i < getSize(); i++)
            result.getSet()[i] = Name(getSet()[i] + divideOperator + std::to_string(a));
        return result;
    }

    const NameSet &operator+=(const NameSet &a) const {

        for (int i = 0; i < getSize(); i++) getSet()[i] += addOperator + a.getSet()[i];
        return *this;
    }

    const NameSet &operator-=(const NameSet &a) const {

        for (int i = 0; i < getSize(); i++) getSet()[i] += subtractOperator + a.getSet()[i];
        return *this;
    }

    const NameSet &operator*=(double a) const {

        for (int i = 0; i < getSize(); i++) getSet()[i] += multiplyOperator + std::to_string(a);
        return *this;
    }

    const NameSet &operator/=(double a) const {

        for (int i = 0; i < getSize(); i++) getSet()[i] += divideOperator + std::to_string(a);
        return *this;
    }

    // file io

    static NameSet *importFull(std::istream &stream, NameSet *result, bool newObject) {

        PointerSet::importFull(stream, result, newObject);
        return result;
    }
};
