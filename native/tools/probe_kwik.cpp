#include "kwik_yyc/elf.hpp"
#include "kwik_yyc/yyc.hpp"
#include <exception>
#include <iostream>
int main(int argc, char** argv) {
    if (argc != 2) return 2;
    try {
        kwik::yyc::ElfImage elf(argv[1]);
        const auto result = kwik::yyc::discover_yyc_functions(elf);
        std::cout << "Recovered registration entries: " << result.functions.size() << '\n';
        for (size_t i=0; i<result.functions.size() && i<5; ++i)
            std::cout << result.functions[i].name << '\n';
        return result.functions.empty() ? 3 : 0;
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return 1;
    }
}
