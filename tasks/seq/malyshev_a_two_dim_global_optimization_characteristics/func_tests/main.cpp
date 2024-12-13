// Copyright 2023 Nesterov Alexander
#include <gtest/gtest.h>

#include <vector>

#include "seq/malyshev_a_two_dim_global_optimization_characteristics/include/ops_seq.hpp"

TEST(malyshev_a_two_dim_global_optimization_characteristics_seq, SimpleTest) {
  auto target = [](double x, double y) -> double { return pow(x - 2, 2) + pow(y - 3, 2); };

  std::vector<malyshev_a_two_dim_global_optimization_characteristics_seq::constraint_t> constraints{
      [](double x, double y) -> bool { return x + y >= 4; }, [](double x, double y) -> bool { return x - y <= 1; },
      [](double x, double y) -> bool { return x >= 0; }, [](double x, double y) -> bool { return y >= 0; }};

  std::shared_ptr<ppc::core::TaskData> taskData = std::make_shared<ppc::core::TaskData>();
  malyshev_a_two_dim_global_optimization_characteristics_seq::TestTaskSequential task(taskData, target, constraints);

  malyshev_a_two_dim_global_optimization_characteristics_seq::Point res;
  malyshev_a_two_dim_global_optimization_characteristics_seq::Point ref(2, 3, target(2, 3));
  std::pair<double, double> bounds[2]{{0, 10}, {0, 10}};
  double eps = 1e-4;

  taskData->inputs.emplace_back(reinterpret_cast<uint8_t *>(&bounds));
  taskData->inputs.emplace_back(reinterpret_cast<uint8_t *>(&eps));
  taskData->outputs.emplace_back(reinterpret_cast<uint8_t *>(&res));
  taskData->inputs_count.emplace_back(2);
  taskData->inputs_count.emplace_back(1);
  taskData->outputs_count.emplace_back(1);

  ASSERT_TRUE(task.validation());
  ASSERT_TRUE(task.pre_processing());
  ASSERT_TRUE(task.run());
  ASSERT_TRUE(task.post_processing());

  ASSERT_NEAR(res.x, ref.x, eps);
  ASSERT_NEAR(res.y, ref.y, eps);
  ASSERT_NEAR(res.value, ref.value, eps);
}

TEST(malyshev_a_two_dim_global_optimization_characteristics_seq, RastrigrinTest) {
  auto target = [](double x, double y) -> double {
    return 20 + (pow(x, 2) - 10 * cos(2 * M_PI * x)) + (pow(y, 2) - 10 * cos(2 * M_PI * y));
  };

  std::vector<malyshev_a_two_dim_global_optimization_characteristics_seq::constraint_t> constraints{
      [](double x, double y) { return x + y >= -1; }, [](double x, double y) { return x - y <= 2; },
      [](double x, double y) { return x >= 0; }, [](double x, double y) { return y >= 0; }};

  std::shared_ptr<ppc::core::TaskData> taskData = std::make_shared<ppc::core::TaskData>();
  malyshev_a_two_dim_global_optimization_characteristics_seq::TestTaskSequential task(taskData, target, constraints);

  malyshev_a_two_dim_global_optimization_characteristics_seq::Point res;
  malyshev_a_two_dim_global_optimization_characteristics_seq::Point ref(0, 0, target(0, 0));
  std::pair<double, double> bounds[2]{{-4.12, 4.12}, {-4.12, 4.12}};
  double eps = 1e-4;

  taskData->inputs.emplace_back(reinterpret_cast<uint8_t *>(&bounds));
  taskData->inputs.emplace_back(reinterpret_cast<uint8_t *>(&eps));
  taskData->outputs.emplace_back(reinterpret_cast<uint8_t *>(&res));
  taskData->inputs_count.emplace_back(2);
  taskData->inputs_count.emplace_back(1);
  taskData->outputs_count.emplace_back(1);

  ASSERT_TRUE(task.validation());
  ASSERT_TRUE(task.pre_processing());
  ASSERT_TRUE(task.run());
  ASSERT_TRUE(task.post_processing());

  ASSERT_NEAR(res.x, ref.x, eps);
  ASSERT_NEAR(res.y, ref.y, eps);
  ASSERT_NEAR(res.value, ref.value, eps);
}

