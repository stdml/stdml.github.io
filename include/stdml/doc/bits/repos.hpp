#pragma once
#include <string>
#include <vector>

using slist = std::vector<std::string>;

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
