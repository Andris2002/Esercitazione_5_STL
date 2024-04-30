#include "Utils.hpp"
#include <iostream>
#include <sstream>
#include <fstream>
#include <cmath>

namespace PoligonalLibrary{


bool ImportMesh(const string& filepath,
                TriangularMesh& mesh)
{

    if(!ImportCell0Ds(filepath + "/Cell0Ds.csv",
                       mesh))
    {
        return false;
    }
    else
    {
        cout << "Cell0D marker:" << endl;
        for(auto it = mesh.Cell0DMarkers.begin(); it != mesh.Cell0DMarkers.end(); it++)
        {
            cout << "key:\t" << it -> first << "\t values:";
            for(const unsigned int id : it -> second)
                cout << "\t" << id;

            cout << endl;
        }
    }

    if(!ImportCell1Ds(filepath + "/Cell1Ds.csv",
                       mesh))
    {
        return false;
    }
    else
    {
        cout << "Cell1D marker:" << endl;
        cout<< mesh.Cell1DMarkers.size();
        for(auto it = mesh.Cell1DMarkers.begin(); it != mesh.Cell1DMarkers.end(); it++)
        {
            cout << "key:\t" << it -> first << "\t values:";
            for(const unsigned int id : it -> second)
                cout << "\t" << id;

            cout << endl;
        }
    }

    if(!ImportCell2Ds(filepath + "/Cell2Ds.csv",
                       mesh))
    {
        return false;
    }
    else
    {
        cout << "Cell2D marker:" << endl;
        if (mesh.Cell2DMarkers.size() != 0){
            for(auto it = mesh.Cell2DMarkers.begin(); it != mesh.Cell1DMarkers.end(); it++)
            {
                cout << "key:\t" << it -> first << "\t values:";
                for(const unsigned int id : it -> second)
                    cout << "\t" << id;

                cout << endl;
            }
        }
        else
            cout<< " no markers";

    }


    //Test for vertices length


        // Test:
        for(auto vertices : mesh.Cell1DVertices)
        {
        unsigned int v1_id = vertices(0);
        unsigned int v2_id = vertices(1);
        Vector2d coord1 = mesh.Cell0DCoordinates.at(v1_id);
        Vector2d coord2 = mesh.Cell0DCoordinates.at(v2_id);
        double eps = 1.0e-10;
        if (abs(coord1(0) - coord2(0)) < eps & abs(coord1(1) - coord2(1))< eps){
            return false;
        }


        }


    return true;

}

bool ImportCell0Ds(const string &filename,
                   TriangularMesh& mesh)
{

    ifstream file;
    file.open(filename);

    if(file.fail())
        return false;

    list<string> listLines;
    string line;
    while (getline(file, line))
        listLines.push_back(line);

    file.close();

    listLines.pop_front();

    mesh.NumberCell0D = listLines.size();

    if (mesh.NumberCell0D == 0)
    {
        cerr << "There is no cell 0D" << endl;
        return false;
    }

    mesh.Cell0DId.reserve(mesh.NumberCell0D);
    mesh.Cell0DCoordinates.reserve(mesh.NumberCell0D);

    for (const string& line : listLines)
    {


        unsigned int id;
        unsigned int marker;
        Vector2d coord;
        unsigned int pos;
        unsigned int pos1;

        pos = line.find(';',0);
        id = stoi(line.substr(0, pos));
        pos1 = line.find(';',++pos);
        marker = stoi(line.substr(pos, pos1));
        pos = line.find(';', ++pos1);
        coord(0) = stod(line.substr(pos1, pos));
        coord(1) = stod(line.substr(++pos, line.size()));


        mesh.Cell0DId.push_back(id);
        mesh.Cell0DCoordinates.push_back(coord);

        if( marker != 0)
        {
            //            if (mesh.Cell0DMarkers.find(marker) == mesh.Cell0DMarkers.end())
            //                mesh.Cell0DMarkers.insert({marker, {id}});
            //            else
            //                mesh.Cell0DMarkers[marker].push_back(id);


            auto ret = mesh.Cell0DMarkers.insert({marker, {id}});
            if(!ret.second)
                (ret.first)->second.push_back(id);
        }

    }
    file.close();
    return true;
}

// ***************************************************************************

bool ImportCell1Ds(const string &filename,
                   TriangularMesh& mesh)
{

    ifstream file;
    file.open(filename);

    if(file.fail())
        return false;

    list<string> listLines;
    string line;
    while (getline(file, line))
        listLines.push_back(line);

    listLines.pop_front();

    mesh.NumberCell1D = listLines.size();

    if (mesh.NumberCell1D == 0)
    {
        cerr << "There is no cell 1D" << endl;
        return false;
    }

    mesh.Cell1DId.reserve(mesh.NumberCell1D);
    mesh.Cell1DVertices.reserve(mesh.NumberCell1D);

    for (const string& line : listLines)
    {
        istringstream converter(line);

        unsigned int id;
        unsigned int marker;
        Vector2i vertices;
        unsigned int pos;
        unsigned int pos1;

        pos = line.find(';',0);
        id = stoi(line.substr(0, pos));
        pos1 = line.find(';',++pos);
        marker = stoi(line.substr(pos, pos1));
        pos = line.find(';', ++pos1);
        vertices(0) = stoi(line.substr(pos1, pos));
        vertices(1) = stoi(line.substr(++pos, line.size()));

        mesh.Cell1DId.push_back(id);
        mesh.Cell1DVertices.push_back(vertices);

        if( marker != 0)
        {
            //            if (mesh.Cell1DMarkers.find(marker) == mesh.Cell1DMarkers.end())
            //                mesh.Cell1DMarkers.insert({marker, {id}});
            //            else
            //                mesh.Cell1DMarkers[marker].push_back(id);


            auto ret = mesh.Cell1DMarkers.insert({marker, {id}});
            if(!ret.second)
                (ret.first)->second.push_back(id);
        }
    }

    file.close();

    return true;
}

// ***************************************************************************

bool ImportCell2Ds(const string &filename,
                   TriangularMesh& mesh)
{

    ifstream file;
    file.open(filename);

    if(file.fail())
        return false;

    list<string> listLines;
    string line;
    while (getline(file, line))
        listLines.push_back(line);

    listLines.pop_front();

    mesh.NumberCell2D = listLines.size();

    if (mesh.NumberCell2D == 0)
    {
        cerr << "There is no cell 2D" << endl;
        return false;
    }

    mesh.Cell2DId.reserve(mesh.NumberCell2D);
    mesh.Cell2DVertices.reserve(mesh.NumberCell2D);
    mesh.Cell2DEdges.reserve(mesh.NumberCell2D);

    for (const string& line : listLines)
    {


        unsigned int id;
        unsigned int marker;
        unsigned int pos;
        unsigned int pos1;

        pos = line.find(';',0);
        id = stoi(line.substr(0, pos));
        pos1 = line.find(';',++pos);
        marker = stoi(line.substr(pos, pos1));
        pos = line.find(';', ++pos1);




        mesh.Cell2DId.push_back(id);

        if( marker != 0)
        {

            auto ret = mesh.Cell1DMarkers.insert({marker, {id}});
            if(!ret.second)
                (ret.first)->second.push_back(id);
        }

        unsigned int n_vertices;
        n_vertices = stoi(line.substr(pos1,pos));
        pos1 = pos;

        std::vector<unsigned int> vertices;
        vertices.reserve(n_vertices);
        for (int i = 1; i <= n_vertices; i++){
            unsigned int vertice;
            pos = ++pos1;
            pos1 = line.find(';', pos);
            vertice = stoi(line.substr(pos, pos1));
            vertices.push_back(vertice);
        }

        mesh.Cell2DVertices.push_back(vertices);

        pos = ++pos1;
        pos1 = line.find(';', pos);
        unsigned int n_edges;
        n_edges = stoi(line.substr(pos,pos1));


        std::vector<unsigned int> edges;
        edges.reserve(n_edges);
        for (int i = 1; i <= n_edges; i++){
            unsigned int edge;
            pos = ++pos1;
            pos1 = line.find(';', pos);
            edge = stoi(line.substr(pos, pos1));
            edges.push_back(edge);
        }
        mesh.Cell2DEdges.push_back(edges);




    }
    file.close();
    return true;
}



}
