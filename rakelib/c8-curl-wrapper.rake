require_relative '_common'

namespace 'c8-curl-wrapper' do
  p = project do |p|
    include_directory p, 'src/c8-curl-wrapper/errors.hpp', Dir['src/c8-curl-wrapper/errors/*.hpp']

    p.flags << $flags
    p.flags << %w[-Isrc]
    p.link 'lib/libc8-common.a'

    p.pkg_config 'libcurl'

    p.library 'lib/libc8-curl-wrapper.a' do |t|
      t.sources << Dir['src/c8-curl-wrapper/**/*.cpp']
    end

    p.executable 'bin/c8-curl-wrapper-ut' do |t|
      t.flags << %w[-Itest]
      t.link_flags << %w[-pthread -lgtest -lgmock]
      t.sources << Dir['test/c8-curl-wrapper/**/*.cpp']
    end
  end

  multitask 'all' => [*p.requirements]
  multitask 'main' => [*p.requirements('lib/libc8-curl-wrapper.a')]

  multitask 'test' => [*p.requirements('bin/c8-curl-wrapper-ut')] do
    sh 'bin/c8-curl-wrapper-ut'
  end

  task 'clean' do
    p.clean
  end
end
