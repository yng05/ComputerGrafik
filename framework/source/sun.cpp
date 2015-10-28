#include "sun.hpp"

Sun::Sun (std::string const& name, float diam)
 : Orb (name)
 , _diam (diam)
{}

glm::mat4
Sun::transformation () const
{
    glm::mat4 t;
    t = glm::scale(t, glm::vec3(_diam));
    return t;
}

glm::vec3
Sun::position () const
{
    return glm::vec3();
}

void
Sun::move (float speed)
{}
