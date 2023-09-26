//
//  main.cpp
//  3D Object Drawing
//
//  Created by Nazirul Hasan on 4/9/23.
//

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "camera.h"
#include "basic_camera.h"

#include <iostream>
#include <stdlib.h>
#include<windows.h>  

using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);
void Table(Shader ourshader, glm::mat4 moveMatrix);
void Bed(Shader ourshader, glm::mat4 moveMatrix);
void Nightstand(Shader ourshader, glm::mat4 moveMatrix);
void Almirah(Shader ourshader, glm::mat4 moveMatrix);
void Handle(Shader ourshader, glm::mat4 moveMatrix);
void AC(Shader ourshader, glm::mat4 moveMatrix);
void Floormat(Shader ourshader, glm::mat4 moveMatrix);
void Window(Shader ourshader, glm::mat4 moveMatrix);
void Monitor(Shader ourshader, glm::mat4 moveMatrix);

void Chair(Shader ourShader, glm::mat4 moveMatrix);
void SideWall(Shader ourShader, glm::mat4 moveMatrix);
void FrontWall(Shader ourShader, glm::mat4 moveMatrix);
void Roof(Shader ourShader, glm::mat4 moveMatrix);
void Floor(Shader ourShader, glm::mat4 moveMatrix);
void Fan(Shader ourShader);


// settings
const unsigned int SCR_WIDTH = 1200;
const unsigned int SCR_HEIGHT = 600;

// modelling transform
float rotateAngle_X = 0.0;
float rotateAngle_Y = 0.0;
float rotateAngle_Z = 0.0;
float rotateAxis_X = 0.0;
float rotateAxis_Y = 0.0;
float rotateAxis_Z = 0.0;
float translate_X = 0.0;
float translate_Y = 0.0;
float translate_Z = 0.0;
float scale_X = 1.0;
float scale_Y = 1.0;
float scale_Z = 1.0;

