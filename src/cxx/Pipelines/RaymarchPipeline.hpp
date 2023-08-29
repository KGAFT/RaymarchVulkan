#pragma once

#include "../Window/IWindowResizeCallback.h"

#include <Vulkan/VulkanGraphicsPipeline/PipelineEndConfiguration.h>
#include <Vulkan/VulkanSwapChain.h>
#include <Vulkan/VulkanSync/VulkanSyncManager.h>
#include <Vulkan/VulkanSync/VulkanThreeFrameSync.h>
#include <Vulkan/VulkanEndRenderPipeline.h>
#include <Util/ShaderLoader.h>
#include <Vulkan/VulkanBuffers/IndexBuffer.h>
#include <Vulkan/VulkanBuffers/VertexBuffer.h>

class RaymarchPipeline : public IWindowResizeCallback{
public:
    RaymarchPipeline(VulkanDevice* device, VulkanSwapChain* swapChain, int startWidth, int startHeight);

private:
    VulkanEndRenderPipeline* endRenderPipeline;
    VulkanDevice* device;
    VulkanSwapChain* swapChain;
    VulkanShader* shader;
    std::pair<IndexBuffer*, VertexBuffer*> quadMesh;
public:
    void render();
    void resized(int width, int height) override;   
    ~RaymarchPipeline(); 
};
