#pragma once

// Stripped-down redefinition of OvObject (just for the chunk IDs):
class OvObject {
public:
	enum class Type : int  ///< Type of entities 
	{
		// Foundation types:
		OBJECT = 0,
		NODE,
		OBJECT2D,
		OBJECT3D,
		LIST,

		// Derived classes:
		BUFFER,
		SHADER,
		TEXTURE,
		FILTER,
		MATERIAL,
		FBO,
		QUAD,
		BOX,
		SKYBOX,
		FONT,
		CAMERA,
		LIGHT,
		BONE,
		MESH,	   // Keep them...
		SKINNED, // ...consecutive        
		INSTANCED,
		PIPELINE,
		EMITTER,

		// Animation type
		ANIM,

		// Physics related:
		PHYSICS,

		// Terminator:
		LAST,
	};
};


// Stripped-down redefinition of OvMesh (just for the subtypes):
class OvMesh {
public:
	enum class Subtype: int ///< Kind of mesh
	{
		// Foundation types:
		DEFAULT = 0,
		NORMALMAPPED,
		TESSELLATED,

		// Terminator:
		LAST,
	};
};


// Stripped-down redefinition of OvLight (just for the subtypes):
class OvLight {
public:
	enum class Subtype : int ///< Kind of light
	{
		// Foundation types:
		OMNI = 0,
		DIRECTIONAL,
		SPOT,

		// Terminator:
		LAST,
	};
};