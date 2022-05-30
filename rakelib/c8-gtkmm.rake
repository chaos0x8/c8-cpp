C8.project 'c8-gtkmm' do
  templates.cpp_include_directory 'src/c8-gtkmm.hpp' => Dir['src/c8-gtkmm/*.hpp']

  flags << $flags
  flags << %w[-Isrc -Wno-parentheses -Wno-sign-conversion]

  link 'lib/libc8-common.a'

  pkg_config 'gtkmm-3.0'

  library 'lib/libc8-gtkmm.a' do
    sources << Dir['src/c8-gtkmm/**/*.cpp']
  end

  test 'bin/c8-gtkmm-ut' do
    flags << %w[-Itest]
    link_flags << %w[-pthread -lgtest -lgmock]
    sources << Dir['test/c8-gtkmm/**/*.cpp']
  end
end
