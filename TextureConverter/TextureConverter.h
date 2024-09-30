#pragma once
#include <string>
#include <DirectXTex.h>


class TextureConverter{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	TextureConverter() = default;

	/// <summary>
	/// テクスチャをWICからDDSに変換する
	/// </summary>
	/// <param name="filePath"></param>
	void ConvertTextureWICToDDS(const std::string& filePath);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~TextureConverter() = default;


private:

	/// <summary>
	/// テクスチャファイルの読み込み
	/// </summary>
	/// <param name="filePath"></param>
	void LoadWICTextureFromFile(const std::string& filePath);


	/// <summary>
	/// マルチバイト文字列をワイド文字列に変換
	/// </summary>
	/// <param name="string"></param>
	/// <returns></returns>
	static std::wstring ConvertMultiByteStringToWideString(const std::string& string);


private:
	//画像の情報
	DirectX::TexMetadata metadata_;

	//画像イメージのコンテナ
	DirectX::ScratchImage scratchImage_;


};

