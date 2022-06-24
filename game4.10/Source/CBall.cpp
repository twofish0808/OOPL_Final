#include "stdafx.h"
#include "resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CEraser.h"
#include "Box.h"
#include "CBall.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// CBall: Ball class
	/////////////////////////////////////////////////////////////////////////////

	CBall::CBall()
	{
		is_alive = true;
		x = y = dx = dy = index = delay_counter = 0;
	}
	string CBall::HitEraserDirection(CEraser* eraser) {
		int x1 = x + dx;				// 球的左上角x座標
		int y1 = y + dy;				// 球的左上角y座標
		int x2 = x1 + bmp.Width();	// 球的右下角x座標
		int y2 = y1 + bmp.Height();	// 球的右下角y座標
		if (HitEraser(eraser)) {
			if (eraser->GetX2() > x1 && eraser->GetX1() < x2) {
				if (eraser->GetY1() < y1 && eraser->GetY2() >= y1) {
					return "up";
				}
				else if (eraser->GetY1() > y1 && eraser->GetY1() <= y2) {
					return "down";
				}
			}
			else{
				if (eraser->GetX1() < x1 && eraser->GetX2() >= x1) {
					return "left";
				}
				else if (eraser->GetX1() <= x2 && eraser->GetX2() > x2) {
					return "right";
				}
			}
			
			
		}
		return "no hitting";
	}
	int CBall::GetX1() {
	return x+dx;
	}
	int CBall::GetY1() {
	return y+dy;
	}
	bool CBall::HitEraser(CEraser *eraser)
	{
		// 檢測擦子所構成的矩形是否碰到球
		return HitRectangle(eraser->GetX1(), eraser->GetY1(),
			eraser->GetX2(), eraser->GetY2());
	}

	bool CBall::HitRectangle(int tx1, int ty1, int tx2, int ty2)
	{
		int x1 = x + dx;				// 球的左上角x座標
		int y1 = y + dy;				// 球的左上角y座標
		int x2 = x1 + bmp.Width();	// 球的右下角x座標
		int y2 = y1 + bmp.Height();	// 球的右下角y座標
									//
									// 檢測球的矩形與參數矩形是否有交集
									//
		return (tx2 >= x1 && tx1 <= x2 && ty2 >= y1 && ty1 <= y2);
	}

	bool CBall::IsAlive()
	{
		return is_alive;
	}

	void CBall::LoadBitmap()
	{
		bmp.LoadBitmap(BOXKID_WALL, RGB(0, 0, 0));			// 載入球的圖形
		//bmp_center.LoadBitmap(IDB_CENTER, RGB(0, 0, 0));	// 載入球圓心的圖形
	}

	void CBall::OnMove()
	{
		if (!is_alive)
			return;
		delay_counter--;
		if (delay_counter < 0) {
			delay_counter = delay;
			//
			// 計算球向對於圓心的位移量dx, dy
			//
			const int STEPS = 0; // 0: 不動 
			static const int DIFFX[] = { 35, 32, 26, 17, 6, -6, -17, -26, -32, -34, -32, -26, -17, -6, 6, 17, 26, 32, };
			static const int DIFFY[] = { 0, 11, 22, 30, 34, 34, 30, 22, 11, 0, -11, -22, -30, -34, -34, -30, -22, -11, };
			index++;
			if (index >= STEPS)
				index = 0;
			dx = DIFFX[index];
			dy = DIFFY[index];
		}
	}

	void CBall::SetDelay(int d)
	{
		delay = d;
	}

	void CBall::SetIsAlive(bool alive)
	{
		is_alive = alive;
	}

	void CBall::SetXY(int nx, int ny)
	{
		x = nx; y = ny;
	}

	void CBall::OnShow()
	{
		if (is_alive) {
			bmp.SetTopLeft(x + dx, y + dy);
			bmp.ShowBitmap();
			//bmp_center.SetTopLeft(x, y);
			//bmp_center.ShowBitmap();
		}
	}







	CEnd::CEnd()
	{
		is_alive = true;
		x = y = dx = dy = index = delay_counter = 0;
	}
	string CEnd::HitEraserDirection(CEraser* eraser) {
		int x1 = x + dx;				// 球的左上角x座標
		int y1 = y + dy;				// 球的左上角y座標
		int x2 = x1 + bmp.Width();	// 球的右下角x座標
		int y2 = y1 + bmp.Height();	// 球的右下角y座標
		if (HitEraser(eraser)) {
			if (eraser->GetX2() > x1 && eraser->GetX1() < x2) {
				if (eraser->GetY1() < y1 && eraser->GetY2() >= y1) {
					return "up";
				}
				else if (eraser->GetY1() > y1 && eraser->GetY1() <= y2) {
					return "down";
				}
			}
			else {
				if (eraser->GetX1() < x1 && eraser->GetX2() >= x1) {
					return "left";
				}
				else if (eraser->GetX1() <= x2 && eraser->GetX2() > x2) {
					return "right";
				}
			}


		}
		return "no hitting";
	}
	bool CEnd::HitEraser(CEraser* eraser)
	{
		// 檢測擦子所構成的矩形是否碰到球
		return HitRectangle(eraser->GetX1(), eraser->GetY1(),
			eraser->GetX2(), eraser->GetY2());
	}

	bool CEnd::HitRectangle(int tx1, int ty1, int tx2, int ty2)
	{
		int x1 = x + dx;				// 球的左上角x座標
		int y1 = y + dy;				// 球的左上角y座標
		int x2 = x1 + bmp.Width();	// 球的右下角x座標
		int y2 = y1 + bmp.Height();	// 球的右下角y座標
									//
									// 檢測球的矩形與參數矩形是否有交集
									//
		return (tx2 >= x1 && tx1 <= x2 && ty2 >= y1 && ty1 <= y2);
	}

	bool CEnd::IsAlive()
	{
		return is_alive;
	}

	void CEnd::LoadBitmap()
	{
		bmp.LoadBitmap(BOXKID_ENDS, RGB(0, 0, 0));			// 載入球的圖形
		//bmp_center.LoadBitmap(IDB_CENTER, RGB(0, 0, 0));	// 載入球圓心的圖形
	}

	void CEnd::OnMove()
	{
		if (!is_alive)
			return;
		delay_counter--;
		if (delay_counter < 0) {
			delay_counter = delay;
			//
			// 計算球向對於圓心的位移量dx, dy
			//
			const int STEPS = 0; // 0: 不動 
			static const int DIFFX[] = { 35, 32, 26, 17, 6, -6, -17, -26, -32, -34, -32, -26, -17, -6, 6, 17, 26, 32, };
			static const int DIFFY[] = { 0, 11, 22, 30, 34, 34, 30, 22, 11, 0, -11, -22, -30, -34, -34, -30, -22, -11, };
			index++;
			if (index >= STEPS)
				index = 0;
			dx = DIFFX[index];
			dy = DIFFY[index];
		}
	}

	void CEnd::SetDelay(int d)
	{
		delay = d;
	}

	void CEnd::SetIsAlive(bool alive)
	{
		is_alive = alive;
	}

	void CEnd::SetXY(int nx, int ny)
	{
		x = nx; y = ny;
	}

	void CEnd::OnShow()
	{
		if (is_alive) {
			bmp.SetTopLeft(x + dx, y + dy);
			bmp.ShowBitmap();
			//bmp_center.SetTopLeft(x, y);
			//bmp_center.ShowBitmap();
		}
	}
}