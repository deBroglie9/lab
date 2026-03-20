#ifndef PID_CONTROLLER_H
#define PID_CONTROLLER_H

class PIDController
{
public:

    PIDController()
    {
        kp = 0;
        ki = 0;
        kd = 0;

        error = 0;
        last_error = 0;
        integral = 0;
    }

    void setParam(float p, float i, float d)
    {
        kp = p;
        ki = i;
        kd = d;
    }

    float update(float target, float actual)
    {
        error = target - actual;

        // 角度环绕处理
        if(error > 180)
            error -= 360;
        else if(error < -180)
            error += 360;

        integral += error;

        float derivative = error - last_error;

        float output =
            kp * error +
            ki * integral +
            kd * derivative;

        last_error = error;

        return output;
    }

    void reset()
    {
        error = 0;
        last_error = 0;
        integral = 0;
    }

    float getError() const
    {
        return error;
    }

private:

    float kp;
    float ki;
    float kd;

    float error;
    float last_error;
    float integral;
};

#endif