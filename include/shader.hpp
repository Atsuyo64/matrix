#pragma once
#include "GL/glew.h"
#include <unordered_map>
#include <string>

class Shader
{
public:
	Shader(char const * vertexFile,char const * fragmentFile);
	Shader(char const * vertexFile,char const * geometryFile,char const * fragmentFile);
	~Shader();
	Shader(Shader const& other) = delete;
	Shader(Shader&& other) = delete;
	Shader& operator=(Shader const& other) = delete;
	Shader& operator=(Shader&& other) = delete;
	
	void use();
	void setInt(char const* name,int a);
	void setFloat(char const* name,float a);
	void setFloat2(char const* name,float a,float b);
	void setFloat3(char const* name,float a,float b,float c);
	void setFloat4(char const* name,float a,float b,float c,float d);
private:
	GLuint program;
	std::unordered_map<std::string,GLuint> map;
    void addMapEntry(char const* name);
};
