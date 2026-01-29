#pragma once
#include <iostream>
#include <string>
#include "../../Singleton/Singleton.h"

class TextView : public Singleton<TextView>
{

	friend class Singleton<TextView>;

	TextView() = default;
	virtual ~TextView() = default;
	// 表示するテキスト
	std::string m_text;
	// 描画Flag
	bool viewFlag = true;

public:

	// テキスト内容の追加
	void AddText(std::string arg_text);

	// 画面のクリア、テキスト内容のリセット
	void ResetText();

	// テキスト内容の表示
	void TextRender();

};

