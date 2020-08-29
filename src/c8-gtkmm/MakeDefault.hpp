#pragma once

#include <gtkmm.h>

namespace C8::Gtkmm {
  inline void makeDefault(Gtk::Widget& widget) {
    widget.set_can_default();
    widget.grab_default();
  }
} // namespace C8::Gtkmm
