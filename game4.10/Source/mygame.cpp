/*
 * mygame.cpp: 本檔案儲遊戲本身的class的implementation
 * Copyright (C) 2002-2008 Woei-Kae Chen <wkc@csie.ntut.edu.tw>
 *
 * This file is part of game, a free game development framework for windows.
 *
 * game is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * game is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * History:
 *   2002-03-04 V3.1
 *          Add codes to demostrate the use of CMovingBitmap::ShowBitmap(CMovingBitmap &).
 *	 2004-03-02 V4.0
 *      1. Add CGameStateInit, CGameStateRun, and CGameStateOver to
 *         demonstrate the use of states.
 *      2. Demo the use of CInteger in CGameStateRun.
 *   2005-09-13
 *      Rewrite the codes for CBall and CEraser.
 *   2005-09-20 V4.2Beta1.
 *   2005-09-29 V4.2Beta2.
 *      1. Add codes to display IDC_GAMECURSOR in GameStateRun.
 *   2006-02-08 V4.2
 *      1. Revise sample screens to display in English only.
 *      2. Add code in CGameStateInit to demo the use of PostQuitMessage().
 *      3. Rename OnInitialUpdate() -> OnInit().
 *      4. Fix the bug that OnBeginState() of GameStateInit is not called.
 *      5. Replace AUDIO_CANYON as AUDIO_NTUT.
 *      6. Add help bitmap to CGameStateRun.
 *   2006-09-09 V4.3
 *      1. Rename Move() and Show() as OnMove and OnShow() to emphasize that they are
 *         event driven.
 *   2006-12-30
 *      1. Bug fix: fix a memory leak problem by replacing PostQuitMessage(0) as
 *         PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE,0,0).
 *   2008-02-15 V4.4
 *      1. Add namespace game_framework.
 *      2. Replace the demonstration of animation as a new bouncing ball.
 *      3. Use ShowInitProgress(percent) to display loading progress. 
 *   2010-03-23 V4.6
 *      1. Demo MP3 support: use lake.mp3 to replace lake.wav.
*/

#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "mygame.h"


namespace game_framework {
	int lev = 1;
	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的遊戲開頭畫面物件
	/////////////////////////////////////////////////////////////////////////////

	CGameStateInit::CGameStateInit(CGame* g)
		: CGameState(g)
	{
	}

	void CGameStateInit::OnInit()
	{
		//
		// 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
		//     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
		//
		ShowInitProgress(0);	// 一開始的loading進度為0%
		//
		// 開始載入資料
		//
		logo.LoadBitmap(IDB_BACKGROUND);//第一張背景
		Sleep(300);				// 放慢，以便看清楚進度，實際遊戲請刪除此Sleep
		//
		// 此OnInit動作會接到CGameStaterRun::OnInit()，所以進度還沒到100%
		// 
		//
		CAudio::Instance()->Load(AUDIO_NTUT, "sounds\\boxkid.wav");	// 載入編號2的聲音ntut.mid
		CAudio::Instance()->Play(AUDIO_NTUT, true);
		audio_enable = 1;
	}

	void CGameStateInit::OnBeginState()
	{


	}

