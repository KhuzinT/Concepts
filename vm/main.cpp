#include "include/VirtualMachine.hpp"

// функция, которую будем переписывать в byte-code
int fib(int n) {
    if (n == 0) {
        return 0;
    }
    if (n < 3) {
        return 1;
    } else {
        return fib(n - 1) + fib(n - 2);
    }
}


int main() {

    // адрес начала функции fib
    const int fib = 0;
    // кол-во аргументов функции
    const int argc = 1;
    int code[] = {
            // начало функции fib
            // кладем на стек один аргумент функции - n
            LOAD, argc,
            // кладем на стек 0
            PUSH, 0,
            // проверяем, что n == 0
            EQ,
            // если n != 0, то идем к 10-ой операции
            JMPF, 10,
            // если n == 0, то кладем 0 на стек и возвращаем результат
            PUSH, 0, RET,
            // 10-ая операция
            // снова кладем на стек n
            LOAD, argc,
            // кладем на стек 3
            PUSH, 3,
            // проверяем что n < 3
            LT,
            // если n => 3, то идеи к 20-ой операции
            JMPF, 20,
            // если n < 3, то кладем 1 на стек и возвращаем результат
            PUSH, 1, RET,
            // 20-ая операция
            // снова кладем на стек n
            LOAD, argc,
            // кладем на стек 1, чтобы вычислить n - 1
            PUSH, 1, SUB,
            // вызываем функцию fib с argc аргументами со стека
            CALL, fib, argc,
            // снова кладем на стек n
            LOAD, argc,
            // кладем на стек 2, чтобы вычислить n - 2
            PUSH, 2, SUB,
            // вызываем функцию fib с argc аргументами со стека
            CALL, fib, argc,
            // складываем значения fib(n-1) и fib(n-2) и возвращаем
            ADD, RET,
            // конец функции fib
            // 38-ая операция - начало функции main
            // закодированная строка длины 16: Please, enter n
            STR, 16,
            80, 108, 101, 97, 115, 101, 44, 32, 101, 110, 116, 101, 114, 32, 110, 10,
            // вводим n
            READ,
            // вызываем функцию fib с введенным аргументом
            CALL, fib, argc,
            // закодированная строка длины 26: The nth fibonacci number
            STR, 26,
            84, 104, 101, 32, 110, 116, 104, 32,
            102, 105, 98, 111, 110, 97, 99, 99, 105, 32, 110, 117, 109, 98, 101, 114, 58, 32,
            // выводим результат и выходим
            WRITE, EXIT
    };

    // адрес начала main
    const int entrypoint = 38;

    std::vector<int> program(code, code + sizeof(code) / sizeof(int));

    auto vm = VirtualMachine();
    vm.exec(program, entrypoint);

    return 0;
}