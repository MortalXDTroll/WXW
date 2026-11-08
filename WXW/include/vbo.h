#pragma once
#include <glad/glad.h>

class VBO {
	private:
		unsigned int ID = 0; 
	public:
		VBO(GLsizeiptr size, const void* data, GLenum usage);
		~VBO();

		// Copy Constructor
		VBO(const VBO&) = delete;
		VBO& operator=(const VBO&) = delete;

		// Move Constructor
		VBO(VBO&& other) noexcept;
		VBO& operator=(VBO&& other) noexcept;

		void bind() const;
		void unbind() const;
		
		inline unsigned int getID() const { return ID; }
};

