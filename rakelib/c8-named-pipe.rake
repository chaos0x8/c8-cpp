namespace('c8-named-pipe') {
  flags = ['--std=c++17']

  library = Library.new { |t|
    t.name = 'lib/libc8-named-pipe.a'
    t.sources << FileList['src/c8-named-pipe/**/*.cpp']
    t.includes << ['src/c8-named-pipe']
    t.flags << flags
  }

  ut = Executable.new { |t|
    t.name = 'bin/c8-named-pipe-ut'
    t.sources << FileList['test/c8-named-pipe/**/*.cpp']
    t.includes << ['src/c8-named-pipe', 'test/c8-named-pipe']
    t.libs << ['-pthread', '-lgtest', '-lgmock', library]
    t.flags << flags
  }

  desc 'Builds c8-named-pipe'
  C8.multitask(default: Names['generated:default', library])

  desc 'Runs c8-named-pipe tests'
  C8.multitask(test: Names['generated:default', library, ut]) {
    sh ut.name
  }
}
