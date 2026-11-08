#pragma once
#include <glad/glad.h>
#include "../include/vbo.h"

class VAO {
	private:
		unsigned int ID = 0;
	public:
		VAO();
		~VAO();

		// Copy Constructor
		VAO(const VAO&) = delete;
		VAO& operator=(const VAO&) = delete;

		// Move Constructor
		VAO(VAO&& other) noexcept;
		VAO& operator=(VAO&& other) noexcept;

		void link(VBO& vbo, unsigned int index, int size, GLenum type, GLboolean normalized, GLsizei stride, const void* offset);
		void bind() const;
		void unbind() const;
		
		inline unsigned int getID() const { return ID; }
};