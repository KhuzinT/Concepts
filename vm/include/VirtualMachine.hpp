#pragma once

#include "Opcode.hpp"

#include <iostream>
#include <vector>

class VirtualMachine {
private:

    // instruction pointer
    int ip_ = 0;
    // stack pointer
    int sp_ = -1;
    // frame pointer
    int fp_ = 0;

    // virtual stack
    std::vector<int> stack_;

    // local data
    std::vector<int> local_;

public:

    explicit VirtualMachine(
            const int &stack_size = 1024,
            const int &local_size = 1024);

    // выполнение программы из вектора байт-кодов
    bool exec(const std::vector<int> &code, const int &entrypoint = 0);

private:

    // вернуть следующий байт-код
    int next_bytecode(const std::vector<int> &code);

    // удалить элемент с вершины стека и вернуть его
    int pop_stack();

    // положить элемент на вершину стека
    void push_stack(const int &value);

private:

    // +
    void add();

    // -
    void sub();

    // *
    void mul();

    // /
    void div();

    // %
    void mod();

    // ==
    void eq();

    // !=
    void ne();

    // <
    void lt();

    // <=
    void le();

    // >
    void gt();

    // =>
    void ge();

    // goto
    void jmp(const std::vector<int> &code);

    // if true
    void jmpt(const std::vector<int> &code);

    // if false
    void jmpf(const std::vector<int> &code);

    // положить следующее число в коде на стек
    void push(const std::vector<int> &code);

    // удалить вершину стека
    void pop();

    // load func arg or local value
    void load(const std::vector<int> &code);

    // store func arg or local value
    void store(const std::vector<int> &code);

    // local -> stack
    void gload();

    // stack -> local
    void gstore(const std::vector<int> &code);

    // вызов функции
    void call(const std::vector<int> &code);

    // возврат из функции
    void ret();

    // положить введенное число на вершину стека
    void read();

    // напечатать число с вершины стека
    void write();

    // вывести строку из кода на экран
    void str(const std::vector<int> &code);

    // hello world
    void hello();

};