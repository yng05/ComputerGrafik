#ifndef BUW_STARFIELD_HPP
#define BUW_STARFIELD_HPP

#include <math.h>

class Starfield
{

    glm::vec3
    _sample_from_unit_sphere ()  const
    {
        float x = random();
        float y = random();
        float z = random();
        return 2 * (glm::normalize(glm::vec3(x, y, z)) - 0.5);
    }

    void
    _generate_geometry (unsigned int num_stars)
    {
        for (int i=0; i<num_stars; ++i)
        {
            glm::vec3 v = sample_from_unit_sphere();
            _pos_data.push_back(v.x);
            _pos_data.push_back(v.y);
            _pos_data.push_back(v.z);
        }

        glGenVertexArrays(1, &_vbuff);
        glBindVertexArray(_vbuff);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * _pos_data.size(), _pos_data.data(), GL_STATIC_DRAW);
    }

public:

    Starfield (unsigned int num_stars) {
        _generate_geometry (num_stars);
    }

    void draw () const
    {
        GLenum index_type = GL_UNSIGNED_INT;
        glBindVertexArray(_vbuff);
        glDrawElements(GL_POINTS, GLsizei(_pos_data.size()), index_type, NULL);
    }

private:
    std::vector<GLfloat> _pos_data;
    std::vector<GLuint> _indices;


    GLuint _vbuff;
};

#endif // BUW_STARFIELD_HPP
