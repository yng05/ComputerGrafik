#include "orb.hpp"

Orb::Orb (std::string const& name)
 : _name   (name)
{}

std::string
Orb::name () const
{
    return _name;
}
