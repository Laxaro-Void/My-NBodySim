#include "app.hpp"


App::App() {
	set_up_glfw();
}

App::~App() {
	glfwDestroyWindow(window);
	glfwTerminate();
}

unsigned int App::make_entity() {
	if (freeEntity.empty())
	{
		activeEntitys++;
		return leastEntity++;
	}
	else
	{
		activeEntitys++;
		unsigned int newID = freeEntity.front();
		freeEntity.pop();
		return newID;
	}
}

void App::delete_entity(unsigned int ID) {
	// Clear Component
	// TODO

	freeEntity.push(ID);
	activeEntitys--;
}

RenderComponent App::make_sphere_mesh(
	GLfloat R,
	GLint sectorCount,
	GLint stackCount,
	unsigned int shader)
{
	auto linspace = [](GLfloat start, GLfloat end, GLuint size)
	{
		std::vector<GLfloat> result;
		GLfloat step = (end - start) / (size - 1);
		for (GLuint i = 0; i < size; ++i)
			result.push_back(start + i * step);

		return result;
	};

	RenderComponent sphere;

	glm::vec3 color = glm::vec3(1.0f);
	std::vector<GLfloat> radial = linspace(0.0f, 2.0f * glm::acos(-1), sectorCount + 1); // phi =  [0, 2PI]
	std::vector<GLfloat> sinoal = linspace(0.0f, glm::acos(-1), stackCount);						 // theta  = [0, PI]

	std::vector<Vertex> vertex;
	std::vector<GLuint> indexs;

	auto f_x = [](GLfloat r, GLfloat theta, GLfloat phi)
	{
		return r * glm::sin(theta) * glm::cos(phi);
	};
	auto f_y = [](GLfloat r, GLfloat theta, GLfloat phi)
	{
		return r * glm::sin(theta) * glm::sin(phi);
	};
	auto f_z = [](GLfloat r, GLfloat theta)
	{
		return r * glm::cos(theta);
	};

	for (GLuint i = 0; i < sinoal.size(); i++)
	{
		for (GLuint j = 0; j < ((i == 0 || i + 1 == sinoal.size()) ? 1 : radial.size() - 1); j++)
		{
			GLfloat theta = sinoal[i];
			GLfloat phi = radial[j];

			glm::vec3 pos = glm::vec3(f_x(R, theta, phi), f_y(R, theta, phi), f_z(R, theta));
			glm::vec3 norm = glm::normalize(pos);

			vertex.push_back({pos, color, norm, glm::vec2(1.0f)});
		}
	}

	for (GLuint i = 0; i < sinoal.size() - 1; i++)
	{
		for (GLuint j = 0; j < radial.size() - 1; j++)
		{
			if (i == 0)
			{
				indexs.push_back(0);
				indexs.push_back(j + 1);
				indexs.push_back((j + 1) % (radial.size() - 1) + 1);
				continue;
			}

			if (i + 1 == sinoal.size() - 1)
			{
				indexs.push_back((i - 1) * (radial.size() - 1) + j + 1);
				indexs.push_back(((i - 1) * (radial.size() - 1) + j + 1) % (radial.size() - 1) + (i - 1) * (radial.size() - 1) + 1);
				indexs.push_back(vertex.size() - 1);
				continue;
			}

			GLuint a = (i - 1) * (radial.size() - 1) + j + 1;
			GLuint b = ((i - 1) * (radial.size() - 1) + j + 1) % (radial.size() - 1) + (i - 1) * (radial.size() - 1) + 1;

			GLuint c = i * (radial.size() - 1) + j + 1;
			GLuint d = (i * (radial.size() - 1) + j + 1) % (radial.size() - 1) + i * (radial.size() - 1) + 1;

			indexs.push_back(a);
			indexs.push_back(c);
			indexs.push_back(b);

			indexs.push_back(c);
			indexs.push_back(d);
			indexs.push_back(b);
		}
	}

	sphere.vertex = vertex;
	sphere.indexs = indexs;
	
	renderSystem->uploadVertexData(sphere);

	sphere.shader = shader;

	return sphere;
}

