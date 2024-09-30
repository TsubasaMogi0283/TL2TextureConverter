#pragma once
#include <string>
#include <DirectXTex.h>


class TextureConverter{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	TextureConverter() = default;

	/// <summary>
	/// �e�N�X�`����WIC����DDS�ɕϊ�����
	/// </summary>
	/// <param name="filePath"></param>
	void ConvertTextureWICToDDS(const std::string& filePath);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~TextureConverter() = default;


private:

	/// <summary>
	/// �e�N�X�`���t�@�C���̓ǂݍ���
	/// </summary>
	/// <param name="filePath"></param>
	void LoadWICTextureFromFile(const std::string& filePath);


	/// <summary>
	/// �}���`�o�C�g����������C�h������ɕϊ�
	/// </summary>
	/// <param name="string"></param>
	/// <returns></returns>
	static std::wstring ConvertMultiByteStringToWideString(const std::string& string);


private:
	//�摜�̏��
	DirectX::TexMetadata metadata_;

	//�摜�C���[�W�̃R���e�i
	DirectX::ScratchImage scratchImage_;


};

