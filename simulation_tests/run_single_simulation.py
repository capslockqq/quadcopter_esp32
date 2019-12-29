from subprocess import call
import sys
import os
import shutil
import time
from threading import Thread
from os import path
from simulation_tests import staus_handling
import csv


generated_test_folder = 'tmp'
status_message = staus_handling.StatusHandling()
SUCCESS = 0
FAIL = 1

def generate_story_dict(lines):
    index = 0
    param_stories = []
    final_stories = []
    write_param_line_no = 0
    end_param_write_line_no = 0
    lines = list(map(lambda x:x.strip(),lines))
    lines = list(filter(None, lines)) # fastest
    for line in lines:
        if "WRITE PARAMETER AT" in line:
            write_param_line_no = index
        elif "END PARAMETER WRITE" in line:
            end_param_write_line_no = index
        if write_param_line_no != end_param_write_line_no and end_param_write_line_no != 0:
            param_stories.append((write_param_line_no, end_param_write_line_no))
            write_param_line_no = 0
            end_param_write_line_no = 0
        index += 1
    for story in param_stories:
        line = lines[story[0]]
        write_at_seconds = float(line[line.find("AT")+3:])
        dict_story = {}
        dict_story['write at'] = write_at_seconds
        dict_story['ids'] = {}
        for i in range((story[1]-1 - story[0])):
            line = lines[story[0]+i+1]
            param_id = line[:line.find("=")]
            param_value = float(line[line.find("=")+1:])
            dict_story['ids'][param_id] = param_value
        final_stories.append(dict_story)
    return final_stories



def get_simulation_story(basepath):
    try: 
        simulation_story = open(basepath+'/simulation_story.txt', 'r')
    except:
        print("Coult not find simulation story")
        sys.exit(10)
    lines = simulation_story.readlines()
    return generate_story_dict(lines)
def test(current_path, path_to_executable, execute):
    call('cd ' + current_path + ' && ' + path_to_executable + '&&' + execute, shell=True)
    print("Done simulating")

def generate_input_argument(simulation_story_dicts):
    simulation_story_str = "simulation_story "
    for simulation_story_dict in simulation_story_dicts:
        for simu_id in simulation_story_dict['ids']:
            simulation_story_str += simu_id + " " + str(simulation_story_dict['write at']) + " " + str(simulation_story_dict['ids'][simu_id]) + " "
    return simulation_story_str


def remove_old_simulation_files():
    pass

def generate_finale_executable_call(simulation_time, ids_to_log_str, simulation_story_str):
    return str('./pc_program ' + str(simulation_time) + ' ' + ids_to_log_str + ' ' + simulation_story_str)

def setup_simulation_folders(basepath):
    if os.path.isdir(basepath+'/'+generated_test_folder): #checking for folder and deleting it 
        shutil.rmtree(basepath+'/'+generated_test_folder)
    os.mkdir(basepath+'/'+generated_test_folder)


def get_ids_to_log_str(ids):
    ids_to_log_str = ""
    for id_to_log in ids:
        ids_to_log_str += id_to_log + ' '

    return ids_to_log_str

def get_ids_to_log_list(basepath): 
    path_to_id_to_log_file = basepath +'/ids_to_log.txt'
    ids_to_log_file = open(path_to_id_to_log_file,'r')
    lines = ids_to_log_file.readlines()

    ids = []
    for line in lines: 
        if line.find(':--:') > -1:
            line = line[:line.find(':--:')]
        line.rstrip('\n')
        line.replace('\n', '')
        ids.append(line)
    
    
    return ids

def generate_log_files(ids, basepath):
    id_files = []
    filepath = path.abspath(path.join(basepath, "..", "..", "build_pc/pc/"))
    for id_to_log in ids:
        id_files.append(open(filepath+'/'+id_to_log+'.txt', 'r'))
    return id_files



def log_data_real_time(id_files, basepath):
    output_file = open(basepath+'/'+generated_test_folder+'/output_file.txt', 'a')

    number_of_id_file = 1
    line_data = ""
    while True:
        for id_file in id_files:
            line_read = id_file.readline()
            append = ";" if number_of_id_file < len(id_files) else ""
            line_data += line_read[:line_read.find(';')] + append
            number_of_id_file += 1
        number_of_id_file = 1
        if not line_read: break
        output_file.write(line_data)
        output_file.write('\n')
        line_data = ""


def start_simulation(basepath, simulation_length):

    setup_simulation_folders(basepath)
    ids = get_ids_to_log_list(basepath)
    ids_to_log_str = get_ids_to_log_str(ids)
    simulation_story_dicts = get_simulation_story(basepath)
    simulation_story_str = generate_input_argument(simulation_story_dicts)

    execute = generate_finale_executable_call(simulation_length, ids_to_log_str, simulation_story_str)
    current_path = os.path.dirname(os.path.abspath(__file__))
    path_to_executable = 'cd ../build_pc/pc/'

    Thread(target=test(current_path,path_to_executable,execute)).start()
    time.sleep(0.5)

    id_files = generate_log_files(ids, basepath)
    log_data_real_time(id_files, basepath)

def simulate_and_test(folder_name, simulation_length):
    basepath = os.path.dirname(os.path.abspath(__file__))+"/"+folder_name

    start_simulation(basepath, simulation_length)
    return compare_test_with_reference(basepath)

def compare_test_with_reference(basepath):
    try:
        reference_file = csv.reader(open(basepath+ '/'+'reference_file.txt', 'r'), delimiter=",")
    except:
        status_message.warning("Could not find a reference test, marking test as sucess")
        return SUCCESS
    output_file = csv.reader(open(basepath+'/tmp/output_file.txt', 'r'), delimiter=';')
    
    for line1, line2 in zip(reference_file, output_file):
        if line1 != line2:
            return FAIL

    return SUCCESS