namespace('c8-option-parser') do
  p = C8.project 'c8-option-parser' do
    templates.cpp_include_directory 'src/c8-option-parser/errors.hpp' => Dir['src/c8-option-parser/errors/*.hpp']

    flags << $flags
    flags << %w[-Isrc]

    link 'lib/libc8-common.a'

    library 'lib/libc8-option-parser.a' do
      sources << Dir['src/c8-option-parser/**/*.cpp']
    end

    executable 'bin/c8-option-parser-ut' do
      flags << %w[-Itest]
      link_flags << %w[-pthread -lgtest -lgmock]
      sources << Dir['test/c8-option-parser/**/*.cpp']
    end
  end

  desc 'Builds c8-option-parser'
  C8.multitask(default: ['lib/libc8-option-parser.a', 'generated:default'])

  desc 'Runs c8-sq-lite tests'
  C8.multitask(test: ['c8-option-parser:default', 'bin/c8-option-parser-ut']) do
    sh 'bin/c8-option-parser-ut'
  end
end
