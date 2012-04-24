#ifndef MATRIX_H
#define MATRIX_H

//#include "Structs.hpp"
//#include <vector>

class Matrix
{
	float
		m_fIndex[4][4];

public:

	Matrix(
	)
	{
		// Initialize matrix
		for(int i = 0; i < 4; i++)
			for(int j = 0; j < 4; j++)
				m_fIndex[i][j] = 0;	// Zero out matrix

	}

	//--------------------------------------------------

	void vRotateX(	// Rotate a set of vertices around the x-axis
		std::vector<Point> &points,	// In/Out: Vertices to rotate
		float degree,										// Degrees to rotate
		Point center										// The point to rotate about
	)
	{
		// Initialize rotation matrix
		m_fIndex[0][0] = 1;
		m_fIndex[1][1] = (float)cos(DegreesToRads(degree));
		m_fIndex[2][2] = (float)cos(DegreesToRads(degree));
		m_fIndex[3][3] = 1;
		m_fIndex[1][2] = (float)(-1*(sin(DegreesToRads(degree))));
		m_fIndex[2][1] = (float)sin(DegreesToRads(degree));

		// Translate the object back to its center before rotation
		for(unsigned int i = 0; i < points.size(); i++)
			vMultiply(*this, points[i]);
	}

	//--------------------------------------------------

	void vRotateX(	// Rotate a vertex around the x-axis
		Point &point,	// In/Out: Vertex to rotate
		float degree,	// Degrees to rotate
		Point center	// The point to rotate about
	)
	{
		// Initialize rotation matrix
		m_fIndex[0][0] = 1;
		m_fIndex[1][1] = (float)cos(DegreesToRads(degree));
		m_fIndex[2][2] = (float)cos(DegreesToRads(degree));
		m_fIndex[3][3] = 1;
		m_fIndex[1][2] = (float)(-1*(sin(DegreesToRads(degree))));
		m_fIndex[2][1] = (float)sin(DegreesToRads(degree));

		vMultiply(*this, point);
	}

	//--------------------------------------------------

	void vRotateY(	// Rotate a set of vertices around the y-axis
		std::vector<Point> &points,	// In/Out: Vertices to rotate
		float degree,									  // Degrees to rotate
		Point center										// The point to rotate about
	)
	{
		// Initialize rotation matrix
		m_fIndex[0][0] = (float)cos(DegreesToRads(degree));
		m_fIndex[1][1] = 1;
		m_fIndex[2][2] = (float)cos(DegreesToRads(degree));
		m_fIndex[3][3] = 1;
		m_fIndex[2][0] = (float)(-1*(sin(DegreesToRads(degree))));
		m_fIndex[0][2] = (float)sin(DegreesToRads(degree));

		for(unsigned int i = 0; i < points.size(); i++)
			vMultiply(*this, points[i]);
	}

	//--------------------------------------------------

	void vRotateY(	// Rotate a vertex around the y-axis
		Point &point,	// In/Out: Vertex to rotate
		float degree,	// Degrees to rotate
		Point center	// The point to rotate about
	)
	{
		// Initialize rotation matrix
		m_fIndex[0][0] = (float)cos(DegreesToRads(degree));
		m_fIndex[1][1] = 1;
		m_fIndex[2][2] = (float)cos(DegreesToRads(degree));
		m_fIndex[3][3] = 1;
		m_fIndex[2][0] = (float)(-1*(sin(DegreesToRads(degree))));
		m_fIndex[0][2] = (float)sin(DegreesToRads(degree));

		vMultiply(*this, point);
	}

	//--------------------------------------------------

	void vRotateZ(	// Rotate a set of vertices around the z-axis
		std::vector<Point> &points,	// In/Out: Vertices to rotate
		float degree,										// Degrees to rotate
		Point center										// The point to rotate about
	)
	{
		// Initialize rotation matrix
		m_fIndex[0][0] = (float)cos(DegreesToRads(degree));
		m_fIndex[1][1] = (float)cos(DegreesToRads(degree));
		m_fIndex[2][2] = 1;
		m_fIndex[3][3] = 1;
		m_fIndex[0][1] = (float)(-1*(sin(DegreesToRads(degree))));
		m_fIndex[1][0] = (float)sin(DegreesToRads(degree));

		for(unsigned int i = 0; i < points.size(); i++)
			vMultiply(*this, points[i]);
	}

	//--------------------------------------------------

	void vRotateZ(	// Rotate a vertex around the z-axis
		Point &point,	// In/Out: Vertex to rotate
		float degree,	// Degrees to rotate
		Point center	// The point to rotate about
	)
	{
		// Initialize rotation matrix
		m_fIndex[0][0] = (float)cos(DegreesToRads(degree));
		m_fIndex[1][1] = (float)cos(DegreesToRads(degree));
		m_fIndex[2][2] = 1;
		m_fIndex[3][3] = 1;
		m_fIndex[0][1] = (float)(-1*(sin(DegreesToRads(degree))));
		m_fIndex[1][0] = (float)sin(DegreesToRads(degree));

		vMultiply(*this, point);
	}

	//--------------------------------------------------

	void vTranslate(	// Translate a set of vertices
		std::vector<Point> &points,	// In/Out: Vertices to translate
		float dX,												// Delta X
		float dY,												// Delta Y
		float dZ												// Delta Z
	)
	{
		// Initialize translation matrix
		m_fIndex[0][0] = 1;
		m_fIndex[1][1] = 1;
		m_fIndex[2][2] = 1;
		m_fIndex[3][3] = 1;
		m_fIndex[0][3] = dX;
		m_fIndex[1][3] = dY;
		m_fIndex[2][3] = dZ;

		for(unsigned int i = 0; i < points.size(); i++)
			vMultiply(*this, points[i]);
	}

	//--------------------------------------------------

	void vTranslate(	// Translate a vertex
		Point &point,	// In/Out: Point to translate
		float dX,												// Delta X
		float dY,												// Delta Y
		float dZ												// Delta Z
	)
	{
		// Initialize translation matrix
		m_fIndex[0][0] = 1;
		m_fIndex[1][1] = 1;
		m_fIndex[2][2] = 1;
		m_fIndex[3][3] = 1;
		m_fIndex[0][3] = dX;
		m_fIndex[1][3] = dY;
		m_fIndex[2][3] = dZ;

		vMultiply(*this, point);
	}

	//--------------------------------------------------

	void vMultiply(	// Multiply a 4x4 matrix with a vertex("4x1 matrix")
		Matrix mat,		// The rotation matrix
		Point &point	// In/Out: The point to be multiplied
	)
	{
		float
			pointMat[4],	// Create a temporary 4x1 matrix from the vertex
			result[4];	// A temporary matrix to hold the result

		// Initialize the vertex matrix
		pointMat[0] = point[X];
		pointMat[1] = point[Y];
		pointMat[2] = point[Z];
		pointMat[3] = 1;

		// Initialize the result matrix
		result[0] = 0;
		result[1] = 0;
		result[2] = 0;
		result[3] = 0;

		// Multiply the matrices
		for(int i = 0; i < 4; i++)
			for(int j = 0; j < 4; j++)
				result[i] += (mat.m_fIndex[i][j] * pointMat[j]);

		// Update the vertex
		point[X] = result[0];
		point[Y] = result[1];
		point[Z] = result[2];
	}
};

#endif