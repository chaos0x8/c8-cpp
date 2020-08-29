#include "c8-gtkmm/QuestionDialog.hpp"

namespace C8::Gtkmm {
  Gtk::ResponseType QuestionDialog<Gtk::ResponseType>::exec(
    Gtk::Window& parent, const std::string& question, Gtk::ButtonsType buttons) {
    Gtk::MessageDialog dialog(parent, question, false, Gtk::MESSAGE_QUESTION, buttons);
    return static_cast<Gtk::ResponseType>(dialog.run());
  }
} // namespace C8::Gtkmm
