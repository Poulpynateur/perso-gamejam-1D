#pragma once

struct inputs_t
{
	bool left_key;
	bool right_key;
	bool up_key;
	bool down_key;

	// XXX : may be better to create a new object each time
	void reinit() {
		left_key = false;
		right_key = false;
		up_key = false;
		down_key = false;
	}
};