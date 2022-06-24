
namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// 這個class提供可以用鍵盤或滑鼠控制的擦子
	// 看懂就可以改寫成自己的程式了
	/////////////////////////////////////////////////////////////////////////////

	class CEraser
	{
	public:
		CEraser();
		int  GetX1();					// 擦子左上角 x 座標
		int  GetY1();					// 擦子左上角 y 座標
		int  GetX2();					// 擦子右下角 x 座標
		int  GetY2();					// 擦子右下角 y 座標
		void Initialize();				// 設定擦子為初始值
		void LoadBitmap();				// 載入圖形
		void Collision(bool HitEraser);				// 圖形碰撞牆壁觸發
		int xy[2][2];
		int find[2]; //當找地圖array時 回傳需要的index
		void findIndex(int type);
		vector<vector<int> >position;				// 記錄之前位置
		void UpdateXYArray();
		void OnMove();					// 移動擦子
		void OnShow();					// 將擦子圖形貼到畫面
		void SetMovingDown(bool flag);	// 設定是否正在往下移動
		void SetMovingLeft(bool flag);	// 設定是否正在往左移動
		void SetMovingRight(bool flag); // 設定是否正在往右移動
		void SetMovingUp(bool flag);	// 設定是否正在往上移動
		void SetMovingNow(bool isMovingDown);
		void SetXY(int nx, int ny);		// 設定擦子左上角座標

		void ArrayToXY(int m, int n);   //mygame.cpp array座標轉XY座標
		void UpdateArray();
		bool isCollision(string direction);
		bool isMatchPoint();			// 是否已經到達所要到達的點
		bool isMovingNow;
		void setPushingBoxDirection(int box_x, int box_y);
		bool isPushingBox(int box_x, int box_y);
		string isNearBox(int box_x, int box_y);
		string PushingBoxDirection;
		bool canPushBoxUp;
		bool canPushBoxDown;
		bool canPushBoxLeft;
		bool canPushBoxRight;
		int myArray[12][9] = {
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
		};
		
	protected:

		CAnimation animation;		// 擦子的動畫
		int x, y;					// 擦子左上角座標
		int target_x, target_y;
		bool isMovingDown;			// 是否正在往下移動
		bool isMovingLeft;			// 是否正在往左移動
		bool isMovingRight;			// 是否正在往右移動
		bool isMovingUp;			// 是否正在往上移動
		int eraser_level = 0;
	private:
		int map[22][12][9] = { {
{0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 1, 1, 1, 1, 1, 1, 1, 0},
{0, 1, 2, 2, 2, 2, 2, 1, 0},
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
{0,1,2,2,2,3,1,0,0},
{0,1,6,2,1,2,1,0,0},
{0,1,2,4,5,2,1,0,0},
{0,1,1,1,1,1,1,0,0},
{0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0} }


		};
	};
}