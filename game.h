#pragma once

namespace Game
{
	//�E�B���h�E���[�h
	constexpr bool kWindowMode = true;
	//�E�B���h�E��
	const char* const kTitelText = "�Q�[����";
	//�E�B���h�E�T�C�Y
#if false	
	constexpr int kScreenWidth = 100;
	constexpr int kScreenHeight = 100;
#else
	constexpr int kScreenWidth = 1280;
	constexpr int kScreenHeight = 720;
#endif
	//�J���[���[�h
	constexpr int kColorDepth = 32; //�R�Qor�P�U
};