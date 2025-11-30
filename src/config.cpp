#include "config.hpp"
// #define STB_IMAGE_IMPLEMENTATION
// #include "stb_image.h"

template<class A, class B> std::ostream& operator <<(std::ostream& out, const std::pair<A, B> &p) {
	return out << "(" << p.x << ", " << p.y << ")";
}

std::ostream& operator <<(std::ostream& out, const glm::vec3 &v) {
    return out << "(" << v.x << ", " << v.y << ", " << v.z << ")";
}

std::ostream& operator <<(std::ostream& out, const glm::mat4 &v) {
    out << "[";
    for (int i = 0; i < 4; i++)
    {
        if (i) out << " ";
        out << "[";
        for (int j = 0; j < 4; j++)
        {
            if (j) out << ", ";
            out << v[i][j];
        }
        out << "]\n";
    }
    return out << "]";
}

template<class A> std::ostream& operator <<(std::ostream& out, const std::vector<A> &v) {
	out << "[";
	for (size_t i = 0; i < v.size(); ++i) {
		if (i) out << ", ";
		out << v[i];
	}
	return out << "]";
}

glm::vec3 cl_float3_to_glm_vec3(const cl_float3 &v) {
    return glm::vec3(v.s[0], v.s[1], v.s[2]);
}
cl_float3 glm_vec3_to_cl_float3(const glm::vec3 &v) {
    return {v.x, v.y, v.z};
}
glm::vec2 cl_float2_to_glm_vec2(const cl_float2 &v) {
    return glm::vec2(v.s[0], v.s[1]);
}
cl_float2 glm_vec2_to_cl_float2(const glm::vec2 &v) {
    return {v.x, v.y};
}

cl_float3 operator +(const cl_float3 &a, const cl_float3 &b){
    return {a.s[0] + b.s[0], a.s[1] + b.s[1], a.s[2] + b.s[2]};
}
cl_float3 operator -(const cl_float3 &a, const cl_float3 &b){
    return {a.s[0] - b.s[0], a.s[1] - b.s[1], a.s[2] - b.s[2]};
}
cl_float3 operator *(const cl_float3 &a, const cl_float3 &b){
    return {a.s[0] * b.s[0], a.s[1] * b.s[1], a.s[2] * b.s[2]};
}
cl_float3 operator *(const float &b, const cl_float3 &a){
    return {a.s[0] * b, a.s[1] * b, a.s[2] * b};
}
cl_float3 operator /(const float &b, const cl_float3 &a){
    return {a.s[0] / b, a.s[1] / b, a.s[2] / b};
}
cl_float3 operator *(const cl_float3 &a, const float &b){
    return {a.s[0] * b, a.s[1] * b, a.s[2] * b};
}
cl_float3 operator /(const cl_float3 &a, const float &b){
    return {a.s[0] / b, a.s[1] / b, a.s[2] / b};
}
cl_float3 sqrt(const cl_float3 &a){
    return {std::sqrtf(a.s[0]), std::sqrtf(a.s[1]), std::sqrtf(a.s[2])};
}
float dot(const cl_float3 &a, const cl_float3 &b){
    return a.s[0]*b.s[0] + a.s[1]*b.s[1] + a.s[2]*b.s[2];
}
float length(const cl_float3 &a){
    return std::sqrtf(dot(a, a));
}


cl::NDRange local_threads( 256 );

bool DEBUG = true;