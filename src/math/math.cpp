#include "carrot_module.h"
#include "cmath"

struct MathSineFn : NinCallable {
    int arity() override { return 1; }
    std::string name() override { return "sin"; }
    Value call(std::vector<Value> args) override {
        if (!std::holds_alternative<double>(args[0]))
            throw std::runtime_error("sin: Invalid input value");
        return sin(std::get<double>(args[0]));
    }
};

struct MathCosineFn : NinCallable {
    int arity() override { return 1; }
    std::string name() override { return "cos"; }
    Value call(std::vector<Value> args) override {
        if (!std::holds_alternative<double>(args[0]))
            throw std::runtime_error("cos: Invalid input value");

        return cos(std::get<double>(args[0]));
    }
};

struct MathTanFn : NinCallable {
    int arity() override { return 1; }
    std::string name() override { return "tan"; }
    Value call(std::vector<Value> args) override {
        if (!std::holds_alternative<double>(args[0]))
            throw std::runtime_error("tan: Invalid input value");

        return tan(std::get<double>(args[0]));
    }
};

struct MathAbsFn : NinCallable {
    int arity() override { return 1; }
    std::string name() override { return "abs"; }
    Value call(std::vector<Value> args) override {
        if (!std::holds_alternative<double>(args[0]))
            throw std::runtime_error("abs: Invalid input value");

        double x = std::get<double>(args[0]);
        return x < 0 ? -x : x;
    }
};

const Value MathPiValue = M_PI;

extern "C" void carrot_module_init(std::unordered_map<std::string, Value> *out){
    (*out)["sin"] = std::make_shared<MathSineFn>();
    (*out)["cos"] = std::make_shared<MathCosineFn>();
    (*out)["tan"] = std::make_shared<MathTanFn>();
    (*out)["abs"] = std::make_shared<MathAbsFn>();
    (*out)["pi"] = MathPiValue;
}