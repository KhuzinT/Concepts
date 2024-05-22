#include "../include/VirtualMachine.hpp"

VirtualMachine::VirtualMachine(const int &stack_size, const int &local_size) {
    stack_ = std::vector<int>(stack_size, 0);
    local_ = std::vector<int>(local_size, 0);
}

bool VirtualMachine::exec(const std::vector<int> &code, const int &entrypoint) {
    ip_ = entrypoint;

    while (true) {
        auto opcode = next_bytecode(code);

        switch (opcode) {
            case ADD:
                add();
                break;
            case SUB:
                sub();
                break;
            case MUL:
                mul();
                break;
            case DIV:
                div();
                break;
            case MOD:
                mod();
                break;
            case EQ:
                eq();
                break;
            case NE:
                ne();
                break;
            case LT:
                lt();
                break;
            case LE:
                le();
                break;
            case GT:
                gt();
                break;
            case GE:
                ge();
                break;
            case JMP:
                jmp(code);
                break;
            case JMPT:
                jmpt(code);
                break;
            case JMPF:
                jmpf(code);
                break;
            case PUSH:
                push(code);
                break;
            case POP:
                pop();
                break;
            case LOAD:
                load(code);
                break;
            case STORE:
                store(code);
                break;
            case GLOAD:
                gload();
                break;
            case GSTORE:
                gstore(code);
                break;
            case CALL:
                call(code);
                break;
            case RET:
                ret();
                break;
            case READ:
                read();
                break;
            case WRITE:
                write();
                break;
            case STR:
                str(code);
                break;
            case HELLO:
                hello();
                break;
            case EXIT:
                return true;
            default:
                return false;
        }
    }
}

int VirtualMachine::next_bytecode(const std::vector<int> &code) {
    return code[ip_++];
}

int VirtualMachine::pop_stack() {
    return stack_[sp_--];
}

void VirtualMachine::push_stack(const int &value) {
    stack_[++sp_] = value;
}

void VirtualMachine::add() {
    int b = pop_stack();
    int a = pop_stack();
    push_stack(a + b);
}

void VirtualMachine::sub() {
    int b = pop_stack();
    int a = pop_stack();
    push_stack(a - b);
}

void VirtualMachine::mul() {
    int b = pop_stack();
    int a = pop_stack();
    push_stack(a * b);
}

void VirtualMachine::div() {
    int b = pop_stack();
    int a = pop_stack();
    push_stack(a / b);
}

void VirtualMachine::mod() {
    int b = pop_stack();
    int a = pop_stack();
    push_stack(a % b);
}

void VirtualMachine::eq() {
    int b = pop_stack();
    int a = pop_stack();
    push_stack((a == b) ? 1 : 0);
}

void VirtualMachine::ne() {
    int b = pop_stack();
    int a = pop_stack();
    push_stack((a != b) ? 1 : 0);
}

void VirtualMachine::lt() {
    int b = pop_stack();
    int a = pop_stack();
    push_stack((a < b) ? 1 : 0);
}

void VirtualMachine::le() {
    int b = pop_stack();
    int a = pop_stack();
    push_stack((a <= b) ? 1 : 0);
}

void VirtualMachine::gt() {
    int b = pop_stack();
    int a = pop_stack();
    push_stack((a > b) ? 1 : 0);
}

void VirtualMachine::ge() {
    int b = pop_stack();
    int a = pop_stack();
    push_stack((a >= b) ? 1 : 0);
}

void VirtualMachine::jmp(const std::vector<int> &code) {
    ip_ = next_bytecode(code);
}

void VirtualMachine::jmpt(const std::vector<int> &code) {
    auto addr = next_bytecode(code);
    if (pop_stack()) {
        ip_ = addr;
    }
}

void VirtualMachine::jmpf(const std::vector<int> &code) {
    auto addr = next_bytecode(code);
    if (!pop_stack()) {
        ip_ = addr;
    }
}

void VirtualMachine::push(const std::vector<int> &code) {
    push_stack(next_bytecode(code));
}

void VirtualMachine::pop() {
    --sp_;
}

void VirtualMachine::load(const std::vector<int> &code) {
    auto offset = next_bytecode(code);
    // Magic number 2: ip + fp
    auto context = stack_[fp_ - 2 - offset];
    push_stack(context);
}

void VirtualMachine::store(const std::vector<int> &code) {
    auto value = pop_stack();
    auto offset = next_bytecode(code);
    // Magic number 2: ip + fp
    local_[fp_ + 2 + offset] = value;
}

void VirtualMachine::gload() {
    auto addr = pop_stack();
    auto value = local_[addr];
    push_stack(value);
}

void VirtualMachine::gstore(const std::vector<int> &code) {
    auto value = pop_stack();
    auto addr = next_bytecode(code);
    local_[addr] = value;
}

void VirtualMachine::call(const std::vector<int> &code) {
    auto addr = next_bytecode(code);
    auto args_count = next_bytecode(code);

    push_stack(args_count);
    push_stack(fp_);
    push_stack(ip_);

    fp_ = sp_;
    ip_ = addr;
}

void VirtualMachine::ret() {
    auto return_value = pop_stack();
    sp_ = fp_;
    ip_ = pop_stack();
    fp_ = pop_stack();
    auto args_count = pop_stack();

    sp_ -= args_count;
    push_stack(return_value);
}

void VirtualMachine::read() {
    auto value = -1;
    std::cin >> value;
    push_stack(value);
}

void VirtualMachine::write() {
    auto value = pop_stack();
    std::cout << value;
}

void VirtualMachine::str(const std::vector<int> &code) {
    auto len = next_bytecode(code);
    while (len > 0) {
        std::cout << char(next_bytecode(code));
        --len;
    }
}

void VirtualMachine::hello() {
    std::cout << "Hello, world!\n";
}
