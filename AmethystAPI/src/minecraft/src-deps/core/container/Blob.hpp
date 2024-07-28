#pragma once
#include <cstddef>
#include <cstdint>
#include <memory>

namespace mce {
    class Blob {
    public:
        typedef std::size_t size_type;
        typedef uint8_t value_type;
        typedef mce::Blob::value_type* iterator;
        typedef void (*delete_function)(value_type*);

        struct Deleter {
            mce::Blob::delete_function m_func;

            Deleter() : m_func(nullptr) {}
            Deleter(delete_function func) : m_func(func) {}

            void operator()(value_type* ptr) const {
                if (m_func) {
                    m_func(ptr);
                }
                else {
                    delete[] ptr;
                }
            }

            delete_function getDeleteFunc() const {
                return m_func;
            }
        };

        typedef std::unique_ptr<unsigned char[], Deleter> pointer_type;

    private:
        pointer_type mBlob;
        size_type mSize;

    public:
        Blob();
        Blob(const iterator data, const size_type size);
        Blob(const Blob& other);

        size_type size() const;

        static void defaultDeleter(iterator data);
    };
}