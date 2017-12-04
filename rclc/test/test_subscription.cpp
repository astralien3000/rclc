// Copyright 2017 Open Source Robotics Foundation, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <gtest/gtest.h>

#include <string>
#include <memory>

#include "rclc/rclc.h"

#include "rcl_interfaces/msg/intra_process_message.h"

#define EXPECT_NULL(ptr) EXPECT_EQ((void *)ptr, (void *)NULL)
#define EXPECT_NON_NULL(ptr) EXPECT_NE((void *)ptr, (void *)NULL)

class TestSubscription : public ::testing::Test
{
protected:
  static void SetUpTestCase()
  {
    rclc_init(0, NULL);
  }

  void SetUp()
  {
    node = rclc_create_node("my_node", "/ns");
  }

  void TearDown()
  {
    rclc_destroy_node(node);
  }

  rclc_node_t * node;
};

/*
   Testing subscription construction and destruction.
 */
TEST_F(TestSubscription, construction_and_destruction) {
  auto callback = [](const void * msg) {
      (void)msg;
    };

  {
    rclc_subscription_t * sub =
      rclc_create_subscription(node,
        RCLC_GET_MSG_TYPE_SUPPORT(rcl_interfaces, msg, IntraProcessMessage),
        "topic", callback, 0, false);
    EXPECT_NON_NULL(sub);
    rclc_destroy_subscription(sub);
  }

  {
    rclc_subscription_t * sub =
      rclc_create_subscription(node,
        RCLC_GET_MSG_TYPE_SUPPORT(rcl_interfaces, msg, IntraProcessMessage),
        "invalid_topic?", callback, 0, false);
    EXPECT_NULL(sub);
  }
}
