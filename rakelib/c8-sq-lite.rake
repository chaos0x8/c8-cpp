namespace('c8-sq-lite') do
  p = C8.project 'c8-sq-lite' do
    phony 'configure' do
      apt_install 'libsqlite3-dev'
    end

    templates.cpp_include_directory 'src/c8-sq-lite/errors.hpp' => Dir['src/c8-sq-lite/errors/*.hpp']

    flags << $flags
    flags << %w[-Isrc]

    link 'lib/libc8-common.a'

    pkg_config 'sqlite3'

    library 'lib/libc8-sq-lite.a' do
      sources << Dir['src/c8-sq-lite/**/*.cpp']
    end

    executable 'bin/c8-sq-lite-ut' do
      flags << %w[-Itest]
      link_flags << %w[-pthread -lgtest -lgmock]
      sources << Dir['test/c8-sq-lite/**/*.cpp']
    end
  end

  desc 'Builds c8-sq-lite'
  C8.multitask(default: ['lib/libc8-sq-lite.a', 'generated:default'])

  desc 'Runs c8-sq-lite tests'
  C8.multitask(test: ['c8-sq-lite:default', 'bin/c8-sq-lite-ut']) do
    sh 'bin/c8-sq-lite-ut'
  end
end
