namespace('c8-named-pipe') {
  flags = ['--std=c++17', '-Wall', '-Werror']

  if $argv[:debug]
    flags += ['-g']
  else
    flags += ['-O3', '-s', '-DNDEBUG']
  end

  library = Library.new { |t|
    t.name = 'lib/libc8-named-pipe.a'
    t.requirements << 'c8-common:default'
    t.sources << FileList['src/c8-named-pipe/**/*.cpp']
    t.includes << ['src']
    t.flags << flags
  }

  ut = Executable.new { |t|
    t.name = 'bin/c8-named-pipe-ut'
    t.requirements << 'c8-common:default'
    t.sources << FileList['test/c8-named-pipe/**/*.cpp']
    t.includes << ['src', 'test']
    t.libs << ['-pthread', '-lgtest', '-lgmock', library, 'lib/libc8-common.a']
    t.flags << flags
  }

  desc 'Builds c8-named-pipe'
  C8.multitask(default: Names['generated:default', library])

  desc 'Runs c8-named-pipe tests'
  C8.multitask(test: Names['generated:default', library, ut]) {
    sh ut.name
  }
}
