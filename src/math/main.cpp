#include "carrot_module.h"
#include "math_header.h"

constexpr double tanEpsilon = 6.12323e-17;
double safeTan(double x) {
    double cosResult = std::cos(x);
    if (std::abs(cosResult) <= tanEpsilon) cosResult = 0.0;

    return std::sin(x) / cosResult; // This is handled automatically by C++
}

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
        if (max < min)
            throw std::runtime_error("clamp: Bad input, \
the MAX value should not be less than the MIN value");

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
        if (alpha < 0) alpha = 0;
        if (alpha < 1) alpha = 1;

        return alpha * (end - start) + start;
    }
};

struct MathLerpNoClampFn : NinCallable {
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

MAKE_CALLABLE("sin", std::sin, MathSineFn);
MAKE_CALLABLE("cos", std::cos, MathCosineFn);
MAKE_CALLABLE("tan", safeTan, MathTangentFn);
MAKE_CALLABLE("sqrt", std::sqrt, MathSquareRootFn);
MAKE_CALLABLE("cbrt", std::cbrt, MathCubeRootFn);
MAKE_CALLABLE("asin", std::asin, MathArcSineFn);
MAKE_CALLABLE("acos", std::acos, MathArcCosineFn);
MAKE_CALLABLE("atan", std::atan, MathArcTangentFn);

extern "C" void carrot_module_init(std::unordered_map<std::string, Value> *out){
    (*out)["sin"] = std::make_shared<MathSineFn>();
    (*out)["cos"] = std::make_shared<MathCosineFn>();
    (*out)["tan"] = std::make_shared<MathTangentFn>();
    (*out)["asin"] = std::make_shared<MathArcSineFn>();
    (*out)["acos"] = std::make_shared<MathArcCosineFn>();
    (*out)["atan"] = std::make_shared<MathArcTangentFn>();
    (*out)["abs"] = std::make_shared<MathAbsFn>();
    (*out)["clamp"] = std::make_shared<MathClampFn>();
    (*out)["cbrt"] = std::make_shared<MathCubeRootFn>();
    (*out)["sqrt"] = std::make_shared<MathSquareRootFn>();
    (*out)["lerp"] = std::make_shared<MathLerpFn>();
    (*out)["lerpNoClamp"] = std::make_shared<MathLerpNoClampFn>();
    (*out)["pi"] = M_PI;
    (*out)["tau"] = M_PI_2;
    (*out)["2pi"] = M_PI_2;
}

#undef SINGLE_ARG_CHECK
#undef TRIBLE_ARG_CHECK