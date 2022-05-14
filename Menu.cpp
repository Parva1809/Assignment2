
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
#include "utils.h"
#include "Menu.h"

using namespace std;

namespace sdds
{
    Menu::Menu(const char* MenuContent, int NoOfSelection)
    {
        this->m_text = new char[strlen(MenuContent) + 1];
        strcpy(this->m_text, MenuContent);
        this->m_noOfSel = NoOfSelection;
    }
    Menu::Menu(Menu const& m)
    {
        this->m_text = new char[strlen(m.m_text) + 1];
        strcpy(this->m_text, m.m_text);
        this->m_noOfSel = m.m_noOfSel;
    }

    Menu::~Menu()
    {
        delete[] this->m_text;
        this->m_noOfSel = 0;
    }

    void Menu::display() const
    {
        cout << this->m_text << endl;
        cout << "0- Exit" << endl;
    }

    int& Menu::operator>>(int& Selection)
    {
        this->display();
        Selection = getInt(0, this->m_noOfSel, "> ", "Invalid option ");
        return Selection;
    }
}