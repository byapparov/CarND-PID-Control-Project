#include "PID.h"
#include <iostream>
#include <math.h>  

/**
 * TODO: Complete the PID class. You may add any additional desired functions.
 */

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp_, double Ki_, double Kd_, int mode) {
  /**
   * TODO: Initialize PID coefficients (and errors, if needed)
   */
   this->Kp = Kp_;
   this->Ki = Ki_;
   this->Kd = Kd_;
   updates_counter = 0;
   rmse_prevous = 100.0;
   
   this->Kp_increment = 0.5;
   this-> Kd_increment = 5.0;
   this->Ki_increment = 0.0005;
   this->increment_control = -1;
   this->mode = mode;
}

void PID::UpdateError(double cte) {
  /**
   * TODO: Update PID errors based on cte.
   */
  d_error = cte - p_error;
  i_error += cte;
  p_error = cte;

  squared_error += cte * cte; 
  
  updates_counter += 1;
  
  if (mode == 0) {
     // exit here as we are not optimising parameters
     return;
  }
  
  std::cout << "Update counter: " << updates_counter << std::endl;
  if (updates_counter > 3000) {
     double rmse = RMSE();
     squared_error = cte * cte;
     updates_counter = 1;
     
     if (increment_control == -1) {
        increment_control += 1;
        rmse_prevous = rmse;
        return;
     }
     
     if (rmse > rmse_prevous) {
        if (increment_control == 0) {
           increment_control += 1;
           this->Kp -= Kp_increment;
           Kp_increment /= 2;
        
        }
        else if (increment_control == 1) {
           increment_control += 1;
           this->Kd -= Kd_increment; 
           Kd_increment /= 2;
        }
        else if (increment_control == 2) {
           increment_control = 0;
           this->Ki -= Ki_increment;
           Ki_increment /= 2;
        }
     } 
     else {
        rmse_prevous = rmse;
     }
     
     
     if (increment_control == 0) {
        this->Kp += Kp_increment;
     }
     else if (increment_control == 1) {
        this->Kd += Kd_increment;
     }
     else if (increment_control == 2) {
        this->Ki += Ki_increment;
     }
  }
  
}

/**
 * Returns the total error
 */
double PID::TotalError() {

  double error =  -Kp * p_error - Kd * d_error - Ki * i_error;
  if (error > 1) {
     error = 1;
  } 
  else if (error < -1) {
     error = -1;
  }
  return error;
}

double PID::RMSE() {
   return sqrt(squared_error) / updates_counter;
}

int PID::Counter() {
   return updates_counter;
}
