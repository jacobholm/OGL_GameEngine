#if 0

/********** Includes ****************************************/

#include "Shader.hpp"

/********** Local Defines ***********************************/

/********** Variables ***************************************/

/************************************************************/

Shader::Shader(
	string sVertexFile,
	string sFragmentFile
)
/*
  Written: 13 Sep 2010: JH
*/
{
	m_hVertexShader = glCreateShaderObjectARB(GL_VERTEX_SHADER_ARB);
	m_hFragmentShader = glCreateShaderObjectARB(GL_FRAGMENT_SHADER_ARB);

	const char
		*pVertFile = pReadShaderFile(sVertexFile.data()),
		*pFragFile = pReadShaderFile(sFragmentFile.data());

	if(pVertFile != NULL && pFragFile != NULL)
	{
		glShaderSourceARB(m_hVertexShader, 1, &pVertFile, NULL);
		glShaderSourceARB(m_hFragmentShader, 1, &pFragFile, NULL);

		delete[] pVertFile;
		delete[] pFragFile;

		glCompileShaderARB(m_hVertexShader);
		glCompileShaderARB(m_hFragmentShader);

		GLint compiled, compiled2;
		glGetObjectParameterivARB(m_hVertexShader, GL_COMPILE_STATUS, &compiled);
		glGetObjectParameterivARB(m_hFragmentShader, GL_COMPILE_STATUS, &compiled2);

		if (compiled || compiled2)
		{
			int stop = 0;
		}
		else
		{
			GLint blen = 0;	
			GLsizei slen = 0;

			glGetShaderiv(m_hVertexShader, GL_INFO_LOG_LENGTH , &blen);       
			if (blen > 1)
			{
				GLchar* compiler_log = (GLchar*)malloc(blen);
				glGetInfoLogARB(m_hVertexShader, blen, &slen, compiler_log);

				free (compiler_log);
			}

			glGetShaderiv(m_hFragmentShader, GL_INFO_LOG_LENGTH , &blen);       
			if (blen > 1)
			{
				GLchar* compiler_log = (GLchar*)malloc(blen);
				glGetInfoLogARB(m_hFragmentShader, blen, &slen, compiler_log);

				free (compiler_log);
			}
		}

		m_hProgram = glCreateProgramObjectARB();
		glAttachObjectARB(m_hProgram, m_hVertexShader);
		glAttachObjectARB(m_hProgram, m_hFragmentShader);

		glLinkProgramARB(m_hProgram);

		GLint linked;
		glGetProgramiv(m_hProgram, GL_LINK_STATUS, &linked);
		if (linked)
		{
			int stop = 0;
		}
	}
}

Shader::~Shader(
)
{

}

/************************************************************/

void Shader::vUseShader(
)
/*
  Written: 14 Sep 2010: JH
*/
{
	glUseProgramObjectARB(m_hProgram);
}

/************************************************************/

void Shader::vSetAttr1i(
	string sAttribute,
	int iValue
)
{
	glUniform1iARB(glGetUniformLocationARB(m_hProgram, sAttribute.data()), iValue);
}

/************************************************************/

void Shader::vSetAttr1f(
	string sAttribute,
	float fValue
)
{
	glUniform1fARB(glGetUniformLocationARB(m_hProgram, sAttribute.data()), fValue);
}

/************************************************************/

void Shader::vSetAttr2f(
	string sAttribute,
	float fValue1,
	float fValue2
)
{
	glUniform2fARB(glGetUniformLocationARB(m_hProgram, sAttribute.data()), fValue1, fValue2);
}

/************************************************************/

void Shader::vSetAttr3f(
	string sAttribute,
	float fValue1,
	float fValue2,
	float fValue3
)
{
	glUniform3fARB(glGetUniformLocationARB(m_hProgram, sAttribute.data()), fValue1, fValue2, fValue3);
}

/************************************************************/

void Shader::vSetAttr4f(
	string sAttribute,
	float fValue1,
	float fValue2,
	float fValue3,
	float fValue4
)
{
	glUniform4fARB(glGetUniformLocationARB(m_hProgram, sAttribute.data()), fValue1, fValue2, fValue3, fValue4);
}

/************************************************************/

void Shader::s_vDisableShaders(
)
/*
  Written: 14 Sep 2010: JH
*/
{
	glUseProgramObjectARB(NULL);
}
/************************************************************/

char *Shader::pReadShaderFile(
	const char *pFileName
)
/*
  Written: 12 Sep 2010: JH
*/
{
	int
		iLength;
	char
		*pBuffer;
	std::ifstream
		fileStream;

	fileStream.open(pFileName, std::ios::binary);

	// File could not be opened
	if(!fileStream.is_open())
		return NULL;

	// Find the length of the file
	fileStream.seekg(0, std::ios::end);
	iLength = (int)fileStream.tellg();
	fileStream.seekg(0, std::ios::beg);

	// Allocate and read file into buffer
	pBuffer = new char[iLength+1];
	fileStream.read(pBuffer, iLength);
	fileStream.close();
	pBuffer[iLength] = '\0';

	return pBuffer;
}

#endif