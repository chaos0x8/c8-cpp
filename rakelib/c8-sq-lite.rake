namespace 'c8-sq-lite' do
  p = project do |p|
    p.configure :install_c8_sq_lite do |t|
      t.apt_install 'libsqlite3-dev'
    end

    include_directory p, 'src/c8-sq-lite/errors.hpp', Dir['src/c8-sq-lite/errors/*.hpp']

    p.flags << $flags
    p.flags << %w[-Isrc]
    p.link 'lib/libc8-common.a'

    p.pkg_config 'sqlite3'

    p.library 'lib/libc8-sq-lite.a' do |t|
      t.sources << Dir['src/c8-sq-lite/**/*.cpp']
    end

    p.executable 'bin/c8-sq-lite-ut' do |t|
      t.flags << %w[-Itest]
      t.link_flags << %w[-pthread -lgtest -lgmock]
      t.sources << Dir['test/c8-sq-lite/**/*.cpp']
    end
  end

  multitask 'all' => [*p.requirements]
  multitask 'main' => [*p.requirements('lib/libc8-sq-lite.a')]

  multitask 'test' => [*p.requirements('bin/c8-sq-lite-ut')] do
    sh 'bin/c8-sq-lite-ut'
  end

  task 'clean' do
    p.clean
  end
end
