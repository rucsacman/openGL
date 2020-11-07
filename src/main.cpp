#include "main.h"
void framebuffer_resize_callback(GLFWwindow* window, int framebufferWidth, int framebufferHeight) {
	glViewport(0, 0, framebufferWidth, framebufferHeight);
}

int main() 
{
	//Initilize GLFW
	glfwInit();

	const int window_width = 640;
	const int window_height = 480;
	int framebufferWidth = 0;
	int framebufferHeight = 0;

	//Set OpenGL version 4.6
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE); 
	//Create a window
	GLFWwindow* window = glfwCreateWindow(window_width, window_height,"OPENGL",NULL, NULL);

	glfwSetFramebufferSizeCallback(window, framebuffer_resize_callback);
	//get Frame buffer size
	//glfwGetFramebufferSize(window, &framebufferWidth, &framebufferHeight);

	//set viewport
	//glViewport(0, 0, framebufferWidth, framebufferHeight);


	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) 
	{
		std::cout << "ERROR::MAIN.CPP FAILED	GLEW_INIT/n";
		glfwTerminate();
	}
	//Main loop

	while (!glfwWindowShouldClose(window))
	{
		//enable events.. etc: mouse event 
		glfwPollEvents();

		//Clear
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);


		//END draw
		glfwSwapBuffers(window);
		glFlush();
	}

	glfwTerminate();
	system("PAUSE");
	return 0;
}
