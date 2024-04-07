#pragma once
#include <memory>
#include <cstdint>
#include <string>

class IDataOutput;
class IDataInput;
class PrintStream;

class Tag {
public:
    enum Type : unsigned char {
        End = 0x0000,
        Byte = 0x0001,
        Short = 0x0002,
        Int = 0x0003,
        Int64 = 0x0004,
        Float = 0x0005,
        Double = 0x0006,
        ByteArray = 0x0007,
        String = 0x0008,
        List = 0x0009,
        Compound = 0x000a,
        IntArray = 0x000b,
    };

public:
    uintptr_t** vtable;

public:
    Tag();

    /* Tag::vfuncs */
    ~Tag();
    void deleteChildren();
    void write(IDataOutput&) const;
    void load(IDataInput&);
    std::string* toString(std::string*) const;
    Tag::Type getId() const;
    bool equals(const Tag&) const;
    void print(PrintStream&) const;
    void print(const std::string&, PrintStream&) const;
    std::unique_ptr<Tag> copy() const;
    size_t hash() const;
};