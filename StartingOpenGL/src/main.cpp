#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

// Our vertex shader source code in GLSL (OpenGL Shading Language)
// Just foward all vertex coordinates to its vec4
const char* vertexShaderSource = "#version 330 core\n"
	"layout (location = 0) in vec3 aPos;\n"
	"void main()\n"
	"{\n"
	"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
	"}\0";
// Our fragment shader source code in GLSL (OpenGL Shading Language)
// Just set fragment color as a orange-ish color
const char* fragmentShaderSource = "#version 330 core\n"
	"out vec4 FragColor;\n"
	"void main()\n"
	"{\n"
	"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
	"}\n";

void buildVertexShader(unsigned int &vertexShader) {
	// Create vertex shader with its source code
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	// Check if vertex shader compilation failed
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
}

void buildFragmentShader(unsigned int &fragmentShader) {
	// Create fragment shader with its source code
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	// Check if fragment shader compilation failed
	int success;
	char infoLog[512];
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
}

void linkProgramShaders(unsigned int& shaderProgram, unsigned int& vertexShader, unsigned int& fragmentShader) {
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	int success;
	char infoLog[512];
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINK_FAILED\n" << infoLog << std::endl;
	}
}

void createVertexBufferObject() {
	// Define triangle vertices in NDC (Normalized Device Coordinates) (Vertex Data)
	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f
	};

	// Create a vertex buffer object
	unsigned int VBO;
	// Generate its ID
	glGenBuffers(1, &VBO);
	// Bind VBO to a buffer type
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// Copy vertex data into buffer's memory
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}

// Callback to resize openGL viewport as the window
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

// Function to process all user input
void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}

int main() {
	// GLFW Initialization
	glfwInit();
	
	// Set openGL version and profile
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);

	// If an error has ocurred, terminate GLFW to free resources
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Otherwise, make current window the main context
	glfwMakeContextCurrent(window);

	// Check if Glad has loaded
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialized GLAD" << std::endl;
		return -1;
	}

	createVertexBufferObject();

	// Build and link OpenGL shaders
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	buildVertexShader(vertexShader);

	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	buildFragmentShader(fragmentShader);

	unsigned int shaderProgram = glCreateProgram();
	linkProgramShaders(shaderProgram, vertexShader, fragmentShader);
	glUseProgram(shaderProgram);

	// Delete useless shaders objects
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// Set how openGL should interpret vertex buffer data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Set openGL viewport and ensures resizing
	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// render loop, while not should be closed
	while (!glfwWindowShouldClose(window)) {
		// Process input
		processInput(window);

		// ----- Rendering commands -----
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// ----------
		// Swap window buffers and call events if needed
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// Free all resources
	glfwTerminate();
	return 0;
}