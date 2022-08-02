namespace 'c8-named-pipe' do
  p = project do |p|
    p.flags << $flags
    p.flags << %w[-Isrc]
    p.link 'lib/libc8-common.a'

    p.library 'lib/libc8-named-pipe.a' do |t|
      t.sources << Dir['src/c8-named-pipe/**/*.cpp']
    end

    p.executable 'bin/c8-named-pipe-ut' do |t|
      t.flags << %w[-Itest]
      t.link_flags << %w[-pthread -lgtest -lgmock]
      t.sources << Dir['test/c8-named-pipe/**/*.cpp']
    end
  end

  multitask 'all' => [*p.requirements]
  multitask 'main' => [*p.requirements('lib/libc8-named-pipe.a')]

  multitask 'test' => [*p.requirements('bin/c8-named-pipe-ut')] do
    sh 'bin/c8-named-pipe-ut'
  end

  task 'clean' do
    p.clean
  end
end
