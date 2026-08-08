Here are the best **free, modern, beginner-friendly** resources that remain useful even if you need to stay compatible with (or fall back to) Vulkan 1.0. Most use Vulkan 1.3+ features (especially dynamic rendering), but the core concepts, structure, and flow translate cleanly—you can map the differences yourself using the official docs.

### Top recommendations (ordered for a new engine)

1. **How to Vulkan in 2026** (Sascha Willems)  
   - Site: [https://www.howtovulkan.com](https://www.howtovulkan.com)  
   - Repo: [https://github.com/SaschaWillems/HowToVulkan](https://github.com/SaschaWillems/HowToVulkan)  
   - Single-page, minimalist, “get something real on screen in one day” tutorial. Uses Vulkan 1.3 + dynamic rendering, but the explanations of instance/device/queues/swapchain/pipelines/synchronization are excellent and map directly to 1.0. Written by one of the most experienced Vulkan sample authors. Highly recommended starting point.

2. **Khronos Vulkan Tutorial** (official, updated)  
   - [https://docs.vulkan.org/tutorial/latest/](https://docs.vulkan.org/tutorial/latest/)  
   - The modernized official tutorial (based on the classic Overvoorde one). Now teaches dynamic rendering, timeline semaphores, modern C++/Vulkan-Hpp, etc. The early chapters still cover all the foundational objects you need for Vulkan 1.0. Also includes a “Building a Simple Game Engine” section that is especially relevant for a custom engine.

3. **vkguide.dev** (Viktor Galecki / “vkguide”)  
   - [https://www.vkguide.dev](https://www.vkguide.dev)  
   - Excellent intermediate-beginner guide focused on building a real engine-style codebase. Uses Vulkan 1.3 + dynamic rendering by default. There is a legacy version for older APIs if you need it. Very practical for engine architecture.

4. **Sascha Willems Vulkan Samples**  
   - [https://github.com/SaschaWillems/Vulkan](https://github.com/SaschaWillems/Vulkan)  
   - Not a linear tutorial, but the gold-standard collection of examples. Includes an explicit **Basic triangle using Vulkan 1.0** example and a Vulkan 1.3 counterpart side-by-side. Perfect for seeing exactly what changes between the old and new paths. Extremely well-commented.

### Strong video / alternative options
- **OGLDEV – Vulkan For Beginners** (YouTube playlist)  
  Solid step-by-step video series. Covers both classic and more modern approaches.
- **“Learn Modern Vulkan in 2 Hours”** (constref on YouTube)  
  Focuses on dynamic rendering and cleaner modern practices. Good for seeing the simplified path, then you can reverse-engineer the 1.0 equivalents.
- Classic **vulkan-tutorial.com** (Alexander Overvoorde)  
  Still useful for pure Vulkan 1.0-era code, but the author himself now points people to the newer resources above. Keep it as a reference for the original render-pass style.

### Quick advice for your use case
- Start with **How to Vulkan in 2026** or the **Khronos tutorial**.  
- When you hit dynamic rendering (`vkCmdBeginRendering`), look up the equivalent `VkRenderPass` + `VkFramebuffer` path in the Sascha Willems 1.0 triangle sample or the official Vulkan specification.  
- For everything else (instance, device, queues, swapchain, command buffers, pipelines, descriptors, synchronization), the modern tutorials are almost 1:1 applicable to Vulkan 1.0.

All of the above are free, actively maintained or recently updated, and written with real engine work in mind. They will give you a solid foundation while letting you stay compatible with older Intel iGPUs when needed.
