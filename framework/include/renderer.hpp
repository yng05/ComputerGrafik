#ifndef BUW_RENDERER_HPP
#define BUW_RENDERER_HPP

#include <glm/glm.hpp>
#include <map>

#include "scene_node.hpp"

class Renderer
{

    typedef std::shared_ptr<Program> ProgramPtr;
    typedef std::shared_ptr<SceneNode> NodePtr;

public:

    void clear ()
    {
        _tasks.erase(_tasks.begin(), _tasks.end());
    }

    void register_for_rendering (NodePtr const& node)
    {
        _tasks.insert(std::make_pair(node->program(), node));
    }

    void camera (Camera const& camera)
    {
        _camera = camera;
    }

    void render_all ()
    {
        for (auto task: _tasks) {
            auto p_program = task.first;

            p_program->use();
            p_program->bind_camera(_camera);

            auto range = _tasks.equal_range(p_program);
            for (auto v_it = range.first; v_it != range.second; ++v_it)
            {
                auto p_node =  v_it->second;
                p_node->draw();
            }
        }
    }

private:
    std::multimap<ProgramPtr, NodePtr> _tasks;
    Camera _camera;
};

#endif // BUW_RENDERER_HPP
