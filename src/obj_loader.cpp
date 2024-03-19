#include "obj_loader.h"

#include <fstream>
#include <string>
#include <sstream>
#include <iostream>

using std::ifstream;
using std::string;
using std::istringstream;

void load_obj(const char* filepath, std::vector<vec3> &vertices, std::vector<vec3i> &indices, Interval &ix, Interval &iy, Interval &iz) {
    ifstream file(filepath);

    string line;
    
    while (std::getline(file, line)) {
        if (line.substr(0, 2) == "v ") {
            istringstream l(line.substr(2));
            double x, y, z;
            l >> x; l >> y; l >> z;

            vertices.push_back(vec3(x, y, z));

            if (x < ix.min) ix.min = x;
            if (x > ix.max) ix.max = x;
            if (y < iy.min) iy.min = y;
            if (y > iy.max) iy.max = y;
            if (z < iz.min) iz.min = z;
            if (z > iz.max) iz.max = z;
        } else if (line.substr(0, 2) == "f ") {
            const char* l = line.c_str();
            int a, b, c;
            sscanf(l, "f %i %i %i", &a, &b, &c);

            indices.push_back(vec3i(a - 1, b - 1, c - 1));
        }
    }
}
