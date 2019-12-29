from subprocess import call
import os
import sys
import staus_handling

status_message = staus_handling.StatusHandling()

filenames= os.listdir(os.path.dirname(os.path.abspath(__file__)))
folders = []
for filename in filenames: # loop through all the files and folders
    if os.path.isdir(os.path.join(os.path.dirname(os.path.abspath(__file__)), filename)): # check whether the current object is a folder or not
        folders.append(filename)

print(os.path.isdir(os.path.join(os.path.dirname(os.path.abspath(__file__)), 'test_somname2')))
print(folders)
test_folders = []
for folder in folders:
    if 'test_' in folder:
        test_folders.append(folder)


status = 0
failed_tests = []
number_of_tests = 0
for test_folder in test_folders:
    execute_test = 'cd ' + os.path.dirname(os.path.abspath(__file__))+'/'+test_folder
    status = call(execute_test + '&& python3 start_test.py', shell=True)
    if status != 0:
        failed_tests.append(execute_test[execute_test.find('/'):]) 
    number_of_tests += 1

if failed_tests:
    status_message.error("Following test(s) failed:")
    for failed_test in failed_tests:
        status_message.error(failed_test)

sys.exit(status)
    
