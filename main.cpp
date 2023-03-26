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

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//�E�B���h�E���[�h�ݒ�
	ChangeWindowMode(Game::kWindowMode);
	//�E�B���h�E���ݒ�
	SetMainWindowText(Game::kTitelText);
	//��ʃT�C�Y�ݒ�
	SetGraphMode(Game::kScreenWidth, Game::kScreenHeight, Game::kColorDepth);

	SetWindowSizeChangeEnableFlag(true);

	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}

	int box_X[Box::kNumY][Box::kNumX];//
	int color[Box::kNumY][Box::kNumX];//
	bool hit[Box::kNumY][Box::kNumX];//
	int mouseX = 0, mouseY = 0;//�}�E�X���W�p

	int L = 0,T = 0;//����
	int R = 0, B = 0;//�E��

	int mouseLeft = 0, mouseTop = 0;//����
	int mouseRight = 0, mouseBottom = 0;//�E��

	//�J���[�p���b�g�\��
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

	//�_�u���o�b�t�@���[�h
	SetDrawScreen(DX_SCREEN_BACK);

	while (ProcessMessage() == 0)
	{
		LONGLONG time = GetNowHiPerformanceCount();

		//��ʂ��N���A����
		ClearDrawScreen();
		//�}�E�X�̍��W�𓾂�
		GetMousePoint(&mouseX, &mouseY);
		//�l�p�}�E�X���W
		mouseLeft = mouseX;//����
		mouseTop = mouseY;
		mouseRight = mouseLeft + 0;//�E��
		mouseBottom = mouseTop + 0;

		//�X�V����//////////////////////////////////////////////
		if (!menu)//���j���[�\�����͒�~
		{
			//���G�`��//
			for (int i = 0; i < Box::kNumY; i++)
			{
				for (int j = 0; j < Box::kNumX; j++)
				{
					//���G�`��///////////////////////////
					box_X[i][j]++;

					L = i * 7;//����
					T = j * 3;
					R = L + 7;//�E��
					B = T + 3;

					hit[i][j] = false;

					if ((R > mouseLeft) &&(L < mouseRight))
					{
						if ((B > mouseTop) &&(T < mouseBottom))
						{
							//�F��t����
							if ((GetMouseInput() & MOUSE_INPUT_LEFT))
							{
								hit[i][j] = true;
								color[i][j] = 0xff00ff;
							}
						}
					}
					//������
					if ((GetMouseInput() & MOUSE_INPUT_RIGHT))
					{
						color[i][j] = 0xffffff;
					}
				}
			}
		}

		for (int i = 0; i < ColorMenu::kOpen; i++)
		{		
			//���j���[�{�^��
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



		//�`��///////////////////////////////////////////////
	
		for (int i = 0; i < Box::kNumY; i++)
		{
			for (int j = 0; j < Box::kNumX; j++)
			{
				//���G�`��///////////////////////////
				box_X[i][j]++;

				L = i * 7;//����
				T = j * 3;
				R = L + 7;//�E��
				B = T + 3;
				//�z��
				DrawBox(L ,T, R, B, color[i][j], true);

				
			}
		}

		//���j���[�{�^��
		DrawBox(colorMenuLeft[0], colorMenuTop[0], colorMenuRight[0], colorMenuBottom[0], 0x00ff00, true);

		if (menu)
		{
			DrawBox(100, 100, Game::kScreenWidth - 100, Game::kScreenHeight - 100, 0x000000, true);
			DrawBox(100, 100, Game::kScreenWidth - 100, Game::kScreenHeight - 100, 0xff0000, false);

			DrawBox(colorMenuLeft[1], colorMenuTop[1], colorMenuRight[1], colorMenuBottom[1], 0x00ff00, true);
		}

		//�}�E�X���W
		DrawFormatString(0, 800, 0xffffff, "X = %d : Y = %d", mouseX,mouseY);

		//����ʂ�\��ʂ����ւ���
		ScreenFlip();

		//esc�������ďI��
		if (CheckHitKey(KEY_INPUT_ESCAPE)) break;

		//60fps�Œ�
		while (GetNowHiPerformanceCount() - time < 16667)
		{

		}
	}

	DxLib_End();			// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}