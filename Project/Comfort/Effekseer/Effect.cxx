#include "Effect.hxx"
#include<cassert>
bool Comfort::Effect::CreateRenderer(ID3D11Device *& aDevice, ID3D11DeviceContext *& aDeviceContext, const int aDrawMax)
{
	mRenderer = ::EffekseerRendererDX11::Renderer::Create(aDevice, aDeviceContext, aDrawMax);


	return mRenderer != nullptr;
}

bool Comfort::Effect::CreateManager(const int aInstanceMax)
{
	mManager = Effekseer::Manager::Create(aInstanceMax);
	return mManager != nullptr;
}

void Comfort::Effect::SetRenderFunction()
{
	mManager->SetSpriteRenderer(mRenderer->CreateSpriteRenderer());
	mManager->SetRibbonRenderer(mRenderer->CreateRibbonRenderer());
	mManager->SetRingRenderer(mRenderer->CreateRingRenderer());
	mManager->SetTrackRenderer(mRenderer->CreateTrackRenderer());
	mManager->SetModelRenderer(mRenderer->CreateModelRenderer());
}

void Comfort::Effect::SetTextureLoader()
{
	mManager->SetTextureLoader(mRenderer->CreateTextureLoader());
	mManager->SetModelLoader(mRenderer->CreateModelLoader());
}

bool Comfort::Effect::CreateSound(IXAudio2 *& aAudio, const int32_t a1ChSoundCount, const int32_t a2ChSoundCount)
{
	mSound = ::EffekseerSound::Sound::Create(aAudio, a1ChSoundCount, a2ChSoundCount);

	return mSound != nullptr;
}

void Comfort::Effect::SetSoundPlayer()
{
	mManager->SetSoundPlayer(mSound->CreateSoundPlayer());
}

void Comfort::Effect::SetSoundLoader()
{
	mManager->SetSoundLoader(mSound->CreateSoundLoader());
}

void Comfort::Effect::SetEyePosition(const::Effekseer::Vector3D & aEye)
{
	mCamera.mEye = aEye;
}

void Comfort::Effect::SetLookPosition(const::Effekseer::Vector3D & aLook)
{
	mCamera.mLookAt = aLook;
}

void Comfort::Effect::SetUpVector(const::Effekseer::Vector3D & aUp)
{
	mCamera.mUp = aUp;
}

void Comfort::Effect::SetLocation(const::Effekseer::Vector3D & aLocation)
{
	mPosition = aLocation;
}

bool Comfort::Effect::Load(const char * aFileName)
{
	wchar_t lTmpWStr[FILENAME_MAX];
	mbstowcs(lTmpWStr, aFileName, strlen(aFileName) + 1);
	mEffect = ::Effekseer::Effect::Create(mManager, (const EFK_CHAR*)lTmpWStr);

	return mEffect != nullptr;
}

void Comfort::Effect::Play()
{
	mRenderer->SetProjectionMatrix(
		mProjection.GetPerspectiveFovRH()
	);
	mRenderer->SetCameraMatrix(
		mCamera.GetLookAtRH()
	);

	mHandle = mManager->Play(mEffect, mPosition.X, mPosition.Y, mPosition.Z);
	mManager->Flip();
}

void Comfort::Effect::Stop()
{
	mManager->StopEffect(mHandle);
}

void Comfort::Effect::Release()
{
	ES_SAFE_RELEASE(mEffect);
	mManager->Destroy();
	mSound->Destory();
	mRenderer->Destory();

}

void Comfort::Effect::Update()
{
//	mManager->Update();


}

void Comfort::Effect::Render()
{
	mRenderer->BeginRendering();
	mManager->Draw();
	mRenderer->EndRendering();
}

::Effekseer::Matrix44 Comfort::EffectCamera::GetLookAtRH()
{
	return ::Effekseer::Matrix44().LookAtRH(mEye, mLookAt, mUp);
}

::Effekseer::Matrix44 Comfort::EffectProjection::GetPerspectiveFovRH()
{
	return ::Effekseer::Matrix44().PerspectiveFovRH(mAngle, mWidth / mHeight, mNear, mFar);
}

void Comfort::EffectDatabase::Initialize(::Effekseer::Manager *& aManager)
{
	mManagerPtr = aManager;
}

bool Comfort::EffectDatabase::Load(const char * aFileName, const int32_t aRegistID)
{
	//登録済みであればエラーとする
	if (this->IsExist(aRegistID)) {
		assert(0);
	}

	wchar_t lTmpWStr[FILENAME_MAX];
	mbstowcs(lTmpWStr, aFileName, strlen(aFileName) + 1);
	auto mEffect = ::Effekseer::Effect::Create(mManagerPtr, (const EFK_CHAR*)lTmpWStr);

	int lFrameCount = 0;
	auto lHandle = mManagerPtr->Play(mEffect, 0, 0, 0);

	//フレーム数取得
	while (mManagerPtr->GetInstanceCount(lHandle) != 0) {
		mManagerPtr->BeginUpdate();
		mManagerPtr->UpdateHandle(lHandle);
		mManagerPtr->EndUpdate();
		++lFrameCount;
	}

	//読み込めたら登録
	if (mEffect != nullptr) {
		mDatabase[aRegistID].mEffect = mEffect;
		mDatabase[aRegistID].mFrameCount = lFrameCount;
	}

	return mEffect != nullptr;
}

