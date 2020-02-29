#pragma once
#include <string>
#include <vector>

#include <stdml/doc/bits/slist.hpp>

const slist ttl_headers =  //
    slist({
        "ttl/algorithm",
        "ttl/cuda_tensor",
        "ttl/device",
        "ttl/flat_shape",
        "ttl/range",
        "ttl/shape",
        "ttl/tensor",
    }) +
    slist({
        "ttl/experimental/flat_tensor",
        "ttl/experimental/operators",
        "ttl/experimental/raw_tensor",
    }) +
    slist({
        "ttl/mixed_tensor_buffer",
        "ttl/tensor_buffer",
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
    "stdml/dataset",
    "stdml/evaluate",
    "stdml/models",
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
