#ifndef __COMMON_HPP__
#define __COMMON_HPP__

namespace common {

extern GLuint CompileShader(const std::string& src, GLenum type);

extern GLuint CreateShader(const std::string& vertexShader, const std::string& fragmentShader);

extern std::string ReadFile(const char *path);

extern void PrintInfo(void);

} // end namespace common

#endif // __COMMON_HPP__
