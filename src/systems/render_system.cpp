#include "render_system.hpp"

RenderSystem::RenderSystem(unsigned int shader, GLFWwindow *window)
{
	modelLocation = glGetUniformLocation(shader, "model");
	this->window = window;
}

void RenderSystem::update(
	std::unordered_map<unsigned int, TransformComponent> &transformComponents,
	std::unordered_map<unsigned int, RenderComponent> &renderComponents)
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (std::pair<unsigned int, RenderComponent> entity : renderComponents)
	{
		TransformComponent &transform = transformComponents[entity.first];
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, transform.position);
		model = glm::rotate(model, glm::radians(transform.eulers.z), {0.0f, 0.0f, 1.0f});
	}
	glfwSwapBuffers(window);
}