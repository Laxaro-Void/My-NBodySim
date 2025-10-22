// Glad, GLFW
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Stdc++
#include <iostream>
#include <ostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>

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