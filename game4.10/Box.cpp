#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CEraser.h"
#include "Box.h"
#include <windows.h>

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// Box: Eraser class
	/////////////////////////////////////////////////////////////////////////////

	Box::Box()
	{
		Initialize();
	}

	int Box::GetX1()
	{
		return x;
	}

	int Box::GetY1()
	{
		return y;
	}

	int Box::GetX2()
	{
		return x + animation.Width();
	}

	int Box::GetY2()
	{
		return y + animation.Height();
	}

	void Box::Initialize()
	{
		const int X_POS = 150;
		const int Y_POS = 150;
		x = X_POS;
		y = Y_POS;
		xy[0][0] = x;
		xy[0][1] = y;
		xy[1][0] = x;
		xy[1][1] = y;
		isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;
	}
	void Box::UpdateXYArray() {
		xy[0][0] = xy[1][0];
		xy[0][1] = xy[1][1];
		xy[1][0] = GetX1();
		xy[1][1] = GetY1();
	}
	void Box::LoadBitmap()
	{
		animation.AddBitmap(BOXKID_WALL, RGB(255, 255, 255));
		//animation.AddBitmap(IDB_ERASER2, RGB(255, 255, 255));
		//animation.AddBitmap(IDB_ERASER3, RGB(255, 255, 255));
		//animation.AddBitmap(IDB_ERASER2, RGB(255, 255, 255));

	}

	bool Box::HitEraser(CEraser* eraser)
	{
		// �˴����l�Һc�����x�άO�_�I��y
		return HitRectangle(eraser->GetX1(), eraser->GetY1(),
			eraser->GetX2(), eraser->GetY2());
	}

	bool Box::HitRectangle(int tx1, int ty1, int tx2, int ty2)
	{
		int x1 = GetX1();				// box�����W��x�y��
		int y1 = GetY1();				// box�����W��y�y��
		int x2 = GetX2();	// �y���k�U��x�y��
		int y2 = GetY2();	// �y���k�U��y�y��
									//
									// �˴��y���x�λP�ѼƯx�άO�_���涰
									//
		return (tx2 >= x1 && tx1 <= x2 && ty2 >= y1 && ty1 <= y2);
	}

	void Box::Collision(bool HitEraser) {
		/*if (isMovingLeft) {
			isMovingLeft = false;
		}

		if (isMovingRight) {
			isMovingRight = false;
		}


		if (isMovingUp) {
			isMovingUp = false;
		}

		if (isMovingDown) {
			isMovingDown = false;
		}*/


		/*if (hitDirection == "up") {
			isMovingDown = false;
		}
		if (hitDirection == "down") {
			isMovingUp = false;
		}
		if (hitDirection == "left") {
			isMovingRight = false;
		}
		if (hitDirection == "right") {
			isMovingLeft = false;
		}*/

		if (HitEraser) {
			int old_x = xy[0][0];
			int old_y = xy[0][1];
			if (x > old_x) { //���k����
				isMovingRight = false;
			}
			else if (x < old_x) {
				isMovingLeft = false;
			}
			else if (y > old_y) { // ���U����
				isMovingDown = false;
			}
			else if (y < old_y) {
				isMovingUp = false;
			}
			x = old_x;
			y = old_y;
			UpdateXYArray();
		}


	}
	void Box::OnMove()
	{
		const int STEP_SIZE = 5;
		animation.OnMove();
		if (isMovingLeft) {
			x -= STEP_SIZE;
			UpdateXYArray();
			/*for (int i = 0; i < STEP_SIZE; i++) {
				Sleep(10);
				x -= 1;

			}*/

			//SetMovingLeft(false);
		}

		if (isMovingRight) {
			x += STEP_SIZE;
			UpdateXYArray();
			//isMovingRight = false;
		}


		if (isMovingUp) {
			y -= STEP_SIZE;
			UpdateXYArray();
			//isMovingUp = false;
		}

		if (isMovingDown) {
			y += STEP_SIZE;
			UpdateXYArray();
			//isMovingDown = false;
		}

	}

	void Box::SetMovingDown(bool flag)
	{
		isMovingDown = flag;
		if (flag == true) {
			//����P�ɤW�U���k
			SetMovingUp(false);
			SetMovingLeft(false);
			SetMovingRight(false);
			animation.AddBitmap(BOXKID_DOWN2, RGB(255, 255, 255));
			animation.AddBitmap(BOXKID_DOWN1, RGB(255, 255, 255));
			animation.RemoveFirstBitmap();

		}
		else {
			if (animation.GetNumOfBitmap() > 1) // ��u�Ѥ@�i�Ϥ��ɤ��n�R��
				animation.RemoveFirstBitmap();

		}

	}

	void Box::SetMovingLeft(bool flag)
	{
		isMovingLeft = flag;
		if (flag == true) {
			SetMovingUp(false);
			SetMovingDown(false);
			SetMovingRight(false);
			animation.AddBitmap(BOXKID_LEFT2, RGB(255, 255, 255));
			animation.AddBitmap(BOXKID_LEFT1, RGB(255, 255, 255));
			animation.RemoveFirstBitmap();

		}
		else {
			if (animation.GetNumOfBitmap() > 1) // ��u�Ѥ@�i�Ϥ��ɤ��n�R��
				animation.RemoveFirstBitmap();

		}


	}

	void Box::SetMovingRight(bool flag)
	{
		isMovingRight = flag;
		if (flag == true) {
			SetMovingUp(false);
			SetMovingDown(false);
			SetMovingLeft(false);
			animation.AddBitmap(BOXKID_RIGHT2, RGB(255, 255, 255));
			animation.AddBitmap(BOXKID_RIGHT1, RGB(255, 255, 255));
			animation.RemoveFirstBitmap();

		}
		else {
			if (animation.GetNumOfBitmap() > 1) // ��u�Ѥ@�i�Ϥ��ɤ��n�R��
				animation.RemoveFirstBitmap();

		}
	}

	void Box::SetMovingUp(bool flag)
	{
		isMovingUp = flag;
		if (flag == true) {
			SetMovingDown(false);
			SetMovingLeft(false);
			SetMovingRight(false);
			animation.AddBitmap(BOXKID_UP2, RGB(255, 255, 255));
			animation.AddBitmap(BOXKID_UP1, RGB(255, 255, 255));
			animation.RemoveFirstBitmap();

		}
		else {
			if (animation.GetNumOfBitmap() > 1) // ��u�Ѥ@�i�Ϥ��ɤ��n�R��
				animation.RemoveFirstBitmap();

		}
	}

	void Box::SetXY(int nx, int ny)
	{
		x = nx; y = ny;
	}

	void Box::OnShow()
	{
		animation.SetTopLeft(x, y);
		animation.OnShow();
	}
}