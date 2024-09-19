#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "shader.hpp"
#include <iostream>

int main(int argc,char** argv)
{
    if(argc<3)
    {
        std::cerr<<"missing shader file"<<std::endl;
        return -1;
    }
    GLFWwindow* window;

    if (!glfwInit())
        return -1;

    //glfwWindowHint(GLFW_FLOATING,GLFW_TRUE);
    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER,GLFW_TRUE);
    glfwWindowHint(GLFW_RESIZABLE,GLFW_FALSE); 
    glfwWindowHint(GLFW_DECORATED,GLFW_FALSE);
    window = glfwCreateWindow(1366,768,"Im gonna eat your screen",NULL,NULL);
    //window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glewInit();

    float vertices[] = {-1,-1,-1366,-768,
    	 1,-1, 1366,-768,
    	-1, 1,-1366, 768,
         1,-1, 1366,-768,
        -1, 1,-1366, 768,
         1, 1, 1366, 768,
        };
	
    GLuint VAO,VBO;
    glGenBuffers(1,&VBO);
    glGenVertexArrays(1,&VAO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,96,vertices,GL_STATIC_DRAW);
    glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,16,(void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,16,(void*)8);
    glEnableVertexAttribArray(1);
    
    Shader program{argv[1],argv[2]};//"src/shader/eater.vs","src/shader/eaterV3.fs"};
    program.use();

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
	    program.setFloat("time",glfwGetTime());
	    glDrawArrays(GL_TRIANGLES,0,6);
        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
