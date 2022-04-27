namespace('c8-embeded-ruby') do
  p = C8.project 'c8-embeded-ruby' do
    phony 'configure' do
      apt_install 'ruby-dev'
    end

    templates.cpp_include_directory 'src/c8-embeded-ruby/errors.hpp' => Dir['src/c8-embeded-ruby/errors/*.hpp']

    flags << $flags
    flags << %w[-Isrc -Wno-register -Wno-sign-conversion]

    link 'lib/libc8-common.a'

    pkg_config 'ruby'

    library 'lib/libc8-embeded-ruby.a' do
      sources << Dir['src/c8-embeded-ruby/**/*.cpp']
    end

    executable 'bin/c8-embeded-ruby-ut' do
      flags << %w[-Itest]
      link_flags << %w[-pthread -lgtest -lgmock]
      sources << Dir['test/c8-embeded-ruby/**/*.cpp']
    end
  end

  desc 'Builds c8-embeded-ruby'
  C8.multitask(default: ['lib/libc8-embeded-ruby.a', 'generated:default'])

  desc 'Runs c8-embeded-ruby tests'
  C8.multitask(test: ['c8-embeded-ruby:default', 'bin/c8-embeded-ruby-ut']) do
    sh 'bin/c8-embeded-ruby-ut'
  end
end
