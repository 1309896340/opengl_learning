#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <string.h>

int main(int argc,char **argv){
	glfwInit();
	glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
	glfwWindowHint(GLFW_RESIZABLE,GL_FALSE);
	
	GLFWwindow *window = glfwCreateWindow(800,600,"Window",NULL,NULL);
	if(window == NULL){
		puts("create window error!");
		glfwTerminate();
		return -1;
	}
	
	if(!galdLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
		puts("glad load failed");
		glfwTerminate();
		return -1;
	}
	
	
	
	
	
	while(!glfwWindowShouldClose(window)){
		glfwPollEvents();
		
	}
	glfwTerminate();
	
	return 0;
}



