#pragma once

class AnimationClip
{
public:
	friend class Animator;

	AnimationClip(wstring clipName, Texture2D* srcTex, UINT frameCount, Vector2 startPos, Vector2 endPos, bool bReversed = false, float playRate = 1.f / 15.f, bool bLoop = true);

protected:
	wstring clipName = L"";
	vector<Vector2> keyFrames;
	UINT frameCount = 0;
	ID3D11ShaderResourceView* srv = nullptr;
	Vector2 texelFrameSize = Values::ZeroVec2;
	float playRate = 0.f;
	bool bReversed = false;
	bool bLoop = true;




};

class Animator
{
public:
	Animator();
	~Animator();

	void Update();

	Vector2 GetCurrentFrame() { return currentFrame; }
	Vector2 GetTexelFrameSize() { return currentClip->texelFrameSize; }
	ID3D11ShaderResourceView* GetCurrentSRV() { return currentClip->srv; }

	void AddAnimClip(AnimationClip* animClip);
	void SetCurrentAnimClip(wstring clipName);

	void SetCurrentFrameIndex(int index);
	int GetCurrentFrameIndex() { return currentFrameIndex; }

	bool IsEnd();
	bool CheckStartFrame(int index);
	bool CheckFrameIndex(int index);
	bool CheckFrameIndex(int index, int index2);

	void InitFrameIndex();

private:
	bool CheckExist(wstring clipname) { return animClips.find(clipname) != animClips.end(); }

private:
	unordered_map<wstring, AnimationClip*> animClips;

	AnimationClip* currentClip = nullptr;
	UINT currentFrameIndex = 0;
	Vector2 currentFrame = Values::ZeroVec2;

	float deltaTime = 0.0f;
	bool StartAnim = true;
	bool EndAnim = false;

	bool bPlay = true;

};