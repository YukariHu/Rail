#include <Novice.h>
#include <SceneManager.h>
#include <ResouresManager.h>

const char kWindowTitle[] = "GC1A_05_コウ_ホウケイ_タイトル";

SceneManager sceneManager;
ResouresManager resouresManager;//画像と音声を管理


// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

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
		sceneManager.onInput(keys, preKeys);
		sceneManager.update();
		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		sceneManager.draw();
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




//// ファイルの読み込み
//ReadCSV read_csv;
//std::vector<std::vector<std::string>> data = read_csv.Read("./music.csv");
//
//// 音声处理
//int audioHandle = Novice::LoadAudio("./maou_game_battle30.mp3");
//int playHandle = -1;
//
//bool isPasue = false;
//
////int times = 0;
//int tapFrame = 21;
//
////节奏点list
//std::vector<TapScript*> tapList;
//
//
////计时器
//int time = 0;
//int time2 = 0;
//
//
////Timer timer;
//
////把data里的数据转换成float
//std::vector<std::vector<float>> data_float;
//for (int i = 0; i < data.size(); i++) {
//	std::vector<float> row;
//	for (int j = 0; j < data[i].size(); j++) {
//		row.push_back(std::stof(data[i][j]));
//	}
//	data_float.push_back(row);
//}



//if (keys[DIK_SPACE] && !preKeys[DIK_SPACE])
//{
//	if (playHandle == -1 || !Novice::IsPlayingAudio(playHandle))
//	{
//		//start_time = clock();
//		playHandle = Novice::PlayAudio(audioHandle, 0, 0.2f);
//		time = 0;
//
//
//	}
//	else if (!isPasue)
//	{
//		isPasue = true;
//		Novice::PauseAudio(playHandle);
//	}
//	else
//	{
//		isPasue = false;
//		Novice::ResumeAudio(playHandle);
//	}
//}
//
//
//if (!isPasue && Novice::IsPlayingAudio(playHandle))
//{
//	time++;
//	time2++;
//	//end_time = clock();
//	//time2 = end_time - start_time;
//}
//if (time2 == tapFrame)
//{
//	time2 = 0;
//	TapScript* tap = new TapScript();
//	tapList.push_back(tap);
//
//
//}
//
//for (int i = 0; i < tapList.size(); i++)
//{
//	tapList[i]->update();
//}
//
////リズム点の削除
//for (int i = 0; i < tapList.size(); i++)
//{
//	if (tapList[i]->getIsCanRemove())
//	{
//		delete tapList[i];
//		tapList.erase(tapList.begin() + i);
//		i--;
//	}
//}



////输出data
//for (int i = 0; i < data.size(); i++) {
//	for (int j = 0; j < data[i].size(); j++) {
//		Novice::ScreenPrintf(j * 30, i * 30, "%.1f", data_float[i][j]);
//	}
//}
////输出time	
//Novice::ScreenPrintf(100, 100, "time:%d", time);
//Novice::ScreenPrintf(100, 120, "time2:%d", time2);
//Novice::ScreenPrintf(100, 150, "isPlaying:%d", Novice::IsPlayingAudio(playHandle));
//
//
////输出tapList
//for (int i = 0; i < tapList.size(); i++)
//{
//	tapList[i]->draw();
//}
//
//Novice::DrawEllipse(740, 500, 20, 20, 0.0f, RED, kFillModeSolid);
