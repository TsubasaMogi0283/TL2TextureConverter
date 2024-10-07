#include "TextureConverter.h"

#include <dxgidebug.h>
#include <dxcapi.h>


void TextureConverter::ConvertTextureWICToDDS(const std::string& filePath){

	//1.�e�N�X�`���t�@�C����ǂݍ���
	LoadWICTextureFromFile(filePath);

	//2.DDS�`���ɕϊ����ď����o��
	SaveDDSTextureToFile();

}

void TextureConverter::LoadWICTextureFromFile(const std::string& filePath){


	//1.�t�@�C���p�X�����C�h������ɕϊ�
	std::wstring wideFilepath = ConvertMultiByteStringToWideString(filePath);

	//2.�e�N�X�`����ǂݍ���
	//WIC�e�N�X�`���̃��[�h
	HRESULT hr = DirectX::LoadFromWICFile(wideFilepath.c_str(), DirectX::WIC_FLAGS::WIC_FLAGS_NONE, &metadata_, scratchImage_);
	assert(SUCCEEDED(hr));

	//�t�H���_�p�X�ƃt�@�C�����𕪗�����
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


	//�u.�v���o�Ă���Ō�̕�����T��
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



	//�u/�v���o�Ă���Ō�̕�����T��
	pointPosition = exceptExt.rfind('/');
	if (pointPosition != std::wstring::npos) {
		//��؂蕶���̑O�܂ł��f�B���N�g���p�X�Ƃ��ĕۑ�
		directoryPath_ = exceptExt.substr(0, pointPosition + 1);
		//��؂蕶���̑O�܂ł𔲂��o��
		fileName_ = exceptExt.substr(pointPosition + 1, exceptExt.size() - pointPosition - 1);
		return;
	}

	//��؂蕶�����Ȃ��̂Ńt�@�C�����݂̂Ƃ��Ĉ���
	directoryPath_ = L"";
	fileName_ = exceptExt;

}

void TextureConverter::SaveDDSTextureToFile(){

	//DirectX::ScratchImage mipChain;
	////�~�b�v�}�b�v�̐���
	//HRESULT hResult = DirectX::GenerateMipMaps(
	//	scratchImage_.GetImages(), scratchImage_.GetImageCount(), scratchImage_.GetMetadata(), DirectX::TEX_FILTER_DEFAULT, 0, mipChain);
	//if (SUCCEEDED(hResult)) {
	//	//�C���[�W�ƃ��^�f�[�^���~�b�v�}�b�v�Œu��������
	//	//�ȉ��̂悤�ɃR�s�[���֎~����Ă���̂�move��
	//	//ScratchImage(const ScratchImage&) = delete;
	//	//ScratchImage& operator=(const ScratchImage&) = delete;
	//	scratchImage_ = std::move(mipChain);
	//	metadata_ = scratchImage_.GetMetadata();
	//}


	//���k�`���ɕϊ�
	DirectX::ScratchImage converted;
	HRESULT hResult = DirectX::Compress(
		scratchImage_.GetImages(), scratchImage_.GetImageCount(), metadata_,DXGI_FORMAT_BC7_UNORM_SRGB,
		DirectX::TEX_COMPRESS_BC7_QUICK|DirectX::TEX_COMPRESS_SRGB_OUT|DirectX::TEX_COMPRESS_PARALLEL,1.0f,converted);
	if (SUCCEEDED(hResult)) {
		scratchImage_ = std::move(converted);
		metadata_ = scratchImage_.GetMetadata();
	}


	//�t�H�[�}�b�g�̕ϊ�
	//���g�͂�����switch���ŏ��������Ă��邾��������
	metadata_.format = DirectX::MakeSRGB(metadata_.format);

	//�o�̓t�@�C������ݒ肷��
	std::wstring filePath = directoryPath_ + fileName_ + L".dds";
	
	//DDS�t�@�C���̏����o��
	hResult =DirectX::SaveToDDSFile(
		scratchImage_.GetImages(),scratchImage_.GetImageCount(),metadata_, DirectX::DDS_FLAGS_NONE,filePath.c_str());
	assert(SUCCEEDED(hResult));
}
