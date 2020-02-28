#pragma once
#include <string>
#include <vector>

#include <stdml/doc/bits/slist.hpp>

struct repo {
    std::string url;
};

const slist stdml_repos({
    "stdtensor",
    "stdnn-ops",
    "stdnn-ops-cuda",
    "nn-graph-experimental",
    "stdtracer",
});

const std::string prefix = "https://github.com/lgarithm";
