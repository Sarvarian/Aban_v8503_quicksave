You're right to push back on that.

If a tutorial **never shows `VkRenderPass` / `VkFramebuffer` / `vkCmdBeginRenderPass`**, it is only partially useful for a Vulkan 1.0 path. You would still learn instance, device, queues, swapchain, command buffers, pipelines, descriptors, and synchronization (all of which are the same), but you would be missing the actual mechanism required to draw anything on a pure 1.0 implementation.

### Resources that *do* teach classic render passes (and are still good)

Here are the ones that remain useful for your constraint:

1. **Sascha Willems – Basic triangle (Vulkan 1.0 version)**  
   https://github.com/SaschaWillems/Vulkan/tree/master/examples/triangle  
   This is deliberately written as a verbose, ground-up example using the original render-pass model. It is the cleanest free reference for exactly what you need on old Intel iGPUs. He also has a side-by-side Vulkan 1.3 version so you can compare.

2. **Legacy vkguide (Vulkan 1.1 era)**  
   https://www.vkguide.dev/docs/old_vkguide/  
   The current vkguide dropped render passes, but the older version still exists specifically so people can learn the classic path. It walks through render passes, framebuffers, and the full render loop.

3. **Original vulkan-tutorial.com (Alexander Overvoorde)**  
   https://vulkan-tutorial.com/  
   Still the most detailed step-by-step explanation of creating a render pass, attachment descriptions, subpasses, framebuffers, and beginning/ending the pass. The author now recommends newer resources, but the content itself is solid and free.

4. **Samsung Developer – Introduction to Vulkan Render Passes**  
   https://developer.samsung.com/galaxy-gamedev/resources/articles/renderpasses.html  
   Short, clear article focused purely on render passes and subpasses (with code). Good supplement.

### Practical recommendation for your engine

- Use one of the modern tutorials (How to Vulkan 2026, current Khronos tutorial, or current vkguide) for everything *except* the actual drawing setup.  
- When you reach the point of recording draw commands, switch to the Sascha Willems 1.0 triangle example or the legacy vkguide / original vulkan-tutorial.com chapters on render passes.  
- Keep both code paths in your engine (classic render pass for Vulkan 1.0 devices, dynamic rendering everywhere else). The rest of the code stays almost identical.

That combination gives you modern practices where they help and the exact 1.0 machinery you need for the old Intel integrated GPUs.
