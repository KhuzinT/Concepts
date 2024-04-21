#pragma once

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// struct Base {
//     static VirtualTable vtable;
//     VirtualTable* vptr;
//
//     Base(): vptr(&vtable) {};
//
//     // Your code here
//
// };
// VirtualTable Base::vtable("Base");


#define CLASS(Base)                         \
struct Base {                               \
    static VirtualTable vtable;             \
    VirtualTable* vptr;                     \
    Base(): vptr(&vtable) {};

#define END(Base)                           \
};                                          \
VirtualTable Base::vtable(#Base);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// struct Derived {
//     static VirtualTable vtable;
//     VirtualTable *vptr;
//
//     Derived() : vptr(&vtable) {
//         vtable.add(Base::vtable);
//     }
//
//     // Your code here
//
// };
// VirtualTable Derived::vtable("Derived");


#define CLASS_DERIVED(Derived, Base)                                \
struct Derived {                                                    \
    static VirtualTable vtable;                                     \
    VirtualTable *vptr;                                             \
    Derived() : vptr(&vtable) {                                     \
        vtable.add(Base::vtable);                                   \
    };                                                              \

#define END_DERIVED(Derived, Base)                                  \
};                                                                  \
VirtualTable Derived::vtable(#Derived);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define METHOD(Class, method) \
void method(Class* curr)

#define ADD(Class, method) \
Class::vtable.add(#method, reinterpret_cast<void*>(&method));

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define CALL(object, method)                                                        \
{                                                                                   \
    void (*func)() = nullptr;                                                       \
    void* ptr = (*object).vptr->get(#method);                                       \
    if (ptr != nullptr) {                                                           \
        func = reinterpret_cast<void (*)()>(ptr);                                   \
        func();                                                                     \
        std::cout << "-- Method " << #method << " done successfully" << std::endl;  \
    } else {                                                                        \
        std::cout << "!! Something went wrong with " << #method << std::endl;       \
    }                                                                               \
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////