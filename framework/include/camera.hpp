#ifndef BUW_CAMERA_HPP
#define BUW_CAMERA_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>

class Camera
{

    static const glm::vec3 V_UP;

public:

    void update_projection (float fov_y, float aspect, float near_plane, float far_plane)
    {
        _proj_transform = glm::perspective(fov_y, aspect, 0.1f, 1000.0f);
    }

    void translate (glm::vec3 const& translation)
    {
        _view_transform = glm::translate(_view_transform, translation);
    }

    void look_at (glm::vec3 const& target)
    {
        _view_transform = glm::lookAt(glm::vec3(_view_transform[3]), target, V_UP);
    }

    glm::mat4 view_transform () const
    {
        return _view_transform;
    }

    void view_transform (glm::mat4 const& transform)
    {
        _view_transform = transform;
    }

    glm::mat4 proj_transform () const
    {
        return _proj_transform;
    }

    void proj_transform (glm::mat4 const& transform)
    {
        _proj_transform = transform;
    }

private:
    glm::mat4 _view_transform;
    glm::mat4 _proj_transform;
};

const glm::vec3
Camera::V_UP = glm::vec3(0.0f, 1.0f, 0.0f);

#endif // BUW_CAMERA_HPP
