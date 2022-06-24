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
		//findIndex(4);//找地圖中BOX 座標
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
		

		

		
		
		/**/const char* file_name = "level.txt";
		FILE* file = fopen(file_name, "r");
		int i = 0;

		fscanf(file, "%d", &i);
		while (!feof(file))
		{
			printf("%d ", i);
			fscanf(file, "%d", &i);
		}
		fclose(file);
		level = i;
		/*FILE* fp = fopen("level.txt", "w");
		if (fp) {
			i = i + 100;
			fprintf(fp, "%d\n", i);
			fclose(fp);
		}*/
	}
	void Box::UpdateXYArray() {
		xy[0][0] = xy[1][0];
		xy[0][1] = xy[1][1];
		xy[1][0] = GetX1();
		xy[1][1] = GetY1();
	}
	void Box::LoadBitmap()
	{
		animation.AddBitmap(BOXKID_BOX, RGB(255, 255, 255));

		//animation.AddBitmap(IDB_ERASER2, RGB(255, 255, 255));
		//animation.AddBitmap(IDB_ERASER3, RGB(255, 255, 255));
		//animation.AddBitmap(IDB_ERASER2, RGB(255, 255, 255));

	}
	void Box::ChangeBitmap(int status) {
		if (status == 1) {
			animation.AddBitmap(BOXKID_CORRECT_BOX, RGB(255, 255, 255));
			if (animation.GetNumOfBitmap() > 1) // 當只剩一張圖片時不要刪除
				animation.RemoveFirstBitmap();
		}
		if (status == 2) {
			animation.AddBitmap(BOXKID_BOX, RGB(255, 255, 255));
			if (animation.GetNumOfBitmap() > 1) // 當只剩一張圖片時不要刪除
				animation.RemoveFirstBitmap();
		}
		
		/*int m = position[position.size() - 1][1] / 40; // last y
		int n = position[position.size() - 1][0] / 40; // last x

		//if (myyArray[m][n] == 6 )
		if ((find[0] == n && find[1] == m)) {
			animation.AddBitmap(BOXKID_BOX, RGB(255, 255, 255));
			if (animation.GetNumOfBitmap() > 1) // 當只剩一張圖片時不要刪除
				animation.RemoveFirstBitmap();
		}
		else {
			animation.AddBitmap(BOXKID_BOX, RGB(255, 255, 255));
			if (animation.GetNumOfBitmap() > 1) // 當只剩一張圖片時不要刪除
				animation.RemoveFirstBitmap();
		}*/
		
	}

	void Box::OnMove()
	{
		const int STEP_SIZE = 4;
		int last_x = position[position.size() - 1][0];
		int last_y = position[position.size() - 1][1];
		animation.OnMove();
		if (isMovingLeft && isCollision("left") == false) {
			isMovingNow = true;
			target_x = last_x - 40;
			target_y = last_y;
			x -= STEP_SIZE;
			UpdateXYArray();
			//SetMovingLeft(false);
		}
		else if (isMovingRight && isCollision("right") == false) {
			isMovingNow = true;
			target_x = last_x + 40;
			target_y = last_y;
			x += STEP_SIZE;
			UpdateXYArray();
			//isMovingRight = false;
		}
		else if (isMovingUp && isCollision("up") == false) {
			isMovingNow = true;
			target_x = last_x;
			target_y = last_y - 40;
			y -= STEP_SIZE;
			UpdateXYArray();
			//isMovingUp = false;
		}
		else if (isMovingDown && isCollision("down") == false) {
			isMovingNow = true;
			target_x = last_x;
			target_y = last_y + 40;
			y += STEP_SIZE;
			UpdateXYArray();
			//isMovingDown = false;
		}
		else {//抵達target
			isMovingNow = false;
			position.push_back({ x,y });
			SetMovingDown(false);
			SetMovingUp(false);
			SetMovingLeft(false);
			SetMovingRight(false);
			//ChangeBitmap(); // 若到終點會變打勾 否則不便 若離開終點會變成一般box
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

		}
		else {
			if (animation.GetNumOfBitmap() > 1) // 當只剩一張圖片時不要刪除
				animation.RemoveFirstBitmap();

		}
	}

	/*void Box::SetMovingNow(bool isMovingNow) {
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

	void Box::SetXY(int nx, int ny)
	{
		x = nx; y = ny;
	}

	

	

	void Box::ArrayToXY(int m, int n) {
		SetXY(n * 40, m * 40);
	}
	void Box::beingPushedAway(string PushingBoxDirection) {
		if (PushingBoxDirection == "up") {
			SetMovingUp(true);
		}
		else if (PushingBoxDirection == "down") {
			SetMovingDown(true);
		}
		else if (PushingBoxDirection == "left") {
			SetMovingLeft(true);
		}
		else if (PushingBoxDirection == "right") {
			SetMovingRight(true);
		}
		else {
			//加了會錯 可能跟到達target前一步時 被設定成false有關, 現在是靠isMacthingPoint確保會到終點
			/*SetMovingUp(false);
			SetMovingDown(false);
			SetMovingLeft(false);
			SetMovingRight(false);
			*/ 
		}
	}

	bool Box::isCollision(string direction) {

		int m = position[position.size() - 1][1] / 40; // last y
		int n = position[position.size() - 1][0] / 40; // last x
		if (direction == "up") {
			if (myyArray[m - 1][n] == 1) {
				return true;
			}
			else {
				return false;
			}
		}
		else if (direction == "down") {
			if (myyArray[m + 1][n] == 1) {
				return true;
			}
			else {
				return false;
			}

		}
		else if (direction == "left") {
			if (myyArray[m][n - 1] == 1) {
				return true;
			}
			else {
				return false;
			}

		}
		else if (direction == "right") {
			if (myyArray[m][n + 1] == 1) {
				return true;
			}
			else {
				return false;
			}

		}
		return false;
	}

	bool Box::isMatchPoint() {
		if (x == target_x && y == target_y) {
			return true;
		}
		else {
			return false;
		}

	}
	void Box::OnShow()
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