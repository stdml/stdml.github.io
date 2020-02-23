#include <fs>
#include <fstream>
#include <html5>
#include <stdml/doc/bits/headers.hpp>
#include <stdml/doc/bits/repos.hpp>

html5::element &add_link(html5::element &e, const std::string &name,
                         const std::string &link)
{
    namespace h5 = html5;
    return e.add(h5::a).text(name).attr(h5::href, link);
};

html5::element &add_link(html5::element &e, const std::string &link)
{
    namespace fs = std::filesystem;
    return add_link(e, fs::path(link).stem(), link);
};

std::string hdr(const std::string &h) { return "&lt;" + h + "&gt;"; }

void index(std::ostream &os)
{
    namespace h5 = html5;
    h5::element doc(h5::html);
    doc.add(h5::head).add(h5::title).text("stdml");
    {
        auto &b = doc.add(h5::body);
        {
            auto &s = b.add(h5::section);
            s.add(h5::h2).text(
                "A collection of libraries for machine learning");
        }
        {
            auto &s = b.add(h5::section);
            s.add(h5::h3).text("[early draft]");
            add_link(s, "header.html");
        }
        {
            auto &section = b.add(h5::section);
            {
                section.add(h5::h3).text("Core");
                auto &ul = section.add(h5::ul);
                {
                    auto &li = ul.add(h5::li);
                    add_link(li, "https://github.com/lgarithm/stdtensor");
                    li.add(h5::span).text("( doc: ");
                    add_link(li, "stdtensor.html").attr(h5::target, "_blank");
                    li.add(h5::span).text(")");
                    {
                        auto &ul = li.add(h5::ul);
                        for (const auto &h : ttl_headers) {
                            ul.add(h5::li).text(hdr(h));
                        }
                    }
                }
                {
                    auto &li = ul.add(h5::li);
                    add_link(li, "https://github.com/lgarithm/stdnn-ops");
                    {
                        auto &ul = li.add(h5::ul);
                        for (const auto &h : ttl_nn_headers) {
                            ul.add(h5::li).text(hdr(h));
                        }
                    }
                }
                {
                    auto &li = ul.add(h5::li);
                    add_link(li, "https://github.com/lgarithm/stdnn-ops-cuda");
                    {
                        // auto &ul = li.add(h5::ul);
                        // ul.add(h5::li).text("ttl/nn/graph");
                    }
                }
                {
                    auto &li = ul.add(h5::li);
                    add_link(
                        li,
                        "https://github.com/lgarithm/nn-graph-experimental");
                    {
                        auto &ul = li.add(h5::ul);
                        for (const auto &h : ttl_nn_graph_headers) {
                            ul.add(h5::li).text(hdr(h));
                        }
                    }
                }
            }
            {
                section.add(h5::h3).text("Learning");
                auto &ul = section.add(h5::ul);
                {
                    auto &li = ul.add(h5::li);
                    li.add(h5::span).text("stdml-core");
                    {
                        auto &ul = li.add(h5::ul);
                        for (const auto &h : stdml_headers) {
                            ul.add(h5::li).text(hdr(h));
                        }
                    }
                }
            }
            {
                section.add(h5::h3).text("Utilities");
                auto &ul = section.add(h5::ul);
                {
                    auto &li = ul.add(h5::li);
                    add_link(li, "https://github.com/lgarithm/stdtracer");
                    {
                        auto &ul = li.add(h5::ul);
                        for (const auto &h : tracer_headers) {
                            ul.add(h5::li).text(hdr(h));
                        }
                    }
                }
            }
        }
    }
    doc >> os;
}

void std_tensor_doc(std::ostream &os);
void header_doc(std::ostream &os);

void gen_doc(const char *filename, void (*gen)(std::ostream &))
{
    std::ofstream fs(filename);
    gen(fs);
}

int main()
{
    gen_doc("index.html", index);
    gen_doc("stdtensor.html", std_tensor_doc);
    gen_doc("header.html", header_doc);
    return 0;
}
