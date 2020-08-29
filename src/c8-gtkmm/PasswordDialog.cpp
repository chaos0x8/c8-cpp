#include "c8-gtkmm/PasswordDialog.hpp"
#include "c8-common/errors/OperationAbortedError.hpp"
#include "c8-gtkmm/MakeDefault.hpp"

namespace C8::Gtkmm {
  PasswordDialog::PasswordDialog(Gtk::Window& parent, const std::string& prompt, const std::string& title)
    : Gtk::Dialog(title, parent), prompt(prompt) {
    construct();
  }

  PasswordDialog::PasswordDialog(const std::string& prompt, const std::string& title) : prompt(prompt) {
    set_title(title);
    construct();
  }

  std::string PasswordDialog::execute() {
    if (run() != Gtk::RESPONSE_OK) {
      throw Common::Errors::OperationAbortedError("Entering password");
    }
    return password.get_text();
  }

  void PasswordDialog::construct() {
    ok = std::unique_ptr<Gtk::Button>(add_button(Gtk::Stock::OK, Gtk::RESPONSE_OK));
    cancel = std::unique_ptr<Gtk::Button>(add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL));

    initWidgets();
    initLayout();

    show_all_children();
  }

  void PasswordDialog::initWidgets() {
    set_border_width(5);
    property_resizable().set_value(false);
    property_deletable().set_value(false);
    password.property_placeholder_text().set_value("Password");
    password.property_caps_lock_warning().set_value(true);
    password.property_visibility().set_value(false);
    password.set_activates_default();

    makeDefault(*ok);
  }

  void PasswordDialog::initLayout() {
    get_vbox()->pack_start(prompt, Gtk::PACK_SHRINK);
    get_vbox()->pack_start(password, Gtk::PACK_SHRINK);
  }
} // namespace C8::Gtkmm
