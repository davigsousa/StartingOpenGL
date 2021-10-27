#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

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

	// Set openGL viewport and ensures resizing
	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// GUI main loop, while not should be closed
	while (!glfwWindowShouldClose(window)) {
		// Process input
		processInput(window);

		// Rendering commands
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Swap window buffers and call events if needed
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// Free all resources
	glfwTerminate();
	return 0;
}