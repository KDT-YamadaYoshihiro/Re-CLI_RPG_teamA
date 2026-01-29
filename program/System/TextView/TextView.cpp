#include "TextView.h"
#include <iostream>
#include <cstdlib>

void TextView::Add(const std::string& text)
{
    m_views.push_back(text);
}

void TextView::RenderFrame()
{
    // 前フレームと完全一致なら何もしない
    if (m_views == m_lastViews)
    {
        m_views.clear();
        return;
    }

#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif

    for (const auto& line : m_views)
    {
        std::cout << line << std::endl;
    }

    m_lastViews = m_views;
    m_views.clear();
}

void TextView::Reset()
{
    m_views.clear();
    m_lastViews.clear();

#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}
