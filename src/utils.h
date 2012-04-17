
#ifndef EP1_UTILS_H_
#define EP1_UTILS_H_

#include <cstdlib>
#include <cstdio>
#include <vector>
#include <string>

#include "vec3D.h"

#define BUFFER_SIZE 256


namespace ep1 {

namespace utils {

std::vector<ep1::Vec3D> LoadForceFieldInfo (const std::string& file_name);

}

}
#endif
