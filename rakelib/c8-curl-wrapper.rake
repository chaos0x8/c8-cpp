C8.project 'c8-curl-wrapper' do
  templates.cpp_include_directory 'src/c8-curl-wrapper/errors.hpp' => Dir['src/c8-curl-wrapper/errors/*.hpp']

  flags << $flags
  flags << %w[-Isrc]

  link 'lib/libc8-common.a'

  pkg_config 'libcurl'

  library 'lib/libc8-curl-wrapper.a' do
    sources << Dir['src/c8-curl-wrapper/**/*.cpp']
  end

  test 'bin/c8-curl-wrapper-ut' do
    flags << %w[-Itest]
    link_flags << %w[-pthread -lgtest -lgmock]
    sources << Dir['test/c8-curl-wrapper/**/*.cpp']
  end
end
