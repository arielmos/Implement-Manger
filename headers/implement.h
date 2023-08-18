/*
 * implement.h
 *
 *  Created on: 16 Aug 2023
 *      Author: mozes
 */

#ifndef HEADERS_IMPLEMENT_H_
#define HEADERS_IMPLEMENT_H_

class Implement {
public:
    virtual void turnOn() = 0;
    virtual void turnOff() = 0;
    virtual bool isTurnedOn() const = 0;
    virtual int getFuelLevel() const = 0;
    virtual ~Implement();
};

class RS232Implement : public Implement {
public:
    void turnOn() override {
        // Implement RS232 turn on logic
    }

    void turnOff() override {
        // Implement RS232 turn off logic
    }

    bool isTurnedOn() const override {
        // Implement RS232 is turned on logic
    }

    int getFuelLevel() const override {
        // Implement RS232 get fuel level logic
    }
    ~RS232Implement();
};


#endif /* HEADERS_IMPLEMENT_H_ */
