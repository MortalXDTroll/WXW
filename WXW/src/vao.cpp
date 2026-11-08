#include "../include/vao.h"
#include <utility>
#include <iostream>

VAO::VAO() {
	glGenVertexArrays(1, &ID);
}

VAO::VAO(VAO&& other) noexcept : ID(std::exchange(other.ID, 0)) {}
VAO& VAO::operator=(VAO&& other) noexcept {
	if (this != &other) {
		if (ID != 0) glDeleteVertexArrays(1, &ID);
		ID = std::exchange(other.ID, 0);
	}

	return *this;
}

void VAO::link(VBO& vbo, unsigned int index, int size, GLenum type, GLboolean normalized, GLsizei stride, const void* offset) {
	this->bind();
	vbo.bind();

	glVertexAttribPointer(index, size, type, normalized, stride, offset);
	glEnableVertexAttribArray(index);

	vbo.unbind();
	this->unbind();
}
void VAO::bind() const{
	glBindVertexArray(ID);
}
void VAO::unbind() const{
	glBindVertexArray(0);
}

VAO::~VAO() {
	std::cout << "Destroying VAO: " << ID << "\n";
	if( ID != 0 ) glDeleteVertexArrays(1, &ID);
}