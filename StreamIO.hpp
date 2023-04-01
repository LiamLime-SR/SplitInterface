#pragma once
#include <iostream>

// device for file io to stream
template<class D>
class StreamIO {

private:

    // pointer to this cast to derived class

    const D *dThis() const { return static_cast<const D *>(this); }

public:

    // file io

    virtual const std::ostream &exportFull(std::ostream &stream, bool newObject) const {

        return stream << *dThis() << " ";
    }

    static D *importFull(std::istream &stream, D *result, bool newObject) {

        if (newObject) *result = D();
        stream >> *result;
        return result;
    }
};

// string wrapper for file io
class Name : public std::string, public StreamIO<Name> {

public:

    // constructor

    explicit Name() : std::string() {}

    explicit Name(std::string a) : std::string(std::move(a)) {}
};
