#include "PolygonalMesh.hpp"
#include "Utils.hpp"





using namespace std;
using namespace PoligonalLibrary;



int main()
{
    TriangularMesh mesh;

    string filepath = "PolygonalMesh";
    if(!ImportMesh(filepath,
                    mesh))
    {
        return 1;
    }

    return 0;
  return 0;
}