RenderComponent App::make_circle_mesh(
    GLfloat R,
    GLint sectorCount,
    unsigned int shader) {
	
	auto linspace = [](GLfloat start, GLfloat end, GLuint size)
	{
		std::vector<GLfloat> result;
		GLfloat step = (end - start) / (size - 1);
		for (GLuint i = 0; i < size; ++i)
			result.push_back(start + i * step);

		return result;
	};

	RenderComponent sphere;
	glm::vec3 color = glm::vec3(1.0f);
	std::vector<GLfloat> radial = linspace(0.0f, 2.0f * glm::acos(-1), sectorCount + 1); // phi =  [0, 2PI]
	
	std::vector<Vertex> vertex;
	std::vector<GLuint> indexs;

	auto f_x = [](GLfloat r, GLfloat phi)
	{
		return r * glm::cos(phi);
	};
	auto f_y = [](GLfloat r, GLfloat phi)
	{
		return r * glm::sin(phi);
	};

	vertex.push_back({glm::vec3(0.0f), color, glm::vec3(0.0f, 0.0f, 1.0f)});

	for (GLuint j = 0; j < radial.size() - 1; j++)
	{
		GLfloat phi = radial[j];

		glm::vec3 pos = glm::vec3(f_x(R, phi), f_y(R, phi), 1.0f);
		glm::vec3 norm = glm::normalize(pos);

		vertex.push_back({pos, color, norm, glm::vec2(1.0f)});
	}

	for (GLuint j = 1; j < vertex.size(); j++)
	{
		GLuint a = 0, b, c;
		if (j == vertex.size() - 1)
		{
			b = j;
			c = 1;
		}
		else
		{
			b = j;
			c = j+1;
		}

		indexs.push_back(a);
		indexs.push_back(c);
		indexs.push_back(b);
	}

	sphere.vertex = vertex;
	sphere.indexs = indexs;
	
	renderSystem->uploadVertexData(sphere);

	sphere.shader = shader;

	return sphere;
	}

void App::run() {
	// Create Shader src/shaders/sphere.vert
	Shaders.push_back(compile_shader("../src/shaders/sphere.vert", "../src/shaders/sphere.frag"));

	// Create Camera Entity
	cameraID = make_entity();
	transformComponents[cameraID] = TransformComponent{
		.position = glm::vec3(1.5f, 2.5f, 2.0f),
		.eulers = glm::vec3(-0.5f, -1.25f, -1.0f),
		.scale = glm::vec3(1.0f),
		.shearX = glm::vec2(0.0f),
		.shearY = glm::vec2(0.0f),
		.shearZ = glm::vec2(0.0f),
	};
	cameraComponents[cameraID] = CameraComponent{
		.up = glm::vec3(0.0f, 0.5f, 0.0f),
		.projection = glm::perspective(glm::radians(45.0f), (float)Width / (float)Height, 0.1f, 100.0f),
		.view = glm::mat4(1.0f),
		.FOV = 45.0f,
		.nearPlane = 0.1f,
		.farPlane = 100.0f,
		.nearPlane_height = glm::tan(glm::radians(45.0f) / 2.0f) * 0.1f,
		.aspect_ratio = (float)Width / (float)Height,
		.speed = 2.5f,
		.sensitivity = 75.0f,
		.firstClick = true,
	};
	if (DEBUG) std::clog << "Camera Created" << '\n';

	// Create a sphere entity
	unsigned int sphereEntity = make_entity();
	renderComponents[sphereEntity] = make_sphere_mesh(0.5f, 34, 18, Shaders[0]);
	transformComponents[sphereEntity] = TransformComponent{
		.position = glm::vec3(0.0f, 0.0f, 0.0f),
		.eulers = glm::vec3(0.0f),
		.scale = glm::vec3(1.0f),
		.shearX = glm::vec2(0.0f),
		.shearY = glm::vec2(0.0f),
		.shearZ = glm::vec2(0.0f),
	};
	if (DEBUG) std::clog << "Sphere Created" << '\n';

	while (!glfwWindowShouldClose(window))
	{
		motionSystem->update(transformComponents, physicsComponents, 16.67f/1000.0f);
		cameraSystem->update(transformComponents, cameraID, cameraComponents, Shaders, 16.67f/1000.0f);
		renderSystem->update(transformComponents, renderComponents, Shaders);

		if (DEBUG) std::clog << "CameraPos: " << transformComponents[cameraID].position << '\n';
		if (DEBUG) std::clog << "CameraLok: " << transformComponents[cameraID].eulers << '\n';
		if (DEBUG) std::clog << "Window Side: " << Width << ", " << Height << '\n';

		glfwPollEvents();
	}
}

void App::set_up_glfw()
{
	if (!glfwInit())
	{
		std::cout << "Failed to initialize GLFW" << std::endl;
		exit(EXIT_FAILURE);
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	// Stable GLFW the version of OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Stable GLFW using the CORE profile
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// GLFW Window is Resizable = 1
	glfwWindowHint(GLFW_RESIZABLE, 1);

	window = glfwCreateWindow(Width, Height, "Project", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to open GLFW window" << std::endl;
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window);
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
	app->Width = width;
	app->Height = height;
};

void App::set_up_opengl()
{
	if (!gladLoadGL())
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	// Specify the viewport of OpenGl in the Window
	glViewport(0, 0, Width, Height);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	
	glfwSetCursorPos(window, Width/2, Height/2);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Enable 3D
	glEnable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
}

void App::make_systems() {
  motionSystem = new MotionSystem();
  cameraSystem = new CameraSystem(window);
  renderSystem = new RenderSystem(window);
}