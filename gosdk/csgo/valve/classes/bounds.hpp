#pragma once

#include "../../../utilities/math/global.hpp"

namespace csgo::valve::classes
{
class rect {
    public:
	float x, y, w, h;

	rect() = default;
	~rect() = default;

	rect(float x, float y, float w, float h) : x(x), y(y), w(w), h(h)
	{
	}
	rect(const utilities::math::vec2_t &tl,
	     const utilities::math::vec2_t &br)
		: x(tl.x), y(tl.y), w(br.x - tl.x), h(tl.y - br.y)
	{
	}

	rect(const rect &) = default;
	rect &operator=(const rect &) = default;

	rect(rect &&) = default;
	rect &operator=(rect &&) = default;

	float right() const
	{
		return x + w;
	}

	float bottom() const
	{
		return y + h;
	}

	bool is_in_bounds(const utilities::math::vec2_t &pt) const
	{
		if (this->x > pt.x)
			return false;
		if (this->y > pt.y)
			return false;
		if (this->right() < pt.x)
			return false;
		if (this->bottom() < pt.y)
			return false;

		return true;
	}
};
} // namespace csgo::valve::classes