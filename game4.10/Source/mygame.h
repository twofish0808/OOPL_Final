/*
 * mygame.h: ���ɮ��x�C��������class��interface
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
 *	 2004-03-02 V4.0
 *      1. Add CGameStateInit, CGameStateRun, and CGameStateOver to
 *         demonstrate the use of states.
 *   2005-09-13
 *      Rewrite the codes for CBall and CEraser.
 *   2005-09-20 V4.2Beta1.
 *   2005-09-29 V4.2Beta2.
 *   2006-02-08 V4.2
 *      1. Rename OnInitialUpdate() -> OnInit().
 *      2. Replace AUDIO_CANYON as AUDIO_NTUT.
 *      3. Add help bitmap to CGameStateRun.
 *   2006-09-09 V4.3
 *      1. Rename Move() and Show() as OnMove and OnShow() to emphasize that they are
 *         event driven.
 *   2008-02-15 V4.4
 *      1. Add namespace game_framework.
 *      2. Replace the demonstration of animation as a new bouncing ball.
 *      3. Use ShowInitProgress(percent) to display loading progress.
*/

#include "CEraser.h"
#include "CBall.h"
#include "CBouncingBall.h"
#include "Box.h"
#include <fstream>

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// Constants
	/////////////////////////////////////////////////////////////////////////////

	enum AUDIO_ID {				// �w�q�U�ح��Ī��s��
		AUDIO_DING,				// 0
		AUDIO_LAKE,				// 1
		AUDIO_NTUT				// 2
	};

	/////////////////////////////////////////////////////////////////////////////
	// �o��class���C�����C���}�Y�e������
	// �C��Member function��Implementation���n����
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateInit : public CGameState {
	public:
		CGameStateInit(CGame *g);
		void OnInit();  								// �C������Ȥιϧγ]�w
		void OnBeginState();							// �]�w�C�������һݪ��ܼ�
		void OnKeyUp(UINT, UINT, UINT); 				// �B�z��LUp���ʧ@
		void OnLButtonDown(UINT nFlags, CPoint point);  // �B�z�ƹ����ʧ@
	protected:
		void OnShow();									// ��ܳo�Ӫ��A���C���e��
	private:
		CMovingBitmap logo;								// csie��logo
		int audio_enable;
	};
	class CGameStateAbout : public CGameState {
	public:
		CGameStateAbout(CGame* g);
		void OnInit();  								// �C������Ȥιϧγ]�w
		void OnBeginState();							// �]�w�C�������һݪ��ܼ�
		void OnLButtonDown(UINT nFlags, CPoint point);  // �B�z�ƹ����ʧ@
	protected:
		void OnShow();									// ��ܳo�Ӫ��A���C���e��
	private:
		CMovingBitmap about;								// csie��logo
		int audio_enable;
	};

	/////////////////////////////////////////////////////////////////////////////
	// �o��class���C�����C�����檫��A�D�n���C���{�����b�o��
	// �C��Member function��Implementation���n����
	/////////////////////////////////////////////////////////////////////////////
	class CGameStateLevel : public CGameState {
	public:
		CGameStateLevel(CGame* g);
		void OnInit();
		void OnLButtonDown(UINT nFlags, CPoint point);
		//void OnRButtonDown(UINT nFlags, CPoint point);
		/*void OnBeginState();
		 
		void OnMouseMove(UINT nFlags, CPoint point);	
		  
		void OnRButtonUp(UINT nFlags, CPoint point);						
		void OnEndState();								
		void OnLButtonDblClk(UINT nFlags, CPoint point);  
		void OnRButtonDblClk(UINT nFlags, CPoint point); 
		void OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);  
		void OnMouseHWheel(UINT nFlags, short zDelta, CPoint pt);  */
	protected:								
		void OnShow();
	private:
		CMovingBitmap levels;
		const char* filename = "../level.txt";
		FILE* open_file;

	};

	class CGameStateRun : public CGameState {
	public:
		CGameStateRun(CGame *g);
		~CGameStateRun();
		void OnBeginState();							// �]�w�C�������һݪ��ܼ�
		void OnInit();  								// �C������Ȥιϧγ]�w
		void OnKeyDown(UINT, UINT, UINT);
		void OnKeyUp(UINT, UINT, UINT);
		void OnLButtonDown(UINT nFlags, CPoint point);  // �B�z�ƹ����ʧ@
		void OnLButtonUp(UINT nFlags, CPoint point);	// �B�z�ƹ����ʧ@
		void OnMouseMove(UINT nFlags, CPoint point);	// �B�z�ƹ����ʧ@ 
		void OnRButtonDown(UINT nFlags, CPoint point);  // �B�z�ƹ����ʧ@
		void OnRButtonUp(UINT nFlags, CPoint point);	// �B�z�ƹ����ʧ@
	protected:
		void OnMove();									// ���ʹC������
		void OnShow();									// ��ܳo�Ӫ��A���C���e��
	private:
		const int		NUMBALLS;	// �y���`��
		CMovingBitmap	background;	// �I����
		CMovingBitmap	help;		// ������
		CBall			*ball;		// �y���}�C
		CEnd* ends;
		CMovingBitmap	corner;		// ������
		CEraser			eraser;		// ��l
		Box				*box;
		CInteger		hits_left;	// �ѤU��������
		CBouncingBall   bball;		// ���мu�����y
		CMovingBitmap   boxkid_map;
		CMovingBitmap fg;
		int  music_is_on;
		int level;
		int mapArray[22][12][9] = { {
{0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 1, 1, 1, 1, 1, 1, 1, 0},
{0, 1, 2, 2, 4, 2, 5, 1, 0},
{0, 1, 2, 2, 1, 1, 1, 1, 0},
{0, 1, 2, 3, 1, 0, 0, 0, 0},
{0, 1, 1, 1, 1, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0}
 } ,

{{0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0},
{0,1,1,1,1,1,1,1,0},
{0,1,2,2,3,2,2,1,0},
{0,1,2,2,2,2,2,1,0},
{0,1,2,2,2,4,5,1,0},
{0,1,2,2,2,2,2,1,0},
{0,1,1,1,1,1,1,1,0},
{0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0}},

{{0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0},
{0,0,0,1,1,1,1,1,0},
{0,1,1,1,5,4,2,1,0},
{0,1,2,2,2,2,2,1,0},
{0,1,2,2,2,2,2,1,0},
{0,1,2,2,4,5,2,1,0},
{0,1,3,2,2,1,1,1,0},
{0,1,1,1,1,1,0,0,0},
{0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0}},


{{0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,1,1,1,1},
{0,1,1,1,0,1,5,2,1},
{0,1,3,1,1,1,2,2,1},
{1,1,2,2,2,2,2,2,1},
{1,5,2,2,4,2,4,1,1},
{1,2,2,2,2,2,2,1,0},
{1,1,1,1,1,1,1,1,0},
{0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0}},


{{0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0},
{0,0,0,1,1,1,1,0,0},
{0,1,1,1,2,2,1,0,0},
{0,1,3,2,5,4,1,1,0},
{0,1,2,2,2,4,2,1,0},
{0,1,2,1,5,2,2,1,0},
{0,1,2,2,2,2,2,1,0},
{0,1,1,1,1,1,1,1,0},
{0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0}},



{{0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0},
{0,0,1,1,1,1,1,0,0},
{0,1,1,3,2,2,1,1,0},
{0,1,2,2,1,2,2,1,0},
{0,1,2,4,6,4,2,1,0},
{0,1,2,2,5,2,2,1,0},
{0,1,1,2,5,2,1,1,0},
{0,0,1,1,1,1,1,0,0},
{0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0}},


{{0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0},
{0,1,1,1,1,1,1,0,0},
{0,1,2,2,2,2,1,1,1},
{0,1,2,2,2,5,5,2,1},
{0,1,2,4,4,4,3,2,1},
{0,1,2,2,1,2,5,2,1},
{0,1,1,1,1,1,1,1,1},
{0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0}},



{{0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0},
{0,0,1,1,1,1,1,0,0},
{0,1,1,5,2,2,1,1,1},
{0,1,2,2,1,2,4,3,1},
{0,1,2,2,1,2,1,2,1},
{0,1,2,6,2,2,4,5,1},
{0,1,2,2,2,2,1,1,1},
{0,1,1,1,1,1,1,0,0},
{0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0}},


{ {0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0},
{0,1,1,1,1,1,1,0,0},
{0,1,2,6,2,2,1,1,0},
{0,1,2,4,1,2,2,1,0},
{0,1,2,4,2,5,2,1,0},
{0,1,5,2,2,2,1,1,0},
{0,1,1,1,1,1,1,0,0},
{0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0} },

{ {0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0},
{0,1,1,1,1,1,1,0,0},
{1,1,2,2,2,2,1,1,0},
{1,2,5,5,2,2,2,1,0},
{1,2,1,2,4,4,4,1,0},
{1,2,2,2,1,3,5,1,0},
{1,1,1,1,1,1,1,1,0},
{0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0} },

{ {0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0},
{0,1,1,1,1,1,1,0,0},
{0,1,5,3,6,2,1,1,0},
{0,1,4,2,2,4,2,1,0},
{0,1,2,2,2,1,2,1,0},
{0,1,2,2,5,2,2,1,0},
{0,1,1,1,1,1,1,1,0},
{0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0} },


{ {0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0},
{0,1,1,1,1,1,1,0,0},
{0,1,3,2,5,5,1,0,0},
{0,1,2,1,4,2,1,1,0},
{0,1,2,1,2,2,2,1,0},
{0,1,2,2,4,1,2,1,0},
{0,1,2,2,6,2,2,1,0},
{0,1,1,1,1,1,1,1,0},
{0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0} },


{ {0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0},
{0,1,1,1,1,1,0,0,0},
{0,1,2,2,2,1,0,0,0},
{0,1,2,1,2,1,1,1,0},
{0,1,6,5,4,2,2,1,0},
{0,1,2,2,1,4,2,1,0},
{0,1,3,2,2,2,5,1,0},
{0,1,1,1,1,1,1,1,0},
{0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0} },



{ {0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0},
{0,0,0,1,1,1,1,1,0},
{0,1,1,1,2,2,3,1,0},
{0,1,5,2,6,1,2,1,0},
{0,1,2,2,2,4,2,1,0},
{0,1,2,4,5,2,1,1,0},
{0,1,1,1,1,1,1,0,0},
{0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0} },


{ {0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0},
{1,1,1,1,1,1,1,0,0},
{1,3,2,2,2,2,1,1,0},
{1,2,5,4,6,2,2,1,1},
{1,2,1,4,5,2,2,2,1},
{1,2,2,2,2,2,2,2,1},
{1,1,1,1,1,1,1,1,1},
{0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0} },


{ {0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0},
{0,1,1,1,1,1,1,0,0},
{0,1,2,2,5,2,1,0,0},
{0,1,2,1,5,2,1,1,0},
{0,1,2,2,5,2,2,1,0},
{0,1,2,4,4,4,2,1,0},
{0,1,2,2,1,2,3,1,0},
{0,1,1,1,1,1,1,1,0},
{0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0} },


{ {0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0},
{0,1,1,1,1,0,0,0,0},
{0,1,2,2,1,1,1,1,0},
{0,1,2,2,2,6,5,1,0},
{0,1,2,2,4,1,2,1,0},
{0,1,2,2,5,4,3,1,0},
{0,1,1,1,1,1,1,1,0},
{0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0} },


{ {0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0},
{0,1,1,1,1,1,1,1,0},
{0,1,2,2,5,2,2,1,1},
{0,1,2,4,4,1,5,2,1},
{0,1,2,1,3,4,2,2,1},
{0,1,2,2,5,1,2,2,1},
{0,1,1,1,1,1,1,1,1},
{0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0} },



{ {0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0},
{0,1,1,1,1,1,1,0,0},
{0,1,3,2,2,2,1,1,0},
{0,1,2,4,4,4,2,1,0},
{0,1,1,2,5,5,5,1,0},
{0,1,2,2,2,1,2,1,0},
{0,1,2,2,2,2,2,1,0},
{0,1,1,1,1,1,1,1,0},
{0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0} },


{ {0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0},
{0,1,1,1,1,0,0,0,0},
{0,1,2,2,1,0,0,0,0},
{0,1,2,2,1,1,0,0,0},
{0,1,2,2,2,1,1,0,0},
{0,1,4,2,4,3,1,1,0},
{0,1,5,2,1,4,2,1,0},
{0,1,2,2,5,2,5,1,0},
{0,1,1,1,1,1,1,1,0},
{0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0} },


{ {0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0},
{0,1,1,1,1,1,1,0,0},
{0,1,2,2,2,5,1,0,0},
{0,1,4,4,4,3,1,0,0},
{0,1,5,2,1,2,1,0,0},
{0,1,2,2,5,2,1,0,0},
{0,1,1,1,1,1,1,0,0},
{0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0} },


{ {0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0},
{0,1,1,1,1,1,1,0,0},
{0,1,2,2,2,6,1,0,0},
{0,1,2,2,2,2,1,0,0},
{0,1,6,2,1,2,1,0,0},
{0,1,3,4,5,2,1,0,0},
{0,1,1,1,1,1,1,0,0},
{0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0} }


		};
	};

	/////////////////////////////////////////////////////////////////////////////
	// �o��class���C�����������A(Game Over)
	// �C��Member function��Implementation���n����
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateOver : public CGameState {
	public:
		CGameStateOver(CGame *g);
		void OnBeginState();							// �]�w�C�������һݪ��ܼ�
		void OnInit();
		void OnLButtonDown(UINT nFlags, CPoint point);
	protected:								// ���ʹC������
		void OnShow();									// ��ܳo�Ӫ��A���C���e��
	private:
		int counter;	// �˼Ƥ��p�ƾ�
		CMovingBitmap victory;
	};


	class CGameStateReset : public CGameState {
	public:
		CGameStateReset(CGame* g);
		void OnInit();
		void OnBeginState();
	protected:
		void OnShow();
	private:
		CMovingBitmap levels;
		

	}; 
	class CGameStateNextLevel : public CGameState {
	public:
		CGameStateNextLevel(CGame* g);
		void OnInit();
		void OnBeginState();
		void OnLButtonDown(UINT nFlags, CPoint point);
	protected:
		void OnShow();
	private:
		CMovingBitmap n_levels;


	};

}