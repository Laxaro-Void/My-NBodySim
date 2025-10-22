#pragma once
#include "../config.hpp"

/**
 * @brief Read the entire contents of a file into a string.
 * @param filename The path to the file to read.
 * @return A string containing the file's contents.
 */
std::string get_file_contents(const char* filename);

/**
 * @brief Compile vertex and fragment shaders from files and link them into a shader program.
 * @param vertexFile The path to the vertex shader file.
 * @param fragmentFile The path to the fragment shader file.
 * @return The OpenGL ID of the compiled shader program.
 */
unsigned int compile_shader(const char* vertexFile, const char* fragmentFile);

/**
 * @brief Activate the specified shader program for rendering.
 * @param shaderID The OpenGL ID of the shader program to activate.
 */
void activate_shader(unsigned int shaderID);

/**
 * @brief Delete the specified shader program.
 * @param shaderID The OpenGL ID of the shader program to delete.
 */
void delete_shader(unsigned int shaderID);

/**
 * @brief Set a boolean uniform variable in the shader program.
 */
void set_shader_Bool(unsigned int shaderID, const std::string &name, bool value);
/**
 * @brief Set an integer uniform variable in the shader program.
 */
void set_shader_Int(unsigned int shaderID, const std::string &name, int value);
/**
 * @brief Set a float uniform variable in the shader program.
 */
void set_shader_Float(unsigned int shaderID, const std::string &name, float value);
/**
 * @brief Set a vec2 uniform variable in the shader program.
 */
void set_shader_Vec2(unsigned int shaderID, const std::string &name, const glm::vec2 &value);
/**
 * @brief Set a vec2 uniform variable in the shader program.
 */
void set_shader_Vec2(unsigned int shaderID, const std::string &name, float x, float y);
/**
 * @brief Set a vec3 uniform variable in the shader program.
 */
void set_shader_Vec3(unsigned int shaderID, const std::string &name, const glm::vec3 &value);
/**
 * @brief Set a vec3 uniform variable in the shader program.
 */
void set_shader_Vec3(unsigned int shaderID, const std::string &name, float x, float y, float z);
/**
 * @brief Set a vec4 uniform variable in the shader program.
 */
void set_shader_Vec4(unsigned int shaderID, const std::string &name, const glm::vec4 &value);
/**
 * @brief Set a vec4 uniform variable in the shader program.
 */
void set_shader_Vec4(unsigned int shaderID, const std::string &name, float x, float y, float z, float w);
/**
 * @brief Set a mat2 uniform variable in the shader program.
 */
void set_shader_Mat2(unsigned int shaderID, const std::string &name, const glm::mat2 &mat);
/**
 * @brief Set a mat3 uniform variable in the shader program.
 */
void set_shader_Mat3(unsigned int shader, const std::string &name, const glm::mat3 &mat);
/**
 * @brief Set a mat4 uniform variable in the shader program.
 */
void set_shader_Mat4(unsigned int shader, const std::string &name, const glm::mat4 &mat);

/**
 * @brief Check for shader compilation and linking errors.
 * @param shader The OpenGL ID of the shader or program to check.
 * @param type A string indicating the type of shader ("VERTEX", "FRAGMENT", or "PROGRAM").
 */
void shader_compileErrors(unsigned int shader, const char* type);