TEST(malyshev_a_two_dim_global_optimization_characteristics_seq, HimmelblauTest) {
  auto target = [](double x, double y) -> double { return pow(x * x + y - 11, 2) + pow(x + y * y - 7, 2); };

  std::vector<malyshev_a_two_dim_global_optimization_characteristics_seq::constraint_t> constraints{
      [](double x, double y) { return x * x + y * y <= 100; }, [](double x, double y) { return x >= -10; },
      [](double x, double y) { return y >= -10; }};

  std::shared_ptr<ppc::core::TaskData> taskData = std::make_shared<ppc::core::TaskData>();
  malyshev_a_two_dim_global_optimization_characteristics_seq::TestTaskSequential task(taskData, target, constraints);

  malyshev_a_two_dim_global_optimization_characteristics_seq::Point res;
  malyshev_a_two_dim_global_optimization_characteristics_seq::Point ref(3, 2, target(3, 2));
  std::pair<double, double> bounds[2]{{-10.0, 10.0}, {-10.0, 10.0}};
  double eps = 1e-4;

  taskData->inputs.emplace_back(reinterpret_cast<uint8_t *>(&bounds));
  taskData->inputs.emplace_back(reinterpret_cast<uint8_t *>(&eps));
  taskData->outputs.emplace_back(reinterpret_cast<uint8_t *>(&res));
  taskData->inputs_count.emplace_back(2);
  taskData->inputs_count.emplace_back(1);
  taskData->outputs_count.emplace_back(1);

  ASSERT_TRUE(task.validation());
  ASSERT_TRUE(task.pre_processing());
  ASSERT_TRUE(task.run());
  ASSERT_TRUE(task.post_processing());

  ASSERT_NEAR(res.x, ref.x, eps);
  ASSERT_NEAR(res.y, ref.y, eps);
  ASSERT_NEAR(res.value, ref.value, eps);
}

TEST(malyshev_a_two_dim_global_optimization_characteristics_seq, AckleyTest) {
  auto target = [](double x, double y) -> double {
    return -20 * exp(-0.2 * sqrt(0.5 * (x * x + y * y))) - exp(0.5 * (cos(2 * M_PI * x) + cos(2 * M_PI * y))) + 20 +
           M_E;
  };

  std::vector<malyshev_a_two_dim_global_optimization_characteristics_seq::constraint_t> constraints{
      [](double x, double y) { return x + y >= -5; }, [](double x, double y) { return x - y <= 5; }};

  std::shared_ptr<ppc::core::TaskData> taskData = std::make_shared<ppc::core::TaskData>();
  malyshev_a_two_dim_global_optimization_characteristics_seq::TestTaskSequential task(taskData, target, constraints);

  malyshev_a_two_dim_global_optimization_characteristics_seq::Point res;
  malyshev_a_two_dim_global_optimization_characteristics_seq::Point ref(0, 0, target(0, 0));
  std::pair<double, double> bounds[2]{{-5.0, 5.0}, {-5.0, 5.0}};
  double eps = 1e-4;

  taskData->inputs.emplace_back(reinterpret_cast<uint8_t *>(&bounds));
  taskData->inputs.emplace_back(reinterpret_cast<uint8_t *>(&eps));
  taskData->outputs.emplace_back(reinterpret_cast<uint8_t *>(&res));
  taskData->inputs_count.emplace_back(2);
  taskData->inputs_count.emplace_back(1);
  taskData->outputs_count.emplace_back(1);

  ASSERT_TRUE(task.validation());
  ASSERT_TRUE(task.pre_processing());
  ASSERT_TRUE(task.run());
  ASSERT_TRUE(task.post_processing());

  ASSERT_NEAR(res.x, ref.x, eps);
  ASSERT_NEAR(res.y, ref.y, eps);
  ASSERT_NEAR(res.value, ref.value, eps);
}

TEST(malyshev_a_two_dim_global_optimization_characteristics_seq, MatyasTest) {
  auto target = [](double x, double y) -> double { return 0.26 * (x * x + y * y) - 0.48 * x * y; };

  std::vector<malyshev_a_two_dim_global_optimization_characteristics_seq::constraint_t> constraints{
      [](double x, double y) { return x >= -10; }, [](double x, double y) { return y >= -10; }};

  std::shared_ptr<ppc::core::TaskData> taskData = std::make_shared<ppc::core::TaskData>();
  malyshev_a_two_dim_global_optimization_characteristics_seq::TestTaskSequential task(taskData, target, constraints);

  malyshev_a_two_dim_global_optimization_characteristics_seq::Point res;
  malyshev_a_two_dim_global_optimization_characteristics_seq::Point ref(0, 0, target(0, 0));
  std::pair<double, double> bounds[2]{{-10.0, 10.0}, {-10.0, 10.0}};
  double eps = 1e-4;

  taskData->inputs.emplace_back(reinterpret_cast<uint8_t *>(&bounds));
  taskData->inputs.emplace_back(reinterpret_cast<uint8_t *>(&eps));
  taskData->outputs.emplace_back(reinterpret_cast<uint8_t *>(&res));
  taskData->inputs_count.emplace_back(2);
  taskData->inputs_count.emplace_back(1);
  taskData->outputs_count.emplace_back(1);

  ASSERT_TRUE(task.validation());
  ASSERT_TRUE(task.pre_processing());
  ASSERT_TRUE(task.run());
  ASSERT_TRUE(task.post_processing());

  ASSERT_NEAR(res.x, ref.x, eps);
  ASSERT_NEAR(res.y, ref.y, eps);
  ASSERT_NEAR(res.value, ref.value, eps);
}

