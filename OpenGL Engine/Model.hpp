#ifndef MODEL_H
#define MODEL_H

class Model // The entire model loaded in from file, restricted to ONE mesh
{
  char
    m_sName[20];
  float
    m_fCollCircleRadius;  // For simple 2D collision
  lineSegment
    m_collisionBox;	      // The models collision box, defined by two corner points

  // 3Ds import variables
  std::vector<Point>
    m_vertices; // A vector for holding all the vertices of the submodel

  std::vector<mapcoord>
    m_mapcoords;  // UV Texture mapping coordinates.
                  // NB! The vertices and mapcoords list are in sync(i.e. vertices[i] have mapcoords[i])

  std::vector<triangleByIndex>
    m_triangles;  // A list of vertex-indices representing each triangle in the submodel.
                  // Several triangles can "reuse" the same vertex(to save space),
                  // i.e. two triangles can share the same corner vertices. Therefor we need to map
                  // each triangle to its respective vertices

  std::vector<material>
    m_materials;  // All the materials
	int
		m_iTmpSize;   // For the 3ds chunks

public:

  Model( // Parametric Constructor
    const char* sPath // Takes a 3ds file as parameter
  );

  bool boImport3ds(   // Import a 3ds model
    const char* sPath // The complete path to the file
  );                  // Returns a bool indicating whether the load was successful or not

  void vSetName(
    char* sName
  )
  {
	  strcpy_s(m_sName, sizeof(m_sName), sName);
  }

  const char* sName(
  ) const
  {
    return m_sName;
  }

  void vDrawModel(  // Draw the model
    const Point &pos,
    const Vector3f rotation
  );

  material *pFindMaterial(
    const char* sName
  );

	lineSegment& getCollisionBox(
	)
	{
		return m_collisionBox;
	}

  //-------------------------------------

  float fCollCircleRadius(
  )
  {
    return m_fCollCircleRadius;
  }

  //----------------------------------------------------------

  std::vector<Point>& getVertices(  // Return the vertices vector
  )
  {
    return m_vertices;
  }

  //-----------------------------------------------------

  std::vector<mapcoord>& getMapcoords( // Return the mapcoords vector
  )
  {
    return m_mapcoords;
  }

  std::vector<triangleByIndex>& getTriangles(  // Return the triangles vector
  )
  {
    return m_triangles;
  }

  std::vector<material>& getMaterials(
  )
  {
    return m_materials;
  }
};

#endif