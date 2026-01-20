#pragma once
#include <iostream>
#include <string>

class TextView
{

	TextView() = default;
	virtual ~TextView() = default;

public:


	// コピーの禁止
	TextView(const TextView&) = delete;
	TextView& operator = (const TextView) = delete;
	static TextView& GetInstance()
	{
		static TextView instance;
		return instance;
	}


	// テキスト内容の追加
	void AddText(std::string arg_text);

	// テキスト内容の削除
	void ResetText();

	// テキスト内容の表示
	void TextRender();


private:

	// 表示するテキスト
	std::string m_text;

};

