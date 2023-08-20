#ifndef HEADERS_IMPLEMENT_H_
#define HEADERS_IMPLEMENT_H_

#include <Arduino.h>

class Implement {
protected:
  int m_id;
  bool m_state;
  double m_fuelLevel;

public:
  Implement():m_id(0), m_state(false) ,m_fuelLevel(0){};
  virtual ~Implement(){};
  
  virtual int getId() const = 0;
  virtual int getState() const = 0;
  virtual double getFuelLevel() const = 0;
  
  virtual void setId(int id) = 0;
  virtual void setState(int state) = 0;
  virtual void setFuelLevel(double level) = 0;
};

#endif /* HEADERS_IMPLEMENT_H_ */
