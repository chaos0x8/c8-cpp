C8.project 'c8-named-pipe' do
  templates.cpp_include_directory 'src/c8-named-pipe.hpp' => Dir['src/c8-named-pipe/*.hpp']

  flags << $flags
  flags << %w[-Isrc]

  link 'lib/libc8-common.a'

  library 'lib/libc8-named-pipe.a' do
    sources << Dir['src/c8-named-pipe/**/*.cpp']
  end

  test 'bin/c8-named-pipe-ut' do
    flags << %w[-Itest]
    link_flags << %w[-pthread -lgtest -lgmock]
    sources << Dir['test/c8-named-pipe/**/*.cpp']
  end
end
