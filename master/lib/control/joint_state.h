#ifndef JOINT_STATE_H
#define JOINT_STATE_H

#include <cmath>

class JointState
{
public:

    JointState()
    {
        target = 0;
        actual = 0;

        target_last = 0;
        actual_last = 0;

        first_update = true;
    }

    void updateTarget(float t)
    {
        target = t;
    }

    void updateActual(float a)
    {
        if(first_update)
        {
            actual_last = a;
            target_last = target;
            first_update = false;
        }

        // 编码器跳变保护
        if(std::abs(a - actual_last) > 20)
            actual = actual_last;
        else
            actual = a;

        actual_last = actual;
        target_last = target;
    }

    float getTarget() const
    {
        return target;
    }

    float getActual() const
    {
        return actual;
    }

private:

    float target;
    float actual;

    float target_last;
    float actual_last;

    bool first_update;
};

#endif