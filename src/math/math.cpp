#define _USE_MATH_DEFINES // Windows-specific cmath flag
#include "carrot_module.h"
#include "cmath"

#define SINGLE_ARG_CHECK(args, name) \
    if (!std::holds_alternative<double>(args[0])) \
    throw std::runtime_error(#name ": Invalid input value")

#define TRIBLE_ARG_CHECK(args, name) \
    if (!std::holds_alternative<double>(args[0]) \
    || !std::holds_alternative<double>(args[1])\
    || !std::holds_alternative<double>(args[2])\
    ) throw std::runtime_error(#name ": Invalid input value")

struct MathSineFn : NinCallable {
    int arity() override { return 1; }
    std::string name() override { return "sin"; }
    Value call(std::vector<Value> args) override {
        SINGLE_ARG_CHECK(args, "sin");

        return sin(std::get<double>(args[0]));
    }
};

struct MathCosineFn : NinCallable {
    int arity() override { return 1; }
    std::string name() override { return "cos"; }
    Value call(std::vector<Value> args) override {
        SINGLE_ARG_CHECK(args, "cos");

        return cos(std::get<double>(args[0]));
    }
};

struct MathTanFn : NinCallable {
    int arity() override { return 1; }
    std::string name() override { return "tan"; }
    Value call(std::vector<Value> args) override {
        SINGLE_ARG_CHECK(args, "tan");

        return tan(std::get<double>(args[0]));
    }
};

struct MathAbsFn : NinCallable {
    int arity() override { return 1; }
    std::string name() override { return "abs"; }
    Value call(std::vector<Value> args) override {
        SINGLE_ARG_CHECK(args, "abs");

        double x = std::get<double>(args[0]);
        return x < 0 ? -x : x;
    }
};

struct MathClampFn : NinCallable {
    int arity() override { return 3; }
    std::string name() override { return "clamp"; }
    Value call(std::vector<Value> args) override {
        TRIBLE_ARG_CHECK(args, "clamp");

        double x = std::get<double>(args[0]);
        double min = std::get<double>(args[1]);
        double max = std::get<double>(args[2]);
        if (x < min) x = min;
        if (x > max) x = max;
        return x;
    }
};

struct MathLerpFn : NinCallable {
    int arity() override { return 3; }
    std::string name() override { return "lerp"; }
    Value call(std::vector<Value> args) override {
        TRIBLE_ARG_CHECK(args, "lerp");

        double start = std::get<double>(args[0]);
        double end = std::get<double>(args[1]);
        double alpha = std::get<double>(args[2]);
        return alpha * (end - start) + start;
    }
};

const Value MathPiValue = M_PI;

extern "C" void carrot_module_init(std::unordered_map<std::string, Value> *out){
    (*out)["sin"] = std::make_shared<MathSineFn>();
    (*out)["cos"] = std::make_shared<MathCosineFn>();
    (*out)["tan"] = std::make_shared<MathTanFn>();
    (*out)["abs"] = std::make_shared<MathAbsFn>();
    (*out)["clamp"] = std::make_shared<MathClampFn>();
    (*out)["lerp"] = std::make_shared<MathLerpFn>();
    (*out)["pi"] = MathPiValue;
}