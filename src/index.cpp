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

void show_header_list(html5::element &ul, const slist &hdrs,
                      const std::string &repo = "",
                      const std::string &tag = "master")
{
    namespace h5 = html5;
    for (const auto &h : hdrs) {
        if (!repo.empty()) {
            const std::string url =
                prefix + "/" + repo + "/tree/" + tag + "/include/" + h;
            ul.add(h5::li)
                .add(h5::a)
                .text(hdr(h))
                .attr(h5::href, url)
                .attr(h5::target, "_blank");
        } else {
            ul.add(h5::li).text(hdr(h));
        }
    }
}

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
                // "stdml - A collection of libraries for machine learning"
                "stdml - The STL for machine learning"  //
            );
        }
        {
            auto &s = b.add(h5::section);
            s.add(h5::h3).text("[early draft]");
        }
        {
            auto &section = b.add(h5::section);
            {
                section.add(h5::h3).text("Core");
                auto &ul = section.add(h5::ul);
                {
                    auto &li = ul.add(h5::li);
                    add_link(li, prefix + "/stdtensor");
                    show_header_list(li.add(h5::ul), ttl_headers, "stdtensor");
                }
                {
                    auto &li = ul.add(h5::li);
                    add_link(li, prefix + "/stdnn-ops");
                    show_header_list(li.add(h5::ul), ttl_nn_headers,
                                     "stdnn-ops");
                }
                {
                    auto &li = ul.add(h5::li);
                    add_link(li, prefix + "/stdnn-ops-cuda");
                }
                {
                    auto &li = ul.add(h5::li);
                    add_link(li, prefix + "/nn-graph-experimental");
                    show_header_list(li.add(h5::ul), ttl_nn_graph_headers,
                                     "nn-graph-experimental", "draft");
                }
            }
            {
                section.add(h5::h3).text("Learning");
                auto &ul = section.add(h5::ul);
                {
                    auto &li = ul.add(h5::li);
                    li.add(h5::span).text("stdml-experimental");
                    show_header_list(li.add(h5::ul), stdml_headers,
                                     "stdml-experimental", "draft");
                }
            }
            {
                section.add(h5::h3).text("Utilities");
                auto &ul = section.add(h5::ul);
                {
                    auto &li = ul.add(h5::li);
                    add_link(li, prefix + "/stdtracer");
                    show_header_list(li.add(h5::ul), tracer_headers,
                                     "stdtracer");
                }
            }
        }
    }
    doc >> os;
}
