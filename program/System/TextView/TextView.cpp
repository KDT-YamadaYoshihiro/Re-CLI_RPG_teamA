#include "TextView.h"


void TextView::AddText(std::string arg_text)
{
	if (m_text == arg_text) {
		return;
	}
	m_text = arg_text;
	viewFlag = true;
}

void TextView::ResetText()
{
	m_text.clear();
	system("cls");
}

void TextView::TextRender()
{
	if (viewFlag) {
		std::cout << m_text << std::endl;
		viewFlag = false;
	}
}
