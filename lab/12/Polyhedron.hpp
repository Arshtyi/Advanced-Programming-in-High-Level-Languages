#ifndef POLYHEDRON_H
#define POLYHEDRON_H
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <limits>
#include <stdexcept>
#include "Point.hpp"
#include "Facet.hpp"
template <typename T>
class Polyhedron
{
private:
    std::vector<Point<T> *> vertices;
    std::vector<Facet<T> *> facets;

public:
    Polyhedron(const char *path)
    {
        std::ifstream file(path);
        if (!file.is_open())
            throw std::runtime_error("无法打开文件");
        std::string line;
        std::getline(file, line);
        if (!line.empty() && line.back() == '\r')
            line.pop_back();
        if (line != "OFF")
            throw std::runtime_error("非法OFF文件格式");
        int numVertices, numFacets, numEdges;
        std::getline(file, line);
        std::istringstream iss(line);
        iss >> numVertices >> numFacets >> numEdges;
        for (int i = 0; i < numVertices; i++)
        {
            std::getline(file, line);
            std::istringstream vss(line);
            T x, y, z;
            vss >> x >> y >> z;
            vertices.push_back(new Point<T>(x, y, z));
        }
        for (int i = 0; i < numFacets; i++)
        {
            std::getline(file, line);
            std::istringstream fss(line);
            int numVerticesInFace;
            fss >> numVerticesInFace;

            Facet<T> *facet = new Facet<T>();
            for (int j = 0; j < numVerticesInFace; j++)
            {
                int vertexIndex;
                fss >> vertexIndex;
                if (vertexIndex >= 0 && vertexIndex < static_cast<int>(vertices.size()))
                    facet->vertices.push_back(vertices[vertexIndex]);
                else
                    throw std::runtime_error("顶点索引越界");
            }
            facets.push_back(facet);
        }
    }
    ~Polyhedron()
    {
        for (auto facet : facets)
            delete facet;
        facets.clear();
        for (auto vertex : vertices)
            delete vertex;
        vertices.clear();
    }
    Point<T> get_low() const
    {
        if (vertices.empty())
            return Point<T>();
        T minX = vertices[0]->getX();
        T minY = vertices[0]->getY();
        T minZ = vertices[0]->getZ();
        for (auto vertex : vertices)
        {
            minX = std::min(minX, vertex->getX());
            minY = std::min(minY, vertex->getY());
            minZ = std::min(minZ, vertex->getZ());
        }
        return Point<T>(minX, minY, minZ);
    }
    Point<T> get_high() const
    {
        if (vertices.empty())
            return Point<T>();
        T maxX = vertices[0]->getX();
        T maxY = vertices[0]->getY();
        T maxZ = vertices[0]->getZ();
        for (auto vertex : vertices)
        {
            maxX = std::max(maxX, vertex->getX());
            maxY = std::max(maxY, vertex->getY());
            maxZ = std::max(maxZ, vertex->getZ());
        }
        return Point<T>(maxX, maxY, maxZ);
    }
    T area() const
    {
        T totalArea = 0;
        for (auto facet : facets)
            totalArea += facet->area();
        return totalArea;
    }
    size_t getVertexCount() const
    {
        return vertices.size();
    }

    // 获取面片数量
    size_t getFacetCount() const
    {
        return facets.size();
    }
};

#endif // POLYHEDRON_H
