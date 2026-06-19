#include "carrot_module.h"
#include "string_contants.h"

#define TRIBLE_ARG_CHECK(args, name) \
    if (!std::holds_alternative<std::string>(args[0]) \
     || !std::holds_alternative<std::string>(args[1]) \
     || !std::holds_alternative<std::string>(args[2])) \
    throw std::runtime_error(#name ": Invalid input value")

struct StrReplaceNFn : NinCallable {
    int arity() override { return 4; }
    std::string name() override { return "replaceN"; }
    Value call(std::vector<Value> args) override {
        TRIBLE_ARG_CHECK(args, "replace");
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
}