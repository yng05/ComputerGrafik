#ifndef BUW_SCENE_NODE_HPP
#define BUW_SCENE_NODE_HPP

#include <glm/glm.hpp>

class SceneNode
{

    typedef std::shared_ptr<Program> ProgramPtr;

public:

    SceneNode ()
     : _p_program ()
     , _model_transform ()
     , _normal_transform ()
    {}

    void draw () const
    {
        _p_program->bind_model_transform(_model_transform);
        _p_program->bind_normal_transform(_normal_transform);
        _draw();
    }

    glm::mat4 transform () const
    {
        return _model_transform;
    }

    void transform (glm::mat4 const& transform)
    {
        _model_transform = transform;
        _normal_transform = glm::transpose(glm::inverse(transform));
    }

    ProgramPtr program (ProgramPtr const& program)
    {
        _p_program = program;
    }

    ProgramPtr program () const
    {
        return _p_program;
    }

protected:

    virtual void _draw () const = 0;

private:

    ProgramPtr _p_program;

    glm::mat4 _model_transform;
    glm::mat4 _normal_transform;

};

#endif // BUW_SCENE_NODE_HPP
