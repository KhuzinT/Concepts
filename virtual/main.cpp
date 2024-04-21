#include <iostream>

#include "include/VirtualTable.hpp"
#include "include/Macros.hpp"

CLASS(Base)
END(Base)

METHOD(Base, BaseMethod) {
    std::cout << "* Not virtual Base Method" << std::endl;
}

METHOD(Base, BaseOverride) {
    std::cout << "* Base method to override" << std::endl;
}


CLASS_DERIVED(Derived, Base)
END_DERIVED(Derived, Base)

METHOD(Derived, DerivedMethod) {
    std::cout << "* Not virtual Derived Method" << std::endl;
}

METHOD(Derived, DerivedOverride) {
    std::cout << "* Overridden Derived Method" << std::endl;
}


int main() {
    Base base;
    ADD(Base, BaseMethod)
    ADD(Base, BaseOverride)

    Derived derived;
    ADD(Derived, DerivedMethod)
    ADD(Derived, DerivedOverride)

    std::cout << "----------------------------------------------------" << std::endl;

    CALL(&base, BaseMethod)
    CALL(&base, BaseOverride)

    std::cout << "----------------------------------------------------" << std::endl;

    // ожидаем ошибку
    CALL(&base, DerivedMethod)
    CALL(&base, DerivedOverride)

    std::cout << "----------------------------------------------------" << std::endl;

    CALL(&derived, BaseMethod)
    CALL(&derived, DerivedMethod)
    CALL(&derived, DerivedOverride)

    std::cout << "----------------------------------------------------" << std::endl;

    Base *fake = reinterpret_cast<Base *>(&derived);

    CALL(fake, BaseMethod)
    CALL(fake, DerivedMethod)
    CALL(fake, DerivedOverride)

    std::cout << "----------------------------------------------------" << std::endl;

    return 0;
}

