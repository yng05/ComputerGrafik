#ifndef BUW_PLANET_HPP
#define BUW_PLANET_HPP

#include "orb.hpp"

class Planet : public Orb
{
public:
    Planet (std::string const& name, std::shared_ptr<Orb> parent, float diam, float orbit);
    /* virtual */ glm::mat4 transformation () const override;
    /* virtual */ glm::vec3 position       () const override;
    /* virtual */ void move (float speed);
private:
    std::shared_ptr<Orb> _parent;
    float _diam, _orbit, _angle;
};

#endif // BUW_PLANET_HPP
