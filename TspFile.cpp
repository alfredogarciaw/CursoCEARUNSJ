#include "pch.h"
#include "TspFile.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>



const int int_MAX = std::numeric_limits<int>::max();
const int int_MIN = std::numeric_limits<int>::min();


TspFile::TspFile() : maxX(int_MIN), maxY(int_MIN), minX(int_MAX), minY(int_MAX) {}

TspFile::TspFile(std::string filePath) : maxX(int_MIN), maxY(int_MIN), minX(int_MAX), minY(int_MAX) {
    std::ifstream fileLineReader(filePath);

    if (!fileLineReader.is_open()) {
        std::cerr << "Cant find File: " << filePath << std::endl;
        return;
    }

    std::string line;
    while (getline(fileLineReader, line) && line.find("NODE_COORD_SECTION") == std::string::npos) {
        if (line.find("EDGE_WEIGHT_TYPE:") != std::string::npos && line.find("EUC_2D") == std::string::npos) {
            throw std::runtime_error("Only EDGE_WEIGHT_TYPE: EUC_2D allowed!");
        }
    }
    int order = 0;
    while (getline(fileLineReader, line) && line.compare("EOF") != 0) {
        std::istringstream st(line);
        std::string token, xStr, yStr;
        st >> token >> xStr >> yStr;
        double xD = std::stod(xStr);
        double yD = std::stod(yStr);

        int x = static_cast<int>(xD);
        int y = static_cast<int>(yD);

        if (x > maxX) maxX = x;
        if (y > maxY) maxY = y;
        if (x < minX) minX = x;
        if (y < minY) minY = y;

        if (xD != x || yD != y) {
            throw std::runtime_error("Only Integer coordinates allowed!");
        }
 
        Point2D point(x, y,order);
        order++;// tiene qu eempezar en cero porque coincide con SkipList qu eusa matriz desde cero
        setCities.push_back(point);
    }

    fileLineReader.close();
}

std::vector<Point2D> TspFile::getSetCities() {
    return setCities;
}

int TspFile::getMaxX() {
    return maxX;
}

int TspFile::getMaxY() {
    return maxY;
}

int TspFile::getMinX() {
    return minX;
}

int TspFile::getMinY() {
    return minY;
}

