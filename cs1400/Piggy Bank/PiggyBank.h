//
//  PiggyBank.h
//  Piggy Bank - Steven Proctor
//
//  Created by Steven Proctor on 3/22/15.
//  Copyright (c) 2015 Steven Proctor. All rights reserved.
//

#ifndef __Piggy_Bank___Steven_Proctor__PiggyBank__
#define __Piggy_Bank___Steven_Proctor__PiggyBank__

class PiggyBank {
private:
    bool broken;
    double savings;
public:
    PiggyBank();
    PiggyBank(double);
    ~PiggyBank();
    
    void depositMoney(double);
    double countSavings();
    void smash();
};

#endif /* defined(__Piggy_Bank___Steven_Proctor__PiggyBank__) */