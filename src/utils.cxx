#include "utils.h"

namespace ep1 {
    
std::vector<ep1::Vec3D> Utils::LoadForceFieldInfo(std::string file_name) {
  FILE *pfile;
  std::vector<ep1::Vec3D> infos;
  double x, y, z;
  int nX, nY, nZ;

  pfile = fopen( file_name.c_str(), "r");
  infos = std::vector<ep1::Vec3D>();
  

}


}
