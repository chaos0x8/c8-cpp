namespace('c8-gtkmm') do
  p = C8.project 'c8-gtkmm' do
    flags << $flags
    flags << %w[-Isrc -Wno-parentheses -Wno-sign-conversion]

    link 'lib/libc8-common.a'

    pkg_config 'gtkmm-3.0'

    library 'lib/libc8-gtkmm.a' do
      sources << Dir['src/c8-gtkmm/**/*.cpp']
    end

    executable 'bin/c8-gtkmm-ut' do
      flags << %w[-Itest]
      link_flags << %w[-pthread -lgtest -lgmock]
      sources << Dir['test/c8-gtkmm/**/*.cpp']
    end
  end

  desc 'Builds c8-gtkmm'
  C8.multitask(default: ['lib/libc8-gtkmm.a', 'generated:default'])

  desc 'Runs c8-gtkmm tests'
  C8.multitask(test: ['c8-gtkmm:default', 'bin/c8-gtkmm-ut']) do
    sh 'bin/c8-gtkmm-ut'
  end
end
