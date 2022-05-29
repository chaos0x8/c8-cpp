def c8_common_errors_new(key, c, lib:)
  libNamespace = lib.gsub(/^c8-/, '').split('-').collect(&:capitalize).join
  namespace = ['C8', libNamespace, 'Errors'].join('::')

  header = GeneratedFile.new(format: true) do |t|
    t.name = File.join("src/#{lib}/errors", "#{key}.hpp")
    t.code = proc {
      C8.erb lib: lib, key: key, namespace: namespace do
        IO.read('templates/Error.hpp.erb')
      end
    }
  end

  source = GeneratedFile.new(format: true) do |t|
    t.name = File.join("src/#{lib}/errors", "#{key}.cpp")
    t.code = proc {
      C8.erb lib: lib, key: key, namespace: namespace, c: c do
        IO.read('templates/Error.cpp.erb')
      end
    }
  end

  test = GeneratedFile.new(format: true) do |t|
    t.name = File.join("test/#{lib}/errors", "Test#{key}.cpp")
    t.code = proc {
      C8.erb lib: lib, key: key, namespace: namespace do
        IO.read('templates/TestError.cpp.erb')
      end
    }
  end

  [header, source, test]
end

C8.project 'c8-common' do
  templates.cpp_include_directory 'src/c8-common/errors.hpp' => Dir['src/c8-common/errors/*.hpp']
  templates.cpp_include_directory 'src/c8-common/type_traits.hpp' => Dir['src/c8-common/type_traits/*.hpp']

  flags << $flags
  flags << %w[-Isrc]

  link 'lib/libc8-common.a'

  pkg_config 'sqlite3'

  library 'lib/libc8-common.a' do
    sources << Dir['src/c8-common/**/*.cpp']
  end

  test 'bin/c8-common-ut' do
    flags << %w[-Itest]
    link_flags << %w[-pthread -lgtest -lgmock]
    sources << Dir['test/c8-common/**/*.cpp']
  end

  desc 'Generates new error in given library (default lib: c8-common)'
  C8.task(:error, %i[name lib]) do |_t, args|
    name = args[:name]
    lib = args[:lib] || 'c8-common'

    gen = c8_common_errors_new(name, { 'string' => "\"#{name}\"" }, lib: lib)

    task('error_exec' => Names[gen])

    Rake::Task['error_exec'].invoke
  end
end
