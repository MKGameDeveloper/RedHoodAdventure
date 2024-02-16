#include "Framework.h"
#include "Animator.h"

AnimationClip::AnimationClip(wstring clipName, Texture2D* srcTex, UINT frameCount, Vector2 startPos, Vector2 endPos, bool bReversed, float playRate, bool bLoop)
	:clipName(clipName), frameCount(frameCount), bReversed(bReversed), playRate(playRate), bLoop(bLoop)
{
	srv = srcTex->GetSRV(); //이미지 소스를 가져와서 대입

	// 텍스처의 너비와 높이
	float imageWidth = srcTex->GetWidth();		//현재 사용하는 이미지의 가로크기 구하기
	float imageHeight = srcTex->GetHeight();	//현재 사용하는 이미지의 세로크기 구하기

	// 클립사이즈 (애니메이션이 그려져 있는 텍스처의 길이)
	Vector2 clipSize = endPos - startPos;

	// 한 프레임 사이즈
	Vector2 frameSize;
	frameSize.x = clipSize.x / frameCount;
	frameSize.y = clipSize.y;

	// 하나의 텍셀 크기를 구하기
	texelFrameSize.x = frameSize.x / imageWidth;
	texelFrameSize.y = frameSize.y / imageHeight;

	// 하나의 텍셀의 시작 위치
	Vector2 texelStartPos;
	texelStartPos.x = startPos.x / imageWidth;
	texelStartPos.y = startPos.y / imageHeight;

	Vector2 keyframe;

	for (UINT i = 0; i < frameCount; i++)
	{
		keyframe.x = texelStartPos.x + (texelFrameSize.x * i);
		keyframe.y = texelStartPos.y;

		keyFrames.push_back(keyframe);
	}
}

Animator::Animator()
{
}

Animator::~Animator()
{
	for (auto clip : animClips)
		SAFE_DELETE(clip.second);
}

void Animator::Update()
{
	if (deltaTime > currentClip->playRate)
	{

		if (currentClip->bReversed == false)
		{

			if (currentFrameIndex == currentClip->frameCount - 1)
			{
				if (currentClip->bLoop == true)
				{
					currentFrameIndex = 0;
				}
			}
			else
			{
				currentFrameIndex++;
			}

			currentFrame = currentClip->keyFrames[currentFrameIndex];
		}
		else
		{

			if (currentFrameIndex == 0)
			{

				if (currentClip->bLoop == true)
				{
					currentFrameIndex = currentClip->frameCount - 1;
				}
			}
			else
			{
				currentFrameIndex--;
			}

			currentFrame = currentClip->keyFrames[currentFrameIndex];
		}
		StartAnim = true;
		deltaTime = 0.0f;
	}
	else
	{
		deltaTime += Time::Get()->WorldDelta();
	}



}

void Animator::AddAnimClip(AnimationClip* animClip)
{
	animClips.insert(make_pair(animClip->clipName, animClip));
}

void Animator::SetCurrentAnimClip(wstring clipName)
{
	if (currentClip == nullptr && CheckExist(clipName) == true)
		currentClip = animClips.find(clipName)->second;
	else if (currentClip != nullptr && currentClip->clipName == clipName)
		return;

	if (CheckExist(clipName))
	{
		currentClip = animClips.find(clipName)->second;
		deltaTime = .0f;

		// 역재생이 활성화 되어있는 경우
		if (currentClip->bReversed == true)
			currentFrameIndex = currentClip->frameCount - 1;
		else
			currentFrameIndex = 0;

		// 현재 프레임 업데이트
		currentFrame = currentClip->keyFrames[currentFrameIndex];

	}
}

void Animator::SetCurrentFrameIndex(int index)
{
	if (currentClip->bReversed == false)
		currentFrameIndex = index - 1;
	else
		currentFrameIndex = currentClip->frameCount - index;
}

bool Animator::IsEnd()
{
	
	if (currentClip->bReversed == false)
		return currentFrameIndex == currentClip->frameCount - 1;
	else
		return currentFrameIndex == 0;

}

bool Animator::CheckStartFrame(int index)
{
	if (StartAnim)
	{
		StartAnim = false;

		if (currentClip->bReversed == false)
			return currentFrameIndex == index - 1;
		else
			return currentFrameIndex == currentClip->frameCount - index;
	}
	
	return false;
}

bool Animator::CheckFrameIndex(int index)
{
	if (currentClip->bReversed == false)
		return currentFrameIndex == index - 1;
	else
		return currentFrameIndex == currentClip->frameCount - index;
}

bool Animator::CheckFrameIndex(int index, int index2)
{
	if (currentClip->bReversed == false)
		return (currentFrameIndex >= index - 1 && currentFrameIndex <= index2 - 1);
	else
		return (currentFrameIndex <= currentClip->frameCount - index && currentFrameIndex >= currentClip->frameCount - index2);
}

void Animator::InitFrameIndex()
{
	if (currentClip->bReversed == false)
		currentFrameIndex = currentClip->frameCount - 1;
	else
		currentFrameIndex = currentFrameIndex == 0;
}
