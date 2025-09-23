#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"

const float blockSize= 0.05f;


// Vertices for the fricking triangle
GLfloat vertices[] =
{ //               COORDINATOS                  /     COLORES           //
	0.0f , 0.0f , 0.0f ,          1.0f, 0.0f, 0.0f,
	0.0f , 0.05f , 0.0f ,		  1.0f, 0.5f, 0.0f,
	0.05f , 0.0f , 0.0f ,		  1.0f, 0.5f, 0.2f,
	0.05f , 0.05f , 0.0f ,		  1.0f, 0.0f, 0.5f,


	0.1f , 0.0f , 0.0f ,		  1.0f, 0.5f, 0.2f,
	0.1f , 0.05f , 0.0f ,		  1.0f, 0.0f, 0.5f,
	



};

// Indices for vertices order
GLuint indices[] =
{
	0,1,2,
	1,2,3,
	2,3,4,
	3,4,5,

	
};





int main()
{
	// Initialize GLFW
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);// Tell GLFW what version of OpenGL we are using 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); 	// Tell GLFW we are using the CORE profile == modern functions only

	GLFWwindow* window = glfwCreateWindow(800, 800, "TRIANGEL YAYAYAY", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "ERROR: creation of window faild" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window); // make the window current? i guess i dont fucking now

	gladLoadGL();


	glViewport(0, 0, 800, 800);	// Specify the viewport of OpenGL in the Window. by the way it is FUKCING reversed



	// Generates Shader object using shaders defualt.vert and default.frag
	Shader shaderProgram("default.vert", "default.frag");



	// Generates Vertex Array Object and binds it
	VAO VAO1;
	VAO1.Bind();

	// Generates Vertex Buffer Object and links it to vertices
	VBO VBO1(vertices, sizeof(vertices));
	// Generates Element Buffer Object and links it to indices
	EBO EBO1(indices, sizeof(indices));

	// Links VBO attributes such as coordinates and colors to VAO
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	// Unbind all to prevent accidentally modifying them bc i am stupid 
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale"); 	// Gets ID of uniform called "scale" no idea why too



	// Main loop
	while (!glfwWindowShouldClose(window))
	{
		
		for (int i = 1; i < sizeof(vertices) / sizeof(float); i += 6) {
			vertices[i] += 0.00001f; // Only update the Y coordinate
		}
		
		


		VBO1.Bind();
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
		VBO1.Unbind();
		
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);    // Specify the color of the background
		glClear(GL_COLOR_BUFFER_BIT);              // Clean the back buffer and assign the new color to it
		shaderProgram.Activate();				  // activate the sader IDK
		glUniform1f(uniID, 0.5f);			     // Assigns a value to the uniformNOTE: Must always be done after activating the Shader Program
		VAO1.Bind();                        	// Bind the VAO so OpenGL knows to use it
		                                       // Draw primitives, number of indices, datatype of indices, index of indices
		glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);		// Swap the back buffer with the front buffer
		glfwPollEvents();			   // Take care of the pooled events 
	}






	//END=========================================END//
	// Delete all the objects 
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();
	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}