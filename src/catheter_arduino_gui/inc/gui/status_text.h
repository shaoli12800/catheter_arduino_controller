


#ifndef GUI_STATUS_H
#define GUI_STATUS_H
#include <wx/wx.h>
#include <boost/thread.hpp>
#include <boost/bind.hpp>

// This file defines the status text box.

class CatheterStatusText : public wxScrolledWindow {
public:
	
    // explicit constructor
    explicit CatheterStatusText(wxWindow* parent, wxWindowID id);

    // public method to send text into the status box
    bool addText(const std::string &incomingInfo);
	bool addWxText(const wxString& msg);

private:
	wxStaticText *statusText;

    // the mutex is used to pass information forward
    boost::mutex textMutex;

    // appends text and scrolls down.
    void SetCatheterStatusText(const wxString& msg);

};


#endif