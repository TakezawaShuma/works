#include "../stdafx.h"
#include "Data.h"
#include <iostream>

using namespace std;

void Data::ErrorState(int errorNumber)
{
	switch (errorNumber)
	{
	case 10004:
		cout << "�֐��̌Ăяo���Ɋ����݂�����܂����B" << endl; break;
	case 10013:
		cout << "�A�N�Z�X�͋��ۂ���܂����B" << endl; break;
	case 10014:
		cout << "�A�h���X������������܂���B" << endl; break;
	case 10022:
		cout << "�����Ȉ����ł��B" << endl; break;
	case 10024:
		cout << "�J���Ă���t�@�C�����������܂��B" << endl; break;
	case 10035:
		cout << "���\�[�X���ꎞ�I�ɗ��p�ł��Ȃ��Ȃ��Ă��܂��B" << endl; break;
	case 10036:
		cout << "����͌��ݎ��s���ł��B" << endl; break;
	case 10037:
		cout << "����͊��Ɏ��s���ł��B" << endl; break;
	case 10038:
		cout << "��\�P�b�g�ɑ΂��ă\�P�b�g��������݂܂����B" << endl; break;
	case 10039:
		cout << "���M��̃A�h���X���K�v�ł��B" << endl; break;
	case 10040:
		cout << "���b�Z�[�W���������܂��B" << endl; break;
	case 10041:
		cout << "�v���g�R���̎�ނ��\�P�b�g�ɑ΂��Đ���������܂���B" << endl; break;
	case 10042:
		cout << "�v���g�R���̃I�v�V����������������܂���B" << endl; break;
	case 10043:
		cout << "�v���g�R�����T�|�[�g����Ă��܂���B" << endl; break;
	case 10044:
		cout << "�T�|�[�g����Ă��Ȃ��\�P�b�g�̎�ނł��B" << endl; break;
	case 10045:
		cout << "���삪�\�P�b�g��ŃT�|�[�g����Ă��܂���B" << endl; break;
	case 10046:
		cout << "�v���g�R�� �t�@�~�����T�|�[�g����Ă��܂���B" << endl; break;
	case 10047:
		cout << "�v���g�R�� �t�@�~���̓A�h���X �t�@�~�����T�|�[�g���Ă��܂���B" << endl; break;
	case 10048:
		cout << "�A�h���X�͊��Ɏg�p���ł��B" << endl; break;
	case 10049:
		cout << "�v�����ꂽ�A�h���X�����蓖�Ă��܂���B" << endl; break;
	case 10050:
		cout << "�l�b�g���[�N���_�E�����Ă��܂��B" << endl; break;
	case 10051:
		cout << "ICMP �l�b�g���[�N�ɓ��B�ł��܂���B" << endl; break;
	case 10052:
		cout << "�l�b�g���[�N�����Z�b�g���ꂽ���ߐؒf����܂����B" << endl; break;
	case 10053:
		cout << "�\�t�g�E�F�A�ɂ���Đڑ������~����܂����B" << endl; break;
	case 10054:
		cout << "�s�A�ɂ���Đڑ������Z�b�g����܂����B" << endl; break;
	case 10055:
		cout << "�o�b�t�@�̈悪�T�|�[�g����Ă��܂���B" << endl; break;
	case 10056:
		cout << "�\�P�b�g�͊��ɐڑ�����Ă��܂��B" << endl; break;
	case 10057:
		cout << "�\�P�b�g���ڑ�����Ă��܂���B" << endl; break;
	case 10058:
		cout << "�\�P�b�g�̃V���b�g�_�E����ɑ��M�ł��܂���B" << endl; break;
	case 10060:
		cout << "�ڑ����^�C���A�E�g�ɂȂ�܂����B" << endl; break;
	case 10061:
		cout << "�ڑ������ۂ���܂����B" << endl; break;
	case 10064:
		cout << "�z�X�g���_�E�����Ă��܂��B" << endl; break;
	case 10065:
		cout << "�z�X�g�ɓ��B���邽�߂̃��[�g������܂���B" << endl; break;
	case 10067:
		cout << "�v���Z�X���������܂��B" << endl; break;

	default:
		break;
	}
}
