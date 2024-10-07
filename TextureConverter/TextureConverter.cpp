#include "TextureConverter.h"

#include <dxgidebug.h>
#include <dxcapi.h>


void TextureConverter::ConvertTextureWICToDDS(const std::string& filePath){

	//1.テクスチャファイルを読み込む
	LoadWICTextureFromFile(filePath);

	//2.DDS形式に変換して書き出す
	SaveDDSTextureToFile();

}

void TextureConverter::LoadWICTextureFromFile(const std::string& filePath){


	//1.ファイルパスをワイド文字列に変換
	std::wstring wideFilepath = ConvertMultiByteStringToWideString(filePath);

	//2.テクスチャを読み込む
	//WICテクスチャのロード
	HRESULT hr = DirectX::LoadFromWICFile(wideFilepath.c_str(), DirectX::WIC_FLAGS::WIC_FLAGS_NONE, &metadata_, scratchImage_);
	assert(SUCCEEDED(hr));

	//フォルダパスとファイル名を分離する
	SeparateFilePath(wideFilepath);

	

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


	//「.」が出てくる最後の部分を探す
	pointPosition = filePath.rfind('.');
	if (pointPosition != std::wstring::npos) {
		//区切り文字の後ろをファイル拡張子として保存
		fileExt_ = filePath.substr(pointPosition + 1, filePath.size() - pointPosition - 1);
		//区切り文字の前までを抜き出す
		exceptExt = filePath.substr(0, pointPosition);
	}
	else {
		fileExt_ = L"";
		exceptExt = filePath;
	}


	//「\\」が出てくる最後の部分を探す
	pointPosition = exceptExt.rfind('\\');
	if (pointPosition != std::wstring::npos) {
		//区切り文字の前までをディレクトリパスとして保存
		directoryPath_ = exceptExt.substr(0, pointPosition + 1);
		//区切り文字の前までを抜き出す
		fileName_ = exceptExt.substr(pointPosition + 1, exceptExt.size() - pointPosition - 1);
		return;
	}



	//「/」が出てくる最後の部分を探す
	pointPosition = exceptExt.rfind('/');
	if (pointPosition != std::wstring::npos) {
		//区切り文字の前までをディレクトリパスとして保存
		directoryPath_ = exceptExt.substr(0, pointPosition + 1);
		//区切り文字の前までを抜き出す
		fileName_ = exceptExt.substr(pointPosition + 1, exceptExt.size() - pointPosition - 1);
		return;
	}

	//区切り文字がないのでファイル名のみとして扱う
	directoryPath_ = L"";
	fileName_ = exceptExt;

}

void TextureConverter::SaveDDSTextureToFile(){
	//フォーマットの変換
	//中身はただのswitch文で書き換えているだけだった
	metadata_.format = DirectX::MakeSRGB(metadata_.format);

	//出力ファイル名を設定する
	std::wstring filePath = directoryPath_ + fileName_ + L".dds";
	
	//DDSファイルの書き出し
	HRESULT hResult =DirectX::SaveToDDSFile(
		scratchImage_.GetImages(),scratchImage_.GetImageCount(),metadata_, DirectX::DDS_FLAGS_NONE,filePath.c_str());
	assert(SUCCEEDED(hResult));
}
