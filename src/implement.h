#ifndef IMPLEMENT_H_
#define IMPLEMENT_H_

#include <Arduino.h>

class Implement
{
protected:
  int m_id;
  bool m_state;
  double m_fuelLevel;

public:
  Implement():m_id(0), m_state(false) ,m_fuelLevel(0){};
  virtual ~Implement(){};
  
  virtual int getId() const = 0;
  virtual bool getState() const = 0;
  virtual double getFuelLevel() const = 0;
  
  virtual void setId(int id) = 0;
  virtual void setState(bool state) = 0;
  virtual void setFuelLevel(double level) = 0;
};

#endif /* IMPLEMENT_H_ */
