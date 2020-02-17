#pragma once
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

namespace html5
{
class attr
{
    const std::string name;

  public:
    using value = std::string;

    attr(std::string name) : name(std::move(name)) {}

    operator std::string() const { return name; }
};

class tag
{
    static constexpr auto default_tab_size = 4;

    const std::string name;
    bool single;
    std::map<std::string, std::string> attrs;

  public:
    tag(std::string name, bool single = false)
        : name(std::move(name)), single(single)
    {
    }

    std::ostream &begin(std::ostream &os, int lvl = 0,
                        int tab = default_tab_size) const
    {
        if (name.empty()) { return os; }
        if (lvl) { os << std::string(lvl * tab, ' '); }
        os << "<" << name;
        if (!attrs.empty()) {
            for (const auto &[k, v] : attrs) {
                os << ' ' << k << "=\"" << v << '"';
            }
        }
        if (single) { os << '/'; }
        os << '>';
        return os;
    }

    std::ostream &end(std::ostream &os, int lvl = 0,
                      int tab = default_tab_size) const
    {
        if (single || name.empty()) { return os; }
        if (lvl) { os << std::string(lvl * tab, ' '); }
        os << "</" << name << ">";
        return os;
    }

    void attr(const attr &a, const std::string &value) { attrs[a] = value; }
};

class element
{
    using element_list = std::vector<std::unique_ptr<element>>;

    tag root;
    element_list children;
    std::string plain_text;

    std::ostream &write_to(std::ostream &os, int lvl = 0) const
    {
        root.begin(os, lvl);
        if (children.empty()) {
            if (!plain_text.empty()) { os << plain_text; }
            root.end(os, 0);
            os << std::endl;
        } else {
            os << std::endl;
            for (const auto &child : children) { child->write_to(os, lvl + 1); }
            root.end(os, lvl);
            os << std::endl;
        }
        return os;
    }

  public:
    element(const tag &root) : root(root) {}

    element &text(std::string t)
    {
        plain_text = t;
        return *this;
    }

    element &add(const tag &child)
    {
        auto p = new element(child);
        children.emplace_back(p);
        return *p;
    }

    element &attr(const attr &a, const std::string value)
    {
        root.attr(a, value);
        return *this;
    }

    void operator<<(const tag &child) { add(child); }

    void operator>>(std::ostream &os) const { write_to(os); }
};
}  // namespace html5
