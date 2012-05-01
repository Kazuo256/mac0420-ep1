
#include "getglut.h"
#include "utils.h"

namespace ep1 {

namespace utils { 

std::vector<ep1::Vec3D> 
  LoadForceFieldInfo (const std::string& file_name) {
  
  FILE *pfile;
  std::vector<ep1::Vec3D> infos;
  double X, Y, Z, distX, distY, distZ;
  int nX, nY, nZ, count;
  char buffer[BUFFER_SIZE];
  
  pfile = fopen(file_name.c_str(), "r");
  if (pfile == NULL) {
    printf("Arquivo não encontrado. Finalizando programa.\n");
    exit(EXIT_FAILURE);
  }

  infos = std::vector<ep1::Vec3D>();
  
  if(!fgets(buffer, BUFFER_SIZE, pfile)) {
    puts("Input problem.");
    exit(EXIT_FAILURE);
  }
  sscanf(buffer, "%d %d %d", &nX, &nY, &nZ);
  infos.push_back(Vec3D(nX, nY, nZ));

  if(!fgets(buffer, BUFFER_SIZE, pfile)) {
    puts("Input problem.");
    exit(EXIT_FAILURE);
  }
  sscanf(buffer, "%lf %lf %lf", &distX, &distY, &distZ);
  infos.push_back(Vec3D(distX, distY, distZ));

  for (count = 0; count < nX*nY*nZ; count++) {
    if(!fgets(buffer, BUFFER_SIZE, pfile)) {
      puts("Input problem.");
      exit(EXIT_FAILURE);
    }
    sscanf(buffer, "%lf %lf %lf", &X, &Y, &Z);
    infos.push_back(Vec3D(X, Y, Z));     
  }
  
  return infos;
  }

}

}
