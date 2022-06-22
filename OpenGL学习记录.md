OpenGL只提供了绘图功能，创建窗口需要自己完成

简化创建窗口的过程，可以使用专门的窗口库，例如GLUT、GLFW等

建议使用GLFW，因为比较新

- glew：对底层 OpenGL 接口的封装，可以让代码跨平台

- glad：glew 的升级版

- glut：处理 OpenGL 程序的工具库，负责处理和底层操作系统的调用

- glfw：glut 的升级版

## GLFW

- GLFW是一个专门针对OpenGL的C语言库，它提供了一些渲染物体所需的最低限度的接口

- 允许用户创建OpenGL上下文、定义窗口参数以及处理用户输入

对于GCC的Linux用户建议用该命令行选项：`-lGLEW -lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi` ，没有正确链接库会产生“未定义引用”的报错。

## GLAD

- OpenGL只是一个标准/规范，具体的实现是由驱动开发商针对特定显卡实现的

- 由于OpenGL驱动版本众多，它大多数函数的位置都无法在编译时确定下来，需要在运行时查询

### CMAKE使用细节

在下载下来的源码文件夹中一般有一个CMakeLists.txt文件，使用`cmake`时会读取它并生成`Makefile`文件，一般需要新建build目录进入并执行`cmake 目录`，该目录必须是CMakeLists.txt所在的目录。

# API归纳

## glfwInit()

初始化GLFW

## glfwTerminate()

销毁GLFW

## glfwWindowHint(key,value)

配置GLFW环境

常用key：

- GLFW_OPENGL_PROFILE：上下文配置，可选“核心版本”或“兼容版本”

- GLFW_RESIZABLE：窗口可调大小

- GLFW_CONTEXT_VERSION_MAJOR：版本上限

- GLFW_CONTEXT_VERSION_MINOR：版本下限

