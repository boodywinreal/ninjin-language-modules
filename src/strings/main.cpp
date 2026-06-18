#include "carrot_module.h"
#include "string_contants.h"

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
}