% Get a list of all files and folders in this folder.
files = dir('C:\Users\Emil\Desktop\build_server\quadcopter\simulation_tests')
% Get a logical vector that tells which is a directory.
dirFlags = [files.isdir]
% Extract only those that are directories.
subFolders = files(dirFlags)
% Print folder names to command window.
for k = 1 : length(subFolders)
  if startsWith(subFolders(k).name,"test_")
  fprintf('%s\n', subFolders(k).name)
  end
end