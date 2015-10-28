#ifndef BUW_SUN_HPP
#define BUW_SUN_HPP

#include "orb.hpp"

class Sun : public Orb
{
public:
    Sun (std::string const& name, float diam);
    /* virtual */ glm::mat4 transformation () const override;
    /* virtual */ glm::vec3 position       () const override;
    /* virtual */ void move (float speed) override;
private:
    float _diam;
};

#endif // BUW_SUN_HPP
