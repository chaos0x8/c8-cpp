require_relative '_common'

namespace 'c8-gtkmm' do
  p = project do |p|
    p.flags << $flags
    p.flags << %w[-Isrc -Wno-parentheses -Wno-sign-conversion]
    p.link 'lib/libc8-common.a'

    p.pkg_config 'gtkmm-3.0'

    p.library 'lib/libc8-gtkmm.a' do |t|
      t.sources << Dir['src/c8-gtkmm/**/*.cpp']
    end

    p.executable 'bin/c8-gtkmm-ut' do |t|
      t.flags << %w[-Itest]
      t.link_flags << %w[-pthread -lgtest -lgmock]
      t.sources << Dir['test/c8-gtkmm/**/*.cpp']
    end
  end

  multitask 'all' => [*p.requirements]
  multitask 'main' => [*p.requirements('lib/libc8-gtkmm.a')]

  multitask 'test' => [*p.requirements('bin/c8-gtkmm-ut')] do
    sh 'bin/c8-gtkmm-ut'
  end

  task 'clean' do
    p.clean
  end
end
