# Copyright 2020 The IREE Authors
#
# Licensed under the Apache License v2.0 with LLVM Exceptions.
# See https://llvm.org/LICENSE.txt for license information.
# SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

load("@bazel_skylib//rules:common_settings.bzl", "string_list_flag")
load("//build_tools/bazel:build_defs.oss.bzl", "iree_runtime_cc_library")

package(
    default_visibility = ["//visibility:public"],
    features = ["layering_check"],
    licenses = ["notice"],  # Apache 2.0
)

ALL_DRIVERS = [
    "cuda",
    "local-sync",
    "local-task",
    "vulkan",
]

string_list_flag(
    name = "enabled_drivers",
    build_setting_default = [
        "local-sync",
        "local-task",
        "vulkan",
    ],
)

[
    config_setting(
        name = "{}_enabled".format(driver),
        flag_values = {
            ":enabled_drivers": driver,
        },
    )
    for driver in ALL_DRIVERS
]

iree_runtime_cc_library(
    name = "drivers",
    srcs = ["init.c"],
    hdrs = ["init.h"],
    deps = [
               "//runtime/src/iree/base",
               "//runtime/src/iree/base:tracing",
               "//runtime/src/iree/hal",
           ] + select({
               ":cuda_enabled": ["//runtime/src/iree/hal/drivers/cuda/registration"],
               "//conditions:default": [],
           }) +
           select({
               ":local-sync_enabled": ["//runtime/src/iree/hal/drivers/local_sync/registration"],
               "//conditions:default": [],
           }) +
           select({
               ":local-task_enabled": ["//runtime/src/iree/hal/drivers/local_task/registration"],
               "//conditions:default": [],
           }) +
           select({
               ":vulkan_enabled": ["//runtime/src/iree/hal/drivers/vulkan/registration"],
               "//conditions:default": [],
           }),
)
