#include "carrot_module.h"
#include "string_contants.h"

#define DOUBLE_ARG_CHECK(args, name) \
    if (!std::holds_alternative<std::string>(args[0]) \
     || !std::holds_alternative<std::string>(args[1])) \
    throw std::runtime_error(#name ": Invalid input value")

#define TRIBLE_ARG_CHECK(args, name) \
    if (!std::holds_alternative<std::string>(args[0]) \
     || !std::holds_alternative<std::string>(args[1]) \
     || !std::holds_alternative<std::string>(args[2])) \
    throw std::runtime_error(#name ": Invalid input value")

struct StrReplaceNFn : NinCallable {
    int arity() override { return 4; }
    std::string name() override { return "replaceN"; }
    Value call(std::vector<Value> args) override {
        TRIBLE_ARG_CHECK(args, "replaceN");
        if (!std::holds_alternative<double>(args[3]))
            throw std::runtime_error("replaceN: Invalid input value");

        std::string string = std::get<std::string>(args[0]);
        std::string target = std::get<std::string>(args[1]);
        std::string replace = std::get<std::string>(args[2]);
        size_t n = floor(std::get<double>(args[3]));

        if (target.empty() || n == 0) return string;

        size_t replacements = 0;
        size_t i = 0;
        while (i < string.length()) {
            if (replacements == n) break; 

            if (string.substr(i, target.length()) == target) {
                string.replace(i, target.length(), replace);
                i += replace.length();
                replacements++;
            } else i++;
        }
        return string;
    }
};

struct StrReplaceAllFn : NinCallable {
    int arity() override { return 3; }
    std::string name() override { return "replaceAll"; }
    Value call(std::vector<Value> args) override {
        TRIBLE_ARG_CHECK(args, "replaceAll");

        std::string string = std::get<std::string>(args[0]);
        std::string target = std::get<std::string>(args[1]);
        std::string replace = std::get<std::string>(args[2]);

        if (target.empty()) return string;

        size_t i = 0;
        while (i < string.length()) {
            if (string.substr(i, target.length()) == target) {
                string.replace(i, target.length(), replace);
                i += replace.length();
            } else i++;
        }
        return string;
    }
};

struct StrFindFirstFn : NinCallable {
    int arity() override { return 2; }
    std::string name() override { return "findFirst"; }
    Value call(std::vector<Value> args) override {
        DOUBLE_ARG_CHECK(args, "findFirst");

        std::string string = std::get<std::string>(args[0]);
        std::string target = std::get<std::string>(args[1]);

        size_t length = target.length();
        if (length > string.length()) return std::monostate{};

        size_t i = 0;
        while (i < string.length()) {
            if (string.substr(i, length) == target) return static_cast<double>(i);
            i++;
        }
        return std::monostate{};
    }
};

struct StrFindLastFn : NinCallable {
    int arity() override { return 2; }
    std::string name() override { return "findFirst"; }
    Value call(std::vector<Value> args) override {
        DOUBLE_ARG_CHECK(args, "findFirst");

        std::string string = std::get<std::string>(args[0]);
        std::string target = std::get<std::string>(args[1]);

        size_t length = target.length();
        if (length > string.length()) return std::monostate{};

        size_t i = string.length() - length;
        while (true) {
            if (string.substr(i, length) == target) return static_cast<double>(i);

            if (i == 0) break;
            i--;
        }
        return std::monostate{};
    }
};

extern "C" void carrot_module_init(std::unordered_map<std::string, Value> *out) {
    (*out)["octal"] = OCTAL;
    (*out)["digits"] = DIGTS;
    (*out)["symbols"] = SYMBL;
    (*out)["lowercase"] = LOWER;
    (*out)["uppercase"] = UPPER;
    (*out)["whitespace"] = SPACE;
    (*out)["alphabet"] = LOWER UPPER;
    (*out)["hexLowercase"] = DIGTS HEX_L;
    (*out)["hexUppercase"] = DIGTS HEX_U;
    (*out)["hexadecimal"] = DIGTS HEX_L HEX_U;
    (*out)["alphanumeric"] = DIGTS LOWER UPPER;
    (*out)["printable"] = DIGTS LOWER UPPER SYMBL " ";

    (*out)["replaceN"] = std::make_shared<StrReplaceNFn>();
    (*out)["replaceAll"] = std::make_shared<StrReplaceAllFn>();

    (*out)["findFirst"] = std::make_shared<StrFindFirstFn>();
    (*out)["findLast"] = std::make_shared<StrFindLastFn>();
}