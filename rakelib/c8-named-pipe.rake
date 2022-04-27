namespace('c8-named-pipe') do
  p = C8.project 'c8-named-pipe' do
    flags << $flags
    flags << %w[-Isrc]

    link 'lib/libc8-common.a'

    library 'lib/libc8-named-pipe.a' do
      sources << Dir['src/c8-named-pipe/**/*.cpp']
    end

    executable 'bin/c8-named-pipe-ut' do
      flags << %w[-Itest]
      link_flags << %w[-pthread -lgtest -lgmock]
      sources << Dir['test/c8-named-pipe/**/*.cpp']
    end
  end

  desc 'Builds c8-named-pipe'
  C8.multitask(default: ['lib/libc8-named-pipe.a', 'generated:default'])

  desc 'Runs c8-sq-lite tests'
  C8.multitask(test: ['c8-named-pipe:default', 'bin/c8-named-pipe-ut']) do
    sh 'bin/c8-named-pipe-ut'
  end
end
