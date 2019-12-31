
#include <stdio.h>
#include <iostream>
#include <string.h>

#include "../../component_framework/components/Input.hpp"
#include "../../component_framework/components/Output.hpp"
#include "../../component_framework/components/Component.hpp"
#include "../../component_framework/components/ParameterWrite.hpp"

#include "../../component_framework/components/Binds.hpp"
#include "../../freertos_distro/FreeRTOS_tasks/tasks.hpp"
#include "../../component_framework/components/Singleton.hpp"
#include "../../component_framework/components/OutputObserver.hpp"
#include "../../component_framework/interface.hpp"
#include "../../component_framework/implementation.hpp"
#include "../../component_framework/components/type_name.hpp"
#include "../application_code/application_code.hpp"
#include "quadcopter_model/quadcopter_simulation.hpp"
SingletonLogging *SingletonLogging::instance = 0;
OutputObserver *OutputObserver::instance = 0;
ParameterWrite *ParameterWrite::instance = 0;




int main(int argc, char * argv[])
{
   //Clearing ID file
   std::string command = "rm ";
   std::string path = "*.txt";
   int result = system(command.append(path).c_str());
   (void)result;
   SingletonLogging *S = SingletonLogging::GetInstance();
   
   

   
   vector<string> ids_to_log;
   bool simulation_story_start = false;
   int param_write_offset = 0;
   int simulation_param_index = 0;
   int i = 2;
   for (i; i < argc; i++) {
      std::string argument = argv[i];
      if (argument == "simulation_story") break;
      ids_to_log.push_back(argument);
   }
   S->SetData(ids_to_log);

   OutputObserver *L = OutputObserver::GetInstance();
   ParameterWrite  *paramwrite = ParameterWrite::GetInstance();
   I_application_code *app = new Application_code("Quadcopter", "QUAD");
   I_application_simulation *sim = new quadcopter_model("Simulation", "SIM");
   Tasks tasks(app, sim);


   auto unique_ids = Component::get_all_unique_ids_as_map();
   if (argv[1] != NULL) {
         std::string simulation_time(argv[1]);
         tasks.m_simulation_time_seconds = std::stof(simulation_time);
      }
      else {
         tasks.m_simulation_time_seconds = 1.0f;
      }
   for (int j = i+1; j < argc; j++) {
      if (param_write_offset % 3 == 0) {
         std::string param_id(argv[j]);
         std::string time(argv[j+1]);
         if (!unique_ids.count(param_id)) {
            std::cout << "____ERROR_____: Could not find parameter ID: " << param_id << std::endl;
            return 1;
         }
         if (std::stof(time) > tasks.m_simulation_time_seconds) { //PArameter write is higher than simulation length
            std::cout << "____ERROR_____: Simulation length is smaller than parameter write: " << param_id << " ,time: " << time <<  std::endl;
            return 1; 
         }
         std::string value(argv[j+2]);
         int* float_param_ptr = paramwrite->get_float_param_ptr_by_id(param_id);
         int* double_param_ptr = paramwrite->get_double_param_ptr_by_id(param_id);
         int* int_param_ptr = paramwrite->get_int_param_ptr_by_id(param_id);
         int* bool_param_ptr = paramwrite->get_bool_param_ptr_by_id(param_id);
         Parameter<float>  *float_param;
         Parameter<double> *double_param;
         Parameter<int>    *int_param;
         Parameter<bool>   *bool_param;
         if (float_param_ptr) {
            float_param = (Parameter<float> *)float_param_ptr;
            paramwrite->simulation_float_params[simulation_param_index] = make_tuple(float_param, std::stof(time), std::stof(value));
         }
         else if (double_param_ptr){
            double_param = (Parameter<double> *)double_param_ptr;
            paramwrite->simulation_double_params[simulation_param_index] = make_tuple(double_param, std::stof(time), std::stof(value));
         }
         else if (int_param_ptr) {
            int_param = (Parameter<int> *)int_param_ptr;
            paramwrite->simulation_int_params[simulation_param_index] = make_tuple(int_param, std::stof(time), std::stof(value));
         }
         else if (bool_param_ptr) {
            bool_param = (Parameter<bool> *)bool_param_ptr;
            paramwrite->simulation_bool_params[simulation_param_index] = make_tuple(bool_param, std::stof(time), std::stof(value));
         }
         paramwrite->simlation_param_write[simulation_param_index] = make_tuple(std::stof(time), std::stof(value));
         simulation_param_index++;

      }
      param_write_offset++;
   }

   
   
   
   tasks.SetUp_Tasks(tasks);
 
   for (auto t : paramwrite->simlation_param_write) {
      std::cout << t.first << ": {time: " << std::get<0>(t.second) << " value: " << std::get<1>(t.second) << "}" << std::endl;
   }
   return 0;
}

