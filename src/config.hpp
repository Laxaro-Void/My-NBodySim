#pragma once
// OpenCL
#define CL_TARGET_OPENCL_VERSION 120
#define __CL_ENABLE_EXCEPTIONS

// Glad, GLFW, OpenCl
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#ifdef __APPLE__
    #include <OpenCL/cl.hpp>
#else
    #include <openCL/cl.hpp>
#endif

// Stdc++
#include <iostream>
#include <ostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <queue>
#include <unordered_map>
#include <memory>

// ImGUI
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

// GLM
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform2.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <glm/gtx/rotate_vector.hpp>


// Global Config
extern bool DEBUG;

// Special Operators
std::ostream& operator <<(std::ostream& out, const glm::vec3 &v);
std::ostream& operator <<(std::ostream& out, const glm::mat4 &v);

// cl <-> glm Conversions
glm::vec3 cl_float3_to_glm_vec3(const cl_float3 &v);
cl_float3 glm_vec3_to_cl_float3(const glm::vec3 &v);
glm::vec2 cl_float2_to_glm_vec2(const cl_float2 &v);
cl_float2 glm_vec2_to_cl_float2(const glm::vec2 &v);

// cl operations
cl_float3 operator +(const cl_float3 &a, const cl_float3 &b);
cl_float3 operator -(const cl_float3 &a, const cl_float3 &b);
cl_float3 operator *(const cl_float3 &a, const cl_float3 &b);
cl_float3 operator *(const float &b, const cl_float3 &a);
cl_float3 operator /(const float &b, const cl_float3 &a);
cl_float3 operator *(const cl_float3 &a, const float &b);
cl_float3 operator /(const cl_float3 &a, const float &b);
cl_float3 sqrt(const cl_float3 &a);
float dot(const cl_float3 &a, const cl_float3 &b);
float length(const cl_float3 &a);

// Kernel Global Config
extern cl::NDRange local_threads;