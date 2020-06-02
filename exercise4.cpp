// インクルード
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>  // ※istringstreamを使うために必要
#include<bits/stdc++.h>
// 名前空間
using namespace std;
//
//  CSVを取得する
//      filename    読み込むファイル名
//      table       読み込んだCSVの内容
//      delimiter   区切り文字(今回はデフォルトでカンマ)
//
bool GetContents(const string& filename, vector<vector<string>>& table, const char delimiter = ',')
{
	// ファイルを開く
	fstream filestream(filename);
	if (!filestream.is_open())
	{
		// ファイルが開けなかった場合は終了する
		return false;
	}
 
	// ファイルを読み込む
	while (!filestream.eof())
	{
		// １行読み込む
		string buffer;
		filestream >> buffer;
 
		// ファイルから読み込んだ１行の文字列を区切り文字で分けてリストに追加する
		vector<string> record;              // １行分の文字列のリスト
		istringstream streambuffer(buffer); // 文字列ストリーム
		string token;                       // １セル分の文字列
		while (getline(streambuffer, token, delimiter))
		{
			// １セル分の文字列をリストに追加する
			record.push_back(token);
		}
 
		// １行分の文字列を出力引数のリストに追加する
		table.push_back(record);
	}
 
	return true;
}

//
// メインメソッド
//
int main()
{
	// 変数を定義する
	bool status = false;    // メソッドのステータス
	string filename = "stock.csv"; // ファイル名
	vector<vector<string>> table;   // 読み込んだCSVファイルの内容
 
	// CSVファイルの内容を取得する
	status = GetContents(filename, table);
	if (!status)
	{
		// 取得に失敗した場合はエラー終了する
		return -1;
	}
    vector<vector<long double>> ldtable(100, vector<long double>(100));
    for(int i=0;i<100;i++){
        for(int j=0;j<100;j++){
            ldtable[i][j]=stod(table[i][j]);
        }
    }
    
    for(int i=0;i<100;i++){
        cout<<ldtable[95][i]<<" ";
    }
    cout<<endl;
    
	return 0;
}