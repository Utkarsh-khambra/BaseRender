/*
  Date - 18/02/2019
  Reads and stores objs, normal and faces in vectore
  Date - 27/02/2019
  Found a bug that stops the index reading before last digit because no delims
  are present Obj uses different index for diff props so have to recreate
  correct indices by making correct vbos
*/
#include "../include/LoadObj.hpp"
#include "../include/Mesh.hpp"
#include "../include/Object.hpp"
#include <GL/glew.h>
#include <cstring>
#include <fstream>
#include <glm/glm.hpp>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

bool isNear(float v1, float v2) { return fabs(v2 - v1) < 0.01; }

struct PackedVertex {
  glm::vec3 pos;
  glm::vec3 nor;
  bool operator<(const PackedVertex that) const {
    return memcmp((void *)this, (void *)&that, sizeof(PackedVertex)) > 0;
  }
};

bool getSameVerts(PackedVertex &packed,
                  std::map<PackedVertex, unsigned int> &objOutIndex,
                  unsigned int &result) {
  std::map<PackedVertex, unsigned int>::iterator it = objOutIndex.find(packed);
  if (it == objOutIndex.end())
    return false;
  else {
    result = it->second;
    return true;
  }
}

void getIndex(std::vector<glm::vec3> &inVerts, std::vector<glm::vec3> &inNor,
              Object &obj) {
  std::map<PackedVertex, uint> VertInd;
  for (int i = 0; i < inVerts.size(); ++i) {
    PackedVertex pac = {inVerts[i], inNor[i]};
    unsigned int index;
    bool found = getSameVerts(pac, VertInd, index);

    if (found) {
      obj.fill(index);
    } else {
      obj.fill(inVerts[i]);
      // obj.fill(inNor[i]);
      unsigned int newInd = (unsigned int)obj.size() - 1;
      obj.fill(newInd);
      VertInd[pac] = newInd;
    }
  }
}
void LoadObj(std::string filepath, Object &obj) {
  std::ifstream stream(filepath);
  std::vector<uint> tempIndexVerts;
  std::vector<uint> tempIndexNormals;
  std::vector<glm::vec3> tempUniqueVerts;
  std::vector<glm::vec3> tempUniqueNormals;
  std::string line;
  if (!stream.is_open())
    std::cout << "invalid path to file" << '\n';

  while (getline(stream, line)) {
    if (line.substr(0, 2) == "v ") {
      std::istringstream ss(line);
      float temp[3];
      std::string c;
      ss >> c >> temp[0] >> temp[1] >> temp[2];
      tempUniqueVerts.push_back(glm::vec3(temp[0], temp[1], temp[2]));
    }

    if (line.substr(0, 2) == "vn") {
      std::istringstream ss(line);
      float temp[3];
      std::string c;
      ss >> c >> temp[0] >> temp[1] >> temp[2];
      tempUniqueNormals.push_back(glm::vec3(temp[0], temp[1], temp[2]));
    }

    if (line.front() == 'f') {
      std::vector<std::string> temp;
      std::size_t prev = 0, pos;
      while ((pos = line.find_first_of("// ", prev)) != std::string::npos) {
        if (pos > prev)
          temp.push_back(line.substr(prev, pos - prev));
        prev = pos + 1;
      }
      temp.push_back(line.substr(prev, line.size()));

      tempIndexVerts.push_back(stoi(temp[1]) - 1);
      tempIndexVerts.push_back(stoi(temp[3]) - 1);
      tempIndexVerts.push_back(stoi(temp[5]) - 1);
      tempIndexNormals.push_back(stoi(temp[2]) - 1);
      tempIndexNormals.push_back(stoi(temp[4]) - 1);
      tempIndexNormals.push_back(stoi(temp[6]) - 1);
    }
  }
  std::vector<glm::vec3> tempAllVerts;
  for (auto i : tempIndexVerts) {
    tempAllVerts.push_back(tempUniqueVerts[i]);
  }
  std::vector<glm::vec3> tempAllNormals;
  for (auto i : tempIndexNormals) {
    tempAllNormals.push_back(tempUniqueNormals[i]);
  }

  getIndex(tempAllVerts, tempAllNormals, obj);
}
