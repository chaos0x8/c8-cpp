namespace('c8-sq-lite') {
  flags = $flags

  install = InstallPkg.new { |t|
    t.name = 'pkgs'
    t.pkgs << ['libsqlite3-dev']
  }

  generated = ['src/c8-sq-lite/errors.hpp'].collect { |fn|
    if dir = fn.chomp(File.extname(fn)) and File.directory?(dir)
      Generate.includeDirectory(dir)
    end
  }.compact

  library = Library.new { |t|
    t.name = 'lib/libc8-sq-lite.a'
    t.requirements << ['c8-sq-lite:pkgs', generated, C8::Config]
    t.sources << FileList['src/c8-sq-lite/**/*.cpp']
    t.includes << ['src']
    t.flags << flags
  }

  ut = Executable.new { |t|
    t.name = 'bin/c8-sq-lite-ut'
    t.requirements << ['c8-sq-lite:pkgs', generated, C8::Config]
    t.sources << FileList['test/c8-sq-lite/**/*.cpp']
    t.includes << ['src', 'test']
    t.libs << ['-pthread', '-lgtest', '-lgmock', library]
    t.libs << '-lgmock_main' unless t.sources.find { |x| File.basename(x.name) == 'main.cpp' }
    t.pkgs << ['sqlite3']
    t.flags << flags
  }

  desc 'Builds c8-sq-lite'
  C8.multitask(default: Names::All['generated:default', library])

  desc 'Runs c8-sq-lite tests'
  C8.multitask(test: Names::All['generated:default', library, ut]) {
    sh ut.name
  }
}
