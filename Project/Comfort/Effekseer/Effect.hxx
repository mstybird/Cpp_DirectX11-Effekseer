#pragma once
#include <Effekseer.h>
#include <EffekseerRendererDX11.h>
#include <EffekseerSoundXAudio2.h>
namespace Comfort {
	//Effekseerローダ
	class EffectLoader {

	};

	//Effekseerマネージャ
	class EffectManager {

	};

	//実際に使うエフェクト
	class Effect {

	public:
		//レンダラ作成
		bool CreateRenderer(ID3D11Device*&aDevice, ID3D11DeviceContext*&aDeviceContext, const int aDrawMax);
		//エフェクトマネージャ作成
		bool CreateManager(const int aInstanceMax);
		//レンダリング機能設定
		void SetRenderFunction();
		//テクスチャ読み込み機能設定
		void SetTextureLoader();

		//音再生用インスタンス生成
		bool CreateSound(IXAudio2*&aAudio, const int32_t a1ChSoundCount, const int32_t a2ChSoundCount);
		//再生機能を設定
		void SetSoundPlayer();
		void SetSoundLoader();
		
		void SetEyePosition(const ::Effekseer::Vector3D& aEye);
		void SetLookPosition(const ::Effekseer::Vector3D& aLook);
		void SetUpVector(const ::Effekseer::Vector3D& aUp);

		bool Load(const char* aFileName);
		void Play();
		void Stop();
		void Release();

		void Update();
		void Render();
	public:
		::Effekseer::Manager* mManager;
		::EffekseerRenderer::Renderer* g_renderer;
		::EffekseerSound::Sound* g_sound;
		::Effekseer::Effect* g_effect;
		::Effekseer::Handle g_handle = -1;
		::Effekseer::Vector3D g_position;

	};

}