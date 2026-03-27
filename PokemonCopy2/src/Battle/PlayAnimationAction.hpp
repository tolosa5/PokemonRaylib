#ifndef PLAYANIMATIONACTION_HPP
#define PLAYANIMATIONACTION_HPP

#include "BattleAction.hpp"
#include "BattleUnit.hpp"

class PlayAnimationAction : public BattleAction
{
private:

    bool finished = false;

public:
    
    PlayAnimationAction() {}

    void Start() override
    {
        
    }

    void Update() override
    {
        
    }

    bool Finished() override
    {
        return finished;
    }
};

#endif