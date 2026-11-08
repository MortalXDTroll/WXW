#pragma once
#include <glad/glad.h>

class EBO {
	private:
		unsigned int ID = 0;
	public:
		EBO(GLsizeiptr size, const void* data, GLenum usage);
		~EBO();

		// Copy Constructor
		EBO(const EBO&) = delete;
		EBO& operator=(const EBO&) = delete;

		// Move Constructor
		EBO(EBO&& other) noexcept;
		EBO& operator=(EBO&& other) noexcept;

		void bind();
		void unbind();

		inline unsigned int getID() const { return ID; }
};