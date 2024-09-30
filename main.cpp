#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cassert>

#include "TextureConverter/TextureConverter.h"
#include <winerror.h>
#include <combaseapi.h>



//コマンドライン引数
enum Argument {
	//アプリケーションのパス
	ApplicationPath,
	//渡されたファイルのパス
	FilPath,

	ArgumentNumber,
};


//ここに入っているargc,argvをコマンドライン引数と呼ぶ
int main(int argc,char*argv[]) {

	//2以上になることは基本無いよ
	assert(argc >= ArgumentNumber);


	//COMライブラリの初期化
	HRESULT hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
	assert(SUCCEEDED(hr));

	//テクスチャコンバーターのインスタンスを生成
	TextureConverter textureConverter;

	//変換を行う
	textureConverter.ConvertTextureWICToDDS(argv[FilPath]);


	for (int i = 0; i < argc; i++) {
		//文字列argvのi番を表示
		std::cout << argv[i] << std::endl;
	}

	//COMライブラリの終了
	CoUninitialize();

	//リターンする前にpauseを入れると良いよ！
	//ログの確認がしやすいから
	system("pause");
	return 0;
}