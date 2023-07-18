#include <iostream>
#include <type_traits>
#include <memory>


template<typename vt>
class smart_ptr{
public:
    vt* _ptr;
    smart_ptr() noexcept (std::is_nothrow_default_constructible_v<vt>) {
        _ptr= reinterpret_cast<vt*>(operator new(sizeof(vt),std::nothrow));
        new (_ptr) (vt);
    }
    ~smart_ptr() noexcept (std::is_nothrow_destructible_v<vt>) {
        if (_ptr !=nullptr) {
            _ptr->~vt();
            operator delete (reinterpret_cast<char*>(_ptr),std::nothrow);
        }
    }

    smart_ptr(const smart_ptr& obj) = delete;
    smart_ptr(smart_ptr&& obj) noexcept {
        _ptr=obj._ptr;
        obj._ptr= nullptr;
    }

    smart_ptr& operator=(const smart_ptr& obj) = delete;
    smart_ptr& operator=(smart_ptr&& obj) noexcept (std::is_nothrow_destructible_v<vt>) {
        if (this!=&obj) {
            this->~smart_ptr();
            new (this) smart_ptr(std::move(obj));
        }
        return *this;
    }

    vt* get() const noexcept { return _ptr; }
    vt* operator->() const noexcept { return _ptr; }
    vt& operator*() const noexcept { return *_ptr; }

};
