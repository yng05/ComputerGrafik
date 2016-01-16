#ifndef PARTICLES_HPP
#define PARTICLES_HPP

#include <iostream>

class ParticleGenerator
{
public:
    virtual std::pair<glm::vec3, glm::vec3> generate () = 0;
};

class SphereGenerator : public ParticleGenerator
{
public:

    SphereGenerator ()
     : _dist()
     , _prng()
    {}

    /* virtual */ std::pair<glm::vec3, glm::vec3> generate () override
    {
        glm::vec3 p = glm::normalize(glm::vec3(_dist(_prng), _dist(_prng), _dist(_prng)));
        glm::vec3 v = p * glm::abs(_dist(_prng));
        return std::make_pair(p, v);
    }
private:
    std::normal_distribution<float> _dist;
    std::default_random_engine _prng;
};

class PlaneGenerator : public ParticleGenerator
{
public:

    PlaneGenerator ()
     : _dist()
     , _prng()
    {}

    /* virtual */ std::pair<glm::vec3, glm::vec3> generate () override
    {
        glm::vec3 p = glm::vec3(_dist(_prng), _dist(_prng), 0);
        float d = p.x*p.x + p.y*p.y;
        glm::vec3 v = glm::vec3(0, 0, 1) * glm::abs(((d+2.0f)/(d+1.0f)));
        return std::make_pair(p, v);
    }
private:
    std::normal_distribution<float> _dist;
    std::default_random_engine _prng;
};

class ParticleManager
{

    void __generate_buffer_data (unsigned num)
    {
        std::vector<GLuint> triangles {
            0,1,3,
            0,2,3
        };

        for (size_t i=0; i<num; ++i)
        {
            auto pv = _generator->generate();

            auto cd = glm::length(_color);
            auto cl = (_color + 0.01f * cd * glm::vec3(_dist(_prng), _dist(_prng), _dist(_prng)));

            auto lifetime = _lifetime;// + glm::max(0.0f, 0.3f * _lifetime * _dist(_prng));

            auto transparency = _transparency + glm::max(0.0f, 0.1f * _lifetime * _dist(_prng));
            auto size = _size + glm::max(0.0f, 0.3f * _size * _dist(_prng));

            auto offset = glm::abs(_dist(_prng));

            for (size_t j=0; j<4; ++j) 
            {
                auto corner = (float) j;
                _data[_n_attr*(4*i+j) + 0] = pv.first.x;
                _data[_n_attr*(4*i+j) + 1] = pv.first.y;
                _data[_n_attr*(4*i+j) + 2] = pv.first.z;
                _data[_n_attr*(4*i+j) + 3] = pv.second.x * _speed;
                _data[_n_attr*(4*i+j) + 4] = pv.second.y * _speed;
                _data[_n_attr*(4*i+j) + 5] = pv.second.z * _speed;
                _data[_n_attr*(4*i+j) + 6] = cl.x;
                _data[_n_attr*(4*i+j) + 7] = cl.y;
                _data[_n_attr*(4*i+j) + 8] = cl.z;
                _data[_n_attr*(4*i+j) + 9] = lifetime;
                _data[_n_attr*(4*i+j) + 10] = transparency;
                _data[_n_attr*(4*i+j) + 11] = corner;
                _data[_n_attr*(4*i+j) + 12] = size;
                _data[_n_attr*(4*i+j) + 13] = offset;
            }

            for (size_t j=0; j<triangles.size(); ++j) 
            {
                _indices[6*i + j] = 4* (unsigned) i + triangles[j];
            }
        }
    }

    void __generate_vao ()
    {
        auto num_bytes = _n_attr * sizeof(GLfloat);

        // generate vertex array object
        glGenVertexArrays(1, &_vao);
        // bind the array for attaching buffers
        glBindVertexArray(_vao);


        //// VERTEX DATA

        // generate generic buffer
        glGenBuffers(1, &_vbo);
        // bind this as an vertex array buffer containing all attributes
        glBindBuffer(GL_ARRAY_BUFFER, _vbo);
        // configure currently bound array buffer
        glBufferData(GL_ARRAY_BUFFER, GLsizeiptr(GLsizei(sizeof(float) * _data.size())), _data.data(), GL_STATIC_DRAW);

        // POSITION
        // activate first attribute on gpu
        glEnableVertexAttribArray(0);
        uintptr_t offset0 = 0 * sizeof(GLfloat);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, GLsizei(num_bytes), (const GLvoid*) offset0);

