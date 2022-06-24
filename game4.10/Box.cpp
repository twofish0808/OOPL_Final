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
		// 檢測擦子所構成的矩形是否碰到球
		return HitRectangle(eraser->GetX1(), eraser->GetY1(),
			eraser->GetX2(), eraser->GetY2());
	}

	bool Box::HitRectangle(int tx1, int ty1, int tx2, int ty2)
	{
		int x1 = GetX1();				// box的左上角x座標
		int y1 = GetY1();				// box的左上角y座標
		int x2 = GetX2();	// 球的右下角x座標
		int y2 = GetY2();	// 球的右下角y座標
									//
									// 檢測球的矩形與參數矩形是否有交集
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
			if (x > old_x) { //往右撞牆
				isMovingRight = false;
			}
			else if (x < old_x) {
				isMovingLeft = false;
			}
			else if (y > old_y) { // 往下撞牆
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
			//不能同時上下左右
			SetMovingUp(false);
			SetMovingLeft(false);
			SetMovingRight(false);
			animation.AddBitmap(BOXKID_DOWN2, RGB(255, 255, 255));
			animation.AddBitmap(BOXKID_DOWN1, RGB(255, 255, 255));
			animation.RemoveFirstBitmap();

		}
		else {
			if (animation.GetNumOfBitmap() > 1) // 當只剩一張圖片時不要刪除
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
			if (animation.GetNumOfBitmap() > 1) // 當只剩一張圖片時不要刪除
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
			if (animation.GetNumOfBitmap() > 1) // 當只剩一張圖片時不要刪除
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
			if (animation.GetNumOfBitmap() > 1) // 當只剩一張圖片時不要刪除
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