// camera
Camera camera(glm::vec3(0.0f, 1.0f, .7f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

float eyeX = 0.0, eyeY = 1.0, eyeZ = .7;
float lookAtX = 0.0, lookAtY = 1.0, lookAtZ = 0.0;
glm::vec3 V = glm::vec3(0.0f, 1.0f, 0.0f);
BasicCamera basic_camera(eyeX, eyeY, eyeZ, lookAtX, lookAtY, lookAtZ, V);

// timing
float deltaTime = 0.0f;    // time between current frame and last frame
float lastFrame = 0.0f;


//rotate
bool isRotate = false;
float fanSpeed = 5.0f;

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "CSE 4208: Computer Graphics Laboratory", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    //glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // build and compile our shader zprogram
    // ------------------------------------
    Shader ourShader("vertexShader.vs", "fragmentShader.fs");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------


    
    float cube_vertices[] = {
        0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,

        0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.0f, 0.5f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,

        0.0f, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f,
        0.5f, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
        0.0f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,

        0.0f, 0.0f, 0.5f, 1.0f, 1.0f, 0.0f,
        0.0f, 0.5f, 0.5f, 1.0f, 1.0f, 0.0f,
        0.0f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,

        0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
        0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f,
        0.0f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f,
        0.0f, 0.5f, 0.5f, 0.0f, 1.0f, 1.0f,

        0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
        0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
        0.5f, 0.0f, 0.5f, 1.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 0.5f, 1.0f, 0.0f, 1.0f
    };
    unsigned int cube_indices[] = {
        0, 3, 2,
        2, 1, 0,

        4, 5, 7,
        7, 6, 4,

        8, 9, 10,
        10, 11, 8,

        12, 13, 14,
        14, 15, 12,

        16, 17, 18,
        18, 19, 16,

        20, 21, 22,
        22, 23, 20
    };
   
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices), cube_indices, GL_STATIC_DRAW);

    // position attribute
   // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    //glEnableVertexAttribArray(0);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)12);
    glEnableVertexAttribArray(1);



    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // per-frame time logic
        // --------------------
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        // activate shader
        ourShader.use();

        // pass projection matrix to shader (note that in this case it could change every frame)
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        //glm::mat4 projection = glm::ortho(-2.0f, +2.0f, -1.5f, +1.5f, 0.1f, 100.0f);
        ourShader.setMat4("projection", projection);

        // camera/view transformation
        //glm::mat4 view = camera.GetViewMatrix();
        glm::mat4 view = camera.GetViewMatrix();
        ourShader.setMat4("view", view);


        glBindVertexArray(VAO);


        // Starting
        glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        glm::mat4 translateMatrix, scaleMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, model;


        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.001f, -3.6f));
        Bed(ourShader, translateMatrix);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(-1.5f, 0.5f, -3.6f));
        Table(ourShader, translateMatrix);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(-1.24f, 0.52f, -3.4f));
        Monitor(ourShader, translateMatrix);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(-1.4f, 0.5f, -3.0f));
        Chair(ourShader, translateMatrix);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(1.2f, 0.001f, -3.6f));
        Nightstand(ourShader, translateMatrix);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(1.34f, 0.4f, -3.094f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.5f, 0.5f, 0.4f));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        Handle(ourShader, model);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(1.34f, 0.17f, -3.094f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.5f, 0.5f, 0.4f));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        Handle(ourShader, model);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(-1.99f, 0.001f, -1.5f));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix;
        Almirah(ourShader, model);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(-1.5f, 0.5f, -1.7f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.5f, 0.5f, 0.4f));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(-90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        Handle(ourShader, model);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(-1.5f, 0.5f, -1.8f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.5f, 0.5f, 0.4f));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(-90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        Handle(ourShader, model);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.25f, 0.8f, -3.95f));
        Window(ourShader, translateMatrix);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.06f, 0.001f, -2.0f));
        Floormat(ourShader, translateMatrix);

        

        /*translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.5f, -0.6f));
        AC(ourShader, translateMatrix);*/


        //Walls
        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, 0.01f));
        SideWall(ourShader, translateMatrix);       //Left

        translateMatrix = glm::translate(identityMatrix, glm::vec3(4.62f, 0.0f, 0.01f));
        SideWall(ourShader, translateMatrix);       //Right

        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.001f, 0.001f, 0.0f));
        FrontWall(ourShader, translateMatrix);       //Front

        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.001f, 0.0f, 5.0f));
        FrontWall(ourShader, translateMatrix);       //Back

        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.001f, 0.0f, 2.0f));
        Roof(ourShader, translateMatrix);       //Roof

        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.001f, -1.701f, 2.0f));
        Floor(ourShader, translateMatrix);       //Floor

        

        //Fan
        Fan(ourShader);


        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {                 //Forward
        camera.ProcessKeyboard(FORWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {                 //Backward
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {                 //Left
        camera.ProcessKeyboard(LEFT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {                 //Right
        camera.ProcessKeyboard(RIGHT, deltaTime);
    }

    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)                   //Down
    {
        camera.ProcessKeyboard(DOWN, deltaTime);


    }

    if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)                   //Rotate Fan
    {
        isRotate ^= true;
        Sleep(100);

    }
    
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)                   //Up
    {
        /*eyeY -= 2.5 * deltaTime;
        basic_camera.changeEye(eyeX, eyeY, eyeZ);*/
        camera.ProcessKeyboard(UP, deltaTime);

    }
    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
    {
        camera.ProcessKeyboard(YAW_R, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
    {
        camera.ProcessKeyboard(YAW_L, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
    {
        camera.ProcessKeyboard(PITCH_R, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
    {
        camera.ProcessKeyboard(PITCH_L, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)
    {
        camera.ProcessKeyboard(ROLL_R, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS)
    {
        camera.ProcessKeyboard(ROLL_L, deltaTime);
    }

}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}



// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}

void Bed(Shader ourShader, glm::mat4 moveMatrix)
{

    //float tableY = 0.05f;
    // Bed box
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, scaleMatrix, model;

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5f, 0.5f, 3.0f));
    model = translateMatrix * scaleMatrix;
    ourShader.setMat4("model", moveMatrix * model);
    ourShader.setVec4("color", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


    // Headstand
    glm::mat4 identityMatrix1 = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix1, scaleMatrix1, model1;
    translateMatrix1 = glm::translate(identityMatrix1, glm::vec3(0.01f, 0.0f, -0.01f));
    scaleMatrix1 = glm::scale(identityMatrix1, glm::vec3(1.5f, 1.2f, 0.1f));
    model1 = translateMatrix1 * scaleMatrix1;
    ourShader.setMat4("model", moveMatrix * model1);
    ourShader.setVec4("color", glm::vec4(0.25f, 0.1f, 0.0f, 1.0f));
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    // Pillow 1
    glm::mat4 identityMatrix2 = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix2, scaleMatrix2, model2;
    translateMatrix2 = glm::translate(identityMatrix2, glm::vec3(0.05f, 0.25f, 0.15f));
    scaleMatrix2 = glm::scale(identityMatrix2, glm::vec3(0.5f, 0.1f, 0.5f));
    model2 = translateMatrix2 * scaleMatrix2;
    ourShader.setMat4("model", moveMatrix * model2);
    ourShader.setVec4("color", glm::vec4(0.33f, .41f, .25f, 1.0f));
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    // Pillow 2
    glm::mat4 identityMatrix3 = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix3, scaleMatrix3, model3;
    translateMatrix3 = glm::translate(identityMatrix3, glm::vec3(0.45f, 0.25f, 0.15f));
    scaleMatrix3 = glm::scale(identityMatrix3, glm::vec3(0.5f, 0.1f, 0.5f));
    model3 = translateMatrix3 * scaleMatrix3;
    ourShader.setMat4("model", moveMatrix * model3);
    ourShader.setVec4("color", glm::vec4(0.33f, .41f, .25f, 1.0f));
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    // Blanket
    glm::mat4 identityMatrix4 = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix4, scaleMatrix4, model4;
    translateMatrix4 = glm::translate(identityMatrix4, glm::vec3(0.05f, 0.25f, 1.0f));
    scaleMatrix4 = glm::scale(identityMatrix4, glm::vec3(1.3f, 0.02f, 1.0f));
    model4 = translateMatrix4 * scaleMatrix4;
    ourShader.setMat4("model", moveMatrix * model4);
    ourShader.setVec4("color", glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    // legstand
    glm::mat4 identityMatrix5 = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix5, scaleMatrix5, model5;
    translateMatrix5 = glm::translate(identityMatrix5, glm::vec3(0.0f, 0.0f, 1.5f));
    scaleMatrix5 = glm::scale(identityMatrix5, glm::vec3(1.5f, 0.5f, 0.1f));
    model5 = translateMatrix5 * scaleMatrix5;
    ourShader.setMat4("model", moveMatrix * model5);
    ourShader.setVec4("color", glm::vec4(0.25f, 0.1f, 0.0f, 1.0f));
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

}

void Table(Shader ourShader, glm::mat4 moveMatrix)
{

    // Top
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, scaleMatrix, model;

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5f, 0.1f, 1.0f));
    model = translateMatrix * scaleMatrix;
    ourShader.setMat4("model", moveMatrix*model);
    ourShader.setVec4("color", glm::vec4(0.87f, 0.72f, 0.53f, 1.0f));
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


    // Leg 1
    glm::mat4 identityMatrix1 = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix1, scaleMatrix1, model1;
    translateMatrix1 = glm::translate(identityMatrix1, glm::vec3(0.02f, -0.46f, 0.01f));
    scaleMatrix1 = glm::scale(identityMatrix1, glm::vec3(0.1f, 1.0f, 0.1f));
    model1 = translateMatrix1 * scaleMatrix1;
    ourShader.setMat4("model", moveMatrix * model1);
    ourShader.setVec4("color", glm::vec4(.44f, .47f, .49f, 1.0f));
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


    // Leg 2
    glm::mat4 identityMatrix2 = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix2, scaleMatrix2, model2;
    translateMatrix2 = glm::translate(identityMatrix2, glm::vec3(0.02f, -0.46f, 0.43f));
    scaleMatrix2 = glm::scale(identityMatrix2, glm::vec3(0.1f, 1.0f, 0.1f));
    model2 = translateMatrix2 * scaleMatrix2;
    ourShader.setMat4("model", moveMatrix * model2);
    ourShader.setVec4("color", glm::vec4(.44f, .47f, .49f, 1.0f));
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


    // Leg 3
    translateMatrix1 = glm::translate(identityMatrix1, glm::vec3(0.69f, -0.46f, 0.01f));
    scaleMatrix1 = glm::scale(identityMatrix1, glm::vec3(0.1f, 1.0f, 0.1f));
    model1 = translateMatrix1 * scaleMatrix1;
    ourShader.setMat4("model", moveMatrix * model1);
    ourShader.setVec4("color", glm::vec4(.44f, .47f, .49f, 1.0f));
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


    // Leg 4
    //glm::mat4 translateMatrix2, rotateXMatrix2, rotateYMatrix2, rotateZMatrix2, scaleMatrix2, model2;
    translateMatrix2 = glm::translate(identityMatrix2, glm::vec3(0.69f, -0.46f, 0.43f));
    scaleMatrix2 = glm::scale(identityMatrix2, glm::vec3(0.1f, 1.0f, 0.1f));
    model2 = translateMatrix2 * scaleMatrix2;
    ourShader.setMat4("model", moveMatrix * model2);
    ourShader.setVec4("color", glm::vec4(.44f, .47f, .49f, 1.0f));
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

void Chair(Shader ourShader, glm::mat4 moveMatrix)
{
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, scaleMatrix, model;

    float fixLeg = 0.7f;
    float fixY = 0.1f;
    float fixYWhole = -0.08f;

    // Top
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.11f, 0.0f - fixY + fixYWhole, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.75f, 0.07f, 0.7f));
    model = translateMatrix * scaleMatrix;
    ourShader.setMat4("model", moveMatrix * model);
    ourShader.setVec4("color", glm::vec4(0.5f, 0.0f, 0.5f, 1.0f));
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    // Leg 1
    glm::mat4 identityMatrix1 = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix1, scaleMatrix1, model1;
    translateMatrix1 = glm::translate(identityMatrix1, glm::vec3(0.13f, -0.32f + fixYWhole, 0.01f));
    scaleMatrix1 = glm::scale(identityMatrix1, glm::vec3(0.07f, 0.7f * fixLeg, 0.07f));
    model1 = translateMatrix1 * scaleMatrix1;
    ourShader.setMat4("model", moveMatrix * model1);
    ourShader.setVec4("color", glm::vec4(0.9f, 0.9f, 1.0f, 1.0f));
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


    // Leg 2
    glm::mat4 identityMatrix2 = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix2, scaleMatrix2, model2;
    translateMatrix2 = glm::translate(identityMatrix2, glm::vec3(0.13f, -0.32f + fixYWhole, 0.28f));
    scaleMatrix2 = glm::scale(identityMatrix2, glm::vec3(0.07f, 0.7f * fixLeg, 0.07f));
    model2 = translateMatrix2 * scaleMatrix2;
    ourShader.setMat4("model", moveMatrix * model2);
    ourShader.setVec4("color", glm::vec4(0.9f, 0.9f, 1.0f, 1.0f));
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


    //// Leg 3
    //glm::mat4 translateMatrix1, rotateXMatrix1, rotateYMatrix1, rotateZMatrix1, scaleMatrix1, model1;
    translateMatrix1 = glm::translate(identityMatrix1, glm::vec3(0.43f, -0.32f + fixYWhole, 0.01f));
    scaleMatrix1 = glm::scale(identityMatrix1, glm::vec3(0.07f, 0.7f * fixLeg, 0.07f));
    model1 = translateMatrix1 * scaleMatrix1;
    ourShader.setMat4("model", moveMatrix * model1);
    ourShader.setVec4("color", glm::vec4(0.9f, 0.9f, 1.0f, 1.0f));
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


    // Leg 4
    //glm::mat4 translateMatrix2, rotateXMatrix2, rotateYMatrix2, rotateZMatrix2, scaleMatrix2, model2;
    translateMatrix2 = glm::translate(identityMatrix2, glm::vec3(0.43f, -0.32f + fixYWhole, 0.28f));
    scaleMatrix2 = glm::scale(identityMatrix2, glm::vec3(0.07f, 0.7f * fixLeg, 0.07f));
    model2 = translateMatrix2 * scaleMatrix2;
    ourShader.setMat4("model", moveMatrix * model2);
    ourShader.setVec4("color", glm::vec4(0.9f, 0.9f, 1.0f, 1.0f));
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


    //Left up 
    translateMatrix2 = glm::translate(identityMatrix2, glm::vec3(0.17f, 0.01f - fixY + fixYWhole, 0.29f));
    scaleMatrix2 = glm::scale(identityMatrix2, glm::vec3(0.07f, 0.25f, 0.07f));
    model2 = translateMatrix2 * scaleMatrix2;
    ourShader.setMat4("model", moveMatrix * model2);
    ourShader.setVec4("color", glm::vec4(0.9f, 0.9f, 1.0f, 1.0f));
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


    //Right up
    translateMatrix2 = glm::translate(identityMatrix2, glm::vec3(0.39f, 0.01f - fixY + fixYWhole, 0.29f));
    scaleMatrix2 = glm::scale(identityMatrix2, glm::vec3(0.07f, 0.25f, 0.07f));
    model2 = translateMatrix2 * scaleMatrix2;
    ourShader.setMat4("model", moveMatrix * model2);
    ourShader.setVec4("color", glm::vec4(0.9f, 0.9f, 1.0f, 1.0f));
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    //Back support
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.15f, 0.09f - fixY + fixYWhole, 0.28f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.6f, 0.5f, 0.1f));
    model = translateMatrix * scaleMatrix;
    ourShader.setMat4("model", moveMatrix * model);
    ourShader.setVec4("color", glm::vec4(0.5f, 0.0f, 0.0f, 1.0f));
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

void Nightstand(Shader ourShader, glm::mat4 moveMatrix)
{
    // Main frame
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, scaleMatrix, model;

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.8f, 1.0f, 1.0f));
    model = translateMatrix * scaleMatrix;
    ourShader.setMat4("model", moveMatrix * model);
    ourShader.setVec4("color", glm::vec4(0.58f, 0.29f, 0.0f, 1.0f));
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    // Bottom drawer
    glm::mat4 identityMatrix1 = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix1, scaleMatrix1, model1;

    translateMatrix1 = glm::translate(identityMatrix1, glm::vec3(0.02f, 0.08f, 0.5f));
    scaleMatrix1 = glm::scale(identityMatrix1, glm::vec3(0.7f, 0.35f, 0.01f));
    model1 = translateMatrix1 * scaleMatrix1;
    ourShader.setMat4("model", moveMatrix * model1);
    ourShader.setVec4("color", glm::vec4(0.71f, 0.39f, 0.11f, 1.0f));
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    // Top drawer
    glm::mat4 identityMatrix2 = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first

    translateMatrix1 = glm::translate(identityMatrix2, glm::vec3(0.02f, 0.28f, 0.5f));
    model1 = translateMatrix1 * scaleMatrix1;
    ourShader.setMat4("model", moveMatrix * model1);
    ourShader.setVec4("color", glm::vec4(0.71f, 0.39f, 0.11f, 1.0f));
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


}

void Handle(Shader ourShader, glm::mat4 moveMatrix)
{
    // left cube
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, scaleMatrix, model;

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 0.1f, 0.1f));
    model = translateMatrix * scaleMatrix;
    ourShader.setMat4("model", moveMatrix * model);
    ourShader.setVec4("color", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    // right cube
    glm::mat4 identityMatrix1 = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix1, model1;

    translateMatrix1 = glm::translate(identityMatrix1, glm::vec3(0.15f, 0.0f, 0.0f));
    model1 = translateMatrix1 * scaleMatrix;
    ourShader.setMat4("model", moveMatrix * model1);
    ourShader.setVec4("color", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    // front cube
    glm::mat4 identityMatrix2 = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix2, model2, scaleMatrix2;

    translateMatrix2 = glm::translate(identityMatrix2, glm::vec3(0.0f, 0.05f, 0.0f));
    scaleMatrix2 = glm::scale(identityMatrix2, glm::vec3(0.4f, 0.1f, 0.1f));
    model2 = translateMatrix2 * scaleMatrix2;
    ourShader.setMat4("model", moveMatrix * model2);
    ourShader.setVec4("color", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

void Almirah(Shader ourShader, glm::mat4 moveMatrix)
{
    // Main frame
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, scaleMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, model;

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, 1.5f, 1.0f));
    rotateXMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    rotateZMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
    ourShader.setMat4("model", moveMatrix * model);
    ourShader.setVec4("color", glm::vec4(0.58f, 0.29f, 0.0f, 1.0f));
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    // left drawer
    glm::mat4 identityMatrix1 = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix1, scaleMatrix1, model1;

    translateMatrix1 = glm::translate(identityMatrix1, glm::vec3(0.02f, 0.08f, 0.5f));
    scaleMatrix1 = glm::scale(identityMatrix1, glm::vec3(0.45f, 1.3f, 0.01f));
    model1 = translateMatrix1 * scaleMatrix1;
    ourShader.setMat4("model", moveMatrix * model1);
    ourShader.setVec4("color", glm::vec4(0.71f, 0.39f, 0.11f, 1.0f));
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    // right drawer
    glm::mat4 identityMatrix2 = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first

    translateMatrix1 = glm::translate(identityMatrix2, glm::vec3(0.255f, 0.08f, 0.5f));
    model1 = translateMatrix1 * scaleMatrix1;
    ourShader.setMat4("model", moveMatrix * model1);
    ourShader.setVec4("color", glm::vec4(0.71f, 0.39f, 0.11f, 1.0f));
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

}

void Floormat(Shader ourShader, glm::mat4 moveMatrix)
{
    // mat
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, scaleMatrix, model;

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.8f, 0.12f, 1.0f));
    model = translateMatrix * scaleMatrix;
    ourShader.setMat4("model", moveMatrix * model);
    ourShader.setVec4("color", glm::vec4(.08f, .70f, .45f, 1.0f));
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

void Window(Shader ourShader, glm::mat4 moveMatrix)
{
    // Main frame
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, scaleMatrix, model;

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.5f, 1.5f, 0.1f));
    model = translateMatrix * scaleMatrix;
    ourShader.setMat4("model", moveMatrix * model);
    ourShader.setVec4("color", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    //// right shadow
    //glm::mat4 identityMatrix1 = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    //glm::mat4 translateMatrix1, scaleMatrix1, model1;

    //translateMatrix1 = glm::translate(identityMatrix1, glm::vec3(2.0f, 0.0f, 0.0f));
    //scaleMatrix1 = glm::scale(identityMatrix1, glm::vec3(0.01f, 1.5f, 0.1f));
    //model1 = translateMatrix1 * scaleMatrix1;
    //ourShader.setMat4("model", moveMatrix * model1);
    //ourShader.setVec4("color", glm::vec4(0.83f, 0.83f, 0.83f, 1.0f));
    //glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    // vertical rod
    glm::mat4 identityMatrix2 = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix2, scaleMatrix2, model2;

    translateMatrix2 = glm::translate(identityMatrix2, glm::vec3(0.625f, 0.0f, 0.01f));
    scaleMatrix2 = glm::scale(identityMatrix2, glm::vec3(0.02f, 1.5f, 0.1f));
    model2 = translateMatrix2 * scaleMatrix2;
    ourShader.setMat4("model", moveMatrix * model2);
    ourShader.setVec4("color", glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    // horizontal rod1
    translateMatrix2 = glm::translate(identityMatrix2, glm::vec3(0.0f, 0.25f, 0.01f));
    scaleMatrix2 = glm::scale(identityMatrix2, glm::vec3(2.5f, 0.03f, 0.1f));
    model2 = translateMatrix2 * scaleMatrix2;
    ourShader.setMat4("model", moveMatrix * model2);
    ourShader.setVec4("color", glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    // horizontal rod2
    translateMatrix2 = glm::translate(identityMatrix2, glm::vec3(0.0f, 0.5f, 0.01f));
    scaleMatrix2 = glm::scale(identityMatrix2, glm::vec3(2.5f, 0.03f, 0.1f));
    model2 = translateMatrix2 * scaleMatrix2;
    ourShader.setMat4("model", moveMatrix * model2);
    ourShader.setVec4("color", glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

}

void Monitor(Shader ourShader, glm::mat4 moveMatrix)
{

    // platform
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, scaleMatrix, model;

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.5f, 0.13f, .3f));
    model = translateMatrix * scaleMatrix;
    ourShader.setMat4("model", moveMatrix * model);
    ourShader.setVec4("color", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    // neck
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.075f, 0.0f, 0.05f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.18f, 0.2f, .1f));
    model = translateMatrix * scaleMatrix;
    ourShader.setMat4("model", moveMatrix * model);
    ourShader.setVec4("color", glm::vec4(.0f, .0f, .0f, 1.0f));
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    // screen
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.075f, 0.1f, 0.05f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.8f, .6f, .1f));
    model = translateMatrix * scaleMatrix;
    ourShader.setMat4("model", moveMatrix * model);
    ourShader.setVec4("color", glm::vec4(.0f, .0f, .0f, 1.0f));
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    // oled
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.066f, 0.1043f, .075f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.76f, .56f, .06f));
    model = translateMatrix * scaleMatrix;
    ourShader.setMat4("model", moveMatrix * model);
    ourShader.setVec4("color", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


}

