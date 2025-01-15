
#include <GL/glew.h>
#include <string>

namespace shaders {
GLuint makeShader(std::string path, GLenum type);

void checkShader(GLuint shader);
} // namespace shaders
