#include <iostream>
#include <cmath>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include<stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include"texture.h"
#include"shaderClass.h"
#include"vao.h"
#include"vbo.h"
#include"ebo.h"
#include"camera.h"
using namespace std; 

 // Vertices coordinates
GLfloat vertices[] =
{   //        COORDINATES            COLORS              TexCoord        NORMALS

    // Bottom side
    -0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,     0.0f, 0.0f,     0.0f, -1.0f,  0.0f,
    -0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,     0.0f, 5.0f,     0.0f, -1.0f,  0.0f,
     0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,     5.0f, 5.0f,     0.0f, -1.0f,  0.0f,
     0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,     5.0f, 0.0f,     0.0f, -1.0f,  0.0f,

    // Left side
    -0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,     0.0f, 0.0f,    -0.8f,  0.5f,  0.0f,
    -0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,     5.0f, 0.0f,    -0.8f,  0.5f,  0.0f,
     0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,     2.5f, 5.0f,    -0.8f,  0.5f,  0.0f,

    // Non-facing side
    -0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,     5.0f, 0.0f,     0.0f,  0.5f, -0.8f,
     0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,     5.0f, 5.0f,     0.0f,  0.5f, -0.8f,
     0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,     2.5f, 5.0f,     0.0f,  0.5f, -0.8f,

    // Right side
     0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,     5.0f, 0.0f,     0.8f,  0.5f,  0.0f,
     0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,     5.0f, 5.0f,     0.8f,  0.5f,  0.0f,
     0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,     2.5f, 5.0f,     0.8f,  0.5f,  0.0f,

    // Facing side
    -0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,     0.0f, 0.0f,     0.0f,  0.5f,  0.8f,
     0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,     5.0f, 0.0f,     0.0f,  0.5f,  0.8f,
     0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,     2.5f, 5.0f,     0.0f,  0.5f,  0.8f
};

// Indices for vertices order
GLuint indices[] =
{
    0, 1, 2,   // Bottom side
    0, 2, 3,   // Bottom side
    4, 6, 5,   // Left side
    7, 9, 8,   // Non-facing side
    10, 12, 11, // Right side
    13, 15, 14  // Facing side
};

GLfloat lightVertices[] =
{   //      COORDINATES      //
    -0.1f, -0.1f,  0.1f,
    -0.1f, -0.1f, -0.1f,
     0.1f, -0.1f, -0.1f,
     0.1f, -0.1f,  0.1f,
    -0.1f,  0.1f,  0.1f,
    -0.1f,  0.1f, -0.1f,
     0.1f,  0.1f, -0.1f,
     0.1f,  0.1f,  0.1f
};

GLuint lightIndices[] =
{
    0, 1, 2,
    0, 2, 3,

    0, 4, 7,
    0, 7, 3,

    3, 7, 6,
    3, 6, 2,

    2, 6, 5,
    2, 5, 1,

    1, 5, 4,
    1, 4, 0,

    4, 5, 6,
    4, 6, 7
};

//define constants for window width and height
const unsigned int width = 800;
const unsigned int height =  800;

int main() {
    glfwInit();

    //tell GLFW what version we are using
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    //tell GLFW we are using the core profile for modern functions
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    
    // create a GLFW window 
    GLFWwindow* window = glfwCreateWindow(width, height, "OpenGlDemo", NULL, NULL);
    //error check
    if (window == NULL) {
        std::cout << "Failed to create window" << std::endl;
        glfwTerminate();
        return -1;
    }
    //add the window into the context
    glfwMakeContextCurrent(window);

    //load glad so it can configure opengl
    gladLoadGL();

    //specify the viewport for the window
    glViewport(0, 0, width, height);


    //creates a new shader object and calls the constructor 
    Shader shaderProgram("Resources/default.vert", "Resources/default.frag");
    
    
    VAO VAO1; //creates a vertex array object and calls its constructor
    VAO1.Bind(); //sets opengls currentvao to this one so following attribute config calls are recorded into this one
    VBO VBO1(vertices, sizeof(vertices)); //creates vertex buffer object and calls its constructor 
    EBO EBO1(indices, sizeof(indices)); //creates element buffer object and calls constructor 

    //links the vbo to the vao
    VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT,11 * sizeof(float), (void*)0);
    VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT,11 * sizeof(float), (void*)(3 * sizeof(float)));
    VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT,11 * sizeof(float), (void*)(6 * sizeof(float)));
    VAO1.LinkAttrib(VBO1, 3, 3, GL_FLOAT,11 * sizeof(float), (void*)(8 * sizeof(float)));
    //unbinds all
    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();

    //creates a light shader object
    Shader lightShader("Resources/light.vert", "Resources/light.frag");

    VAO lightVAO; //creates vao 
    lightVAO.Bind(); //binds vao into slot

    VBO lightVBO(lightVertices, sizeof(lightVertices)); //creates vbo
    EBO lightEBO(lightIndices, sizeof(lightIndices)); //creates ebo

    lightVAO.LinkAttrib(lightVBO, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0); //links the vbo to vao passing in how to read the data
    lightVAO.Unbind();
    lightVBO.Unbind();
    lightEBO.Unbind();

    //creates RGBA vector for the light color
    glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f); //creates vector for the position
    glm::mat4 lightModel = glm::mat4(1.0f); //sets a matrix for the model
    lightModel = glm::translate(lightModel, lightPos); //moves the model into position

    glm::vec3 pyramidPos = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::mat4 pyramidModel = glm::mat4(1.0f);
    pyramidModel = glm::translate(pyramidModel, pyramidPos);

    //activate the light shader
    lightShader.Activate();
    glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel)); //gets the location of the uniform in the shader and writes the values into the slot
    glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
    shaderProgram.Activate();
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(pyramidModel));
    glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
    glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);








   //TEXTURE
   Texture popCat("brick.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE); //Creates a new texture object
   popCat.texUnit(shaderProgram, "tex0", 0); //sets the value of the uniform

    //enables the depth buffer, which stores the z value for every pixel and compares which is closer to the camera to draw it
    glEnable(GL_DEPTH_TEST);




    //create the camera object passing in the window dimensions
    Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));
    //while loop
    while (!glfwWindowShouldClose(window)) {

        glClearColor(0.07f, 0.13f, 0.17f, 1.0f); 
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clear the color and depth buffer
        
        camera.Inputs(window); //apply any inputs every frame
        camera.updateMatrix(45.0f, 0.1f, 100.0f); //pass in the FOV near and far plane as well as the shader to process the uniform

        //tell opengl which shader program to use
        shaderProgram.Activate();
        glUniform3f(glGetUniformLocation(shaderProgram.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z); //gets the location of the uniform and passes in the camera position

        camera.Matrix(shaderProgram, "camMatrix");

        popCat.Bind();
        //bind the vao so opengl knows how to use it
        VAO1.Bind();
        //draws the elements in order 
        glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, 0); //when these elements are drawn it applys the matrix transformations

        lightShader.Activate();
        camera.Matrix(lightShader, "camMatrix");
        lightVAO.Bind();
        glDrawElements(GL_TRIANGLES, sizeof(lightIndices) / sizeof(int), GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window);
        //handle GLFW events
        glfwPollEvents();
    }


    //delete all objects
    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();
    popCat.Delete();
    shaderProgram.Delete();

    lightVAO.Delete();
    lightVBO.Delete();
    lightEBO.Delete();
    lightShader.Delete();
    //delete widnow
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}