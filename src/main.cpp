#include "main.h"
void framebuffer_resize_callback(GLFWwindow* window, int framebufferWidth, int framebufferHeight) {
	glViewport(0, 0, framebufferWidth, framebufferHeight);
}

bool loadShaders(GLuint &program)
{
	char infoLog[512];
	GLint success;
	bool loadSuccess = true;

	std::string temp = "";
	std::string src = "";

	std::ifstream in_file;

	//Load Vertex shader
	in_file.open("../../shaders/vertex_shaders.glsl");

	if (in_file.is_open()) {
		while (std::getline(in_file, temp))
		{
			src += temp + "\n";
		}
	}
	else {
		std::cout << "ERROR::LOADSHADERS FAILED SHADER FILE NOT FOUND\n";
		loadSuccess = false;
	}

	in_file.close();

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	const GLchar* vertexsrc = src.c_str();
	glShaderSource(vertexShader, 1, &vertexsrc, NULL);
	glCompileShader(vertexShader);

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::LOADSHADERS FAILED VERTEX SHADER FILE IS NOT COMPILE\n";
		std::cout << "ERROR: " << infoLog << std::endl;
		loadSuccess = false;
	}

	src = "";
	temp = "";

	// Load Fragment Shader
	in_file.open("../../shaders/fragment_shaders.glsl");

	if (in_file.is_open()) {
		while (std::getline(in_file, temp))
		{
			src += temp + "\n";
		}
	}
	else {
		std::cout << "ERROR::LOADSHADERS FAILED FRAGMENT SHADER FILE NOT FOUND\n";
		loadSuccess = false;
	}

	in_file.close();

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	const GLchar* fragmentSrc = src.c_str();
	glShaderSource(fragmentShader, 1, &fragmentSrc, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::LOADSHADERS FAILED FRAGMENT SHADER FILE IS NOT COMPILE\n";
		std::cout << "ERROR: " << infoLog << std::endl;
		loadSuccess = false;
	}

	src = "";
	temp = "";

	program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);

	glLinkProgram(program);

	glGetProgramiv(program, GL_LINK_STATUS, &success);

	if (!success) {
		glGetProgramInfoLog(program, 512, NULL, infoLog);

		std::cout << "ERROR::LOADSHADERS FAILED::SHADER LINKING ERROR" << std::endl;;
		std::cout << "ERROR: " << infoLog << std::endl;
		loadSuccess = false;

	}

	//END
	glUseProgram(0);
	glDeleteShader(vertexShader); 
	glDeleteShader(fragmentShader);
	return loadSuccess;
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
		std::cout << "ERROR::MAIN.CPP FAILED GLEW_INIT\n";
		glfwTerminate();
	}

	int nrAttributes;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
	std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;

	GLuint core_program;

	if (!loadShaders(core_program))
		glfwTerminate();

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

	glfwDestroyWindow(window);
	glfwTerminate();

	glDeleteProgram(core_program);
	system("PAUSE");
	return 0;
}
