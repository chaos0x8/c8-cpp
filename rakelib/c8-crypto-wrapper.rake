C8.project 'c8-crypto-wrapper' do
  templates.cpp_include_directory 'src/c8-crypto-wrapper.hpp' => Dir['src/c8-crypto-wrapper/*.hpp']

  phony 'configure' do
    apt_install 'libcrypto++-dev'
  end

  flags << $flags
  flags << %w[-Isrc]

  link 'lib/libc8-common.a'

  pkg_config 'libcrypto++'

  library 'lib/libc8-crypto-wrapper.a' do
    sources << Dir['src/c8-crypto-wrapper/**/*.cpp']
  end

  test 'bin/c8-crypto-wrapper-ut' do
    flags << %w[-Itest]
    link_flags << %w[-pthread -lgtest -lgmock]
    sources << Dir['test/c8-crypto-wrapper/**/*.cpp']
  end
end
