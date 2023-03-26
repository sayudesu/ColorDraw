#include "DxLib.h"

#include "game.h"

namespace Box
{
	constexpr int kNumX = 320;
	constexpr int kNumY = 200;
}

namespace ColorMenu
{
	constexpr int kOpen = 2;

	constexpr int kRed = 0xff0000;
	constexpr int kBule = 0x00ff00;
	constexpr int kGreen = 0x0000ff;
}

namespace Size
{
	//constexpr int 
}

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//ウィンドウモード設定
	ChangeWindowMode(Game::kWindowMode);
	//ウィンドウ名設定
	SetMainWindowText(Game::kTitelText);
	//画面サイズ設定
	SetGraphMode(Game::kScreenWidth, Game::kScreenHeight, Game::kColorDepth);

	SetWindowSizeChangeEnableFlag(true);

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	int box_X[Box::kNumY][Box::kNumX];//
	int color[Box::kNumY][Box::kNumX];//
	bool hit[Box::kNumY][Box::kNumX];//
	int mouseX = 0, mouseY = 0;//マウス座標用

	int L = 0,T = 0;//左上
	int R = 0, B = 0;//右下

	int mouseLeft = 0, mouseTop = 0;//左上
	int mouseRight = 0, mouseBottom = 0;//右下

	//カラーパレット表示
	int colorMenuLeft[ColorMenu::kOpen];
	int colorMenuTop[ColorMenu::kOpen];
	int colorMenuRight[ColorMenu::kOpen];
	int colorMenuBottom[ColorMenu::kOpen];

	colorMenuLeft[0] = 5;
	colorMenuTop[0] = 5;
	colorMenuRight[0] = colorMenuLeft[0] + 30;
	colorMenuBottom[0] = colorMenuTop[0] + 30;

	colorMenuLeft[1] = 100;
	colorMenuTop[1] = 100;
	colorMenuRight[1] = colorMenuLeft[1] + 30;
	colorMenuBottom[1] = colorMenuTop[1] + 30;

	bool menu = false;

	for (int i = 0; i < Box::kNumY; i++)
	{
		for (int j = 0; j < Box::kNumX; j++)
		{
			box_X[i][j] = 0;
			color[i][j] = 0xffffff;
			hit[i][j] = false;
		}
	}

	//ダブルバッファモード
	SetDrawScreen(DX_SCREEN_BACK);

	while (ProcessMessage() == 0)
	{
		LONGLONG time = GetNowHiPerformanceCount();

		//画面をクリアする
		ClearDrawScreen();
		//マウスの座標を得る
		GetMousePoint(&mouseX, &mouseY);
		//四角マウス座標
		mouseLeft = mouseX;//左上
		mouseTop = mouseY;
		mouseRight = mouseLeft + 0;//右下
		mouseBottom = mouseTop + 0;

		//更新処理//////////////////////////////////////////////
		if (!menu)//メニュー表示中は停止
		{
			//お絵描き//
			for (int i = 0; i < Box::kNumY; i++)
			{
				for (int j = 0; j < Box::kNumX; j++)
				{
					//お絵描き///////////////////////////
					box_X[i][j]++;

					L = i * 7;//左上
					T = j * 3;
					R = L + 7;//右下
					B = T + 3;

					hit[i][j] = false;

					if ((R > mouseLeft) &&(L < mouseRight))
					{
						if ((B > mouseTop) &&(T < mouseBottom))
						{
							//色を付ける
							if ((GetMouseInput() & MOUSE_INPUT_LEFT))
							{
								hit[i][j] = true;
								color[i][j] = 0xff00ff;
							}
						}
					}
					//初期化
					if ((GetMouseInput() & MOUSE_INPUT_RIGHT))
					{
						color[i][j] = 0xffffff;
					}
				}
			}
		}

		for (int i = 0; i < ColorMenu::kOpen; i++)
		{		
			//メニューボタン
			if ((colorMenuRight[i] > mouseLeft) && (colorMenuLeft[i] < mouseRight))
			{
				if ((colorMenuBottom[i] > mouseTop) && (colorMenuTop[i] < mouseBottom))
				{
					if ((GetMouseInput() & MOUSE_INPUT_LEFT))
					{
						if (i == 1)
						{
							if (!menu)
							{
								menu = true;
							}

						}
						if(i == 2)
						{
							if (menu)
							{
								menu = false;
							}
						}
					}
				}

			}
		}



		//描画///////////////////////////////////////////////
	
		for (int i = 0; i < Box::kNumY; i++)
		{
			for (int j = 0; j < Box::kNumX; j++)
			{
				//お絵描き///////////////////////////
				box_X[i][j]++;

				L = i * 7;//左上
				T = j * 3;
				R = L + 7;//右下
				B = T + 3;
				//配列
				DrawBox(L ,T, R, B, color[i][j], true);

				
			}
		}

		//メニューボタン
		DrawBox(colorMenuLeft[0], colorMenuTop[0], colorMenuRight[0], colorMenuBottom[0], 0x00ff00, true);

		if (menu)
		{
			DrawBox(100, 100, Game::kScreenWidth - 100, Game::kScreenHeight - 100, 0x000000, true);
			DrawBox(100, 100, Game::kScreenWidth - 100, Game::kScreenHeight - 100, 0xff0000, false);

			DrawBox(colorMenuLeft[1], colorMenuTop[1], colorMenuRight[1], colorMenuBottom[1], 0x00ff00, true);
		}

		//マウス座標
		DrawFormatString(0, 800, 0xffffff, "X = %d : Y = %d", mouseX,mouseY);

		//裏画面を表画面を入れ替える
		ScreenFlip();

		//escを押して終了
		if (CheckHitKey(KEY_INPUT_ESCAPE)) break;

		//60fps固定
		while (GetNowHiPerformanceCount() - time < 16667)
		{

		}
	}

	DxLib_End();			// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}