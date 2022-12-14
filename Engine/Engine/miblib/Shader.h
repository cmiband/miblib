#pragma once

#include <iostream>
#include <fstream>
#include <string>

#include "Math/Vectors.h"
#include "glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

struct ShaderType {
	std::string Vertex;
	std::string Fragment;
};

enum class readType {
	VERTEXREAD,
	FRAGMENTREAD
};

class Shader
{
private:
	unsigned int m_graphicsId;
	std::string m_vertexSource;
	std::string m_fragmentSource;

	ShaderType readShader(const std::string& filepath);
	unsigned int CompileShader(const std::string &source, unsigned int type);
	unsigned int CreateShader(const std::string& vs, std::string& fs);
public:
	Shader() : m_graphicsId(0) {};
	Shader(const std::string& filepath);
	~Shader();

	void SetUniform4f(const std::string& name, const math::Color4<float>& color);
	void SetUniformMatf(const std::string& name, const glm::mat4& matrix);

	void Bind() const;
	void Unbind() const;
	void CreatePostInitialization(const std::string& filelpath);
};

