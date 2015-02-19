#include <cpmf/common/common.hpp>
#include <cpmf/utils/utils.hpp>
#include "switch.hpp"

namespace cpmf {
namespace parallel {

void train(const std::shared_ptr<cpmf::common::Matrix> R,
           const std::shared_ptr<cpmf::common::Matrix> V,
           std::shared_ptr<cpmf::common::Model> model,
           const cpmf::BaseParams &base_params) {
  cpmf::utils::Timer timer;
  cpmf::utils::Logger logger;
  Scheduler scheduler(R->num_user_blocks, R->num_item_blocks,
                      base_params.num_threads);

  // print header
  if (base_params.calc_rmse) {
    logger.put_table_header("iteration", 3, "time", "tr_rmse", "te_rmse");
  } else {
    logger.put_table_header("iteration", 1, "time");
  }

  // training
  timer.start();
  scheduler.start(R, model);
  for (int iter = 1; iter <= base_params.max_iter; iter++) {
    scheduler.wait_for_all_blocks_processed();
    float iter_time = timer.pause();
    if (base_params.calc_rmse) {
      logger.put_table_row(iter, 3, iter_time, model->calc_rmse(R),
                           model->calc_rmse(V));
    } else {
      logger.put_table_row(iter, 1, iter_time);
    }
    timer.resume();
    scheduler.resume();
  }
  timer.stop("traininig finishes.");
  scheduler.terminate();
}

} // namespace parallel
} // namespace cpmf
