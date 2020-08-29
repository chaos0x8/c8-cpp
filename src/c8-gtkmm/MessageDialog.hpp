#pragma once

#include <gtkmm.h>

namespace C8::Gtkmm {
  Gtk::ResponseType messageDialog(const std::string& message, const std::string& title,
    Gtk::MessageType messageType = Gtk::MESSAGE_ERROR, Gtk::ButtonsType buttons = Gtk::BUTTONS_OK);
  Gtk::ResponseType messageDialog(Gtk::Window& parent, const std::string& message, const std::string& title,
    Gtk::MessageType messageType = Gtk::MESSAGE_ERROR, Gtk::ButtonsType buttons = Gtk::BUTTONS_OK);
} // namespace C8::Gtkmm
