#include "camera_system.hpp"

CameraSystem::CameraSystem(GLFWwindow *window) {
    this->window = window;
}

bool CameraSystem::update(
    std::unordered_map<unsigned int,TransformComponent> &transformComponents,
    unsigned int cameraID, std::unordered_map<unsigned int, CameraComponent>& cameraComponents, 
    std::vector<unsigned int> &Shaders, float dt)
{
    TransformComponent &cameraTransformComponent = transformComponents[cameraID];
    CameraComponent &cameraComponent = cameraComponents[cameraID];

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    
    // Makes camera look in the right direction from the right position
	cameraComponent.view = glm::lookAt(cameraTransformComponent.position, cameraTransformComponent.position + cameraTransformComponent.eulers, cameraComponent.up);
	// Adds perspective to the scene
	cameraComponent.projection = glm::perspective(cameraComponent.FOV, (float(width) / float(height)), cameraComponent.nearPlane, cameraComponent.farPlane);
    
    glm::mat4 cameraMatrix = cameraComponent.projection * cameraComponent.view;

    for(unsigned int &shaderID : Shaders)
    {
        activate_shader(shaderID);
        set_shader_Vec3(shaderID, "camPos", cameraTransformComponent.position);
        set_shader_Mat4(shaderID, "camMatrix", cameraMatrix);
    }
    
    this->Inputs(transformComponents, cameraID, cameraComponents, dt);

    return false;
}


void CameraSystem::Inputs(
    std::unordered_map<unsigned int,TransformComponent> &transformComponents,
    unsigned int cameraID, std::unordered_map<unsigned int, CameraComponent>& cameraComponents, float dt)
{
    TransformComponent &cameraTransformComponent = transformComponents[cameraID];
    CameraComponent &cameraComponent = cameraComponents[cameraID];

    glm::vec3 &Position = cameraTransformComponent.position;
    glm::vec3 &Orientation = cameraTransformComponent.eulers;
    glm::vec3 &Up = cameraComponent.up;

    bool &firstClick = cameraComponent.firstClick;
    float &sensitivity = cameraComponent.sensitivity;
    float &speed = cameraComponent.speed;

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);

	// Handles key inputs
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		Position += speed * Orientation;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		Position += speed * -glm::normalize(glm::cross(Orientation, Up)) * 0.5f;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		Position += speed * -Orientation;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		Position += speed * glm::normalize(glm::cross(Orientation, Up)) * 0.5f;
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		Position += speed * Up;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
		Position += speed * -Up;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		speed = 5.5f * dt;
	}
	else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
	{
		speed = 3.0f * dt;
	}


	// Handles mouse inputs
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		// Hides mouse cursor
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		// Prevents camera from jumping on the first click
		if (firstClick)
		{
			glfwSetCursorPos(window, (width / 2), (height / 2));
			firstClick = false;
		}

		// Stores the coordinates of the cursor
		double mouseX;
		double mouseY;
		// Fetches the coordinates of the cursor
		glfwGetCursorPos(window, &mouseX, &mouseY);

		// Normalizes and shifts the coordinates of the cursor such that they begin in the middle of the screen
		// and then "transforms" them into degrees 
		float rotX = sensitivity * (mouseY - (height / 2)) / float(height);
		float rotY = sensitivity * (mouseX - (width / 2)) / float(width);

		// Calculates upcoming vertical change in the Orientation
		glm::vec3 newOrientation = glm::rotate(Orientation, glm::radians(-rotX), glm::normalize(glm::cross(Orientation, Up)));

		// Decides whether or not the next vertical Orientation is legal or not
		if (abs(glm::angle(newOrientation, Up) - glm::radians(90.0f)) <= glm::radians(85.0f))
		{
			Orientation = newOrientation;
		}

		// Rotates the Orientation left and right
		Orientation = glm::rotate(Orientation, glm::radians(-rotY), Up);

		// Sets mouse cursor to the middle of the screen so that it doesn't end up roaming around
		glfwSetCursorPos(window, (width / 2), (height / 2));
	}
	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
	{
		// Unhides cursor since camera is not looking around anymore
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		// Makes sure the next time the camera looks around it doesn't jump
		firstClick = true;
	}
}
