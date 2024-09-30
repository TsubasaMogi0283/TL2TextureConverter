#include "TextureConverter.h"

#include <dxgidebug.h>
#include <dxcapi.h>



void TextureConverter::ConvertTextureWICToDDS(const std::string& filePath){

	//1.�e�N�X�`���t�@�C����ǂݍ���
	LoadWICTextureFromFile(filePath);

	//2.DDS�`���ɕϊ����ď����o��


}

void TextureConverter::LoadWICTextureFromFile(const std::string& filePath){


	//1.�t�@�C���p�X�����C�h������ɕϊ�
	std::wstring wideFilepath = ConvertMultiByteStringToWideString(filePath);

	//2.�e�N�X�`����ǂݍ���
	//WIC�e�N�X�`���̃��[�h
	HRESULT hr = DirectX::LoadFromWICFile(wideFilepath.c_str(), DirectX::WIC_FLAGS::WIC_FLAGS_NONE, &metadata_, scratchImage_);
	assert(SUCCEEDED(hr));

}

std::wstring TextureConverter::ConvertMultiByteStringToWideString(const std::string& string){

	if (string.empty())
	{
		return std::wstring();
	}

	int sizeNeeded = MultiByteToWideChar(CP_UTF8, 0, reinterpret_cast<const char*>(&string[0]), static_cast<int>(string.size()), NULL, 0);
	if (sizeNeeded == 0)
	{
		return std::wstring();
	}
	std::wstring result(sizeNeeded, 0);
	MultiByteToWideChar(CP_UTF8, 0, reinterpret_cast<const char*>(&string[0]), static_cast<int>(string.size()), &result[0], sizeNeeded);
	return result;
}

void TextureConverter::SeparateFilePath(const std::wstring& filePath){
	size_t pointPosition;
	std::wstring exceptExt;


	//�u.�v���o�ăL���Ō�̕�����T��
	pointPosition = filePath.rfind('.');
	if (pointPosition != std::wstring::npos) {
		//��؂蕶���̌����t�@�C���g���q�Ƃ��ĕۑ�
		fileExt_ = filePath.substr(pointPosition + 1, filePath.size() - pointPosition - 1);
		//��؂蕶���̑O�܂ł𔲂��o��
		exceptExt = filePath.substr(0, pointPosition);
	}
	else {
		fileExt_ = L"";
		exceptExt = filePath;
	}


	//�u\\�v���o�Ă���Ō�̕�����T��
	pointPosition = exceptExt.rfind('\\');
	if (pointPosition != std::wstring::npos) {
		//��؂蕶���̑O�܂ł��f�B���N�g���p�X�Ƃ��ĕۑ�
		directoryPath_ = exceptExt.substr(0, pointPosition + 1);
		//��؂蕶���̑O�܂ł𔲂��o��
		fileName_ = exceptExt.substr(pointPosition + 1, exceptExt.size() - pointPosition - 1);
		return;
	}



	//��؂蕶���u/�v���o�Ă���Ō�̕�����T��
	pointPosition = exceptExt.rfind('/');
	if (pointPosition != std::wstring::npos) {

	}

}
