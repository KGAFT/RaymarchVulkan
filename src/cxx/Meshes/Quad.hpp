#pragma once

#include "Vulkan/VulkanDevice/VulkanDevice.h"
#include <map>

#include <Vulkan/VulkanBuffers/IndexBuffer.h>
#include <Vulkan/VulkanBuffers/VertexBuffer.h>

std::pair<IndexBuffer*, VertexBuffer*> acquireQuadMesh(VulkanDevice* device);