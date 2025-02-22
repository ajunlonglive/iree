// Copyright 2021 The IREE Authors
//
// Licensed under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

// Exports "main" entry-points for individual IREE compiler tools. Actual
// binaries delegate to these main entry-points, allowing their backing
// implementations to be commingled in a backing shared library that is
// hermetic.

#ifndef IREE_COMPILER_API2_TOOL_ENTRY_POINTS_H
#define IREE_COMPILER_API2_TOOL_ENTRY_POINTS_H

#include "mlir-c/Support.h"

#ifdef __cplusplus
extern "C" {
#endif

/// Runs the IREE compiler main function. This is used to build
/// iree-compile-like binaries that link against a common shared library.
MLIR_CAPI_EXPORTED int ireeCompilerRunMain(int argc, char **argv);

/// Runs the iree-opt main function.
MLIR_CAPI_EXPORTED int ireeOptRunMain(int argc, char **argv);

/// Runs the iree-mlir-lsp-server main function.
MLIR_CAPI_EXPORTED int ireeMlirLspServerRunMain(int argc, char **argv);

/// Runs LLD in "generic" mode (i.e. as `lld`, requiring a -flavor command line
/// option). This does *not* mean that we support invoking LLD as a library,
/// but we do support creating busybox style tools that invoke it standalone
/// by linking against the CAPI.
MLIR_CAPI_EXPORTED int ireeCompilerRunLldMain(int argc, char **argv);

#ifdef __cplusplus
}
#endif

#endif  // IREE_COMPILER_API2_TOOL_ENTRY_POINTS_H
