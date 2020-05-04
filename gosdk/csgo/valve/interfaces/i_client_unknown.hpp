#pragma once

#include "../../../utilities/math/vector2d.hpp"
#include "../../../utilities/math/vector3d.hpp"
#include "../classes/client_class.hpp"

// very ugly, I know, and I'm so sorry for it, but I'll fix it very soon!
namespace csgo::valve::interfaces
{
class i_client_thinkable;
class i_client_alpha_property;
class i_client_unknown;
class c_player;

class i_client_renderable;

using c_base_handle = unsigned long;

class i_handle_entity {
    public:
	virtual ~i_handle_entity()
	{
	}
	virtual void set_ref_e_handle(const c_base_handle &handle) = 0;
	virtual const c_base_handle &get_ref_handle() const = 0;
};

class i_collideable {
    public:
	virtual i_handle_entity *get_entity_handle() = 0;
	virtual utilities::math::vec3_t &obb_mins() const = 0;
	virtual utilities::math::vec3_t &obb_maxs() const = 0;
};

class i_client_unknown : public i_handle_entity {
    public:
	virtual i_collideable *get_collideable() = 0;
	virtual csgo::valve::classes::i_client_networkable *
	get_client_networkable() = 0;
	virtual i_client_renderable *get_client_renderable() = 0;
	virtual c_player *get_i_client_entity() = 0;
	virtual c_player *get_base_entity() = 0;
	virtual i_client_thinkable *get_client_thinkable() = 0;
	virtual i_client_alpha_property *get_client_alpha_property() = 0;
};
}; // namespace csgo::valve::interfaces
