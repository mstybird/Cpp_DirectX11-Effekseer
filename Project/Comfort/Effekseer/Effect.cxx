#include "Effect.hxx"

bool Comfort::Effect::CreateRenderer(ID3D11Device *& aDevice, ID3D11DeviceContext *& aDeviceContext, const int aDrawMax)
{
	return false;
}

bool Comfort::Effect::CreateManager(const int aInstanceMax)
{
	return false;
}

void Comfort::Effect::SetRenderFunction()
{
}

void Comfort::Effect::SetTextureLoader()
{
}

bool Comfort::Effect::CreateSound(IXAudio2 *& aAudio, const int32_t a1ChSoundCount, const int32_t a2ChSoundCount)
{
	return false;
}

void Comfort::Effect::SetSoundPlayer()
{
}

void Comfort::Effect::SetSoundLoader()
{
}

void Comfort::Effect::SetEyePosition(const::Effekseer::Vector3D & aEye)
{
}

void Comfort::Effect::SetLookPosition(const::Effekseer::Vector3D & aLook)
{
}

void Comfort::Effect::SetUpVector(const::Effekseer::Vector3D & aUp)
{
}

bool Comfort::Effect::Load(const char * aFileName)
{
	return false;
}

void Comfort::Effect::Play()
{
}

void Comfort::Effect::Stop()
{
}

void Comfort::Effect::Release()
{
}

void Comfort::Effect::Update()
{
}

void Comfort::Effect::Render()
{
}