        // VELOCITY
        // activate second attribute on gpu
        glEnableVertexAttribArray(1);
        uintptr_t offset1 = offset0 + 3 * sizeof(GLfloat);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, GLsizei(num_bytes), (const GLvoid*) offset1);

        // COLOR
        // activate third attribute on gpu
        glEnableVertexAttribArray(2);
        uintptr_t offset2 = offset1 + 3 * sizeof(GLfloat);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, GLsizei(num_bytes), (const GLvoid*) offset2);

        // LIFETIME
        // activate second attribute on gpu
        glEnableVertexAttribArray(3);
        uintptr_t offset3 = offset2 + 3 * sizeof(GLfloat);
        glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, GLsizei(num_bytes), (const GLvoid*) offset3);

        // TRANSPARENCY
        // activate second attribute on gpu
        glEnableVertexAttribArray(4);
        uintptr_t offset4 = offset3 + 1 * sizeof(GLfloat);
        glVertexAttribPointer(4, 1, GL_FLOAT, GL_FALSE, GLsizei(num_bytes), (const GLvoid*) offset4);

        // CORNER
        // activate second attribute on gpu
        glEnableVertexAttribArray(5);
        uintptr_t offset5 = offset4 + 1 * sizeof(GLfloat);
        glVertexAttribPointer(5, 1, GL_FLOAT, GL_FALSE, GLsizei(num_bytes), (const GLvoid*) offset5);

        // SIZE
        // activate second attribute on gpu
        glEnableVertexAttribArray(6);
        uintptr_t offset6 = offset5 + 1 * sizeof(GLfloat);
        glVertexAttribPointer(6, 1, GL_FLOAT, GL_FALSE, GLsizei(num_bytes), (const GLvoid*) offset6);

        // OFFSET
        // activate second attribute on gpu
        glEnableVertexAttribArray(7);
        uintptr_t offset7 = offset6 + 1 * sizeof(GLfloat);
        glVertexAttribPointer(7, 1, GL_FLOAT, GL_FALSE, GLsizei(num_bytes), (const GLvoid*) offset7);


        //// INDEX DATA

        // generate generic buffer
        glGenBuffers(1, &_ebo);
        // bind this as an vertex array buffer containing all attributes
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
        // configure currently bound array buffer
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, GLsizeiptr(GLsizei(sizeof(GLuint) * _indices.size())), _indices.data(), GL_STATIC_DRAW);
    }

public:

    ParticleManager (unsigned num, std::shared_ptr<ParticleGenerator> const& pg,
        float lifetime = 1.0f, float transparency = 1.0f, float size = 1.0f, float speed = 1.0f,
        glm::vec3 color = glm::vec3(1,1,1))
     : _lifetime(lifetime)
     , _transparency(transparency)
     , _size(size)
     , _speed(speed)
     , _color(color)
     , _generator(pg)
     , _data(num * _n_attr * 4)
     , _indices(num * 6)
     , _vao(0)
     , _vbo(0)
     , _ebo(0)
     , _dist()
     , _prng()
    {
        __generate_buffer_data(num);
        __generate_vao();
    }

    GLuint vao () const
    {
        return _vao;
    }

    std::vector<GLuint> indices() const
    {
        return _indices;
    }

    std::vector<GLfloat> data() const
    {
        return _data;
    }


private:

    const unsigned _n_attr = 14;

    float _lifetime;
    float _transparency;
    float _size;
    float _speed;

    glm::vec3 _color;

    std::shared_ptr<ParticleGenerator>  _generator;

    std::vector<GLfloat> _data;
    std::vector<GLuint> _indices;

    GLuint _vao, _vbo, _ebo;

    std::normal_distribution<float> _dist;
    std::default_random_engine _prng;

};

#endif // PARTICLES_HPP