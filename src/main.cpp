#include <fs>
#include <fstream>
#include <html5>
#include <stdml/doc/bits/headers.hpp>
#include <stdml/doc/bits/repos.hpp>

void header_doc(std::ostream &os);
void index(std::ostream &os);
void std_tensor_doc(std::ostream &os);

void gen_doc(const char *filename, void (*gen)(std::ostream &))
{
    std::ofstream fs(filename);
    fs << "<!doctype html>\n";
    gen(fs);
}

int main()
{
    gen_doc("index.html", index);
    gen_doc("stdtensor.html", std_tensor_doc);
    gen_doc("header.html", header_doc);
    return 0;
}
