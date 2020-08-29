#pragma once

#include <glibmm.h>
#include <gtkmm.h>

namespace C8::Gtkmm {
  class PasswordDialog : public Gtk::Dialog {
  public:
    PasswordDialog(Gtk::Window&, const std::string& prompt, const std::string& title = "Password dialog");
    explicit PasswordDialog(const std::string& prompt, const std::string& title = "Password dialog");

    std::string execute();

  protected:
    void construct();
    void initWidgets();
    void initLayout();

    Gtk::Label prompt;
    Gtk::Entry password;
    std::unique_ptr<Gtk::Button> ok;
    std::unique_ptr<Gtk::Button> cancel;
  };
} // namespace C8::Gtkmm
