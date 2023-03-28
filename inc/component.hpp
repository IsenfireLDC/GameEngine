#ifndef _COMPONENT_HPP_
#define _COMPONENT_HPP_

namespace Engine {
	extern int GCID;
};
/*
 * Must hold some form of unique component id
 */
template<typename T>
class Component {
public:
	Component() {
		this->id = getComponentID<T>();
	};

	const int id;

private:
	//6365115
	template<typename D>
	static int getComponentID() {
		static int id = ++Engine::GCID;
		return id;
	};
};

#endif
