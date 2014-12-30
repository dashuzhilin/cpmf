#include <cpmf/common/common.hpp>
#include <cpmf/utils/utils.hpp>
#include "switch.hpp"

namespace cpmf {
namespace parallel {

void train(const std::shared_ptr<cpmf::common::Matrix> R,
           std::shared_ptr<cpmf::common::Model> model,
           const cpmf::BaseParams &base_params) {
  cpmf::utils::Timer timer;
  cpmf::utils::Logger logger;
  Scheduler scheduler(R->num_user_blocks, R->num_item_blocks,
                      base_params.num_threads);

  float init_rmse = model->calc_rmse();
  timer.start("Now iteration starts...");
  logger.put_table_header("iteration", 2, "time", "RMSE");
  logger.put_table_row(0, 2, 0.000, init_rmse);
  scheduler.start(R, model);
  for (int iter = 1; iter <= base_params.max_iter; iter++) {
    scheduler.wait_for_all_blocks_processed();
    float iter_time = timer.pause();
    float rmse = model->calc_rmse();
    logger.put_table_row(iter, 2, iter_time, rmse);
    timer.resume();
    scheduler.resume();
  }
  timer.stop("ends.");
  scheduler.terminate();
}

} // namespace parallel
} // namespace cpmf
