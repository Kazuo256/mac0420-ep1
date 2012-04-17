
#ifndef EP1_UTILS_H_
#define EP1_UTILS_H_

#include <cstdlib>
#include <cstdio>
#include <vector>

#define BUFFER_SIZE 256


namespace ep1 {

class Utils {
  public:
    std::vector<Vec3D> LoadForceFieldInfo (std::string file_name);
}

}
#endif
