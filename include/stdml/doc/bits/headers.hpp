#pragma once
#include <string>
#include <vector>

using slist = std::vector<std::string>;

const slist ttl_headers({
    "ttl/algorithm",
    "ttl/cuda_tensor",
    "ttl/device",
    "ttl/range",
    "ttl/shape",
    "ttl/tensor",
    "ttl/experimental/flat_tensor",
    "ttl/experimental/raw_tensor",
    "ttl/experimental/operators",
});

const slist ttl_nn_headers({
    "ttl/nn/ops",
    "ttl/nn/layers",
    "ttl/nn/models",
});

const slist ttl_nn_graph_headers({
    "ttl/nn/computation_graph",
    "ttl/nn/graph/builder",
    "ttl/nn/graph/layers",
});

const slist stdml_headers({
    "stdml/control",
    "stdml/models",
    "stdml/dataset",
});

const slist tracer_headers({
    "tracer/cuda",
    "tracer/simple",
    "tracer/stack",
    "tracer/thread",
    "tracer/disable",
});

const std::vector<const slist *> core_headers({
    &ttl_headers,
    &ttl_nn_headers,
    &ttl_nn_graph_headers,
});

const std::vector<const slist *> utility_headers({
    &tracer_headers,
});
