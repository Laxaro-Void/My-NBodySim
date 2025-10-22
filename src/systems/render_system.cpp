#include "render_system.hpp"

RenderSystem::RenderSystem(GLFWwindow *window) {
	this->window = window;
}

void RenderSystem::update(
	std::unordered_map<unsigned int, TransformComponent> &transformComponents,
	std::unordered_map<unsigned int, RenderComponent> &renderComponents,
	std::vector<unsigned int> &Shaders) {
	/*
		Update and render all entities with TransformComponent and RenderComponent
	*/
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (std::pair<unsigned int, RenderComponent> entity : renderComponents)
	{
		TransformComponent &transform = transformComponents[entity.first];

		// Initialize matrices
		glm::mat4 matrix = glm::mat4(1.0f);
		glm::mat4 trans = glm::mat4(1.0f);
		glm::mat4 rot = glm::mat4(1.0f);
		glm::mat4 sca = glm::mat4(1.0f);
		glm::mat4 shrX = glm::mat4(1.0f);
		glm::mat4 shrY = glm::mat4(1.0f);
		glm::mat4 shrZ = glm::mat4(1.0f);

		// Transform the matrices to their correct form
		trans = glm::translate(trans, transform.position);
		rot = glm::rotate(rot, glm::radians(transform.eulers.x), {1.0f, 0.0f, 0.0f});
		rot = glm::rotate(rot, glm::radians(transform.eulers.y), {0.0f, 1.0f, 0.0f});
		rot = glm::rotate(rot, glm::radians(transform.eulers.z), {0.0f, 0.0f, 1.0f});
		sca = glm::scale(sca, transform.scale);
		shrX = glm::shearX3D(shrX, transform.shearX[0], transform.shearX[1]);
		shrY = glm::shearY3D(shrX, transform.shearY[0], transform.shearY[1]);
		shrZ = glm::shearZ3D(shrX, transform.shearZ[0], transform.shearZ[1]);

		glm::mat4 model = matrix * trans * sca * shrX * shrY * shrZ;
		glm::mat4 norm = glm::transpose(glm::inverse(matrix * rot * sca * shrX * shrY * shrZ));

		unsigned int shaderID = entity.second.shader;
		activate_shader(shaderID);
		set_shader_Mat4(shaderID, "modelMatrix", model);
		set_shader_Mat4(shaderID, "normalMatrix", norm);

		bindVAO(entity.second.VAO);
		glDrawElements(GL_TRIANGLES, entity.second.indexs.size(), GL_UNSIGNED_INT, 0);
	}

	glfwSwapBuffers(window);
}

void RenderSystem::uploadVertexData(RenderComponent &renderComponent) {
	/*
		Upload for the first time the vertex data to the GPU
	*/
	// VAO - Vertex Array Object
	// Generate and bind VAO
	glGenVertexArrays(1, &renderComponent.VAO);
	glBindVertexArray(renderComponent.VAO);

	// VBO - Vertex Buffer Object
	// Generate and bind VBO
	glGenBuffers(1, &renderComponent.VBO);
	glBindBuffer(GL_ARRAY_BUFFER, renderComponent.VBO);
	glBufferData(GL_ARRAY_BUFFER, renderComponent.vertex.size() * sizeof(Vertex), &renderComponent.vertex[0], GL_STATIC_DRAW);

	// EBO - Element Buffer Object
	// Generate and bind EBO
	glGenBuffers(1, &renderComponent.EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderComponent.EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, renderComponent.indexs.size() * sizeof(GLuint), &renderComponent.indexs[0], GL_STATIC_DRAW);

	// Link vertex attributes
	// Position
	linkAttribute(renderComponent.VBO, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
	// Color
	linkAttribute(renderComponent.VBO, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));
	// Normal
	linkAttribute(renderComponent.VBO, 2, 3, GL_FLOAT, sizeof(Vertex), (void*)(6 * sizeof(float)));
	// Texture UV
	linkAttribute(renderComponent.VBO, 3, 2, GL_FLOAT, sizeof(Vertex), (void*)(9 * sizeof(float)));

	// Unbind VAO VBO EBO
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void RenderSystem::linkAttribute(
	unsigned int VBO, 
	GLuint layout, 
	GLuint numComponents, 
	GLenum type, 
	GLsizeiptr stride, 
	void *offset) {
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
	glEnableVertexAttribArray(layout);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void RenderSystem::bindVAO(unsigned int ID) {
	glBindVertexArray(ID);
}
void RenderSystem::bindVBO(unsigned int ID) {
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}
void RenderSystem::bindEBO(unsigned int ID) {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

void RenderSystem::unbindVAO(unsigned int ID) {
	glBindVertexArray(0);
}
void RenderSystem::unbindVBO(unsigned int ID) {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
void RenderSystem::unbindEBO(unsigned int ID) {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void RenderSystem::deleteVAO(unsigned int ID) {
	glDeleteVertexArrays(1, &ID);
}
void RenderSystem::deleteVBO(unsigned int ID) {
	glDeleteBuffers(1, &ID);
}
void RenderSystem::deleteEBO(unsigned int ID) {
	glDeleteBuffers(1, &ID);
}
