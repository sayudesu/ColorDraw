#pragma once

namespace Game
{
	//ウィンドウモード
	constexpr bool kWindowMode = true;
	//ウィンドウ名
	const char* const kTitelText = "ゲーム名";
	//ウィンドウサイズ
#if false	
	constexpr int kScreenWidth = 100;
	constexpr int kScreenHeight = 100;
#else
	constexpr int kScreenWidth = 1280;
	constexpr int kScreenHeight = 720;
#endif
	//カラーモード
	constexpr int kColorDepth = 32; //３２or１６
};