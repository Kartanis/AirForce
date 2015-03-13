#pragma once

#include "../Dependencies/glew/glew.h"
#include "../Dependencies/freeglut/freeglut.h"
#include <iostream>

#include <stdio.h>
#include <string.h>


	namespace Core{


		char* getShaderLanguageVersion(void);

		class Shader_Loader{
		private:

			std::string ReadShader(char *filename);
			GLuint CreateShader(GLenum shaderType,
				std::string source,
				char* shaderName);

		public:

			Shader_Loader(void);
			~Shader_Loader(void);
			GLuint CreateProgram(char* VertexShaderFilename,
				char* FragmentShaderFilename);

		};
	}
