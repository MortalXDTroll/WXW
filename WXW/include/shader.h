#pragma once
#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/gtc/type_ptr.hpp>

class Shader {
	private:
		unsigned int ID = 0;
	public:
		Shader(const char* vertexPath, const char* fragmentPath);

		void use() const;
		void setBool(const std::string& name, bool value) const;
		void setInt(const std::string& name, int value) const;
		void setFloat(const std::string& name, float value) const;
		void setMat4(const std::string& name, const glm::mat4& mat) const;
		void setVec4(const std::string& name, const glm::vec4& vec) const;
		void setVec4(const std::string& name, float x, float y, float z, float w) const;

		inline unsigned int getID() const { return ID; }
};