[GLFW: Window reference](https://www.glfw.org/docs/3.3/group__window.html)

## glfwCreateWindow(width,height,title,monitor,share)

创建窗口

参数：

- monitor：不用于全屏模式时设置为NULL

- share：与上下文不共享资源时设置为NULL

返回：

- 类型：GLFWwindow 指针

[GLFW: Window reference](https://www.glfw.org/docs/3.3/group__window.html#ga3555a418df92ad53f917597fe2f64aeb)

## glfwMakeContextCurrent(window)

将窗口设置为当前上下文

参数：

- window：窗口句柄

## gladLoadGLLoader(loadproc)

加载GLAD，通常初始化语句：`gladLoadGLLoader((GLADLoadproc)glfwGetProcAddress)`

## glBuffers(size,buffers)

生成缓冲对象

参数：

- size：创建缓冲的数量

- buffers：GLuint指针

## glGenVertexArrays(size,vertexArrays)

生成点数组对象

参数：

- size：创建数组的数量

- vertexArrays：GLuint指针

## glCreateShader(shaderType)

创建着色器

参数：

- shaderType：着色器类型
  
  - GL_COMPUTE_SHADER
  
  - GL_VERTEX_SHADER：顶点着色器
  
  - GL_TESS_CONTROL_SHADER
  
  - GL_TESS_EVALUATION_SHADER
  
  - GL_GEOMETRY_SHADER：几何着色器
  
  - GL_FRAGMENT_SHADER：片段着色器

返回值：

- GLuint，着色器

## glShaderSource(shader,count,shaderSource,length)

着色器加载源码

参数：

- shader：GLuint，着色器

- count：源码字符串数量

- shaderSource：字符串指针(字符二级指针，有特殊const约束)

- length：字符数组长度，为NULL默认以'\0'结尾

## glCompileShader(shader)

编译着色器

参数：

- shader：GLuint，着色器

## glGetShaderiv(shader,pname,params)

取得着色器参数

参数：

- shader：GLuint，着色器

- pname：GLenum，着色器参数名
  
  - GL_SHADER_TYPE：着色器类型
  
  - GL_DELETE_STATUS：删除状态
  
  - GL_COMPILE_STATUS：编译状态
  
  - GL_INFO_LOG_LENGTH：信息日志长度
  
  - GL_SHADER_SOURCE_LENGTH：源码长度

- params：GLint指针，输出参数
  
  - GL_INVALID_ENUM：pname不合法
  
  - GL_INVALID_VALUE：shader不合法
  
  - GL_INVALID_OPERATION：shader没有关联着色器对象

## glGetShaderInfoLog(shader,maxLength,length,infoLog)

取着色器日志信息

参数：

- shader：GLuint，着色器

- maxLength：infoLog的最大长度

- length：GLsize指针，返回infoLog实际长度

- infoLog：GLchar指针，返回日志内容

## glBindVertexArray(vertexArrays)

绑定点数组对象

参数：

- vertexArrays：GLuint，点数组对象

## glBufferData(GLenum target,GLsizeiptr size,const void * data,GLenum usage)

创建和初始化缓冲对象数据

参数：

- target：目标
  
  - GL_ARRAY_BUFFER
  
  - GL_UNIFORM_BUFFER
  
  - etc

- size：data的字节数

- data：数据指针

- usage：使用模式
  
  - GL_STREAM_DRAW
  
  - GL_STREAM_READ
  
  - GL_STREAM_COPY
  
  - GL_STATIC_DRAW
  
  - GL_STATIC_READ
  
  - GL_STATIC_COPY
  
  - GL_DYNAMIC_DRAW
  
  - GL_DYNAMIC_READ
  
  - GL_DYNAMIC_COPY

## glVertexAttribPointer(GLuint index,GLint size,GLenum type,GLboolean normalized,GLsizei stride,const void * pointer)

定义通用顶点数组属性

参数：

- index：需要修改的通用顶点属性的索引

- size：顶点维数，默认为4

- type：顶点数据类型

- normalized：是否归一化

- stride：一个点的步长，单位为字节，一般为size*sizeof(type)。默认0，表示紧密排布

- pointer：偏移量，默认0

## glEnableVertexAttribArray(GLuint index)

使能顶点属性数组

参数：

- index：顶点数组对象

## glfwWindowShouldClose(GLFWwindow *window)

返回指定窗口是否关闭的标志位

参数：

- window：目标窗口

返回值：

- int类型，关闭标志位。0表示不关，1表示关了

## glfwPollEvents()

检查事件触发，若设置了回调函数，会调用与相应事件绑定的回调

## glfwSwapBuffers(GLFWwindow *window)

交换窗口的两个颜色缓冲

参数：

- window：目标窗口

## glUseProgram(GLuint program)

装入progam对象作为当前渲染状态

参数：

- program：指定progam对象的句柄

## glDrawArrays(GLenum mode,GLint first,GLsizei count)

根据array data渲染图元

参数：

- mode：指定渲染的图元类型
  
  - GL_POINTS
  
  - GL_LINE_STRIP
  
  - GL_LINE_LOOP
  
  - GL_LINES
  
  - GL_LINE_STRIP_ADJACENCY
  
  - GL_LINES_ADJACENCY
  
  - GL_TRIANGLE_STRIP
  
  - GL_TRIANGLE_FAN
  
  - GL_TRIANGLES
  
  - GL_TRIANGLE_STRIP_ADJACENCY
  
  - GL_TRIANGLES_ADJACENCY
  
  - GL_PATCHES

- first：若干数组中指定开始数组的索引

- count：指定要渲染的索引数



## glViewport(GLint x,GLint y,GLsizei width,GLsizei height)

调整视口

参数：

- x,y：指定视口左下角位置默认为(0,0)

- width,height：指定视口的宽和高



## glfwSetFramebufferSizeCallback(GLFWwindow *window,GLFWframebuffersizefun cbfun)

设置当窗口大小发生改变时调用的回调函数
