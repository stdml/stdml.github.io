#include <algorithm>
#include <experimental/iterator>
#include <fs>
#include <html5>
#include <map>
#include <sstream>
#include <ttl/tensor>

#include <cxxabi.h>

template <typename T>
std::string type_name(bool html)
{
    int status = 0;

    const std::string name(
        abi::__cxa_demangle(typeid(T).name(), 0, 0, &status));
    if (html) {
        namespace h5 = html5;
        h5::element e(h5::span);
        e.text(h5::escape(name)).attr(h5::_class, "typename");
        std::stringstream ss;
        e >> ss;
        return ss.str();
    }
    return name;
}

std::string join(const std::vector<std::string> &a)
{
    std::stringstream ss;
    std::copy(a.begin(), a.end(),
              std::experimental::make_ostream_joiner(ss, ", "));
    return ss.str();
}

template <typename Pairs>
void add_section(html5::element &e, const std::string &title, const Pairs &doc)
{
    namespace h5 = html5;
    auto &s = e.add(h5::section);
    s.add(h5::h3).text(title);
    auto &t = s.add(h5::table);
    for (const auto &[k, v] : doc) {
        auto &tr = t.add(h5::tr);
        tr.add(h5::td).text(k);
        tr.add(h5::td).text(v);
    }
}

void std_tensor_doc(std::ostream &os)
{
    namespace h5 = html5;
    h5::element doc(h5::html);
    {
        auto &h = doc.add(h5::head);
        h.add(h5::title).text("stdml - stdtensor");
        h.add(h5::link)
            .attr(h5::rel, "stylesheet")
            .attr(h5::type, "text/css")
            .attr(h5::href, "style.css");
    }
    auto &b = doc.add(h5::body);

    {
        auto &s = b.add(h5::section);
        s.add(h5::h2).text("stdtensor - templates for tensor types");
    }
    {
        auto &s = b.add(h5::section);
        s.add(h5::h3).text(
            h5::escape("ttl::tensor<R, r, D = ttl::host_memory>"));
        s.add(h5::h3).text(
            h5::escape("ttl::tensor_ref<R, r, D = ttl::host_memory>"));
        s.add(h5::h3).text(
            h5::escape("ttl::tensor_view<R, r, D = ttl::host_memory>"));
    }

    using ordered_pairs = std::vector<std::pair<std::string, std::string>>;
    using unordered_pairs = std::map<std::string, std::string>;

    const std::vector<std::string> scalar_types({
        type_name<uint8_t>(true),
        type_name<uint16_t>(true),
        type_name<uint32_t>(true),
        type_name<uint64_t>(true),

        type_name<uint8_t>(true),
        type_name<uint16_t>(true),
        type_name<uint32_t>(true),
        type_name<uint64_t>(true),

        type_name<float>(true),
        type_name<double>(true),

        type_name<std::string>(true),
    });

    ordered_pairs template_parameters({
        {"R", "scalar type, e.g. " + join(scalar_types)},
        {"r", "rank"},
        {"D", "device"},
    });

    unordered_pairs static_member_constants({
        {"rank", "r"},
    });

    unordered_pairs member_types({
        {"value_type", "R"},
        {"shape_type", h5::escape("ttl::shape<r>")},
        {"device_type", "D"},
    });

    unordered_pairs member_functions({
        // Element access
        {"at", "get scalar component"},
        {"data_end", "get pointer to end of data"},
        {"data", "get pointer to data"},
        {"slice", "get slice"},
        {"operator[]", "get sub-tensor"},

        // Iterators
        {"begin", "returns an iterator to the beginning"},
        {"end", "returns an iterator to the end"},

        // Capacity
        {"data_size", "get size of tensor data in bytes"},
        {"dims", "get dimensions"},
        {"shape", "get shape"},
        {"size", "get number of scalar components"},
    });

    add_section(b, "template parameters", template_parameters);
    add_section(b, "static members constants", static_member_constants);
    add_section(b, "member types", member_types);
    add_section(b, "member functions", member_functions);
    doc >> os;
}
