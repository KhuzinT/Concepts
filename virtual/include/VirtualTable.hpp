#pragma once

#include <string>
#include <unordered_map>

class VirtualTable {
private:

    using name = std::string;
    using func = void *;

    std::unordered_map<name, func> table_;
    name class_name_;

public:

    explicit VirtualTable(const name &class_name) {
        class_name_ = class_name;
        std::cout << "$ Virtual table for " << class_name_ << " initialized" << std::endl;
    }

    func get(const name &fname) const {
        if (!table_.contains(fname)) {
            return nullptr;
        }

        return table_.at(fname);
    }

    void add(const name &fname, func addr) {
        table_[fname] = addr;
        std::cout << "+ Method " << fname << " added to " << class_name_ << std::endl;
    }

    void add(const VirtualTable &vtable) {
        for (const auto &entry: vtable.table_) {
            auto fname = entry.first;
            auto addr = entry.second;
            if (!table_.contains(fname)) {
                add(fname, addr);
            }
        }
    }
};