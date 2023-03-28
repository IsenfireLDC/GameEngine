#ifndef _UPDATE_HPP_
#define _UPDATE_HPP_

#include <unordered_set>

class Update {
public:
	Update();
	virtual ~Update();

	virtual void update(float) = 0;

protected:
	bool doUpdate;


public:
	static void updateAll(float);

private:
	static std::unordered_set<Update*> members;
};

#endif
