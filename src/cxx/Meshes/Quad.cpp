#include "Quad.hpp"
#include "Vulkan/VulkanBuffers/IndexBuffer.h"
#include "Vulkan/VulkanBuffers/VertexBuffer.h"
#include <cstddef>

VertexBuffer* quadVB;
IndexBuffer* quadIb;

std::pair<IndexBuffer*, VertexBuffer*> acquireQuadMesh(VulkanDevice* device){
    if(quadVB==nullptr || quadIb==nullptr){
        float QuadVertices[]{
            -1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
            -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
            1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
            1.0f, -1.0f, 0.0f, 1.0f, 0.0f};

        unsigned int QuadIndices[]{
            0, 1, 2,
            3, 2, 1};
        quadVB = new VertexBuffer(5*sizeof(float), 4, device, QuadVertices);
        quadIb = new IndexBuffer(device, QuadIndices, 6);
    }
    return std::pair(quadIb, quadVB);
}