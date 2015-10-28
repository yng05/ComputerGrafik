#ifndef BUW_ORB_HPP
#define BUW_ORB_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include <memory>

class Orb
{
public:
    Orb (std::string const& name);
    virtual glm::mat4 transformation () const = 0;
    virtual glm::vec3 position () const = 0;
    virtual void      move (float speed) = 0;
    std::string name () const;
private:
    std::string _name;
};

#endif // BUW_ORB_HPP
