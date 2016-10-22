#pragma once
#include <Effekseer.h>
#include <EffekseerRendererDX11.h>
#include <EffekseerSoundXAudio2.h>
namespace Comfort {
	//Effekseer���[�_
	class EffectLoader {

	};

	//Effekseer�}�l�[�W��
	class EffectManager {

	};

	//���ۂɎg���G�t�F�N�g
	class Effect {

	public:
		//�����_���쐬
		bool CreateRenderer(ID3D11Device*&aDevice, ID3D11DeviceContext*&aDeviceContext, const int aDrawMax);
		//�G�t�F�N�g�}�l�[�W���쐬
		bool CreateManager(const int aInstanceMax);
		//�����_�����O�@�\�ݒ�
		void SetRenderFunction();
		//�e�N�X�`���ǂݍ��݋@�\�ݒ�
		void SetTextureLoader();

		//���Đ��p�C���X�^���X����
		bool CreateSound(IXAudio2*&aAudio, const int32_t a1ChSoundCount, const int32_t a2ChSoundCount);
		//�Đ��@�\��ݒ�
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