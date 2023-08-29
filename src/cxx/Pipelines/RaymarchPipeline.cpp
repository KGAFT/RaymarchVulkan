#include "RaymarchPipeline.hpp"
#include "../Meshes/Quad.hpp"
#include "vulkan/vulkan_core.h"
#include <stdexcept>

RaymarchPipeline::RaymarchPipeline(VulkanDevice *device,
                                   VulkanSwapChain *swapChain, int startWidth,
                                   int startHeight)
    : device(device), swapChain(swapChain) {
  if (device == nullptr || swapChain == nullptr) {
    throw std::runtime_error("Error swapchain or device is not initialized");
  }
  input.resolution.x = startWidth;
  input.resolution.y = startHeight;

  shader = ShaderLoader::loadShaders("glsl/Raymarch", device);

  PipelineEndConfig endConfig{};
  endConfig.vertexInputs.push_back(
      {0, 3, sizeof(float), VK_FORMAT_R32G32B32_SFLOAT});

  endConfig.vertexInputs.push_back(
      {1, 2, sizeof(float), VK_FORMAT_R32G32_SFLOAT});
  endConfig.pushConstantInfos.push_back(
      {VK_SHADER_STAGE_FRAGMENT_BIT, sizeof(HostInput)});
  endRenderPipeline = new VulkanEndRenderPipeline(
      device, new VulkanSyncManager(device, swapChain), shader, &endConfig,
      startWidth, startHeight, swapChain->getSwapChainImageViews(), 1,
      swapChain->getSwapChainImageFormat(), true, VK_CULL_MODE_NONE,
      VK_COMPARE_OP_LESS);
  endRenderPipeline->getPushConstants()[0]->setData(&input);
  quadMesh = acquireQuadMesh(device);
}

void RaymarchPipeline::render() {
  VkCommandBuffer cmd = endRenderPipeline->beginRender();
  endRenderPipeline->updatePushConstants();
  quadMesh.second->bind(cmd);
  quadMesh.first->bind(cmd);
  quadMesh.first->draw(cmd);
  endRenderPipeline->endRenderPass();
  endRenderPipeline->endRender();
}

void RaymarchPipeline::resized(int width, int height) {
  input.resolution.x = width;
  input.resolution.y = height;
  vkDeviceWaitIdle(device->getDevice());
  endRenderPipeline->resized(width, height);
}

RaymarchPipeline::~RaymarchPipeline() {
  delete endRenderPipeline;
  delete shader;
}