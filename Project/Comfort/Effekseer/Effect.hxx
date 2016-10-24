#pragma once
#include <Effekseer.h>
#include <EffekseerRendererDX11.h>
#include <EffekseerSoundXAudio2.h>
#include<string>
#include<unordered_map>
namespace Comfort {



	//Effekseerローダ
	class EffectDatabase {
	public:
		void Initialize(::Effekseer::Manager*&aManager);
		//エフェクトファイルを登録する
		bool Load(const char*aFileName, const int32_t aRegistID);
		//登録済みエフェクト
		::Effekseer::Effect* Get(const int32_t aID)const;
		bool IsExist(const int32_t aID)const;
		void CleanAll();
		void Clean(const int32_t aID);
	private:
		//識別ID,エフェクト
		std::unordered_map<int32_t, ::Effekseer::Effect*>mDatabase;
		::Effekseer::Manager* mManagerPtr;
	};

	struct EffectCamera {
		::Effekseer::Vector3D mEye;
		::Effekseer::Vector3D mLookAt;
		::Effekseer::Vector3D mUp;

//		::Effekseer::Matrix44 GetLookAtLH();
		::Effekseer::Matrix44 GetLookAtRH();

	};

	struct EffectProjection {
		float mAngle;
		float mWidth;
		float mHeight;
		float mNear;
		float mFar;

//		::Effekseer::Matrix44 GetPerspectiveFovLH();
		::Effekseer::Matrix44 GetPerspectiveFovRH();

	};

	class EfkManager;
	class EfkObject {
	public:
		void SetEffect(::Effekseer::Effect*& aEffect);
		void SetManager(EfkManager*aManager);

		void SetPosition(const ::Effekseer::Vector3D& aPosition);
		void AddPosition(const ::Effekseer::Vector3D& aPosition);

		void Play();
		void Stop();
	private:
		::Effekseer::Effect* mEffect;
		::Effekseer::Handle mHandle = -1;
		::Effekseer::Vector3D mPosition;	//エフェクト座標
		//再生登録したマネージャが入る
		::Effekseer::Manager* mParentManager;


	};

	class EfkManager {
	public:
		void Initialize( ::EffekseerRenderer::Renderer*&aRenderer, const int aInstanceMax = 2000);
		::Effekseer::Manager*& GetManager();
		::Effekseer::Manager* mManager;
		void Update();
	};

	class EfkRenderer {
	public:
		void Initialize(ID3D11Device*&aDevice, ID3D11DeviceContext*&aDeviceContext, const int aDrawMax = 2000);

		::EffekseerRenderer::Renderer*& GetRenderer();

		void RenderAll(EfkManager*aManager);
//		void Render(const int32_t aID);

		void SetProjection(EffectProjection* aProjection);
		void SetCamera(EffectCamera* aProjection);
	private:
		::EffekseerRenderer::Renderer* mRenderer;

	};


	//実際に使うエフェクト
	class Effect {

	public:
		//レンダラ作成
		bool CreateRenderer(ID3D11Device*&aDevice, ID3D11DeviceContext*&aDeviceContext, const int aDrawMax = 2000);
		//エフェクトマネージャ作成
		bool CreateManager(const int aInstanceMax = 2000);
		//レンダリング機能設定
		void SetRenderFunction();
		//テクスチャ読み込み機能設定
		void SetTextureLoader();

		//音再生用インスタンス生成
		bool CreateSound(IXAudio2*&aAudio, const int32_t a1ChSoundCount = 16, const int32_t a2ChSoundCount = 16);
		//再生機能を設定
		void SetSoundPlayer();
		void SetSoundLoader();
		
		void SetEyePosition(const ::Effekseer::Vector3D& aEye);
		void SetLookPosition(const ::Effekseer::Vector3D& aLook);
		void SetUpVector(const ::Effekseer::Vector3D& aUp);
		//エフェクトの座標設定
		void SetLocation(const ::Effekseer::Vector3D& aLocation);

		bool Load(const char* aFileName);
		void Play();
		void Stop();
		void Release();

		void Update();
		void Render();
	public:
		::Effekseer::Manager* mManager;
		::EffekseerRenderer::Renderer* mRenderer;
		::EffekseerSound::Sound* mSound;
		::Effekseer::Effect* mEffect;
		::Effekseer::Handle mHandle = -1;
		::Effekseer::Vector3D mPosition;	//エフェクト座標
		EffectCamera mCamera;
		EffectProjection mProjection;
	};

}