#include "Framework.h"
#include "Animator.h"

AnimationClip::AnimationClip(wstring clipName, Texture2D* srcTex, UINT frameCount, Vector2 startPos, Vector2 endPos, bool bReversed, float playRate, bool bLoop)
	:clipName(clipName), frameCount(frameCount), bReversed(bReversed), playRate(playRate), bLoop(bLoop)
{
	srv = srcTex->GetSRV(); //�̹��� �ҽ��� �����ͼ� ����

	// �ؽ�ó�� �ʺ�� ����
	float imageWidth = srcTex->GetWidth();		//���� ����ϴ� �̹����� ����ũ�� ���ϱ�
	float imageHeight = srcTex->GetHeight();	//���� ����ϴ� �̹����� ����ũ�� ���ϱ�

	// Ŭ�������� (�ִϸ��̼��� �׷��� �ִ� �ؽ�ó�� ����)
	Vector2 clipSize = endPos - startPos;

	// �� ������ ������
	Vector2 frameSize;
	frameSize.x = clipSize.x / frameCount;
	frameSize.y = clipSize.y;

	// �ϳ��� �ؼ� ũ�⸦ ���ϱ�
	texelFrameSize.x = frameSize.x / imageWidth;
	texelFrameSize.y = frameSize.y / imageHeight;

	// �ϳ��� �ؼ��� ���� ��ġ
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

		// ������� Ȱ��ȭ �Ǿ��ִ� ���
		if (currentClip->bReversed == true)
			currentFrameIndex = currentClip->frameCount - 1;
		else
			currentFrameIndex = 0;

		// ���� ������ ������Ʈ
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
