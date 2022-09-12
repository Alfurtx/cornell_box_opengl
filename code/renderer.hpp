#if !defined(RENDERER_HPP)
#define RENDERER_HPP

#include "common.hpp"

struct Shader {
    uint32 program_handle;
    
    void compile_program(char* vertex_filepath, char* fragment_filepath, char* geometry_filepath);
    void use();
    
    void set_uniform(char* name, glm::mat4 value);
    void set_uniform(char* name, glm::mat3 value);
    void set_uniform(char* name, glm::vec4 value);
    void set_uniform(char* name, glm::vec3 value);
    void set_uniform(char* name, glm::vec2 value);
    void set_uniform(char* name, int value);
    void set_uniform(char* name, float value);
    void set_uniform(char* name, uint value);
    void set_uniform(char* name, bool value);
};

#endif