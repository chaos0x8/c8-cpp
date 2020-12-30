namespace('c8-curl-wrapper') {
  flags = $flags

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
    t.requirements << ['c8-curl-wrapper:pkgs', generated, C8::Config]
    t.sources << FileList['src/c8-curl-wrapper/**/*.cpp']
    t.includes << ['src']
    t.pkgs << ['libcurl']
    t.flags << flags
  }

  ut = Executable.new { |t|
    t.name = 'bin/c8-curl-wrapper-ut'
    t.requirements << ['c8-curl-wrapper:pkgs', generated, C8::Config]
    t.sources << FileList['test/c8-curl-wrapper/**/*.cpp']
    t.includes << ['src', 'test']
    t.libs << ['-pthread', '-lgtest', '-lgmock', library]
    t.libs << '-lgmock_main' unless t.sources.find { |x| File.basename(x.name) == 'main.cpp' }
    t.pkgs << ['libcurl']
    t.flags << flags
  }

  desc 'Builds c8-curl-wrapper'
  C8.multitask(default: Names::All['generated:default', library])

  desc 'Runs c8-curl-wrapper tests'
  C8.multitask(test: Names::All['generated:default', library, ut]) {
    sh ut.name
  }
}
