#include <cstdio>
#include <cstdlib>
#include <iostream>

//ここに入っているargc,argvをコマンドライン引数と呼ぶ
int main(int argc,char*argv[]) {

	for (int i = 0; i < argc; i++) {
		//文字列argvのi番を表示
		std::cout << argv[i] << std::endl;
	}

	//リターンする前にpauseを入れると良いよ！
	//ログの確認がしやすいから
	system("pause");
	return 0;
}