#include "TextureConverter.h"

#include <dxgidebug.h>
#include <dxcapi.h>



void TextureConverter::ConvertTextureWICToDDS(const std::string& filePath){

	//1.テクスチャファイルを読み込む
	LoadWICTextureFromFile(filePath);

	//2.DDS形式に変換して書き出す


}

void TextureConverter::LoadWICTextureFromFile(const std::string& filePath){


	//1.ファイルパスをワイド文字列に変換
	std::wstring wideFilepath = ConvertMultiByteStringToWideString(filePath);

	//2.テクスチャを読み込む
	//WICテクスチャのロード
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
