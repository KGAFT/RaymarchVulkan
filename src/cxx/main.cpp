#include <iostream>

#include <Vulkan/VulkanDevice/VulkanDevice.h>
#include <Vulkan/VulkanSwapChain.h>
#include "GLFW/glfw3.h"
#include "Pipelines/RaymarchPipeline.hpp"
#include "Vulkan/VulkanInstance.h"
#include "Window/Window.h"
#include "vulkan/vulkan_core.h"

VulkanInstance* instance;
VulkanDevice* device;
Window* window;
VulkanSwapChain* swapChain;
RaymarchPipeline* raymarch;

void createInstance();
void createDevice();

int main(){
    window = Window::createWindow(800, 600, "RayMarchExample", nullptr);
    createInstance();
    createDevice();
    swapChain = new VulkanSwapChain(device, 800, 600);
    raymarch = new RaymarchPipeline(device, swapChain, 800, 600);
    window->registerResizeCallback(raymarch);
   
    while(!window->needToClose()){
        window->preRenderEvents();
        raymarch->render();
       window->postRenderEvents();
    }
    delete raymarch;
    delete swapChain;
    delete device;
    delete instance;
    delete window;
}

void createInstance(){
    instance = new VulkanInstance;
    std::vector<const char*> extensions;
    uint32_t c;
    const char** exts = glfwGetRequiredInstanceExtensions(&c);
    for(uint32_t counter = 0; counter<c; counter++){
        extensions.push_back(exts[counter]);
    }

    instance->createInstance("RayMarchExample", true, extensions);
}

VkPhysicalDevice askUserForDevice(){
    std::map<VkPhysicalDevice, VkPhysicalDeviceProperties> devices = VulkanDevice::enumerateSupportedDevices(instance->getInstance(), window->getWindowSurface(instance->getInstance()), false);
    std::vector<VkPhysicalDevice> suitDevs;
    std::cout<<"The engine found several devices, choose what use for render: "<<std::endl;
    std::cout<<"ID:\tDeviceName:"<<std::endl;
    int count = 0;
    for(const auto& el : devices){
        std::cout<<count<<"\t"<<el.second.deviceName<<std::endl;
        count++;
        suitDevs.push_back(el.first);
    }
    std::cout<<"Please enter selected device ID: ";
    std::cin>>count;
    return suitDevs[count];
}

void createDevice(){
    VkPhysicalDevice dev = askUserForDevice();
    device = new VulkanDevice(dev, window->getWindowSurface(instance->getInstance()), instance->getInstance(), true, false);
}
