namespace('c8-curl-wrapper') {
  flags = ['--std=c++17', '-Wall', '-Werror']

  if $argv[:debug]
    flags += ['-g']
  else
    flags += ['-O3', '-s', '-DNDEBUG']
  end

  install = InstallPkg.new { |t|
    t.name = 'pkgs'
    t.pkgs << []
  }

  generated = [
    'src/c8-curl-wrapper/errors.hpp'
  ].collect { |fn|
    if dir = fn.chomp(File.extname(fn)) and File.directory?(dir)
      Generate.includeDirectory(dir)
    end
  }

  library = Library.new { |t|
    t.name = 'lib/libc8-curl-wrapper.a'
    t.requirements << ['c8-curl-wrapper:pkgs', generated]
    t.sources << FileList['src/c8-curl-wrapper/**/*.cpp']
    t.includes << ['src']
    t.pkgs << ['libcurl']
    t.flags << flags
  }

  ut = Executable.new { |t|
    t.name = 'bin/c8-curl-wrapper-ut'
    t.requirements << ['c8-curl-wrapper:pkgs', generated]
    t.sources << FileList['test/c8-curl-wrapper/**/*.cpp']
    t.includes << ['src', 'test']
    t.libs << ['-pthread', '-lgtest', '-lgmock', library]
    t.pkgs << ['libcurl']
    t.flags << flags
  }

  desc 'Builds c8-curl-wrapper'
  C8.multitask(default: Names['generated:default', library])

  desc 'Runs c8-curl-wrapper tests'
  C8.multitask(test: Names['generated:default', library, ut]) {
    sh ut.name
  }
}
