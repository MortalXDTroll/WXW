#include "../include/vbo.h"
#include <utility>
#include <iostream>

VBO::VBO(GLsizeiptr size, const void* data, GLenum usage){
	glGenBuffers(1, &ID);
	this->bind();

	glBufferData(GL_ARRAY_BUFFER, size, data, usage);
	this->unbind();
};

VBO::VBO(VBO&& other) noexcept: ID(std::exchange(other.ID, 0)) {}
VBO& VBO::operator=(VBO&& other) noexcept {
	if (this != &other) {
		if (ID != 0) glDeleteBuffers(1, &ID);
		ID = std::exchange(other.ID, 0);
	}

	return *this;
}

void VBO::bind() const{
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}
void VBO::unbind() const{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

VBO::~VBO(){
	std::cout << "Destroying VBO: " << ID << "\n";
	if(ID != 0) glDeleteBuffers(1, &ID);
};
