===================C++踩地雷說明============================
1. 先根據提示輸入一正整數n>1，以開始一n*n之踩地雷遊戲
2. 根據提示輸入一正整數來決定地雷數量，地雷數量不得<1，也不得>=n*n
3. 顯示之地雷圖如下(圖例為10*10之圖):   
 
	*號為地雷圖邊框

	空白為未踩地區

     1 2 3 4 5 6 7 8 9 101112
   * * * * * * * * * * * * * *
 1 *                         *
 2 *                         *
 3 *                         *
 4 *                         *
 5 *                         *
 6 *                         *
 7 *                         *
 8 *                         *
 9 *                         *
10 *                         *
11 *                         *
12 *                         *
   * * * * * * * * * * * * * *
4.依序輸入row、column進行踩地雷動作(如圖):
	依序輸入2、2
     1 2 3 4 5 6 7 8 9 101112
   * * * * * * * * * * * * * *
 1 * 0 0 1                   *
 2 * 0 0 1                   *
 3 * 1 1 2                   *
 4 *                         *
 5 *                         *
 6 *                         *
 7 *                         *
 8 *                         *
 9 *                         *
10 *                         *
11 *                         *
12 *                         *
   * * * * * * * * * * * * * *
5. 如果沒有安全的未踩地區或踩中地雷，則遊戲結束，顯示整張圖:
	$為地雷
     1 2 3 4 5 6 7 8 9 101112
   * * * * * * * * * * * * * *
 1 * 0 0 1 1 1 0 0 0 0 0 0 0 *
 2 * 0 0 1 $ 1 0 0 0 0 0 0 0 *
 3 * 1 1 2 1 1 0 0 0 0 0 0 0 *
 4 * 1 $ 1 0 0 0 1 1 1 0 0 0 *
 5 * 1 1 1 0 0 0 1 $ 1 0 0 0 *
 6 * 0 0 0 0 0 0 1 1 1 0 0 0 *
 7 * 0 0 0 0 0 0 0 0 0 0 0 0 *
 8 * 0 0 0 0 0 0 0 0 0 0 0 0 *
 9 * 0 0 0 0 0 0 0 0 0 0 0 0 *
10 * 0 0 0 0 0 0 0 0 1 1 1 0 *
11 * 0 1 1 1 0 0 0 0 1 $ 1 0 *
12 * 0 1 $ 1 0 0 0 0 1 1 1 0 *
   * * * * * * * * * * * * * *

