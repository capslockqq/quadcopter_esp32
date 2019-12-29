#!/usr/bin/python
import sys
import os
import filecmp
import csv

sys.path.append(os.path.dirname(os.path.abspath(__file__))+'/../..')
from simulation_tests import run_single_simulation
from simulation_tests import staus_handling

status_message = staus_handling.StatusHandling()

        
if __name__ == "__main__":
    folder_name = str(os.path.dirname(os.path.realpath(__file__)))[os.path.dirname(os.path.realpath(__file__)).rfind('/')+1:]
    simulation_length = 10
    if run_single_simulation.simulate_and_test(folder_name, simulation_length) == run_single_simulation.SUCCESS:
        status_message.success("Output file and reference are identical!")
        sys.exit(0)
    else:
        status_message.error("Output file and reference are NOT identical!")
        sys.exit(1)
