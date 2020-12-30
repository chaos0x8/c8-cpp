def c8_common_errors_new key, c, lib:
  libNamespace = lib.gsub(/^c8-/, '').split('-').collect(&:capitalize).join
  namespace = ['C8', libNamespace, 'Errors'].join('::')

  header = GeneratedFile.new(format: true) { |t|
    t.name = File.join("src/#{lib}/errors", "#{key}.hpp")
    t.code = proc {
      C8.erb(
        IO.read('templates/Error.hpp.erb'),
        lib: lib, key: key, namespace: namespace)
    }
  }

  source = GeneratedFile.new(format: true) { |t|
    t.name = File.join("src/#{lib}/errors", "#{key}.cpp")
    t.code = proc {
      C8.erb(
        IO.read('templates/Error.cpp.erb'),
        lib: lib, key: key, namespace: namespace, c: c)
    }
  }

  test = GeneratedFile.new(format: true) { |t|
    t.name = File.join("test/#{lib}/errors", "Test#{key}.cpp")
    t.code = proc {
      C8.erb(
        IO.read('templates/TestError.cpp.erb'),
        lib: lib, key: key, namespace: namespace)
    }
  }

  [header, source, test]
end

namespace('c8-common') {
  flags = $flags

  generated = [
    'src/c8-common/errors.hpp',
    'src/c8-common/type_traits.hpp'
  ].collect { |fn|
    if dir = fn.chomp(File.extname(fn)) and File.directory?(dir)
      Generate.includeDirectory(dir)
    end
  }

  library = Library.new { |t|
    t.name = 'lib/libc8-common.a'
    t.requirements << generated << C8::Config
    t.sources << FileList['src/c8-common/**/*.cpp']
    t.includes << ['src']
    t.flags << flags
  }

  ut = Executable.new { |t|
    t.name = 'bin/c8-common-ut'
    t.requirements << generated << C8::Config
    t.sources << FileList['test/c8-common/**/*.cpp']
    t.includes << ['src', 'test']
    t.libs << ['-pthread', '-lgtest', '-lgmock', library]
    t.libs << '-lgmock_main' unless t.sources.find { |x| File.basename(x.name) == 'main.cpp' }
    t.flags << flags
  }

  desc 'Builds c8-common'
  C8.multitask(default: Names::All['generated:default', library])

  desc 'Runs c8-common tests'
  C8.multitask(test: Names::All['generated:default', library, ut]) {
    sh ut.name
  }

  desc 'Generates new error in given library (default lib: c8-common)'
  C8.task(:error, [:name, :lib]) { |t, args|
    name = args[:name]
    lib = args[:lib] || 'c8-common'

    gen = c8_common_errors_new(name, {'string' => "\"#{name}\""}, lib: lib)

    task('error_exec' => Names[gen])

    Rake::Task['error_exec'].invoke
  }
}
