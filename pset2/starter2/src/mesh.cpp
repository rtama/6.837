#include "mesh.h"

#include "vertexrecorder.h"

using namespace std;

void Mesh::load( const char* filename )
{
	// 4.1. load() should populate bindVertices, currentVertices, and faces

	// Add your code here.

	// make a copy of the bind vertices as the current vertices
	std::ifstream infile(filename);
	std::string line;

	while (std::getline(infile, line)) {
		// read file line by line
		std::istringstream ss(line);
		Vector3f v;
		Tuple3u f;
        string label;
		ss >> label;

		if (label == "v") {
			ss >> v[0] >> v[1] >> v[2];
			bindVertices.push_back(v);
		} else {
			ss >> f[0] >> f[1] >> f[2];
			faces.push_back(f);
//            cerr << f[0] << ", " << f[1] << " , " << f[2] << endl;
		}
	}
	currentVertices = bindVertices;
}

void Mesh::draw()
{
	// 4.2 Since these meshes don't have normals
	// be sure to generate a normal per triangle.
	// Notice that since we have per-triangle normals
	// rather than the analytical normals from
	// assignment 1, the appearance is "faceted".
	VertexRecorder vr;
	for (int f = 0; f < faces.size(); ++f ) {
		Tuple3u face = faces[f];
		Vector3f v1 = currentVertices[face[0] -1];
		Vector3f v2 = currentVertices[face[1] -1];
		Vector3f v3 = currentVertices[face[2] -1];
		Vector3f side1 = v1-v2;
		Vector3f side2 = v2-v3;

		Vector3f normal = Vector3f::cross(side1, side2).normalized();
        vr.record(v1, normal);
		vr.record(v2, normal);
		vr.record(v3, normal);
	}
	vr.draw();
}

void Mesh::loadAttachments( const char* filename, int numJoints )
{
	// 4.3. Implement this method to load the per-vertex attachment weights
	// this method should update m_mesh.attachments

	std::ifstream infile(filename);
	std::string line;
	while (std::getline(infile, line)) {
		// read file line by line
		std::istringstream ss(line);
		std::vector< float > vectors;
        for (int i=0; i < numJoints-1; ++i ) {
			float v;
			ss >> v;
			vectors.push_back(v);
		}
		attachments.push_back(vectors);
	}
}
