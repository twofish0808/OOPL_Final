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
	// CEraser: Eraser class
	/////////////////////////////////////////////////////////////////////////////

	CEraser::CEraser()
	{
		Initialize();
	}

	int CEraser::GetX1()
	{
		return x;
	}

	int CEraser::GetY1()
	{
		return y;
	}

	int CEraser::GetX2()
	{
		return x + animation.Width();
	}

	int CEraser::GetY2()
	{
		return y + animation.Height();
	}

	void CEraser::Initialize()
	{
		findIndex(3);//找地圖中BOX KID座標
		const int X_POS = find[0] * 40;; //設定kid初始位置
		const int Y_POS = find[1] * 40;;
		x = X_POS;
		y = Y_POS;
		target_x = x;
		target_y = y;
		xy[0][0] = x;
		xy[0][1] = y;
		xy[1][0] = x;
		xy[1][1] = y;
		position.clear();
		position.push_back({ X_POS , Y_POS });
		//isMatchPoint = true;
		isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;
		isMovingNow = false;
		PushingBoxDirection = "none";
		
	}
	void CEraser::UpdateXYArray() {
		xy[0][0] = xy[1][0];
		xy[0][1] = xy[1][1];
		xy[1][0] = GetX1();
		xy[1][1] = GetY1();
	}
	void CEraser::LoadBitmap()
	{
		animation.AddBitmap(BOXKID_DOWN1, RGB(255, 255, 255));
		
		//animation.AddBitmap(IDB_ERASER2, RGB(255, 255, 255));
		//animation.AddBitmap(IDB_ERASER3, RGB(255, 255, 255));
		//animation.AddBitmap(IDB_ERASER2, RGB(255, 255, 255));
		
	}
	
	void CEraser::OnMove()
	{
		const int STEP_SIZE = 4;
		int last_x = position[position.size() - 1][0];
		int last_y = position[position.size() - 1][1];
		animation.OnMove();
		if (isMovingLeft && isCollision("left")==false && canPushBoxLeft) {
			isMovingNow = true;
			target_x = last_x-40;
			target_y = last_y;
			x -= STEP_SIZE;
			UpdateXYArray();
			//SetMovingLeft(false);
		}else if (isMovingRight && isCollision("right") == false && canPushBoxRight) {
			isMovingNow = true;
			target_x = last_x+40;
			target_y = last_y;
			x += STEP_SIZE;
			UpdateXYArray();
			//isMovingRight = false;
		}else if (isMovingUp && isCollision("up") == false && canPushBoxUp) {
			isMovingNow = true;
			target_x = last_x;
			target_y = last_y-40;
			y -= STEP_SIZE;
			UpdateXYArray();
			//isMovingUp = false;
		}else if (isMovingDown && isCollision("down") == false && canPushBoxDown) {
			isMovingNow = true;
			target_x = last_x;
			target_y = last_y+40;
			y += STEP_SIZE;
			UpdateXYArray();
			//isMovingDown = false;
		}
		else {
			isMovingNow = false;
			position.push_back({x,y});
			SetMovingDown(false);
			SetMovingUp(false);
			SetMovingLeft(false);
			SetMovingRight(false);
		}
			
	}

	void CEraser::SetMovingDown(bool flag)
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

	void CEraser::SetMovingLeft(bool flag)
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

	void CEraser::SetMovingRight(bool flag)
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

	void CEraser::SetMovingUp(bool flag)
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

	/*void CEraser::SetMovingNow(bool isMovingNow) {
		if (isMovingNow == true) {
			if (isMovingUp) {
				SetMovingUp(true);
			}
			else if (isMovingDown) {
				SetMovingDown(true);
			}
			else if (isMovingLeft) {
				SetMovingLeft(true);
			}
			else if (isMovingRight) {
				SetMovingRight(true);
			}
		}
	}
	*/

	void CEraser::SetXY(int nx, int ny)
	{
		x = nx; y = ny;
	}



	void CEraser::findIndex(int type) {
		int m = sizeof(myArray) / sizeof(myArray[0]);
		int n  = sizeof(myArray[0]) / sizeof(myArray[0][0]);
		//若找到 將座標值輸入至find array
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				if (myArray[i][j] == type) {
					find[0] = j;
					find[1] = i;
				}
					
			}
		}
	}

	void CEraser::ArrayToXY(int m, int n) {
		SetXY(n * 40, m * 40);
	}


	bool CEraser::isCollision(string direction) {

		int m = position[position.size()-1][1] / 40; // last y
		int n = position[position.size() - 1][0] / 40; // last x
		if (direction == "up") {
			if (myArray[m - 1][n] == 1) {
				return true;
			}
			else {
				return false;
			}
		}
		else if (direction == "down") {
			if(myArray[m + 1][n] == 1) {
				return true;
			}
			else {
				return false;
			}

		}
		else if (direction == "left") {
			if(myArray[m][n-1] == 1) {
				return true;
				}
			else {
			return false;
			}

		}
		else if (direction == "right") {
			if(myArray[m][n+1] == 1) {
				return true;
			}
			else {
				return false;
			}

		}
		return false;
	}

	bool CEraser::isPushingBox(int box_x, int box_y) {
		if (target_x == box_x && target_y == box_y) {//下一步會重合, PushingBoxDirection來啟動box的移動功能
			if (y < box_y) {//往下推
				PushingBoxDirection = "down";
			}
			else if (y > box_y) {//往上推
				PushingBoxDirection = "up";
			}
			else if (x > box_x) {//往左推
				PushingBoxDirection = "left";
			}
			else if (x < box_x) {//往右推
				
				PushingBoxDirection = "right";
			}
			else {
				PushingBoxDirection = "none";
			}
			return true;
		}
		else {
			PushingBoxDirection = "none";
			return false;
		}
	}
	string CEraser::isNearBox(int box_x, int box_y) {
		if (x == box_x + 40 && y == box_y) {
			return "left";
		}
		else if (x == box_x - 40 && y == box_y) {
			return "right";
		}
		else if (x == box_x && y == box_y - 40) {
			return "down";
		}
		else if (x == box_x && y == box_y + 40) {
			return "up";
		}
		else {
			return "none";
		}
	}

	void CEraser::setPushingBoxDirection(int box_x, int box_y) {
		if (target_x == box_x && target_y == box_y) {//下一步會重合, PushingBoxDirection來啟動box的移動功能
			if (y < box_y) {//往下推
				PushingBoxDirection = "down";
			}
			else if (y > box_y) {//往上推
				PushingBoxDirection = "up";
			}
			else if (x > box_x) {//往左推
				PushingBoxDirection = "left";
			}
			else if (x < box_x) {//往右推
				PushingBoxDirection = "right";
			}
			else {
				PushingBoxDirection = "none";
			}
		}
		else {
			PushingBoxDirection = "none";
		}
	}

	bool CEraser::isMatchPoint() {
		if (x == target_x && y == target_y) {
			return true;
		}
		else {
			return false;
		}

	}
	void CEraser::OnShow()
	{	
		//SetMovingNow(isMovingNow);
		if (isMatchPoint()) {
			SetMovingDown(false);
			SetMovingUp(false);
			SetMovingLeft(false);
			SetMovingRight(false);
		}
		animation.SetTopLeft(x, y);
		animation.OnShow();
	}
}