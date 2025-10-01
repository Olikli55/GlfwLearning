#include "glad/glad.h"
#include<GLFW/glfw3.h>
#include<iostream>
#include"window.h"


Window::Window(unsigned short h, unsigned short w){
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);// Tell GLFW what version of OpenGL we are using 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); 	// Tell GLFW we are using the CORE profile == modern functions only

	window = glfwCreateWindow(w, h, "TRIANGEL YAYAYAY", NULL, NULL);
	if (window == NULL)
	{
		glfwTerminate();
		throw std::runtime_error("ERROR: creation of window faild");
	}
	glfwMakeContextCurrent(window); // make the window current? i guess. i dont fucking now

	gladLoadGL();


	glViewport(0, 0, w, h);
}