#include "common/nbt/Tag.h"

Tag::Tag()
{
    vtable = 0x0;
}

Tag::~Tag()
{
    // If vtable was nullptr thats because the tag was constructed here, when we should be calling the in game ctor for the tag
    using function = void(__thiscall*)(Tag*);
    reinterpret_cast<function>(this->vtable[0])(this);
}

void Tag::deleteChildren()
{
    using function = void(__thiscall*)(Tag*);
    return reinterpret_cast<function>(this->vtable[1])(this);
}

void Tag::write(IDataOutput& a1) const
{
    using function = void(__thiscall*)(const Tag*, IDataOutput&);
    return reinterpret_cast<function>(this->vtable[2])(this, a1);
}

void Tag::load(IDataInput& a1)
{
    using function = void(__thiscall*)(Tag*, IDataInput&);
    return reinterpret_cast<function>(this->vtable[3])(this, a1);
}

std::string* Tag::toString(std::string* a1) const
{
    using function = std::string*(__thiscall*)(const Tag*, std::string*);
    return reinterpret_cast<function>(this->vtable[4])(this, a1);
}

Tag::Type Tag::getId() const
{
    using function = Tag::Type(__thiscall*)(const Tag*);
    return reinterpret_cast<function>(this->vtable[5])(this);
}

bool Tag::equals(const Tag& a1) const
{
    using function = bool(__thiscall*)(const Tag*, const Tag&);
    return reinterpret_cast<function>(this->vtable[6])(this, a1);
}

void Tag::print(PrintStream& a1) const
{
    using function = void(__thiscall*)(const Tag*, PrintStream&);
    return reinterpret_cast<function>(this->vtable[7])(this, a1);
}

void Tag::print(const std::string& a1, PrintStream& a2) const
{
    using function = void(__thiscall*)(const Tag*, const std::string&, PrintStream&);
    return reinterpret_cast<function>(this->vtable[8])(this, a1, a2);
}

std::unique_ptr<Tag> Tag::copy() const
{
    using function = std::unique_ptr<Tag>(__thiscall*)(const Tag*);
    return reinterpret_cast<function>(this->vtable[9])(this);
}

size_t Tag::hash() const
{
    using function = size_t(__thiscall*)(const Tag*);
    return reinterpret_cast<function>(this->vtable[10])(this);
}