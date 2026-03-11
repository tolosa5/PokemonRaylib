#ifndef BATTLEACTION_HPP
#define BATTLEACTION_HPP


class BattleAction
{
public:
    virtual void Start() {}
    virtual void Update() {}
    virtual bool Finished() = 0;
    ~BattleAction() {}
};

#endif