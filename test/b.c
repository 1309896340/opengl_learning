#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "p_vector.h"

GLuint shaderCompile(const char *source,GLenum type){
	// 编译shader并检查编译是否通过
	// 默认source是以'\0'结尾的字符串
	GLuint shader = glCreateShader(type);
	glShaderSource(shader,1,&source,NULL);
	glCompileShader(shader);

	GLint success;
	glGetShaderiv(shader,GL_COMPILE_STATUS,&success);
	if(!success){
		printf("shader %u compile failed!\n",type);
		glfwTerminate();
		return type;
	}
}

GLuint initProgram(GLuint *shader,int n){
	// 初始化program并连接shader,自动清理shader
	GLuint program = glCreateProgram();
	for(int i=0;i<n;i++)
		glAttachShader(program,shader[i]);
	glLinkProgram(program);
	for(int i=0;i<n;i++)
		glDeleteShader(shader[i]);
	GLint success;
	glGetProgramiv(program,GL_LINK_STATUS,&success);
	if(success==GL_FALSE){
		puts("program link failed!");
		glfwTerminate();
		return 0;
	}
	return program;
}

void initGlad(){
	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
		puts("glad load failed!");
		glfwTerminate();
	}

}

void clearBackground(){
	glClearColor(1.0f,1.0f,1.0f,1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void showEdge(unsigned int *p1,unsigned int *p2,unsigned int n_dims){
	putchar('(');
	for(int i=0;i<n_dims;i++){
		if(i)
			putchar(',');
		printf("%u",p1[i]);
	}
	putchar(')');
	printf("->");
	putchar('(');
	for(int i=0;i<n_dims;i++){
		if(i)
			putchar(',');
		printf("%d",p2[i]);
	}
	putchar(')');
	putchar('\n');
}

int cmpEdge(unsigned int *p1,unsigned int *p2,unsigned int n_dims){
	// 完全相同返回0,不相同返回非0
	for(int i=0;i<n_dims;i++)
		if(p1[i]!=p2[i])
			return 1;
	return 0;
}

p_vector pv;

void genEdge(unsigned int *point,unsigned int n_dims){
	// 注:必须保证两个点开辟好n_dimns长度的数组空间

	// unsigned int *p1 = (unsigned int *)malloc(n_dims*sizeof(unsigned int));
	// unsigned int *p2 = (unsigned int *)malloc(n_dims*sizeof(unsigned int));

	unsigned int *pp = (unsigned int *)malloc(2*n_dims*sizeof(unsigned int));

	for(int i=0;i<n_dims;i++){
		if(point[i] == 0){
			memcpy(pp,point,n_dims*sizeof(unsigned int));
			point[i] = 1;
			memcpy(pp + n_dims,point,n_dims*sizeof(unsigned int));
			p_push(pv,pp);
			showEdge(pp,pp+n_dims,n_dims);	// 调试输出
			genEdge(point,n_dims);
			point[i] = 0;
		}
	}
	// free(p1);
	// free(p2);
	free(pp);

}


int main(int argc,char **argv){
	glfwInit();

	glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);


	GLFWwindow *window = glfwCreateWindow(800,600,"Window",NULL,NULL);
	glfwMakeContextCurrent(window);

	initGlad();

	const char *vertexShaderSource = "#version 330 core\nlayout(location=0) in vec3 position;\nvoid main(){gl_Position = vec4(position.xyz,1.0f);}";
	const char *fragmentShaderSource = "#version 330 core\nout vec4 color;\nvoid main(){color = vec4(0.0f,0.0f,1.0f,1.0f);}";

	GLuint shader[2] = {0};
	GLuint program = 0;
	shader[0] = shaderCompile(vertexShaderSource,GL_VERTEX_SHADER);
	shader[1] = shaderCompile(fragmentShaderSource,GL_FRAGMENT_SHADER);
	program = initProgram(shader,2);
	glUseProgram(program);


	unsigned int ndims = 3;
	unsigned int pbuf[3] = {0};

	p_init(&pv,20,ndims*2);
	genEdge(pbuf,ndims);

	uint flt[90] = {0};
	p_flatten(pv,flt,90);	// 将顶点数据存入flt
	p_del(&pv);
	showArray(flt,90);

	GLuint VBO;
	glGenBuffers(1,&VBO);
	glBindBuffer(GL_ARRAY_BUFFER,VBO);
	glBufferData(GL_ARRAY_BUFFER,90*sizeof(uint),flt,GL_STATIC_DRAW);
	GLuint VAO;
	
	glGenVertexArrays(1,&VAO);
	glBindVertexArray(VAO);
	glVertexAttribPointer(0,3,GL_UNSIGNED_INT,GL_FALSE,0,(GLvoid *)0);
	glEnableVertexAttribArray(0);
	
	glLineWidth(3);

	while(!glfwWindowShouldClose(window)){
		glfwPollEvents();

		clearBackground();

		glBindVertexArray(VAO);
		glDrawArrays(GL_LINES,0,30);
		glBindVertexArray(0);

		glfwSwapBuffers(window);

	}
	glfwTerminate();
	return 0;
}
