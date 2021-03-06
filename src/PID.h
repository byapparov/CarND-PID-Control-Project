#ifndef PID_H
#define PID_H

class PID {
 public:
  /**
   * Constructor
   */
  PID();

  /**
   * Destructor.
   */
  virtual ~PID();

  /**
   * Initialize PID.
   * @param (Kp_, Ki_, Kd_) The initial PID coefficients
   */
  void Init(double Kp_, double Ki_, double Kd_, int mode);

  /**
   * Update the PID error variables given cross track error.
   * @param cte The current cross track error
   */
  void UpdateError(double cte);

  /**
   * Calculate the total PID error.
   * @output The total PID error
   */
  double TotalError();

  /**
   * Calculate root mean squared error for optimisation
   */
  double RMSE();
  
  int Counter();
  
 private:
  /**
   * PID Errors
   */
  double p_error;
  double i_error;
  double d_error;

  /**
   * PID updates counter
   */
  int updates_counter;
  double squared_error, rmse_prevous;
    
  /**
   * PID Coefficients
   */ 
  double Kp;
  double Ki;
  double Kd;
  
  /** PID Coeffient increments for optimisation
   * 
   */
  double Kp_increment;
  double Kd_increment;
  double Ki_increment;
  int increment_control;
  
  /**
   * if set to 1, PID parameters will be tuned.
   */
  int mode;
};

#endif  // PID_H