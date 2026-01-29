#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "../../Singleton/Singleton.h"

class TextView : public Singleton<TextView>
{

	friend class Singleton<TextView>;

	TextView() = default;
	virtual ~TextView() = default;


	/// <summary>
	/// 表示用テキスト一覧
	/// </summary>
	std::vector<std::string> m_views;
	/// <summary>
	/// 表示履歴一覧
	/// </summary>
	std::vector<std::string> m_lastViews;


public:

	// 表示内容の追加
	void Add(const std::string& arg_text);


	// 表示内容の表示
	void RenderFrame();

	// 表示内容のリセット
	void Reset();
};