//void AC(Shader ourShader, glm::mat4 moveMatrix)
//{
//    // Main frame
//    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
//    glm::mat4 translateMatrix, scaleMatrix, model;
//
//    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
//    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5f, 0.4f, 0.3f));
//    model = translateMatrix *  scaleMatrix;
//    ourShader.setMat4("model", moveMatrix * model);
//    ourShader.setVec4("color", glm::vec4(0.83f, 0.83f, 0.83f, 1.0f));
//    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
//
//    // upper ac
//    glm::mat4 identityMatrix1 = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
//    glm::mat4 translateMatrix1, scaleMatrix1, rotateXMatrix, rotateYMatrix, rotateZMatrix, model1;
//
//    translateMatrix1 = glm::translate(identityMatrix1, glm::vec3(1.0f, 0.0f, 0.0f));
//    scaleMatrix1 = glm::scale(identityMatrix1, glm::vec3(1.5f, 0.4f, 0.3f));
//    rotateXMatrix = glm::rotate(identityMatrix, glm::radians(45.0f), glm::vec3(1.0f, 0.0f, 0.0f));
//    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
//    rotateZMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
//    model1 = translateMatrix1 * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix1;
//    ourShader.setMat4("model", moveMatrix * model1);
//    ourShader.setVec4("color", glm::vec4(0.83f, 0.83f, 0.83f, 1.0f));
//    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
//
//    /*// left drawer
//    glm::mat4 identityMatrix1 = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
//    glm::mat4 translateMatrix1, scaleMatrix1, model1;
//
//    translateMatrix1 = glm::translate(identityMatrix1, glm::vec3(0.02f, 0.08f, 0.5f));
//    scaleMatrix1 = glm::scale(identityMatrix1, glm::vec3(0.45f, 1.3f, 0.01f));
//    model1 = translateMatrix1 * scaleMatrix1;
//    ourShader.setMat4("model", moveMatrix * model1);
//    ourShader.setVec4("color", glm::vec4(0.71f, 0.39f, 0.11f, 1.0f));
//    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
//
//    // right drawer
//    glm::mat4 identityMatrix2 = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
//
//    translateMatrix1 = glm::translate(identityMatrix2, glm::vec3(0.255f, 0.08f, 0.5f));
//    model1 = translateMatrix1 * scaleMatrix1;
//    ourShader.setMat4("model", moveMatrix * model1);
//    ourShader.setVec4("color", glm::vec4(0.71f, 0.39f, 0.11f, 1.0f));
//    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);*/
//
//}

