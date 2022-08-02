class IncludeDirectory
  include Rake::DSL
  include RakeBuilder::DSL

  def initialize(project, name, files)
    project.generated_file name do |t|
      dir = t.path.dirname

      t.erb = proc do
        <<~INLINE
          #pragma once

          <%- files.each do |path| -%>
          #include "<%= RakeBuilder::Utility.to_pathname(path).relative_path_from(dir) %>"
          <%- end -%>
        INLINE
      end

      t.track files
    end
  end
end

def include_directory(project, *args)
  IncludeDirectory.new(project, *args)
end