	void CGameStateInit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		const char KEY_ESC = 27;
		const char KEY_SPACE = ' ';
		if (nChar == KEY_SPACE)
			GotoGameState(GAME_STATE_RUN);						// 切換至GAME_STATE_RUN
		else if (nChar == KEY_ESC)								// Demo 關閉遊戲的方法
			PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE, 0, 0);	// 關閉遊戲
	}

	void CGameStateInit::OnLButtonDown(UINT nFlags, CPoint point)
	{
		CAudio::Instance()->Play(AUDIO_DING, false);
		if (point.x <= 245 && point.y >= 291 && point.x >= 125 && point.y <= 341)
			GotoGameState(GAME_STATE_LEVEL);						// 切換至GAME_STATE_LEVEL
		if (point.x <= 234 && point.y >= 381 && point.x >= 129 && point.y <= 427) {
			if (audio_enable == 1) {
				CAudio::Instance()->Stop(AUDIO_NTUT);
				audio_enable = 0;
			}
			else {
				CAudio::Instance()->Play(AUDIO_NTUT, true);
				audio_enable = 1;
			}
		}
		if (point.x <= 323 && point.y >= 597 && point.x >= 272 && point.y <= 620) {
			GotoGameState(GAME_STATE_ABOUT);
		}

	}

	void CGameStateInit::OnShow()
	{
		//
		// 貼上logo
		//
		logo.SetTopLeft(0, 0);
		logo.ShowBitmap();

		//
		// Demo螢幕字型的使用，不過開發時請盡量避免直接使用字型，改用CMovingBitmap比較好
		//
		/*
		CDC *pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC
		CFont f,*fp;
		f.CreatePointFont(160,"Times New Roman");	// 產生 font f; 160表示16 point的字
		fp=pDC->SelectObject(&f);					// 選用 font f
		pDC->SetBkColor(RGB(0,0,0));
		pDC->SetTextColor(RGB(255,255,0));
		pDC->TextOut(120,220,"Please click mouse or press SPACE to begin.");
		pDC->TextOut(5,395,"Press Ctrl-F to switch in between window mode and full screen mode.");
		if (ENABLE_GAME_PAUSE)
			pDC->TextOut(5,425,"Press Ctrl-Q to pause the Game.");
		pDC->TextOut(5,455,"Press Alt-F4 or ESC to Quit.");
		pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
		CDDraw::ReleaseBackCDC();	*/				// 放掉 Back Plain 的 CDC
	}
	CGameStateReset::CGameStateReset(CGame* g)
		:CGameState(g)
	{}
	void CGameStateReset::OnInit() {
		levels.LoadBitmap(BOXKID_LEVEL);
		levels.SetTopLeft(0, 0);


	}
	void CGameStateReset::OnShow() {
		levels.ShowBitmap();
		GotoGameState(GAME_STATE_RUN);


	}
	void CGameStateReset::OnBeginState() {

	}

	CGameStateAbout::CGameStateAbout(CGame* g)
		: CGameState(g)
	{
	}
	void CGameStateAbout::OnInit() {
		about.LoadBitmap(BOXKID_ABOUT);
		about.SetTopLeft(0, 0);
	}
	void CGameStateAbout::OnShow() {
		about.ShowBitmap();
	}
	void CGameStateAbout::OnBeginState() {
	}
	void CGameStateAbout::OnLButtonDown(UINT nFlags, CPoint point) {
		if (point.x <= 237 && point.y >= 497 && point.x >= 88 && point.y <= 539)
			GotoGameState(GAME_STATE_INIT);
	}


	/////////////////////////////////////////////////////////////////////////////
	// 這個class為關卡選擇
	/////////////////////////////////////////////////////////////////////////////
	CGameStateLevel::CGameStateLevel(CGame* g)
		: CGameState(g)
	{
	}
	void CGameStateLevel::OnInit() {
		levels.LoadBitmap(BOXKID_LEVEL);
		levels.SetTopLeft(0, 0);
		//system("type nul > level.txt");


	}
	void CGameStateLevel::OnShow() {
		levels.ShowBitmap();
	}
	void CGameStateLevel::OnLButtonDown(UINT nFlags, CPoint point) {
		CAudio::Instance()->Play(AUDIO_DING, false);
		const char* str = "0";
		if (point.x <= 69 && point.y >= 129 && point.x >= 29 && point.y <= 170) {


			lev = 1;
		}				// 切換至GAME_STATE_RUN
		else if (point.x <= 136 && point.y >= 129 && point.x >= 96 && point.y <= 170) {

			lev = 2;
		}				// 切換至GAME_STATE_RUN
		else if (point.x <= 206 && point.y >= 129 && point.x >= 164 && point.y <= 170) {

			lev = 3;
		}				// 切換至GAME_STATE_RUN
		else if (point.x <= 274 && point.y >= 129 && point.x >= 234 && point.y <= 170) {

			lev = 4;
		}				// 切換至GAME_STATE_RUN
		else if (point.x <= 343 && point.y >= 129 && point.x >= 302 && point.y <= 170) {

			lev = 5;
		}				// 切換至GAME_STATE_RUN
		else if (point.x <= 69 && point.y >= 196 && point.x >= 29 && point.y <= 239) {

			lev = 6;
		}				// 切換至GAME_STATE_RUN
		else if (point.x <= 136 && point.y >= 196 && point.x >= 96 && point.y <= 239) {

			lev = 7;
		}				// 切換至GAME_STATE_RUN
		else if (point.x <= 206 && point.y >= 196 && point.x >= 164 && point.y <= 239) {

			lev = 8;
		}				// 切換至GAME_STATE_RUN
		else if (point.x <= 274 && point.y >= 196 && point.x >= 234 && point.y <= 239) {

			lev = 9;
		}				// 切換至GAME_STATE_RUN
		else if (point.x <= 343 && point.y >= 196 && point.x >= 302 && point.y <= 239) {

			lev = 10;
		}				// 切換至GAME_STATE_RUN
		else if (point.x <= 69 && point.y >= 265 && point.x >= 29 && point.y <= 307) {

			lev = 11;
		}				// 切換至GAME_STATE_RUN
		else if (point.x <= 136 && point.y >= 265 && point.x >= 96 && point.y <= 307) {

			lev = 12;
		}				// 切換至GAME_STATE_RUN
		else if (point.x <= 206 && point.y >= 265 && point.x >= 164 && point.y <= 307) {

			lev = 13;
		}				// 切換至GAME_STATE_RUN
		else if (point.x <= 274 && point.y >= 265 && point.x >= 234 && point.y <= 307) {

			lev = 14;
		}				// 切換至GAME_STATE_RUN
		else if (point.x <= 343 && point.y >= 265 && point.x >= 302 && point.y <= 307) {

			lev = 15;
		}				// 切換至GAME_STATE_RUN
		else if (point.x <= 69 && point.y >= 332 && point.x >= 29 && point.y <= 375) {

			lev = 16;
		}				// 切換至GAME_STATE_RUN
		else if (point.x <= 136 && point.y >= 332 && point.x >= 96 && point.y <= 375) {

			lev = 17;
		}				// 切換至GAME_STATE_RUN
		else if (point.x <= 206 && point.y >= 332 && point.x >= 164 && point.y <= 375) {

			lev = 18;
		}				// 切換至GAME_STATE_RUN
		else if (point.x <= 274 && point.y >= 332 && point.x >= 234 && point.y <= 375) {

			lev = 19;
		}				// 切
		else if (point.x <= 343 && point.y >= 332 && point.x >= 302 && point.y <= 375) {

			lev = 20;
		}				// 切
		else if (point.x <= 69 && point.y >= 403 && point.x >= 29 && point.y <= 440) {

			lev = 21;
		}				// 切
		else if (point.x <= 136 && point.y >= 403 && point.x >= 96 && point.y <= 440) {

			lev = 22;
		}				// 切
		/*else if (point.x <= 206 && point.y >= 403 && point.x >= 164 && point.y <= 440) {
			str = "23";
		}				// 切
		else if (point.x <= 274 && point.y >= 403 && point.x >= 234 && point.y <= 440) {
			str = "24";
		}				// 切
		else if (point.x <= 343 && point.y >= 403 && point.x >= 302 && point.y <= 440) {
			str = "25";
		}				// 切
		else if (point.x <= 69 && point.y >= 472 && point.x >= 29 && point.y <= 513) {
			str = "26";
		}				// 切
		else if (point.x <= 136 && point.y >= 472 && point.x >= 96 && point.y <= 513) {
			str = "27";
		}				// 切
		else if (point.x <= 206 && point.y >= 472 && point.x >= 164 && point.y <= 513) {
			str = "28";
		}				// 切
		else if (point.x <= 274 && point.y >= 472 && point.x >= 234 && point.y <= 513) {
			str = "29";
		}				// 切
		else if (point.x <= 343 && point.y >= 472 && point.x >= 302 && point.y <= 513) {
			str = "30";
		}				// 切*/
		else
		{
			lev = 100;
		}

		if (lev != 100) {
			//CAudio::Instance()->Stop(AUDIO_NTUT);
			/*open_file = fopen(filename, "w");
			fwrite(str, 1, strlen(str), open_file);
			fclose(open_file);*/
			GotoGameState(GAME_STATE_RUN);
		}

	}



	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的結束狀態(Game Over)
	/////////////////////////////////////////////////////////////////////////////


	CGameStateOver::CGameStateOver(CGame* g)
		: CGameState(g)
	{
	}



	void CGameStateOver::OnBeginState()
	{
	}

	void CGameStateOver::OnInit()
	{
		victory.LoadBitmap(VICTORY);
	}

	void CGameStateOver::OnShow()
	{
		victory.ShowBitmap();

	}
	void CGameStateOver::OnLButtonDown(UINT nFlags, CPoint point) {
		if (point.x <= 237 && point.y >= 497 && point.x >= 88 && point.y <= 539)
			GotoGameState(GAME_STATE_INIT);

	}

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
	/////////////////////////////////////////////////////////////////////////////
	int a = 40;
	CGameStateRun::CGameStateRun(CGame* g)
		: CGameState(g), NUMBALLS(40)
	{
		ball = new CBall[NUMBALLS];
		ends = new CEnd[NUMBALLS];
		box = new Box[NUMBALLS];
	}

	CGameStateRun::~CGameStateRun()
	{
		delete[] ball;
		delete[] ends;
		delete[] box;
	}

	void CGameStateRun::OnBeginState()
	{
		
		const int BALL_GAP = 90;
		const int BALL_XY_OFFSET = 45;
		const int BALL_PER_ROW = 7;
		const int HITS_LEFT = 10;
		const int HITS_LEFT_X = 590;
		const int HITS_LEFT_Y = 60;
		const int BACKGROUND_X = 1;
		const int ANIMATION_SPEED = 15;
		//for (int n = 0; n < NUMBALLS; n++) {				// 設定球的起始座標
			//int x_pos = i % BALL_PER_ROW;
			//int y_pos = i / BALL_PER_ROW;
			//ball[i].SetXY(x_pos * BALL_GAP + BALL_XY_OFFSET, y_pos * BALL_GAP + BALL_XY_OFFSET);
			//ball[i].SetDelay(x_pos);
			// 
			//將mapArray中value值為1的座標傳給ball的SetXY
		//}

		//讀txt
		/*
		const char* file_name = "../level.txt";
		FILE* file = fopen(file_name, "r");
		int i = 0;

		fscanf(file, "%d", &i);
		while (!feof(file))
		{
			printf("%d ", i);
			fscanf(file, "%d", &i);
		}
		fclose(file);*/
		level = lev;

		for (int i = 0; i < 12; i++) {
			for (int j = 0; j < 9; j++) {
				eraser.myArray[i][j] = mapArray[level - 1][i][j];
				for (int z = 0; z < NUMBALLS; z++) {
					box[z].myyArray[i][j] = mapArray[level - 1][i][j]; // 更新地圖
				}
			}
		}

		//新增box圖案by地圖array
		int n = 0;
		for (int i = 0; i < 12; i++) {
			for (int j = 0; j < 9; j++) {
				//box[n].SetXY(-36 + j * 40, i * 40);
				if (mapArray[level - 1][i][j] == 4 || mapArray[level - 1][i][j] == 6) {
					box[n].find[0] = j;
					box[n].find[1] = i;
					n++;
				}
			}
		}


		n = 0;
		for (int y = 0; y < 12; y++) {
			for (int x = 0; x < 9; x++) {
				if (mapArray[level - 1][y][x] == 1) {
					//ball[n].SetXY(-36+x*40, y*40); //X向調整init位置
					ball[n].SetXY(-36 + x * 40, y * 40); //X向調整init位置
					ball[n].SetIsAlive(true);
					n++;
				}
			}
		}
		n = 0;

		for (int y = 0; y < 12; y++) {
			for (int x = 0; x < 9; x++) {
				if (mapArray[level - 1][y][x] == 5 || mapArray[level - 1][y][x] == 6) {
					//ball[n].SetXY(-36+x*40, y*40); //X向調整init位置
					ends[n].SetXY(-36 + x * 40, y * 40); //X向調整init位置
					ends[n].SetIsAlive(true);
					n++;
				}
			}
		}

		eraser.Initialize();
		for (int z = 0; z < NUMBALLS; z++) {
			box[z].Initialize();
		}







		background.SetTopLeft(0, 0);				// 設定背景的起始座標
		help.SetTopLeft(0, SIZE_Y - help.Height());			// 設定說明圖的起始座標
		hits_left.SetInteger(HITS_LEFT);					// 指定剩下的撞擊數
		hits_left.SetTopLeft(HITS_LEFT_X, HITS_LEFT_Y);		// 指定剩下撞擊數的座標
		CAudio::Instance()->Play(AUDIO_LAKE, true);			// 撥放 WAVE
		CAudio::Instance()->Play(AUDIO_DING, false);		// 撥放 WAVE
		if (music_is_on != 0) {
			CAudio::Instance()->Play(AUDIO_NTUT, true);			// 撥放 MIDI
			music_is_on = 1;
		}


		for (int n_target = 0; n_target < 3; n_target++) {
			int index_point = 0;
			int point[3][2] = { { 10000, 10000 } ,{ 10000, 10000 } ,{ 10000, 10000 } };
			int win_status[3] = { 0,0,0 };
			//掃描array
			for (int row = 0; row < 9; row++) {
				for (int col = 0; col < 12; col++) {
					if (mapArray[level - 1][col][row] == 5 || mapArray[level - 1][col][row] == 6) {
						point[index_point][0] = col;
						point[index_point][1] = row;
						index_point++;
					}
				}
			}
			int flag1 = 0;
			int flag2 = 0;
			int flag3 = 0;


			if (box[0].GetX1() + 5 >= point[n_target][1] * 40 && box[0].GetX1() <= point[n_target][1] * 40 + 5 && box[0].GetY1() + 5 >= point[n_target][0] * 40 && box[0].GetY1() <= point[n_target][0] * 40 + 5) {
				box[0].ChangeBitmap(1);
				win_status[0] = 1;
				flag1 = 1;
			}
			else if (flag1 == 0) { box[0].ChangeBitmap(2); }
			if (box[1].GetX1() + 5 >= point[n_target][1] * 40 && box[1].GetX1() <= point[n_target][1] * 40 + 5 && box[1].GetY1() + 5 >= point[n_target][0] * 40 && box[1].GetY1() <= point[n_target][0] * 40 + 5) {
				box[1].ChangeBitmap(1);
				win_status[1] = 1;
				flag2 = 1;
			}
			else if (flag2 == 0) { box[1].ChangeBitmap(2); }
			if (box[2].GetX1() + 5 >= point[n_target][1] * 40 && box[2].GetX1() <= point[n_target][1] * 40 + 5 && box[2].GetY1() + 5 >= point[n_target][0] * 40 && box[2].GetY1() <= point[n_target][0] * 40 + 5) {
				box[2].ChangeBitmap(1);
				win_status[2] = 1;
				flag3 = 1;
			}
			else if (flag3 == 0) { box[2].ChangeBitmap(2); }

		}



	}

	void CGameStateRun::OnMove()							// 移動遊戲元素
	{
		//
		// 如果希望修改cursor的樣式，則將下面程式的commment取消即可
		//
		// SetCursor(AfxGetApp()->LoadCursor(IDC_GAMECURSOR));
		//
		// 移動背景圖的座標
		//
		/*if (background.Top() > SIZE_Y)
			background.SetTopLeft(6 ,-background.Height());
		background.SetTopLeft(background.Left(),background.Top()+1);*/
		//
		// 移動球
		//
		int i;
		for (i = 0; i < NUMBALLS; i++) {
			ball[i].OnMove();
			ends[i].OnMove();
		}
		//
		// 移動擦子
		//
		eraser.OnMove();
		//
		// 判斷擦子是否碰到球
		//

		string hitDirection;
		for (i = 0; i < NUMBALLS; i++)
			if (ball[i].IsAlive() && ball[i].HitEraser(&eraser)) {
				ball[i].SetIsAlive(true); // true 取消碰撞後wall消失
				//CAudio::Instance()->Play(AUDIO_DING);
				//hitDirection = ball[i].HitEraserDirection(&eraser);
				//eraser.Collision(ball[i].HitEraser(&eraser));
				hits_left.Add(-0);
				//
				// 若剩餘碰撞次數為0，則跳到Game Over狀態
				//
				if (hits_left.GetInteger() <= 0) {
					CAudio::Instance()->Stop(AUDIO_LAKE);	// 停止 WAVE
					CAudio::Instance()->Stop(AUDIO_NTUT);	// 停止 MIDI
					GotoGameState(GAME_STATE_OVER);
				}
			}




		// 判斷是否碰觸到BOX
		for (i = 0; i < NUMBALLS; i++) {
			int box_x = box[i].position[box[i].position.size() - 1][0];
			int box_y = box[i].position[box[i].position.size() - 1][1];
			eraser.setPushingBoxDirection(box_x, box_y); //帶修正(要用座標紀錄 還是矩陣inedx紀錄)
			if (eraser.isNearBox(box_x, box_y) == "up" && box[i].isCollision("up")) {
				eraser.canPushBoxUp = false;
			}
			else if (eraser.isNearBox(box_x, box_y) == "down" && box[i].isCollision("down")) {
				eraser.canPushBoxDown = false;
			}
			else if (eraser.isNearBox(box_x, box_y) == "left" && box[i].isCollision("left")) {
				eraser.canPushBoxLeft = false;
			}
			else if (eraser.isNearBox(box_x, box_y) == "right" && box[i].isCollision("right")) {
				eraser.canPushBoxRight = false;
			}
			else {
				eraser.canPushBoxUp = true;
				eraser.canPushBoxDown = true;
				eraser.canPushBoxLeft = true;
				eraser.canPushBoxRight = true;
				box[i].beingPushedAway(eraser.PushingBoxDirection);
				box[i].OnMove();
				box[i].OnShow();

			}
		}
		

		//update array





		//
		// 移動彈跳的球
		//
		//bball.OnMove();
	}

	void CGameStateRun::OnInit()  								// 遊戲的初值及圖形設定
	{

		//
		// 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
		//     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
		//
		ShowInitProgress(33);	// 接個前一個狀態的進度，此處進度視為33%
		//
		// 開始載入資料
		//
		int i;
		fg.LoadBitmap(GREEN_1);
		fg.SetTopLeft(0, 0);
		for (i = 0; i < NUMBALLS; i++) {
			ball[i].LoadBitmap();
			ends[i].LoadBitmap();
		}
		// 載入第i個球的圖形


		eraser.LoadBitmap();
		for (i = 0; i < NUMBALLS; i++) {
			box[i].LoadBitmap();
		}

		/*const char* file_name = "level.txt";
		FILE* file = fopen(file_name, "r");
		int lv = 0;

		fscanf(file, "%d", &i);
		while (!feof(file))
		{
			printf("%d ", i);
			fscanf(file, "%d", &i);
		}
		fclose(file);*/
		level = lev;



		//
		background.LoadBitmap(IDB_BACKGROUND);

		// 載入背景的圖形
	   //
	   // 完成部分Loading動作，提高進度
	   //
		ShowInitProgress(50);
		Sleep(300); // 放慢，以便看清楚進度，實際遊戲請刪除此Sleep
		//
		// 繼續載入其他資料
		//
		boxkid_map.LoadBitmap(BOXKID_MAP1);
		help.LoadBitmap(IDB_HELP, RGB(255, 255, 255));				// 載入說明的圖形
		corner.LoadBitmap(IDB_CORNER);							// 載入角落圖形
		//corner.ShowBitmap(background);							// 將corner貼到background
		//bball.LoadBitmap();										// 載入圖形
		hits_left.LoadBitmap();
		CAudio::Instance()->Load(AUDIO_DING, "sounds\\ding.wav");	// 載入編號0的聲音ding.wav
		CAudio::Instance()->Load(AUDIO_LAKE, "sounds\\blank.wav");	// 載入編號1的聲音lake.mp3
		music_is_on = 1;

		//
		// 此OnInit動作會接到CGameStaterOver::OnInit()，所以進度還沒到100%
		//
	}

	void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) // 按鍵被按壓
	{
		
		const char KEY_LEFT = 0x25; // keyboard左箭頭
		const char KEY_UP = 0x26; // keyboard上箭頭
		const char KEY_RIGHT = 0x27; // keyboard右箭頭
		const char KEY_DOWN = 0x28; // keyboard下箭頭
		if (nChar == KEY_LEFT)
			if (eraser.isMovingNow == false)
				eraser.SetMovingLeft(true);
		if (nChar == KEY_RIGHT)
			if (eraser.isMovingNow == false)
				eraser.SetMovingRight(true);
		if (nChar == KEY_UP)
			if (eraser.isMovingNow == false)
				eraser.SetMovingUp(true);
		if (nChar == KEY_DOWN)
			if (eraser.isMovingNow == false)
				eraser.SetMovingDown(true);


		//判斷箱子是否在位子上
		





	}

	void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) // 按鍵被鬆開
	{
		const char KEY_LEFT = 0x25; // keyboard左箭頭
		const char KEY_UP = 0x26; // keyboard上箭頭
		const char KEY_RIGHT = 0x27; // keyboard右箭頭
		const char KEY_DOWN = 0x28; // keyboard下箭頭



	}

	void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
	{	
		if (point.x <= 76 && point.y >= 543 && point.x >= 31 && point.y <= 592)
			GotoGameState(GAME_STATE_LEVEL);
		if (point.x <= 206 && point.y >= 542 && point.x >= 156 && point.y <= 591)
			GotoGameState(GAME_STATE_LEVEL);
		if (point.x <= 134 && point.y >= 544 && point.x >= 88 && point.y <= 590) {
			if (music_is_on == 1) {
				CAudio::Instance()->Stop(AUDIO_NTUT);
				music_is_on = 0;
			}
			else {
				CAudio::Instance()->Play(AUDIO_NTUT);
				music_is_on = 1;
			}
		}
		if (point.x <= 330 && point.y >= 546 && point.x >= 283 && point.y <= 590) {
			/*int i = 50;
			FILE* fp = fopen("level.txt", "w");
			if (fp) {
				i = i + 100;
				fprintf(fp, "%d\n", i);
				fclose(fp);
			}*/
			GotoGameState(GAME_STATE_RESET);
		}
		if (point.x <= 273 && point.y >= 546 && point.x >= 221 && point.y <= 590) {
			printf("return");
		}

		//GotoGameState(GAME_STATE_RESET);
	}

	void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
	{
		eraser.SetMovingLeft(false);
	}

	void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// 處理滑鼠的動作
	{
		// 沒事。如果需要處理滑鼠移動的話，寫code在這裡
	}

	void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
	{
		eraser.SetMovingRight(true);
	}

	void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
	{
		eraser.SetMovingRight(false);
	}

	void CGameStateRun::OnShow()
	{
		//
		//  注意：Show裡面千萬不要移動任何物件的座標，移動座標的工作應由Move做才對，
		//        否則當視窗重新繪圖時(OnDraw)，物件就會移動，看起來會很怪。換個術語
		//        說，Move負責MVC中的Model，Show負責View，而View不應更動Model。
		//
		//
		//  貼上背景圖、撞擊數、球、擦子、彈跳的球
		//
		//background.ShowBitmap();			// 貼上背景圖
		//help.ShowBitmap();					// 貼上說明圖
		boxkid_map.ShowBitmap();
		//hits_left.ShowBitmap();
		for (int i = 0; i < NUMBALLS; i++) {
			ball[i].OnShow();				// 貼上第i號球
			ends[i].OnShow();
		}
		//bball.OnShow();						// 貼上彈跳的球
		eraser.OnShow();					// 貼上擦子
		for (int i = 0; i < NUMBALLS; i++) {
			box[i].OnShow();
		}

		//
		//  貼上左上及右下角落的圖
		//
		corner.SetTopLeft(0, 0);
		//corner.ShowBitmap();
		corner.SetTopLeft(SIZE_X - corner.Width(), SIZE_Y - corner.Height());
		//corner.ShowBitmap();
		int index_point = 0;
		int point[3][2] = { { 10000, 10000 } ,{ 10000, 10000 } ,{ 10000, 10000 } };
		int win_status[3] = { 0,0,0 };
		//掃描array
		for (int row = 0; row < 9; row++) {
			for (int col = 0; col < 12; col++) {
				if (mapArray[level - 1][col][row] == 5 || mapArray[level - 1][col][row] == 6) {
					point[index_point][0] = col;
					point[index_point][1] = row;
					index_point++;
				}
			}
		}

		int flag1 = 0;
		int flag2 = 0;
		int flag3 = 0;
		for (int n_target = 0; n_target < 3; n_target++) {


			if (box[0].GetX1() + 5 >= point[n_target][1] * 40 && box[0].GetX1() <= point[n_target][1] * 40 + 5 && box[0].GetY1() + 5 >= point[n_target][0] * 40 && box[0].GetY1() <= point[n_target][0] * 40 + 5) {
				box[0].ChangeBitmap(1);
				win_status[0] = 1;
				flag1 = 1;
			}
			else if (flag1 == 0) { box[0].ChangeBitmap(2); }
			if (box[1].GetX1() + 5 >= point[n_target][1] * 40 && box[1].GetX1() <= point[n_target][1] * 40 + 5 && box[1].GetY1() + 5 >= point[n_target][0] * 40 && box[1].GetY1() <= point[n_target][0] * 40 + 5) {
				box[1].ChangeBitmap(1);
				win_status[1] = 1;
				flag2 = 1;
			}
			else if (flag2 == 0) { box[1].ChangeBitmap(2); }
			if (box[2].GetX1() + 5 >= point[n_target][1] * 40 && box[2].GetX1() <= point[n_target][1] * 40 + 5 && box[2].GetY1() + 5 >= point[n_target][0] * 40 && box[2].GetY1() <= point[n_target][0] * 40 + 5) {
				box[2].ChangeBitmap(1);
				win_status[2] = 1;
				flag3 = 1;
			}
			else if (flag3 == 0) { box[2].ChangeBitmap(2); }

		}
		int num_hid_box = 0;
		for (int i = 0; i < 3; i++) {
			if (point[i][0] == 10000) {
				num_hid_box += 1;
			}
		}
		int num_win_status = 0;
		for (int j = 0; j < 3; j++) {
			if (win_status[j] == 1) {
				num_win_status += 1;
			}
		}
		if (num_hid_box + num_win_status == 3) {
			if (lev <= 20) {
				lev += 1;
				GotoGameState(GAME_STATE_NEXT);
			}
			if (lev == 21 || lev == 22) {
				//victory
				GotoGameState(GAME_STATE_OVER);
			}
		}
		fg.ShowBitmap();
	}

	CGameStateNextLevel::CGameStateNextLevel(CGame* g)
		: CGameState(g)
	{
	}
	void CGameStateNextLevel::OnBeginState() {
	}
	void CGameStateNextLevel::OnInit() {
		n_levels.LoadBitmap(NEXT_LV);
		n_levels.SetTopLeft(0, 0);
		//system("type nul > level.txt");


	}
	void CGameStateNextLevel::OnShow() {
		n_levels.ShowBitmap();

	}
	void CGameStateNextLevel::OnLButtonDown(UINT nFlags, CPoint point){
		GotoGameState(GAME_STATE_RUN);

	}
}