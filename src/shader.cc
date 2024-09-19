#include "shader.hpp"
#include <iostream>
#include <fstream>

static GLuint compile(char const* file,GLenum shaderType)
{
	GLuint shader = glCreateShader(shaderType);
	std::ifstream f(file);
	if(!f)
	{
		std::cout << "Could not open \""<<file<<'"'<<std::endl;
		return 0;
	}
	int length;
	f.seekg(0,std::ios::end);
	length = f.tellg();
	f.seekg(0,std::ios::beg);
	char* buffer = new char[length+1];
	f.read(buffer,length);
	f.close();
    buffer[length]='\0';//????
	glShaderSource(shader,1,&buffer,NULL);
	delete[] buffer;
	glCompileShader(shader);

	GLint status;
	glGetShaderiv(shader,GL_COMPILE_STATUS,&status);
	if(status != GL_TRUE)
	{
		char log[1024];
		int logLength;
		glGetShaderInfoLog(shader,1023,&length,log);
		log[length]=0;
		switch(shaderType)
		{
			case GL_VERTEX_SHADER:std::cout<<"[Vertex Shader Error]"<<std::endl;break;
			case GL_GEOMETRY_SHADER:std::cout<<"[Geometry Shader Error]"<<std::endl;break;
			case GL_FRAGMENT_SHADER:std::cout<<"[Fragment Shader Error]"<<std::endl;break;
		}
		std::cout<<log<<std::endl;
		return 0;
	}
	return shader;
}

Shader::Shader(char const* vertexFile,char const* fragmentFile):Shader(vertexFile,NULL,fragmentFile){}

Shader::Shader(char const* vertexFile,char const* geometryFile,char const* fragmentFile):map{}
{
	GLuint vertex = compile(vertexFile,GL_VERTEX_SHADER);
	GLuint fragment = compile(fragmentFile,GL_FRAGMENT_SHADER);
	GLuint geometry = geometryFile==NULL ? 0 : compile(geometryFile,GL_GEOMETRY_SHADER);
	if(vertex==0 || fragment==0)
	{
		program = 0;
		return;
	}
	program = glCreateProgram();
	glAttachShader(program,vertex);
	glAttachShader(program,fragment);
	glDeleteShader(vertex);
	glDeleteShader(fragment);
	if(geometry)
	{
		glAttachShader(program,geometry);
		glDeleteShader(geometry);
	}
	glLinkProgram(program);

	GLint status;
	glGetProgramiv(program, GL_LINK_STATUS, &status);
	if(status != GL_TRUE)
	{
		char log[1024];
		int length;
		glGetProgramInfoLog(program,1023,&length,log);
		log[length]=0;
		std::cout<<"[Linking Error]"<<std::endl<<log<<std::endl;
		glDeleteProgram(program);
		program=0;
	}
}

Shader::~Shader()
{
	glDeleteProgram(program);
}

void Shader::addMapEntry(char const* name)
{
    if((map[name]=glGetUniformLocation(program,name))==-1)
        std::cout<<"[LOG INFO] \""<<name<<"\" not found in shader"<<std::endl;
}


void Shader::use()
{
	glUseProgram(program);
}

void Shader::setInt(char const* name,int a)
{
	if(map.count(name)==0)
		addMapEntry(name);
	glUniform1i(map[name],a);
}

void Shader::setFloat(char const* name,float a)
{
	if(map.count(name)==0)
		addMapEntry(name);
	glUniform1f(map[name],a);
}

void Shader::setFloat2(char const* name,float a,float b)
{
	if(map.count(name)==0)
		addMapEntry(name);
	glUniform2f(map[name],a,b);
}

void Shader::setFloat3(char const* name,float a,float b,float c)
{
	if(map.count(name)==0)
		addMapEntry(name);
	glUniform3f(map[name],a,b,c);
}

void Shader::setFloat4(char const* name,float a,float b,float c,float d)
{
	if(map.count(name)==0)
		addMapEntry(name);
	glUniform4f(map[name],a,b,c,d);
}
