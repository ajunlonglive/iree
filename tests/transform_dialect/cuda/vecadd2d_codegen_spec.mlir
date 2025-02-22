transform.structured.canonicalized_sequence failures(propagate) {
^bb1(%variant_op: !pdl.operation):
  // Step 1. Find three linalg.generics and tile to GPU thread blocks.
  // ===========================================================================
  %generics = transform.structured.match ops{["linalg.generic"]} in %variant_op
  transform.iree.tile_to_foreach_thread_and_workgroup_count_region %generics 
                  tile_sizes [5, 3] ( mapping = [#gpu.block<z>, #gpu.block<x>])

  // Step 2. Rank reduce and bufferize and drop HAL decriptor from memref ops.
  // ===========================================================================
  %func = transform.structured.match ops{["func.func"]} in %variant_op
  transform.iree.apply_patterns %func { rank_reducing }
  %variant_op_2 = transform.iree.bufferize { target_gpu } %variant_op
  %memref_func = transform.structured.match ops{["func.func"]} in %variant_op_2
  transform.iree.erase_hal_descriptor_type_from_memref %memref_func

  // Step 3. Map to GPU thread blocks.
  // ===========================================================================
  %func_2 = transform.structured.match ops{["func.func"]} in %variant_op_2
  transform.iree.foreach_thread_to_workgroup %func_2
}
