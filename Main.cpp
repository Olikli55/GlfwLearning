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
	-0.5f, -0.5f * float(sqrt(3)) * 1 / 3, 0.0f,     0.8f, 0.3f,  0.02f, // Lower left corner
	 0.5f, -0.5f * float(sqrt(3)) * 1 / 3, 0.0f,     0.8f, 0.3f,  0.02f, // Lower right corner
	 0.0f,  0.5f * float(sqrt(3)) * 2 / 3, 0.0f,     1.0f, 0.6f,  0.32f, // Upper corner
	-0.25f, 0.5f * float(sqrt(3)) * 1 / 6, 0.0f,     0.9f, 0.45f, 0.17f, // Inner left
	 0.25f, 0.5f * float(sqrt(3)) * 1 / 6, 0.0f,     0.9f, 0.45f, 0.17f, // Inner right
	 0.0f, -0.5f * float(sqrt(3)) * 1 / 3, 0.0f,     0.8f, 0.3f,  0.02f  // Inner down
};

// Indices for vertices order
GLuint indices[] =
{
	0, 3, 5, // Lower left triangle
	3, 2, 4, // Lower right triangle
	5, 4, 1 // Upper triangle
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
		
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);    // Specify the color of the background
		glClear(GL_COLOR_BUFFER_BIT);              // Clean the back buffer and assign the new color to it
		shaderProgram.Activate();				  // activate the sader IDK
		glUniform1f(uniID, 0.5f);			     // Assigns a value to the uniformNOTE: Must always be done after activating the Shader Program
		VAO1.Bind();                        	// Bind the VAO so OpenGL knows to use it
		                                       // Draw primitives, number of indices, datatype of indices, index of indices
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);		// Swap the back buffer with the front buffer
		glfwPollEvents();			   // Take care of the pooled events 
	}

	for (unsigned short i = 0; i < 5; i++) {
        float blockOffset = blockSize * i;
        // Use blockOffset as needed
		vertices[0] = 
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