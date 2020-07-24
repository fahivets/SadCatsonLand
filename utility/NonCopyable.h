#ifndef NONCOPYABLE_H_INCLUDE
#define NONCOPYABLE_H_INCLUDE

class NonCopyable
{
public:
	NonCopyable(const NonCopyable&) = delete;
	NonCopyable& operator=(const NonCopyable&) = delete;

	NonCopyable(NonCopyable&&) = default;
	NonCopyable& operator=(NonCopyable&&) = default;
protected:
	NonCopyable() = default;
	~NonCopyable() = default;
};

#endif
