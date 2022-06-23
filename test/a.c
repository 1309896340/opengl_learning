#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>

int getStringFromFile(const char *filename,void *dst,int max_size){
	FILE *fp = NULL;
	char c;
	char *cptr = (char *)dst;
	int size = 0;
	
	fp = fopen(filename,"r");
	while((c=fgetc(fp))!=EOF){
		*cptr = c;
		size++;
		cptr++;
		if(size >= max_size-1)
			break;
	}
	*cptr = '\0';
	
	//printf("sz=%d\n%s\n",size,(char *)dst);
	
	fclose(fp);
	return size;
}


int main(int argc,char **argv){
// initialize glfw
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
	glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE,GL_FALSE);

	GLFWwindow *window = glfwCreateWindow(800,600,"my window",NULL,NULL);
	if(window==NULL){
		puts("failed to create GLFW window");
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	
// initialize glad
	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
		puts("failed to initialize GLAD");
		return -1;
	}

// vertice ready
	GLfloat vertices[] = {
		-0.5f,0.5f,0.0f,
		0.5f,0.5f,0.0f,
		0.0f,-0.5f,0.0f
	};

	GLuint VBO;
	glGenBuffers(1,&VBO);	//segmentation fault (GLAD must be loaded!)
	
// compile shader
	//const GLchar *vertexShaderSource = "#version 330 core\nlayout (location = 0) in vec3 position;\nvoid main(){\ngl_Position = vec4(position.x,position.y,position.z,1.0);\n}\n";
	//const GLchar *fragmentShaderSource = "#version 330 core\nout vec4 color;\nvoid main(){\ncolor = vec4(1.0f,0.5f,0.2f,1.0f);\n}\n";
	
	//GLchar *vertexShaderSource = (GLchar *)malloc(200*sizeof(GLchar));
	//GLchar *fragmentShaderSource = (GLchar *)malloc(200*sizeof(GLchar));
	
	GLchar aaa[200] = {0};
	GLchar bbb[200] = {0};
	GLchar *vertexShaderSource = (GLchar *)aaa;
	GLchar *fragmentShaderSource = (GLchar *)bbb;
	getStringFromFile("vertexShader",vertexShaderSource,200);
	getStringFromFile("fragmentShader",fragmentShaderSource,200);
	

	GLuint vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader,1,(const GLchar **)&vertexShaderSource,NULL);
	glCompileShader(vertexShader);

	GLuint success;
	GLchar infoLog[512];
	glGetShaderiv(vertexShader,GL_COMPILE_STATUS,&success);
	if(!success){
		glGetShaderInfoLog(vertexShader,512,NULL,infoLog);
		puts("error : vertexShader compile failed");
		puts(infoLog);
	}
	
	GLuint fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader,1,(const GLchar **)&fragmentShaderSource,NULL);
	glCompileShader(fragmentShader);
	
	memset(infoLog,0,512);
	glGetShaderiv(fragmentShader,GL_COMPILE_STATUS,&success);
	if(!success){
		glGetShaderInfoLog(fragmentShader,512,NULL,infoLog);
		puts("error : fragmentShader compile failed");
		puts(infoLog);
	}
// shader connecting
	GLint shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram,vertexShader);
	glAttachShader(shaderProgram,fragmentShader);
	glLinkProgram(shaderProgram);
	
	glGetProgramiv(shaderProgram,GL_LINK_STATUS,&success);
	if(!success){
		glGetProgramInfoLog(shaderProgram,512,NULL,infoLog);
		puts("error : shaderPrograme link failed");
	}
	glUseProgram(shaderProgram);
	
	
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);	
	
// bind VAO
	GLuint VAO;
	glGenVertexArrays(1,&VAO);
	
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER,VBO);
	glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,(GLvoid *)0);
	glEnableVertexAttribArray(0);

	
// start game loop
	while(!glfwWindowShouldClose(window)){
		glfwPollEvents();
		
		glClearColor(1.0f,1.0f,1.0f,0.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES,0,3);
		glBindVertexArray(0);
		
		
		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;
}