void SideWall(Shader ourShader, glm::mat4 moveMatrix)
{
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, scaleMatrix, model;

    translateMatrix = glm::translate(identityMatrix, glm::vec3(-2.0f, 0.0f, -4.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 2.5f * 1.6f, 10.0f));
    model = translateMatrix * scaleMatrix;
    ourShader.setMat4("model", moveMatrix * model);
    ourShader.setVec4("color", glm::vec4(0.98f, 0.87f, 0.92f, 1.0f));
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

void FrontWall(Shader ourShader, glm::mat4 moveMatrix)
{
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, scaleMatrix, model;

    translateMatrix = glm::translate(identityMatrix, glm::vec3(-2.0f, 0.0f, -4.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(9.3f, 2.5f * 1.6f, 0.1f));
    model = translateMatrix * scaleMatrix;
    ourShader.setMat4("model", moveMatrix * model);
    ourShader.setVec4("color", glm::vec4(0.61f, 0.69f, 0.69f, 1.0f));
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

void Roof(Shader ourShader, glm::mat4 moveMatrix)
{
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, scaleMatrix, model;

    translateMatrix = glm::translate(identityMatrix, glm::vec3(-2.0f, 2.0f, -6.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(9.3f, 0.1f, 10.0f));
    model = translateMatrix * scaleMatrix;
    ourShader.setMat4("model", moveMatrix * model);
    ourShader.setVec4("color", glm::vec4(0.59f, 0.58f, 0.61f, 1.0f));
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

void Floor (Shader ourShader, glm::mat4 moveMatrix)
{
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, scaleMatrix, model;

    translateMatrix = glm::translate(identityMatrix, glm::vec3(-2.0f, 1.25f + 0.45f, -6.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(9.3f, 0.1f, 10.0f));
    model = translateMatrix * scaleMatrix;
    ourShader.setMat4("model", moveMatrix * model);
    ourShader.setVec4("color", glm::vec4(0.51f, 0.44f, 0.38f, 1.0f));
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

void Fan(Shader ourShader)
{
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateToPivot, translateFromPivot, rotateYMatrix, scaleMatrix, model, moveModel;

    //hook
    moveModel = glm::translate(identityMatrix, glm::vec3(0.0f, 1.77f, -2.5f));   //z 0.0
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 0.5f, 0.1f));
    model = moveModel * scaleMatrix;
    ourShader.setMat4("model",  model);
    ourShader.setVec4("color", glm::vec4(0.2f, 0.2f, 0.2f, 1.0f));
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    if (isRotate)
    {
        rotateAngle_Y += fanSpeed;
        rotateAngle_Y = fmod(rotateAngle_Y, 360);
    }
    


    //middle
    translateToPivot = glm::translate(identityMatrix, glm::vec3(-0.125f, -0.075f, -0.125f));   
    translateFromPivot = glm::translate(identityMatrix, glm::vec3(0.125f, 0.075f, 0.125f));     
    moveModel = glm::translate(identityMatrix, glm::vec3(-0.1f, 1.65f, -2.6f));   
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.5f, 0.3f, 0.5f));
    model = moveModel * translateFromPivot * rotateYMatrix * translateToPivot * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("color", glm::vec4(0.75f, .75f, 0.75f, 1.0f));
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    //blade1
    translateToPivot = glm::translate(identityMatrix, glm::vec3(-0.7f, -0.025f, -0.075f));
    translateFromPivot = glm::translate(identityMatrix, glm::vec3(0.7f, 0.025f, 0.075f));
    moveModel = glm::translate(identityMatrix, glm::vec3(-0.65f, 1.67f, -2.55f));      
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.8f, 0.1f, 0.3f));
    model = moveModel * translateFromPivot * rotateYMatrix * translateToPivot * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("color", glm::vec4(1.0f, 0.99f, 0.82f, 1.0f));
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    //blade2
    translateToPivot = glm::translate(identityMatrix, glm::vec3(-0.075f, -0.025f, -0.7f));
    translateFromPivot = glm::translate(identityMatrix, glm::vec3(0.075f, 0.025f, 0.7f));
    moveModel = glm::translate(identityMatrix, glm::vec3(-0.05f, 1.67f, -3.15f));       //-.65
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.3f, 0.1f, 2.8f));
    model = moveModel * translateFromPivot * rotateYMatrix * translateToPivot * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("color", glm::vec4(1.0f, 0.99f, 0.82f, 1.0f));
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

}


void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}
