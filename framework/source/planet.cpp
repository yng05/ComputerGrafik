#include "planet.hpp"

Planet::Planet (std::string const& name, std::shared_ptr<Orb> parent, float diam, float orbit)
 : Orb     (name)
 , _parent (parent)
 , _diam   (diam)
 , _orbit  (orbit)
 , _angle  (0.0f)
{}

glm::mat4
Planet::transformation () const
{
    glm::mat4 t;
    t = glm::translate(t, -position());
    t = glm::scale(t, glm::vec3(_diam));
    return t;
}

glm::vec3
Planet::position () const
{
    glm::vec3 origin = _parent->position();
    float px = _orbit * glm::cos(_angle);
    float pz = _orbit * glm::sin(_angle);
    return glm::vec3(px, 0, pz) + origin;
}

void
Planet::move (float speed)
{
    _angle += speed / _diam;
}
