// Copyright 2014 Open Source Robotics Foundation, Inc.
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

#ifndef RCLC__RCLC_H_
#define RCLC__RCLC_H_

#include <stdbool.h>  // For bool
#include <stddef.h>  // For size_t

// For rosidl_message_type_support_t
#include "rosidl_generator_c/message_type_support_struct.h"

#include "rclc/types.h"  // For rclc_*_t types

/// Global initialization for rclc; should be called once per process.
rclc_ret_t
rclc_init(int argc, char ** argv);

/// Global state check; returns false on user shutdown after ctrl-c.
bool
rclc_ok(void);

/// Sleeps (blocks) for a given number of milliseconds.
void
rclc_sleep_ms(size_t milliseconds);

/// Processes node callbacks and blocks until user shutdown or ctrl-c.
void
rclc_spin_node(rclc_node_t * node);

/// Creates a rclc_node_t, which represents a ROS Node.
rclc_node_t *
rclc_create_node(const char * name, const char * namespace_);

/// Destroys a rclc_node_t.
rclc_ret_t
rclc_destroy_node(rclc_node_t * node);

/// Creates a rclc_publisher_t, which represents a ROS Publisher.
rclc_publisher_t *
rclc_create_publisher(
  rclc_node_t * node,
  const rosidl_message_type_support_t * type_support,
  const char * topic_name,
  size_t queue_size);

/// Destroys a rclc_publisher_t.
rclc_ret_t
rclc_destroy_publisher(rclc_publisher_t * publisher);

/// Publishes a ROS message to a ROS Topic using a ROS Publisher.
rclc_ret_t
rclc_publish(const rclc_publisher_t * publisher, const void * ros_message);

/// Creates a rclc_subscription_t, which represents a ROS Subscription.
rclc_subscription_t *
rclc_create_subscription(
  rclc_node_t * node,
  const rosidl_message_type_support_t * type_support,
  const char * topic_name,
  rclc_callback_t callback,
  size_t queue_size,
  bool ignore_local_publications);

/// Destroys a rclc_subscription_t.
rclc_ret_t
rclc_destroy_subscription(rclc_subscription_t * subscription);

/// Creates a rclc_executor_t, which processes callbacks in ROS Nodes.
rclc_executor_t *
rclc_create_executor();

/// Destroys a rclc_executor_t.
rclc_ret_t
rclc_destroy_executor(rclc_executor_t * executor);

/// Adds a ROS Node to the internal list of nodes in the executor.
rclc_ret_t
rclc_executor_add_node(rclc_executor_t * executor, const rclc_node_t * node);

/// Causes the executor to process callbacks generated by ROS Nodes.
rclc_ret_t
rclc_executor_spin();

#endif  // RCLC__RCLC_H_
