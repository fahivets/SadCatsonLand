#ifndef ANIMATION_H_INLCUDE
#define ANIMATION_H_INLCUDE

struct FrameData
{
	int id;
	SDL_Rect rect;
	float displayTimeSeconds;
};

class Animation
{
public:
	// Constructor/Destructor
	Animation() = default;
	~Animation() = default;

	// Functions
	void addFrame(const int& textureID, const SDL_Rect& rect, const float& frameTime);
	const FrameData& getCurrentFrame() const;
	bool updateFrame(const float& deltaTime);
	void reset();
	void incrementFrame();

private:
	// Members
	std::vector<FrameData> m_frames{ 0 };
	int m_currentFrameIndex{ 0 };
	float m_currentFrameTime{ 0.0f };
};

#endif	/*	end ANIMATION_H_INLCUDE		*/