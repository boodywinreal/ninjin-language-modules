#include "carrot_module.h"
#include <iostream>

struct IOWriteFn : NinCallable {
    int arity() override { return 1; }
    std::string name() override { return "write"; }
    Value call(std::vector<Value> args) override {
        if (!std::holds_alternative<std::string>(args[0]))
            throw std::runtime_error("write: Invalid input value");
        std::cout << std::get<std::string>(args[0]);
        return std::monostate{};
    }
};

struct IOReadFn : NinCallable {
    int arity() override { return 0; }
    std::string name() override { return "write"; }
    Value call(std::vector<Value> args) override {
        std::string input;
        std::cin >> input;
        return input;
    }
};

extern "C" void carrot_module_init(std::unordered_map<std::string, Value> *out) {
    (*out)["write"] = std::make_shared<IOWriteFn>();
    (*out)["read"]  = std::make_shared<IOReadFn>();
}