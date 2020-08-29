#pragma once

#include <gtkmm.h>

namespace C8::Gtkmm {
  class FileChooserDialog : public Gtk::FileChooserDialog {
  public:
    FileChooserDialog(Gtk::Window& parent, const Glib::ustring& prompt, Gtk::FileChooserAction action);

    void addFilter(const std::string& name, const std::string& pattern);
    void setFileName(const std::string& fileName);

    std::string execute();

  private:
    void initDefaultButtons();

    std::vector<Glib::RefPtr<Gtk::FileFilter>> filters;
  };
} // namespace C8::Gtkmm
