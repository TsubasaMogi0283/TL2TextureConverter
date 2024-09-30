#include "TextureConverter.h"
#include <stringapiset.h>

void TextureConverter::ConvertTextureWICToDDS(const std::string& filePath){

	//1.�e�N�X�`���t�@�C����ǂݍ���
	LoadWICTextureFromFile(filePath);

	//2.DDS�`���ɕϊ����ď����o��


}

void TextureConverter::LoadWICTextureFromFile(const std::string& filePath){

	//1.�t�@�C���p�X�����C�h������ɕϊ�


	//2.�e�N�X�`����ǂݍ���


}

std::wstring TextureConverter::ConvertMultiByteStringToWideString(const std::string& string){

	if (string.empty())
	{
		return std::wstring();
	}

	auto sizeNeeded = MultiByteToWideChar(CP_UTF8, 0, reinterpret_cast<const char*>(&string[0]), static_cast<int>(string.size()), NULL, 0);
	if (sizeNeeded == 0)
	{
		return std::wstring();
	}
	std::wstring result(sizeNeeded, 0);
	MultiByteToWideChar(CP_UTF8, 0, reinterpret_cast<const char*>(&string[0]), static_cast<int>(string.size()), &result[0], sizeNeeded);
	return result;
}
