#include "TextView.h"


void TextView::AddText(std::string arg_text)
{
	m_text += arg_text;
}

void TextView::ResetText()
{
	m_text.clear();
}

void TextView::TextRender()
{
	std::cout << m_text << std::endl;
}
