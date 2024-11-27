#include <Novice.h>
#include <SceneManager.h>
#include <ResouresManager.h>

const char kWindowTitle[] = "5202_ヨケレール";

SceneManager sceneManager;
ResouresManager resouresManager;//画像と音声を管理
Camera mainCamera;

int windowHeight = 720;
int windowWidth = 1280;
float deltaTime = 1.0f / 60.0f;


//レティクル
int aimPosX = 0;
int aimPosY = 0;
int aimLength = 6;


// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, windowWidth, windowHeight);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	resouresManager.loadResoures();//画像と音声を読み込む

	sceneManager.init();

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///
		Novice::SetMouseCursorVisibility(0);
		Novice::GetMousePosition(&aimPosX, &aimPosY);
		sceneManager.onInput(keys, preKeys);
		sceneManager.update();
		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		sceneManager.draw(mainCamera);

		// レティクル 
		
		Novice::DrawBox(aimPosX - aimLength, aimPosY, aimLength, 2, 0.0f, 0xff0000ff, kFillModeSolid);
		Novice::DrawBox(aimPosX + aimLength, aimPosY, aimLength, 2, 0.0f, 0xff0000ff, kFillModeSolid);
		Novice::DrawBox(aimPosX + 2, aimPosY + aimLength - 2, 2, aimLength, 0.0f, 0xff0000ff, kFillModeSolid);
		Novice::DrawBox(aimPosX + 2, aimPosY - aimLength - 2, 2, aimLength, 0.0f, 0xff0000ff, kFillModeSolid);

		
		
		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}

