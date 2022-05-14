
#ifndef _SDDS_MENU_H_
#define _SDDS_MENU_H_

namespace sdds
{

    class Menu
    {
        char* m_text;  // holds the menu content dynamically
        int m_noOfSel; // holds the number of options displayed in menu content
        void display() const;

    public:
        Menu(const char* MenuContent, int NoOfSelections);
        virtual ~Menu();
        int& operator>>(int& Selection);

        // add safe copying logic
        Menu(Menu const& m);
    };
}

#endif // _SDDS_MENU_H_