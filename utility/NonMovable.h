#ifndef NONMOVABLE_H_INCLUDE
#define NONMOVABLE_H_INCLUDE

class NonMovable
{
public:
	NonMovable(NonMovable&&) = delete;
	NonMovable& operator=(NonMovable&&) = delete;
protected:
	NonMovable() = default;
	~NonMovable() = default;
};

#endif
