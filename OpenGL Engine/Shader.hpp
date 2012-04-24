#if 0

/*
  Written: 13 Sep 2010: JH
  Comment: 
*/

#ifndef SHADER_H
#define SHADER_H

/********** Includes ****************************************/

//#define GLEW_STATIC	// Will link glew statically, linker input must use glew32s.lib
#include <gl\glew.h>

#include <string>

#include "Texture.hpp"	// This includes fstream

/********** Local Defines ***********************************/

/************************************************************/

using std::string;

class Shader
/*
  Purpose: Class for shader implementation, loading, compiling and linking of shaders
  Written: 13 Sep 2010: JH
*/
{

//---------- Member Variables --------------------------------

	GLhandleARB
		m_hVertexShader,
		m_hFragmentShader,
		m_hProgram;

//---------- Ctor/Dtor ---------------------------------------

public:

  Shader(	// Initialize shader; read in the shader file, compile, attach and link
		string sVertexFile,
		string sFragmentFile
  );

  ~Shader(
  );

//---------- Set/Get Member Variables ------------------------

//---------- Public Functions --------------------------------

	void vUseShader(	// Activate shader program
	);

	//----------------------------------------------------------

	void vSetAttr1i(	// Set shader attributes
		string sAttribute,
		int iValue
	);

	//----------------------------------------------------------

	void vSetAttr1f(	// Set shader attributes
		string sAttribute,
		float fValue
	);

	//----------------------------------------------------------

	void vSetAttr2f(	// Set shader attributes
		string sAttribute,
		float fValue1,
		float fValue2
	);

	//----------------------------------------------------------

	void vSetAttr3f(	// Set shader attributes
		string sAttribute,
		float fValue1,
		float fValue2,
		float fValue3
	);

	//----------------------------------------------------------

	void vSetAttr4f(	// Set shader attributes
		string sAttribute,
		float fValue1,
		float fValue2,
		float fValue3,
		float fValue4
	);

	//----------------------------------------------------------

	static void s_vDisableShaders(	// Disable all shaders
	);

//---------- Private Functions -------------------------------

private:

	char *pReadShaderFile(	// Read a shader file into memory
		const char *pFileName
	);

};

#endif

#endif