#include "../stdafx.h"
#include "Data.h"
#include <iostream>

using namespace std;

void Data::ErrorState(int errorNumber)
{
	switch (errorNumber)
	{
	case 10004:
		cout << "関数の呼び出しに割込みがありました。" << endl; break;
	case 10013:
		cout << "アクセスは拒否されました。" << endl; break;
	case 10014:
		cout << "アドレスが正しくありません。" << endl; break;
	case 10022:
		cout << "無効な引数です。" << endl; break;
	case 10024:
		cout << "開いているファイルが多すぎます。" << endl; break;
	case 10035:
		cout << "リソースが一時的に利用できなくなっています。" << endl; break;
	case 10036:
		cout << "操作は現在実行中です。" << endl; break;
	case 10037:
		cout << "操作は既に実行中です。" << endl; break;
	case 10038:
		cout << "非ソケットに対してソケット操作を試みました。" << endl; break;
	case 10039:
		cout << "送信先のアドレスが必要です。" << endl; break;
	case 10040:
		cout << "メッセージが長すぎます。" << endl; break;
	case 10041:
		cout << "プロトコルの種類がソケットに対して正しくありません。" << endl; break;
	case 10042:
		cout << "プロトコルのオプションが正しくありません。" << endl; break;
	case 10043:
		cout << "プロトコルがサポートされていません。" << endl; break;
	case 10044:
		cout << "サポートされていないソケットの種類です。" << endl; break;
	case 10045:
		cout << "操作がソケット上でサポートされていません。" << endl; break;
	case 10046:
		cout << "プロトコル ファミリがサポートされていません。" << endl; break;
	case 10047:
		cout << "プロトコル ファミリはアドレス ファミリをサポートしていません。" << endl; break;
	case 10048:
		cout << "アドレスは既に使用中です。" << endl; break;
	case 10049:
		cout << "要求されたアドレスを割り当てられません。" << endl; break;
	case 10050:
		cout << "ネットワークがダウンしています。" << endl; break;
	case 10051:
		cout << "ICMP ネットワークに到達できません。" << endl; break;
	case 10052:
		cout << "ネットワークがリセットされたため切断されました。" << endl; break;
	case 10053:
		cout << "ソフトウェアによって接続が中止されました。" << endl; break;
	case 10054:
		cout << "ピアによって接続がリセットされました。" << endl; break;
	case 10055:
		cout << "バッファ領域がサポートされていません。" << endl; break;
	case 10056:
		cout << "ソケットは既に接続されています。" << endl; break;
	case 10057:
		cout << "ソケットが接続されていません。" << endl; break;
	case 10058:
		cout << "ソケットのシャットダウン後に送信できません。" << endl; break;
	case 10060:
		cout << "接続がタイムアウトになりました。" << endl; break;
	case 10061:
		cout << "接続が拒否されました。" << endl; break;
	case 10064:
		cout << "ホストがダウンしています。" << endl; break;
	case 10065:
		cout << "ホストに到達するためのルートがありません。" << endl; break;
	case 10067:
		cout << "プロセスが多すぎます。" << endl; break;

	default:
		break;
	}
}
