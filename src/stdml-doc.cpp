#include <html5>

void add_link(html5::element &e, const std::string &name,
              const std::string &link)
{
    namespace h5 = html5;
    e.add(h5::li).add(h5::a).text(name).attr(h5::href, link);
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
            add_link(ul, "stdtensor", "https://github.com/lgarithm/stdtensor");
            add_link(ul, "stdnn-ops", "https://github.com/lgarithm/stdnn-ops");
            add_link(ul, "stdnn-ops-cuda",
                     "https://github.com/lgarithm/stdnn-ops-cuda");
            add_link(ul, "nn-graph-experimental",
                     "https://github.com/lgarithm/nn-graph-experimental");
        }

        s1.add(h5::h3).text("Utilities");
        {
            auto &ul = s1.add(h5::ul);
            add_link(ul, "stdtracer", "https://github.com/lgarithm/stdtracer");
        }
    }
    doc >> os;
    os << std::endl;
}

int main()
{
    std::freopen("index.html", "w", stdout);
    index(std::cout);
    return 0;
}
