#pragma once
#include <iostream>
#include <string>
#include "../../Singleton/Singleton.h"

class TextView : public Singleton<TextView>
{

	friend class Singleton<TextView>;

	TextView() = default;
	virtual ~TextView() = default;

public:

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