::Effekseer::Effect* Comfort::EffectDatabase::Get(const int32_t aID)const
{
	//存在するか調べる
	//存在しなければnullptrを返す
	if (!this->IsExist(aID)) {
		return nullptr;
	}


	return mDatabase.at(aID).mEffect;
}

bool Comfort::EffectDatabase::IsExist(const int32_t aID)const
{
	return mDatabase.count(aID) != 0;
}

void Comfort::EffectDatabase::CleanAll()
{
}

void Comfort::EffectDatabase::Clean(const int32_t aID)
{
}



void Comfort::EfkManager::Initialize(::EffekseerRenderer::Renderer *& aRenderer, const int aInstanceMax)
{
	mManager= ::Effekseer::Manager::Create(2000);

	mManager->SetSpriteRenderer(aRenderer->CreateSpriteRenderer());
	mManager->SetRibbonRenderer(aRenderer->CreateRibbonRenderer());
	mManager->SetRingRenderer(aRenderer->CreateRingRenderer());
	mManager->SetTrackRenderer(aRenderer->CreateTrackRenderer());
	mManager->SetModelRenderer(aRenderer->CreateModelRenderer());

	mManager->SetTextureLoader(aRenderer->CreateTextureLoader());
	mManager->SetModelLoader(aRenderer->CreateModelLoader());
}

::Effekseer::Manager *& Comfort::EfkManager::GetManager()
{
	return mManager;
}

void Comfort::EfkManager::Play(EfkObject * aEffect, const bool aIsLoop)
{
	auto lPosition = aEffect->GetPosition();
	auto lHandle = mManager->Play(aEffect->GetEffect(), lPosition->X, lPosition->Y, lPosition->Z);
	aEffect->SetHandle(lHandle);
	if (aIsLoop == true) {
		mRegisteredEffectsLoop[lHandle] = aEffect;
	}
	else {
		mRegisteredEffectsNoLoop[lHandle] = aEffect;
	}
}

void Comfort::EfkManager::Stop(EfkObject * aEffect)
{
	mManager->StopEffect(aEffect->GetHandle());
}

void Comfort::EfkManager::Update()
{
	mManager->BeginUpdate();
	//ループするエフェクトは再生終了時に再度再生する

	auto lEfkLoopBegin = mRegisteredEffectsLoop.begin();
	auto lEfkLoopEnd = mRegisteredEffectsLoop.end();

	for (auto lEffect = lEfkLoopBegin; lEffect != lEfkLoopEnd; ++lEffect) {
		mManager->UpdateHandle(lEffect->first);
		if (mManager->GetInstanceCount(lEffect->first) == 0) {
			this->Play(lEffect->second, true);
			mRegisteredEffectsLoop.erase(lEffect++);
		}
	}

	auto lEfkNoLoopBegin = mRegisteredEffectsNoLoop.begin();
	auto lEfkNoLoopEnd = mRegisteredEffectsNoLoop.end();

	for (auto lEffect = lEfkNoLoopBegin; lEffect != lEfkNoLoopEnd; ) {
		mManager->UpdateHandle(lEffect->first);
		if (mManager->GetInstanceCount(lEffect->first) == 0) {
			mRegisteredEffectsNoLoop.erase(lEffect++);
		}
		else {
			++lEffect;
		}
	}

	mManager->EndUpdate();

}

void Comfort::EfkObject::SetEffect(::Effekseer::Effect *& aEffect)
{
	mEffect = aEffect;
}

void Comfort::EfkObject::SetManager(EfkManager * aManager)
{
	mParentManager = aManager;
}

void Comfort::EfkObject::SetPosition(const::Effekseer::Vector3D & aPosition)
{
	mPosition = aPosition;
}

void Comfort::EfkObject::AddPosition(const::Effekseer::Vector3D & aPosition)
{
	mPosition += aPosition;
}



bool Comfort::EfkObject::IsPlaying()
{
	return mParentManager->mManager->GetInstanceCount(mHandle) != 0;
}

::Effekseer::Vector3D * Comfort::EfkObject::GetPosition()
{
	return &mPosition;
}

::Effekseer::Effect * Comfort::EfkObject::GetEffect()
{
	return mEffect;
}

void Comfort::EfkObject::SetHandle(::Effekseer::Handle aHandle)
{
	mHandle = aHandle;
}

::Effekseer::Handle Comfort::EfkObject::GetHandle()
{
	return mHandle;
}

void Comfort::EfkRenderer::Initialize(ID3D11Device *& aDevice, ID3D11DeviceContext *& aDeviceContext, const int aDrawMax)
{
	mRenderer = ::EffekseerRendererDX11::Renderer::Create(aDevice, aDeviceContext, 2000);
}

::EffekseerRenderer::Renderer *& Comfort::EfkRenderer::GetRenderer()
{
	// TODO: return ステートメントをここに挿入します
	return mRenderer;
}

void Comfort::EfkRenderer::RenderAll(EfkManager*aManager)
{
	mRenderer->BeginRendering();
	aManager->GetManager()->Draw();
	mRenderer->EndRendering();
}

void Comfort::EfkRenderer::SetProjection(EffectProjection * aProjection)
{
	mRenderer->SetProjectionMatrix(
		aProjection->GetPerspectiveFovRH()
	);
}

void Comfort::EfkRenderer::SetCamera(EffectCamera * aCamera)
{
	mRenderer->SetCameraMatrix(
		aCamera->GetLookAtRH()
	);
}
