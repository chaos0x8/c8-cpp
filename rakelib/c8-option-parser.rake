require_relative '_common'

namespace 'c8-option-parser' do
  p = project do |p|
    include_directory p, 'src/c8-option-parser/errors.hpp', Dir['src/c8-option-parser/errors/*.hpp']

    p.flags << $flags
    p.flags << %w[-Isrc]
    p.link 'lib/libc8-common.a'

    p.library 'lib/libc8-option-parser.a' do |t|
      t.sources << Dir['src/c8-option-parser/**/*.cpp']
    end

    p.executable 'bin/c8-option-parser-ut' do |t|
      t.flags << %w[-Itest]
      t.link_flags << %w[-pthread -lgtest -lgmock]
      t.sources << Dir['test/c8-option-parser/**/*.cpp']
    end
  end

  multitask 'all' => [*p.requirements]
  multitask 'main' => [*p.requirements('lib/libc8-option-parser.a')]

  multitask 'test' => [*p.requirements('bin/c8-option-parser-ut')] do
    sh 'bin/c8-option-parser-ut'
  end

  task 'clean' do
    p.clean
  end
end