TEST(malyshev_a_two_dim_global_optimization_characteristics_seq, GoldsteinPriceTest) {
  auto target = [](double x, double y) -> double {
    return (1 + pow(x + y + 1, 2) * (19 - 14 * x + 3 * x * x - 14 * y + 6 * x * y + 3 * y * y)) *
           (30 + pow(2 * x - 3 * y, 2) * (18 - 32 * x + 12 * x * x + 48 * y - 36 * x * y + 27 * y * y));
  };

  std::vector<malyshev_a_two_dim_global_optimization_characteristics_seq::constraint_t> constraints{
      [](double x, double y) { return x * x + y * y <= 4; }, [](double x, double y) { return x >= -2; },
      [](double x, double y) { return y >= -2; }};

  std::shared_ptr<ppc::core::TaskData> taskData = std::make_shared<ppc::core::TaskData>();
  malyshev_a_two_dim_global_optimization_characteristics_seq::TestTaskSequential task(taskData, target, constraints);

  malyshev_a_two_dim_global_optimization_characteristics_seq::Point res;
  malyshev_a_two_dim_global_optimization_characteristics_seq::Point ref(0, -1, target(0, -1));
  std::pair<double, double> bounds[2]{{-2.0, 2.0}, {-2.0, 2.0}};
  double eps = 1e-4;

  taskData->inputs.emplace_back(reinterpret_cast<uint8_t *>(&bounds));
  taskData->inputs.emplace_back(reinterpret_cast<uint8_t *>(&eps));
  taskData->outputs.emplace_back(reinterpret_cast<uint8_t *>(&res));
  taskData->inputs_count.emplace_back(2);
  taskData->inputs_count.emplace_back(1);
  taskData->outputs_count.emplace_back(1);

  ASSERT_TRUE(task.validation());
  ASSERT_TRUE(task.pre_processing());
  ASSERT_TRUE(task.run());
  ASSERT_TRUE(task.post_processing());

  ASSERT_NEAR(res.x, ref.x, eps);
  ASSERT_NEAR(res.y, ref.y, eps);
  ASSERT_NEAR(res.value, ref.value, eps);
}

TEST(malyshev_a_two_dim_global_optimization_characteristics_seq, BoothTest) {
  auto target = [](double x, double y) -> double { return pow(x + 2 * y - 7, 2) + pow(2 * x + y - 5, 2); };

  std::vector<malyshev_a_two_dim_global_optimization_characteristics_seq::constraint_t> constraints{
      [](double x, double y) { return x >= -10; }, [](double x, double y) { return y >= -10; },
      [](double x, double y) { return x * x + y * y <= 100; }};

  std::shared_ptr<ppc::core::TaskData> taskData = std::make_shared<ppc::core::TaskData>();
  malyshev_a_two_dim_global_optimization_characteristics_seq::TestTaskSequential task(taskData, target, constraints);

  malyshev_a_two_dim_global_optimization_characteristics_seq::Point res;
  malyshev_a_two_dim_global_optimization_characteristics_seq::Point ref(1, 3, target(1, 3));
  std::pair<double, double> bounds[2]{{-10.0, 10.0}, {-10.0, 10.0}};
  double eps = 1e-4;

  taskData->inputs.emplace_back(reinterpret_cast<uint8_t *>(&bounds));
  taskData->inputs.emplace_back(reinterpret_cast<uint8_t *>(&eps));
  taskData->outputs.emplace_back(reinterpret_cast<uint8_t *>(&res));
  taskData->inputs_count.emplace_back(2);
  taskData->inputs_count.emplace_back(1);
  taskData->outputs_count.emplace_back(1);

  ASSERT_TRUE(task.validation());
  ASSERT_TRUE(task.pre_processing());
  ASSERT_TRUE(task.run());
  ASSERT_TRUE(task.post_processing());

  ASSERT_NEAR(res.x, ref.x, eps);
  ASSERT_NEAR(res.y, ref.y, eps);
  ASSERT_NEAR(res.value, ref.value, eps);
}