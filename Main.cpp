#include<iostream>
#include"glad/glad.h"
#include<GLFW/glfw3.h>
#include <vector>
#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"
#include <cstdlib>
#include <ctime>
#include "window.h"

const GLfloat blockSize = 0.05f;	

short grid[20][20];
struct Vector
{
	GLfloat x, y, z;
};

struct Vertex
{
	GLfloat pos[3];
	GLfloat color[3];
};


// Vertices for the fricking triangle
std::vector<Vertex> vertices;

// Indices for vertices order
std::vector<GLuint> indices;


void blockToVerticies(float x, float y);


int main()
{
	blockToVerticies(0, 0);

	Window myWindow(900, 1000);

	// Generates Shader object using shaders defualt.vert and default.frag
	Shader shaderProgram("default.vert", "default.frag");



	// Generates Vertex Array Object and binds it
	VAO VAO1;
	VAO1.Bind();

	// Generates Vertex Buffer Object and links it to vertices
	VBO VBO1(reinterpret_cast<GLfloat*>(vertices.data()), vertices.size() * sizeof(Vertex)); // no fucking idea this gave me chatgtp
	// Generates Element Buffer Object and links it to indices
	EBO EBO1(indices.data(), indices.size() * sizeof(GLuint));

	// Links VBO attributes such as coordinates and colors to VAO
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	// Unbind all to prevent accidentally modifying them bc i am stupid 
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale"); 	// Gets ID of uniform called "scale" no idea why too

	// Main loop
	while (!glfwWindowShouldClose(myWindow.window))
	{
		






		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);    // Specify the color of the background
		glClear(GL_COLOR_BUFFER_BIT);              // Clean the back buffer and assign the new color to it
		shaderProgram.Activate();				  // activate the sader IDK
		glUniform1f(uniID, 0.5f);			     // Assigns a value to the uniformNOTE: Must always be done after activating the Shader Program
		VAO1.Bind();                        	// Bind the VAO so OpenGL knows to use it
											   // Draw primitives, number of indices, datatype of indices, index of indices
		glDrawElements(GL_TRIANGLES, GLsizei(indices.size()), GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(myWindow.window);		// Swap the back buffer with the front buffer
		glfwPollEvents();			   // Take care of the pooled events 
	}






	//END=========================================END//
	// Delete all the objects 
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();
	// Delete window before ending the program
	glfwDestroyWindow(myWindow.window);
	// Terminate GLFW tqybgtgtbefore ending the program
	glfwTerminate();
	return 0;
}




void blockToVerticies(float x, float y) {
	Vector color = {1.0, 1.0, 1.0 };
	vertices.push_back(Vertex{ { x,y,0.0 }, {color.x,color.y,color.z} });
	vertices.push_back(Vertex{ { x,y + blockSize,0.0 }, {color.x,color.y,color.z} });
	vertices.push_back(Vertex{ { x + blockSize,y,0.0 }, {color.x,color.y,color.z} });
	vertices.push_back(Vertex{ { x + blockSize,y + blockSize,0.0 }, {color.x,color.y,color.z} });


	GLuint lastINdicie = 0;
	if (!indices.empty()) {
		lastINdicie = indices.back() + 1;
	}

	indices.insert(indices.end(), {
		lastINdicie + 0,lastINdicie + 1, lastINdicie + 2,
		lastINdicie + 1,lastINdicie + 2,lastINdicie + 3,


		});


}





