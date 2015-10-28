#ifndef BUW_PROGRAM_HPP
#define BUW_PROGRAM_HPP


#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>


#include "shader_loader.hpp"
#include "camera.hpp"


void
print_mat (glm::mat4 const& m)
{
    for (int i=0; i<4; ++i) {
        for (int j=0; j<4; ++j) {
            std::cout << m[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

class Program
{
    typedef GLuint ShaderAddress;
    typedef GLint  UniformAdress;

    static const GLchar * FIELD_NAME_MODEL_TRANSFORM;
    static const GLchar * FIELD_NAME_NORMAL_TRANSFORM;
    static const GLchar * FIELD_NAME_VIEW_TRANSFORM;
    static const GLchar * FIELD_NAME_PROJ_TRANSFORM;

    /* gets the locations of the uniform transformations */
    void _get_transformation_locations ()
    {
        _loc_model_transform  = glGetUniformLocation(_loc_shader, FIELD_NAME_MODEL_TRANSFORM);
        _loc_normal_transform = glGetUniformLocation(_loc_shader, FIELD_NAME_NORMAL_TRANSFORM);
        _loc_view_transform   = glGetUniformLocation(_loc_shader, FIELD_NAME_VIEW_TRANSFORM);
        _loc_proj_transform   = glGetUniformLocation(_loc_shader, FIELD_NAME_PROJ_TRANSFORM);
    }

public:

    Program ()
     : _loc_shader (0)
     , _loc_model_transform (0)
     , _loc_normal_transform (0)
     , _loc_view_transform (0)
     , _loc_proj_transform (0)
    {}

    void load_from_file (std::string const& path_vert, std::string const& path_frag)
    {
        try {
            ShaderAddress _loc_new_shader = shader_loader::program(path_vert, path_frag);

            if (_loc_shader != 0)
            {
                std::cout << _loc_shader << std::endl;
                glDeleteProgram(_loc_shader);
            }

            _loc_shader = _loc_new_shader;
        }
        catch(std::exception&) {
            std::cout << "could not load shader: <vert> \"" << path_vert << "\" <frag> \"" << path_frag << "\"" << std::endl;
        }
    }

    void use ()
    {
        glUseProgram(_loc_shader);
        _get_transformation_locations();
    }

    void bind_model_transform (glm::mat4 const& transform)
    {
        glUniformMatrix4fv(_loc_model_transform, /* count */ 1, /* no transpose */ GL_FALSE, glm::value_ptr(transform));
    }

    void bind_normal_transform (glm::mat4 const transform)
    {
        glUniformMatrix4fv(_loc_normal_transform, /* count */ 1, /* no transpose */ GL_FALSE, glm::value_ptr(transform));
    }

    void bind_view_transform (glm::mat4 const transform)
    {
        glUniformMatrix4fv(_loc_view_transform, /* count */ 1, /* no transpose */ GL_FALSE, glm::value_ptr(transform));
    }

    void bind_proj_transform (glm::mat4 const transform)
    {
        glUniformMatrix4fv(_loc_proj_transform, /* count */ 1, /* no transpose */ GL_FALSE, glm::value_ptr(transform));
    }

    void bind_camera (Camera const& camera)
    {
        bind_proj_transform(camera.proj_transform());
        bind_view_transform(camera.view_transform());
    }

    ~Program ()
    {
        glDeleteProgram(_loc_shader);
    }

private:
    ShaderAddress _loc_shader;

    UniformAdress _loc_model_transform;
    UniformAdress _loc_normal_transform;
    UniformAdress _loc_view_transform;
    UniformAdress _loc_proj_transform;
};

const GLchar *
Program::FIELD_NAME_MODEL_TRANSFORM = "ModelMatrix";

const GLchar *
Program::FIELD_NAME_NORMAL_TRANSFORM = "NormalMatrix";

const GLchar *
Program::FIELD_NAME_VIEW_TRANSFORM = "ViewMatrix";

const GLchar *
Program::FIELD_NAME_PROJ_TRANSFORM = "ProjectionMatrix";

#endif // BUW_PROGRAM_HPP
