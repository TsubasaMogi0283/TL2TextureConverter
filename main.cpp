#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cassert>

#include "TextureConverter/TextureConverter.h"
#include <winerror.h>
#include <combaseapi.h>



//�R�}���h���C������
enum Argument {
	//�A�v���P�[�V�����̃p�X
	ApplicationPath,
	//�n���ꂽ�t�@�C���̃p�X
	FilPath,


	//�Ō�ɂ���������Ă����Ɨv�f���������ɕ������I
	//�����Ă����ƕ֗��I�I
	ArgumentNumber,
};


//�����ɓ����Ă���argc,argv���R�}���h���C�������ƌĂ�
int main(int argc,char*argv[]) {

	//2�ȏ�ɂȂ邱�Ƃ͊�{������
	assert(argc >= ArgumentNumber);


	//COM���C�u�����̏�����
	HRESULT hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
	assert(SUCCEEDED(hr));

	//�e�N�X�`���R���o�[�^�[�̃C���X�^���X�𐶐�
	TextureConverter textureConverter;

	//�ϊ����s��
	textureConverter.ConvertTextureWICToDDS(argv[FilPath]);


	for (int i = 0; i < argc; i++) {
		//������argv��i�Ԃ�\��
		std::cout << argv[i] << std::endl;
	}

	//COM���C�u�����̏I��
	CoUninitialize();

	

	
	return 0;
}