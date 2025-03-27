#include <iostream>
#include "CharacterSystem.h"
#include "NumberMath.h"


bool player::IsAirbone()const {
    return bool(AIRBONE);
}

void player::dash() {
    if (state != STATE::DASH) {
        state = STATE::DASH;
        state_timer = dash_time;
    }
}

void player::jump() {
    if (state != STATE::JUMP) {
        state = STATE::JUMP;
        state_timer = dash_time;
    }
}

void player::slam() {
    if (state != STATE::JUMP && state != STATE::SLAM) {
        if (IsAirbone()) { state = STATE::SLAM; }
    }
}

void player::idle() {
    if (state_timer <= 0 && IsAirbone()) {
        state = STATE::IDLE;
    }
}
void player::SetPosition(int inpx, int inpy) {
    x = inpx;
    y = inpy;
}

void player::SetVelocity(int inpvx, int inpvy) {
    vx = inpvx;
    vy = inpvy;
}

void player::Update() {
    switch (player::state)
    {
    case STATE::IDLE: {
        if (abs(vx) > BASE_DECELERATION) {
            if (vx > 0)
            {
                vx -= BASE_DECELERATION;
            }
            if (vx < 0) {
                vx += BASE_DECELERATION;
            }
        }
        else vx = 0;
    }
    case STATE::JUMP: {
        double hold = sine((double(state_timer) / double(jump_time)) * MathPi/2);
        vy += JUMP_FORCE * (1 - hold * hold);
    }
    case STATE::DASH: {
        vx = DASH_SPEED
    }

    default:
        break;
    }
}


