#pragma once

enum Opcode {
    // арифметические операции
    ADD = 1,
    SUB = 2,
    MUL = 3,
    DIV = 4,
    MOD = 5,
    // условные выражения
    EQ = 6,
    NE = 7,
    LT = 8,
    LE = 9,
    GT = 10,
    GE = 11,
    // условные конструкции
    JMP = 12,
    JMPT = 13,
    JMPF = 14,
    // операции со стеком
    PUSH = 15,
    POP = 16,
    // управление памятью
    // локально
    LOAD = 17,
    STORE = 18,
    // глобально
    GLOAD = 19,
    GSTORE = 20,
    // вызовы процедур
    CALL = 21,
    RET = 22,
    // ввод-вывод
    READ = 23,
    WRITE = 24,
    HELLO = 25,
    STR = 26,
    // выход
    EXIT = 27
};