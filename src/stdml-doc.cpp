#include <fs>
#include <fstream>
#include <html5>

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

void index(std::ostream &os)
{
    namespace h5 = html5;
    h5::element doc(h5::html);
    doc.add(h5::head).add(h5::title).text("stdml");
    {
        auto &b = doc.add(h5::body);
        auto &s1 = b.add(h5::section);
        s1.add(h5::h2).text("A collection of libraries for machine learning.");

        s1.add(h5::h3).text("Core");
        {
            auto &ul = s1.add(h5::ul);
            {
                auto &li = ul.add(h5::li);
                add_link(li, "https://github.com/lgarithm/stdtensor");
                li.add(h5::span).text("( doc: ");
                add_link(li, "stdtensor.html").attr(h5::target, "_blank");
                li.add(h5::span).text(")");
                {
                    auto &ul = li.add(h5::ul);
                    ul.add(h5::li).text("ttl/cuda_tensor");
                    ul.add(h5::li).text("ttl/device");
                    ul.add(h5::li).text("ttl/range");
                    ul.add(h5::li).text("ttl/shape");
                    ul.add(h5::li).text("ttl/tensor");
                }
            }
            {
                auto &li = ul.add(h5::li);
                add_link(li, "https://github.com/lgarithm/stdnn-ops");
                {
                    auto &ul = li.add(h5::ul);
                    ul.add(h5::li).text("ttl/nn/ops");
                }
            }
            add_link(ul.add(h5::li),
                     "https://github.com/lgarithm/stdnn-ops-cuda");
            add_link(ul.add(h5::li),
                     "https://github.com/lgarithm/nn-graph-experimental");
        }

        s1.add(h5::h3).text("Utilities");
        {
            auto &ul = s1.add(h5::ul);
            add_link(ul.add(h5::li), "https://github.com/lgarithm/stdtracer");
        }
    }
    doc >> os;
}

void std_tensor_doc(std::ostream &os);

void gen_doc(const char *filename, void (*gen)(std::ostream &))
{
    std::ofstream fs(filename);
    gen(fs);
}

int main()
{
    gen_doc("index.html", index);
    gen_doc("stdtensor.html", std_tensor_doc);
    return 0;
}
