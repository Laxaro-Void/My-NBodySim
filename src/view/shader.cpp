#include "shader.hpp"

std::string get_file_contents(const char* filename)
{	
	if (DEBUG) std::clog << "Reading file at: " << filename << "\n";
	std::ifstream in(filename, std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);
}

unsigned int compile_shader(const char* vertexFile, const char* fragmentFile)
{
    std::string vertexCode = get_file_contents(vertexFile);
    std::string fragmentCode = get_file_contents(fragmentFile);
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    // Compile Vertex Shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vShaderCode, NULL);
    glCompileShader(vertexShader);
    compile_shader(vertexShader, "VERTEX");

    // Compile Fragment Shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fShaderCode, NULL);
    glCompileShader(fragmentShader);
    compile_shader(fragmentShader, "FRAGMENT");

    // Link Shaders
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    compile_shader(shaderProgram, "PROGRAM");

    // Delete the shaders as they're linked into our program now and no longer necessary
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}

void activate_shader(unsigned int shaderID) {
    glUseProgram(shaderID);
}
void delete_shader(unsigned int shaderID) {
    glDeleteProgram(shaderID);
}

void set_shader_Bool(unsigned int shaderID, const std::string &name, bool value) {
    glUniform1i(glGetUniformLocation(shaderID, name.c_str()), (int)value);
}
void set_shader_Int(unsigned int shaderID, const std::string &name, int value) {
    glUniform1i(glGetUniformLocation(shaderID, name.c_str()), value);
}
void set_shader_Float(unsigned int shaderID, const std::string &name, float value) {
    glUniform1f(glGetUniformLocation(shaderID, name.c_str()), value);
}
void set_shader_Vec2(unsigned int shaderID, const std::string &name, const glm::vec2 &value) {
    glUniform2fv(glGetUniformLocation(shaderID, name.c_str()), 1, &value[0]);
}
void set_shader_Vec2(unsigned int shaderID, const std::string &name, float x, float y) {
    glUniform2f(glGetUniformLocation(shaderID, name.c_str()), x, y);
}
void set_shader_Vec3(unsigned int shaderID, const std::string &name, const glm::vec3 &value) {
    glUniform3fv(glGetUniformLocation(shaderID, name.c_str()), 1, &value[0]);
}
void set_shader_Vec3(unsigned int shaderID, const std::string &name, float x, float y, float z) {
    glUniform3f(glGetUniformLocation(shaderID, name.c_str()), x, y, z);
}
void set_shader_Vec4(unsigned int shaderID, const std::string &name, const glm::vec4 &value) {
    glUniform4fv(glGetUniformLocation(shaderID, name.c_str()), 1, &value[0]);
}
void set_shader_Vec4(unsigned int shaderID, const std::string &name, float x, float y, float z, float w) {
    glUniform4f(glGetUniformLocation(shaderID, name.c_str()), x, y, z, w);
}
void set_shader_Mat2(unsigned int shaderID, const std::string &name, const glm::mat2 &mat) {
    glUniformMatrix2fv(glGetUniformLocation(shaderID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
void set_shader_Mat3(unsigned int shaderID, const std::string &name, const glm::mat3 &mat) {
    glUniformMatrix3fv(glGetUniformLocation(shaderID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
void set_shader_Mat4(unsigned int shaderID, const std::string &name, const glm::mat4 &mat) {
    glUniformMatrix4fv(glGetUniformLocation(shaderID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void compile_shader(unsigned int shaderID, const char* type)
{
	// Stores status of compilation
	GLint hasCompiled;
	// Character array to store error message in
	char infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetShaderInfoLog(shaderID, 1024, NULL, infoLog);
			std::cerr << "SHADER_COMPILATION_ERROR for:" << type << "\n" << infoLog << std::endl;
		}
	}
	else
	{
		glGetProgramiv(shaderID, GL_LINK_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetProgramInfoLog(shaderID, 1024, NULL, infoLog);
			std::cerr << "SHADER_LINKING_ERROR for:" << type << "\n" << infoLog << std::endl;
		}
	}
}