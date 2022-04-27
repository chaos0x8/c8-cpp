namespace('c8-curl-wrapper') do
  p = C8.project 'c8-curl-wrapper' do
    templates.cpp_include_directory 'src/c8-curl-wrapper/errors.hpp' => Dir['src/c8-curl-wrapper/errors/*.hpp']

    flags << $flags
    flags << %w[-Isrc]

    link 'lib/libc8-common.a'

    pkg_config 'libcurl'

    library 'lib/libc8-curl-wrapper.a' do
      sources << Dir['src/c8-curl-wrapper/**/*.cpp']
    end

    executable 'bin/c8-curl-wrapper-ut' do
      flags << %w[-Itest]
      link_flags << %w[-pthread -lgtest -lgmock]
      sources << Dir['test/c8-curl-wrapper/**/*.cpp']
    end
  end

  desc 'Builds c8-curl-wrapper'
  C8.multitask(default: ['lib/libc8-curl-wrapper.a', 'generated:default'])

  desc 'Runs c8-curl-wrapper tests'
  C8.multitask(test: ['c8-curl-wrapper:default', 'bin/c8-curl-wrapper-ut']) do
    sh 'bin/c8-curl-wrapper-ut'
  end
end
