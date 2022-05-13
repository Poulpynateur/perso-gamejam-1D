Create new game engine with:

* render_entity_t			= sf::Transform
	* draw()
	* sf::Transform

* logic_entity_t
	* logic()
	* sf::Transform

* group_entity_t
	* group of logic

* dynamic_entity_t			-> can be moved around (effects, empty, ...)
	* render_entity_t
	* logic_entity_t

* collision_entity_t		-> can collide
	* dynamic_entity_t

* parent relationship ?

Load all ressource in folder to dictionnary (including json ?)