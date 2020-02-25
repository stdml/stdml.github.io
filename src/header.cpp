#include <fs>
#include <fstream>
#include <html5>
#include <stdml/doc/bits/headers.hpp>
#include <stdml/doc/bits/repos.hpp>

std::string hdr(const std::string &h);

void header_doc(std::ostream &os)
{
    namespace h5 = html5;
    h5::element doc(h5::html);
    doc.add(h5::head).add(h5::title).text("stdml");
    {
        auto &b = doc.add(h5::body);
        auto &s1 = b.add(h5::section);
        s1.add(h5::h2).text("stdml headers");

        auto &t = s1.add(h5::table);
        {
            auto &th = t.add(h5::thead);
            auto &tr = th.add(h5::tr);
            tr.add(h5::td).text("Core");
            tr.add(h5::td);
        }
        {
            auto &tb = t.add(h5::tbody);
            for (const auto &headers : core_headers) {
                for (const auto h : *headers) {
                    auto &tr = tb.add(h5::tr);
                    tr.add(h5::td).text(hdr(h));
                    tr.add(h5::td);
                }
            }
        }
        {
            auto &th = t.add(h5::thead);
            auto &tr = th.add(h5::tr);
            tr.add(h5::td).text("Utility");
            tr.add(h5::td);
        }
        {
            auto &tb = t.add(h5::tbody);
            for (const auto &headers : utility_headers) {
                for (const auto h : *headers) {
                    auto &tr = tb.add(h5::tr);
                    tr.add(h5::td).text(hdr(h));
                    tr.add(h5::td);
                }
            }
        }
    }
    doc >> os;
}
