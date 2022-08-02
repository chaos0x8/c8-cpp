require_relative '_common'

namespace 'c8-embeded-ruby' do
  p = project do |p|
    include_directory p, 'src/c8-embeded-ruby/errors.hpp', Dir['src/c8-embeded-ruby/errors/*.hpp']

    p.configure :configure_c8_embeded_ruby do |t|
      t.apt_install 'ruby-dev'
    end

    p.flags << $flags
    p.flags << %w[-Isrc -Wno-register -Wno-sign-conversion]
    p.link 'lib/libc8-common.a'

    p.pkg_config 'ruby'

    p.library 'lib/libc8-embeded-ruby.a' do |t|
      t.sources << Dir['src/c8-embeded-ruby/**/*.cpp']
    end

    p.executable 'bin/c8-embeded-ruby-ut' do |t|
      t.flags << %w[-Itest]
      t.link_flags << %w[-pthread -lgtest -lgmock]
      t.sources << Dir['test/c8-embeded-ruby/**/*.cpp']
    end
  end

  multitask 'all' => [*p.requirements]
  multitask 'main' => [*p.requirements('lib/libc8-embeded-ruby.a')]

  multitask 'test' => [*p.requirements('bin/c8-embeded-ruby-ut')] do
    sh 'bin/c8-embeded-ruby-ut'
  end

  task 'clean' do
    p.clean
  end
end
