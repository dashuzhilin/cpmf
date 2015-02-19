#ifndef CPMF_PARALLEL_HPP_
#define CPMF_PARALLEL_HPP_

#if defined TP_BASED
#include <cpmf/parallel/tp_based/tp_based.hpp>
using namespace cpmf::parallel::tp_based;

#elif defined LINE_BASED
#include <cpmf/parallel/line_based/line_based.hpp>
using namespace cpmf::parallel::line_based;

#elif defined FPSGD
#include <cpmf/parallel/fpsgd/fpsgd.hpp>
using namespace cpmf::parallel::fpsgd;

#endif


#include <cpmf/utils/utils.hpp>

namespace cpmf {
namespace parallel {

void train(const std::shared_ptr<cpmf::common::Matrix> R,
           std::shared_ptr<cpmf::common::Model> model,
           const cpmf::BaseParams &base_params);

} // namespace parallel
} // namespace cpmf

#endif // CPMF_PARALLEL_HPP_
