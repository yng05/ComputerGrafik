#ifndef BUW_POINT_CLOUD_HPP
#define BUW_POINT_CLOUD_HPP

#include <vector>

#include "scene_node.hpp"

class PointCloud : public SceneNode
{

    typedef GLuint IndexBuffer;
    typedef GLuint VertexBuffer;
    typedef GLuint VertexArray;

    PointCloud ()
    {}

    glm::vec3
    _sample_from_unit_sphere ()  const
    {
        float x = float(random() % 1000) / 1000.0f;
        float y = float(random() % 1000) / 1000.0f;
        float z = float(random() % 1000) / 1000.0f;

        x = (x-0.5) * 2;
        y = (y-0.5) * 2;
        z = (z-0.5) * 2;

        glm::vec3 p (x, y, z);

        float r = glm::length(p) * 0.01 + 0.99;
        p = r / glm::length(p) * p;
        return p;
    }

    void
    _generate_points (unsigned int num)
    {
        for (int i=0; i<num; ++i)
        {
            auto p = _sample_from_unit_sphere ();
            _positions.push_back (p.x);
            _positions.push_back (p.y);
            _positions.push_back (p.z);
            _indices.push_back (i);
        }
    }

    void
    _generate_buffers ()
    {
        glGenVertexArrays(1, &_vao);
        glBindVertexArray(_vao);

        glGenBuffers(1, &_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, _vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * _positions.size(), _positions.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float), (GLvoid*)(0));
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

public:

    PointCloud (unsigned int num)
    {
        _generate_points(num);
        _generate_buffers();
    }


    ~PointCloud ()
    {
        glDeleteBuffers(1, &_vbo);
        glDeleteVertexArrays(1, &_vao);
    }

protected:

    /* virtual */ void _draw () const override
    {
        glBindVertexArray(_vao);
        glDrawArrays(GL_POINTS, 0, _indices.size());
        glBindVertexArray(0);
    }

private:

    std::vector<GLfloat> _positions;
    std::vector<GLuint> _indices;

    VertexArray _vao;
    VertexBuffer _vbo;
    IndexBuffer _idxbuff;
};

#endif // BUW_POINT_CLOUD_HPP
