namespace(:generated) do
  p = C8.project 'default' do
    desc 'Generate files'

    Pathname.new('src').glob('*')
            .select(&:directory?)
            .collect do |dir|
      templates.cpp_include_directory dir.sub_ext('.hpp') => dir.glob('*.hpp')
    end
  end

  desc 'Remove generated files'
  C8.target :clean do
    p.dependencies.each do |path|
      rm path
    end
  end
end
