C8.project 'c8-option-parser' do
  templates.cpp_include_directory 'src/c8-option-parser/errors.hpp' => Dir['src/c8-option-parser/errors/*.hpp']
  templates.cpp_include_directory 'src/c8-option-parser.hpp' => Dir['src/c8-option-parser/*.hpp'] + %w[
    src/c8-option-parser/errors.hpp
  ]

  flags << $flags
  flags << %w[-Isrc]

  link 'lib/libc8-common.a'

  library 'lib/libc8-option-parser.a' do
    sources << Dir['src/c8-option-parser/**/*.cpp']
  end

  test 'bin/c8-option-parser-ut' do
    flags << %w[-Itest]
    link_flags << %w[-pthread -lgtest -lgmock]
    sources << Dir['test/c8-option-parser/**/*.cpp']
  end
end
