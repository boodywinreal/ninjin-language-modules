#define _USE_MATH_DEFINES // Windows-specific cmath flag
#include <cmath>

#define MAKE_CALLABLE(funcName, func, className) struct className : NinCallable { \
    int arity() override { return 1; } \
    std::string name() override { return funcName; } \
    Value call(std::vector<Value> args) override { \
        if (!std::holds_alternative<double>(args[0])) \
            throw std::runtime_error(funcName ": Invalid input value"); \
        return func(std::get<double>(args[0])); \
    } \
} \

#define SINGLE_ARG_CHECK(args, name) \
    if (!std::holds_alternative<double>(args[0])) \
    throw std::runtime_error(#name ": Invalid input value")

#define TRIBLE_ARG_CHECK(args, name) \
    if (!std::holds_alternative<double>(args[0]) \
    || !std::holds_alternative<double>(args[1])\
    || !std::holds_alternative<double>(args[2])\
    ) throw std::runtime_error(#name ": Invalid input value")