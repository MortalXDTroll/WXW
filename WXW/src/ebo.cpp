#include "../include/ebo.h"
#include <utility>
#include <iostream>

EBO::EBO(GLsizeiptr size, const void* data, GLenum usage) {
	glGenBuffers(1, &ID);
	this->bind();

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, usage);
	this->unbind();
}

EBO::EBO(EBO&& other) noexcept : ID(std::exchange(other.ID, 0)) {}
EBO& EBO::operator=(EBO&& other) noexcept {
	if (this != &other) {
		if (ID != 0) glDeleteBuffers(1, &ID);
		ID = std::exchange(other.ID, 0);
	}

	return *this;
}

void EBO::bind() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}
void EBO::unbind() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

EBO::~EBO() {
	std::cout << "Destroying EBO: " << ID << "\n";
	if (ID != 0) glDeleteBuffers(1, &ID);
}